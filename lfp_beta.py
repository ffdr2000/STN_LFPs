"""

Utilities for generating time-varying (sinusoidally modulated) firing rates
and correlated inhomogeneous Poisson spike trains for excitatory and
inhibitory synaptic inputs.

All time quantities are expressed in milliseconds (ms) unless a variable
name explicitly says otherwise (e.g. ``*_s`` for seconds).
"""

import gc
import pickle
import random
from functools import partial
from os.path import join
import multiprocessing as mp
import numpy as np
from scipy.spatial import KDTree
from tqdm import tqdm
import neuron
import LFPy


def sinusoidal_inputs_vectorized(
    N,
    freq,
    r_base_exc,
    r_base_inh,
    r_amp_exc,
    r_amp_inh,
    T_ms,
    phase_inh=np.pi,
    dt_ms=1.0,
    jitter_std=6.25,
):
    """
    Generate sinusoidally modulated firing rates for N excitatory and N
    inhibitory input channels.

    Each channel gets its own random temporal jitter (phase offset in ms),
    so that channels are not perfectly synchronized even though they share
    the same modulation frequency.

    Parameters
    ----------
    N : int
        Number of input channels (e.g. number of cells).
    freq : float
        Modulation frequency in Hz.
    r_base_exc, r_base_inh : float
        Baseline (mean) firing rate in Hz for excitatory / inhibitory
        channels.
    r_amp_exc, r_amp_inh : float
        Amplitude of the sinusoidal modulation in Hz for excitatory /
        inhibitory channels.
    T_ms : float
        Total duration of the simulation in ms.
    phase_inh : float, optional
        Phase offset (radians) applied to the inhibitory rate relative to
        the excitatory rate. Default is pi (i.e. anti-phase).
    dt_ms : float, optional
        Time step in ms used to discretize the rate signal. Default is 1.0.
    jitter_std : float, optional
        Standard deviation (ms) of the per-channel random time jitter
        applied independently to excitatory and inhibitory channels.
        Default is 6.25 ms.

    Returns
    -------
    time_bins_ms : ndarray, shape (n_time,)
        Time vector in ms (shared reference time axis, without jitter).
    rate_exc : ndarray, shape (N, n_time)
        Excitatory firing rate (Hz) for each channel and time bin.
    rate_inh : ndarray, shape (N, n_time)
        Inhibitory firing rate (Hz) for each channel and time bin.
    """
    n_time = int(T_ms / dt_ms)
    time_bins_ms = np.arange(n_time) * dt_ms

    # Independent random temporal jitter per channel (broadcast over time).
    jitter_exc = np.random.normal(0, jitter_std, size=(N, 1))
    jitter_inh = np.random.normal(0, jitter_std, size=(N, 1))

    time_exc = time_bins_ms + jitter_exc
    time_inh = time_bins_ms + jitter_inh

    # np.sin() expects an angular argument; freq is in Hz, so time must be
    # converted to seconds before computing 2*pi*freq*t.
    time_exc_s = time_exc / 1000.0
    time_inh_s = time_inh / 1000.0

    rate_exc = np.clip(
        r_base_exc + r_amp_exc * np.sin(2 * np.pi * freq * time_exc_s),
        0,
        None,
    )
    rate_inh = np.clip(
        r_base_inh
        + r_amp_inh * np.sin(2 * np.pi * freq * time_inh_s + phase_inh),
        0,
        None,
    )

    return time_bins_ms, rate_exc, rate_inh


def generate_inhomogeneous_spike_trains_array(N, r_array, c, T_ms):
    """
    Generate N inhomogeneous Poisson spike trains sharing correlation
    coefficient ``c``, using the thinning method.

    When ``c > 0``, all N trains are derived from a single shared "source"
    spike train via independent random thinning, which yields the desired
    pairwise correlation between output trains. When ``c == 0``, each train
    is generated independently.

    Parameters
    ----------
    N : int
        Number of spike trains to generate.
    r_array : ndarray, shape (n_steps,)
        Instantaneous firing rate (Hz) as a function of time, sampled at a
        fixed time step (see ``T_ms`` / ``len(r_array)`` for the step size).
    c : float
        Pairwise correlation coefficient between output spike trains.
        Must lie in [0, 1].
    T_ms : float
        Total duration spanned by ``r_array``, in ms.

    Returns
    -------
    spike_trains : list of ndarray
        List of length N, each element an array of spike times in ms.
    """
    if c < 0 or c > 1:
        raise ValueError("Correlation coefficient c must be in [0, 1].")

    spike_trains = []

    n_steps = len(r_array)
    dt_ms = T_ms / n_steps
    dt_s = dt_ms / 1000.0
    T_s = T_ms / 1000.0
    r_max = np.max(r_array)

    if c == 0:
        # Independent thinning: draw candidate spikes from a homogeneous
        # Poisson process at r_max, then keep each with probability
        # r(t) / r_max ("rejection"/thinning method).
        for _ in range(N):
            num_candidates = np.random.poisson(r_max * T_s)
            candidate_spikes_s = np.sort(np.random.uniform(0, T_s, num_candidates))
            indices = np.minimum(
                (candidate_spikes_s / dt_s).astype(int), n_steps - 1
            )
            keep_prob = r_array[indices] / r_max
            accepted = np.random.uniform(0, 1, len(candidate_spikes_s)) < keep_prob
            spikes_s = candidate_spikes_s[accepted]
            spike_trains.append(spikes_s * 1000.0)  # back to ms
    else:
        # Correlated thinning: generate one shared "source" spike train at
        # an inflated rate (r_max / c), thin it down to r_array to obtain
        # a common reference train, then independently sub-sample it with
        # probability c for each of the N output trains. This produces
        # pairwise correlation approximately equal to c between outputs.
        r_source_max = r_max / c
        num_source_candidates = np.random.poisson(r_source_max * T_s)
        source_candidates_s = np.sort(
            np.random.uniform(0, T_s, num_source_candidates)
        )
        indices = np.minimum(
            (source_candidates_s / dt_s).astype(int), n_steps - 1
        )
        keep_prob_source = r_array[indices] / r_max
        accepted_source = (
            np.random.uniform(0, 1, len(source_candidates_s)) < keep_prob_source
        )
        source_spike_train_s = source_candidates_s[accepted_source]

        for _ in range(N):
            mask = np.random.uniform(0, 1, len(source_spike_train_s)) < c
            spike_trains.append(source_spike_train_s[mask] * 1000.0)  # to ms

    return spike_trains


def neuron_input_generator(r_exc_list, r_inh_list, c_exc, c_inh, T_ms, N_exc, N_inh, neuron_index):
    """
    Convenience wrapper that generates correlated excitatory and inhibitory
    spike trains for a single neuron, given precomputed per-neuron rate
    profiles.

    Parameters
    ----------
    r_exc_list, r_inh_list : ndarray, shape (n_neurons, n_steps)
        Per-neuron excitatory / inhibitory rate profiles (Hz), as returned
        by ``sinusoidal_inputs_vectorized``.
    c_exc, c_inh : float
        Correlation coefficients for excitatory / inhibitory input
        populations (see ``generate_inhomogeneous_spike_trains_array``).
    T_ms : float
        Total simulated duration in ms.
    N_exc, N_inh : int
        Number of excitatory / inhibitory synapses (spike trains) to
        generate for this neuron.
    neuron_index : int
        Row index into ``r_exc_list`` / ``r_inh_list`` selecting this
        neuron's rate profile.

    Returns
    -------
    exc_spikes, inh_spikes : list of ndarray
        Excitatory and inhibitory spike trains (times in ms), one array
        per synapse.
    """
    exc_spikes = generate_inhomogeneous_spike_trains_array(
        N_exc, r_exc_list[neuron_index], c_exc, T_ms
    )
    inh_spikes = generate_inhomogeneous_spike_trains_array(
        N_inh, r_inh_list[neuron_index], c_inh, T_ms
    )
    return exc_spikes, inh_spikes


"""

Simulate a population of subthalamic nucleus (STN) neurons (multi-compartment
NEURON/LFPy models), each receiving independent excitatory and inhibitory
synaptic bombardment with a shared sinusoidal rate modulation ("beta-band"
drive), and compute the summed extracellular local field potential (LFP)
recorded on a linear electrode array.

Cells are distributed at random positions within a sphere and simulated in
parallel (one process per cell) using multiprocessing. Only the running sum
of the LFP contributions is kept in memory (not each cell's individual LFP),
to keep memory usage bounded for large populations.

Outputs (pickled to the working directory):
    lfp_sum_beta_def.pkl                 - summed LFP, shape (n_contacts, n_timepoints)
    vmem_spatial_beta_def.pkl            - somatic membrane potential per cell
    rotation_spatial_beta_def.pkl        - random (x, y, z) rotation applied to each cell
    complete_exc_idxs_beta_def.pkl       - excitatory synapse segment indices per cell
    complete_inh_idxs_beta_def.pkl       - inhibitory synapse segment indices per cell
    complete_exc_spiketrains_beta_def.pkl- excitatory spike trains per cell
    complete_inh_spiketrains_beta_def.pkl- inhibitory spike trains per cell
    complete_electrode_positions_beta_def.pkl - sampled cell positions in the sphere

Requires: NEURON, LFPy, numpy, scipy, tqdm, and a compiled STN cell model
(Miocinovic et al. 2006) located under ``neuron_models/MiocinovicEtAl2006``.
"""



# =====================================================================
# Geometry helpers: placing and de-overlapping cells within a sphere
# =====================================================================

def generate_random_positions_in_sphere(n_neurons, center, radius):
    """
    Generate uniformly distributed random positions inside a sphere.

    Sampling is performed in spherical coordinates. The radial coordinate is
    drawn according to the cube root of a uniform random variable to ensure
    a uniform density throughout the sphere volume (rather than an excessive
    concentration of points near the center).

    Parameters
    ----------
    n_neurons : int
        Number of positions to generate.

    center : array-like of length 3
        Cartesian coordinates of the sphere center (µm).

    radius : float
        Sphere radius (µm).

    Returns
    -------
    numpy.ndarray
        Array of shape (n_neurons, 3) containing the generated Cartesian
        coordinates.
    """
    positions = []

    while len(positions) < n_neurons:

        # Sample a radius that produces a uniform volumetric density.
        r = radius * np.cbrt(np.random.random())

        # Sample angular coordinates uniformly.
        theta = np.random.uniform(0, 2 * np.pi)  # Azimuth
        phi = np.random.uniform(0, np.pi)        # Polar angle

        # Convert spherical coordinates to Cartesian coordinates.
        x = center[0] + r * np.sin(phi) * np.cos(theta)
        y = center[1] + r * np.sin(phi) * np.sin(theta)
        z = center[2] + r * np.cos(phi)

        positions.append([x, y, z])

    return np.array(positions)


# =====================================================================
# Cell model construction
# =====================================================================

def remove_active_mechanisms(cell):
    """
    Strip all active (voltage-gated / calcium / ion-accumulation)
    mechanisms from every segment of ``cell``, leaving only passive
    membrane properties. Used to build a "passive" control version of the
    STN cell model.
    """
    remove_list = [
        'myions', 'Cacum', 'CaT', 'HVA', 'sKCa', 'KDR', 'Kv31',
        'Na', 'NaL', 'Ih', 'axnode75',
    ]
    mt = neuron.h.MechanismType(0)
    for sec in neuron.h.allsec():
        for seg in sec:
            for mech in remove_list:
                mt.select(mech)
                mt.remove(sec=sec)
    return cell


def return_stn_cell_model(dt, tstart, tstop, axon_type, conductance_type):
    """
    Build an LFPy.Cell instance of the STN neuron model.

    Parameters
    ----------
    dt : float
        Simulation time step (ms).
    tstart, tstop : float
        Simulation start / stop time (ms).
    axon_type : {'reduced_axon', 'full_axon'}
        If 'reduced_axon', apply the ``remove_axon_file`` hoc customization
        to truncate/simplify the axon.
    conductance_type : {'active', 'passive'}
        If 'passive', strip active conductances via
        ``remove_active_mechanisms`` and set resting potentials to -60 mV.

    Returns
    -------
    cell : LFPy.Cell
    """
    cell_parameters = {
        'morphology': join(MODEL_FOLDER, CELL_FILE),
        'passive': False,
        'nsegs_method': None,
        'dt': dt,
        'tstart': tstart,
        'tstop': tstop,
        'v_init': np.random.uniform(-70, -50),
        'pt3d': True,
        'extracellular': True,
    }
    if axon_type == 'reduced_axon':
        cell_parameters['custom_code'] = [REMOVE_AXON_FILE]

    cell = LFPy.Cell(**cell_parameters)

    if conductance_type == 'passive':
        remove_active_mechanisms(cell)
        for sec in cell.allseclist:
            if hasattr(sec, "e_pas"):
                sec.e_pas = -60
            if hasattr(sec, "epas_STh"):
                sec.epas_STh = -60

    return cell


def return_exc_inh_target_idxs(cell, perisomatic_dist_limit=100):
    """
    Split a cell's dendritic/somatic segments into "perisomatic" (targeted
    by inhibition) and "distal" (targeted by excitation) pools, based on
    path distance from the soma.

    Parameters
    ----------
    cell : LFPy.Cell
    perisomatic_dist_limit : float, optional
        Path distance (um) from the soma below which a segment is
        considered perisomatic (inhibitory target). Default 100 um.

    Returns
    -------
    exc_target_idxs, inh_target_idxs : list of int
        Segment indices eligible for excitatory / inhibitory synapses.
    """
    inh_target_idxs, exc_target_idxs = [], []
    for c_idx in range(cell.totnsegs):
        soma_dist = cell.get_intersegment_distance(0, c_idx)
        sec_name = cell.get_idx_name(c_idx)[1]
        if not (("dend" in sec_name) or ("soma" in sec_name)):
            continue
        if soma_dist < perisomatic_dist_limit:
            inh_target_idxs.append(c_idx)
        else:
            exc_target_idxs.append(c_idx)
    return exc_target_idxs, inh_target_idxs


# =====================================================================
# Per-cell simulation (run in a worker process)
# =====================================================================

def process_cell(cell_tuple, dt, tstop, axon_type, conductance_type, center, radius_um):
    """
    Build, synaptically drive, and simulate a single STN cell, then compute
    its contribution to the extracellular LFP on the linear electrode
    array.

    Intended to be called via ``multiprocessing.Pool.imap`` with
    ``cell_tuple = (cell_index, cell_position)``. Each worker seeds its own
    RNGs from ``cell_index`` for reproducibility.

    Returns
    -------
    LFP : ndarray, shape (n_contacts, n_timepoints)
        This cell's contribution to the linear-array LFP (uV).
    rotation_array : list of float
        The random (x, y, z) rotation (radians) applied to the morphology.
    exc_idxs, inh_idxs : ndarray
        Segment indices receiving excitatory / inhibitory synapses.
    exc_spiketrains, inh_spiketrains : list of ndarray
        Spike times (ms) for each excitatory / inhibitory synapse.
    vmem : ndarray
        Somatic membrane potential trace over time.
    """
    cell_index, cell_pos = cell_tuple
    np.random.seed(cell_index)
    random.seed(cell_index)

    cell = return_stn_cell_model(dt, -100, tstop, axon_type, conductance_type)
    exc_target_idx_list, inh_target_idx_list = return_exc_inh_target_idxs(cell)

    # Weight synapse placement probability by segment membrane area.
    area_exc = cell.area[exc_target_idx_list]
    area_inh = cell.area[inh_target_idx_list]
    area_exc = area_exc / area_exc.sum()
    area_inh = area_inh / area_inh.sum()

    # Synapse counts: excitatory count scaled relative to a reference
    # inhibitory count of 883 (see original model calibration).
    num_exc_syns = int(883 / 8 * 20)
    num_inh_syns = 883

    # Randomly orient and place the cell within the population volume.
    rotation = {
        'x': random.uniform(0, 2 * np.pi),
        'y': random.uniform(0, 2 * np.pi),
        'z': random.uniform(0, 2 * np.pi),
    }
    rotation_array = [rotation['x'], rotation['y'], rotation['z']]
    cell.set_rotation(**rotation)
    cell.set_pos(cell_pos[0], cell_pos[1], cell_pos[2])

    exc_idxs = np.random.choice(exc_target_idx_list, num_exc_syns, replace=True, p=area_exc)
    inh_idxs = np.random.choice(inh_target_idx_list, num_inh_syns, replace=True, p=area_inh)

    exc_spiketrains, inh_spiketrains = neuron_input_generator(
        RATE_EXC, RATE_INH, c_exc=0.05, c_inh=0.05,
        T_ms=tstop, N_exc=num_exc_syns, N_inh=num_inh_syns,
        neuron_index=cell_index,
    )

    for i, idx in enumerate(exc_idxs):
        syn = LFPy.Synapse(cell, idx=idx, syntype="Exp2Syn",
                            e=0, weight=0.015, tau1=0.1, tau2=3)
        syn.set_spike_times(exc_spiketrains[i])
    for i, idx in enumerate(inh_idxs):
        syn = LFPy.Synapse(cell, idx=idx, syntype="Exp2Syn",
                            e=-80, weight=0.00028, tau1=1.1, tau2=7.8)
        syn.set_spike_times(inh_spiketrains[i])

    cell.simulate(rec_vmem=True, rec_imem=True)

    # Compute this cell's contribution to the linear-array LFP.
    electrode = LFPy.RecExtElectrode(
        cell,
        sigma=0.3,
        x=LINEAR_ELECTRODE_POSITIONS[:, 0],
        y=LINEAR_ELECTRODE_POSITIONS[:, 1],
        z=LINEAR_ELECTRODE_POSITIONS[:, 2],
        method="linesource",
        r=25,
        n=15,
    )
    M = electrode.get_transformation_matrix()
    LFP = M @ cell.imem * 1000  # convert to uV
    vmem = cell.vmem[0]  # somatic membrane potential trace

    del cell, electrode
    gc.collect()

    return LFP, rotation_array, exc_idxs, inh_idxs, exc_spiketrains, inh_spiketrains, vmem


# =====================================================================
# Parallel driver: simulate all cells and accumulate the summed LFP
# =====================================================================

def parallel_lfp_sum(cell_positions, dt, tstop, axon_type, conductance_type,
                      center, radius_um, n_workers=5):
    """
    Simulate every cell in ``cell_positions`` in parallel and accumulate
    their LFP contributions into a running sum (rather than storing each
    cell's full LFP trace), to keep peak memory usage bounded.

    Parameters
    ----------
    cell_positions : ndarray, shape (n_cells, 3)
        Position at which to place each cell.
    dt, tstop, axon_type, conductance_type, center, radius_um :
        Forwarded to ``process_cell`` / ``return_stn_cell_model``.
    n_workers : int, optional
        Number of worker processes. Default 5.

    Returns
    -------
    sum_lfp : ndarray, shape (n_contacts, n_timepoints)
        Summed LFP across all cells (uV).
    rotation_array_list, exc_idxs_list, inh_idxs_list,
    exc_spiketrains_list, inh_spiketrains_list, vmem_list : list
        Per-cell outputs, in the same order as ``cell_positions``
        (order is preserved by ``Pool.imap``).
    """
    n_contacts = LINEAR_ELECTRODE_POSITIONS.shape[0]
    n_timepoints = int(tstop / dt) + 1
    sum_lfp = np.zeros((n_contacts, n_timepoints))

    rotation_array_list = []
    exc_idxs_list = []
    inh_idxs_list = []
    exc_spiketrains_list = []
    inh_spiketrains_list = []
    vmem_list = []

    # 'fork' start method is required so worker processes inherit the
    # already-loaded NEURON mechanisms and module-level globals.
    ctx = mp.get_context("fork")
    pool = ctx.Pool(n_workers)
    worker_fn = partial(
        process_cell, dt=dt, tstop=tstop,
        axon_type=axon_type, conductance_type=conductance_type,
        center=center, radius_um=radius_um,
    )

    for LFP, rotation, exc_idxs, inh_idxs, exc_spikes, inh_spikes, vmem in tqdm(
        pool.imap(worker_fn, enumerate(cell_positions)),
        total=len(cell_positions),
        desc="Accumulating LFP",
    ):
        sum_lfp += LFP
        rotation_array_list.append(rotation)
        exc_idxs_list.append(exc_idxs)
        inh_idxs_list.append(inh_idxs)
        exc_spiketrains_list.append(exc_spikes)
        inh_spiketrains_list.append(inh_spikes)
        vmem_list.append(vmem)

    pool.close()
    pool.join()

    return (sum_lfp, rotation_array_list, exc_idxs_list, inh_idxs_list,
            exc_spiketrains_list, inh_spiketrains_list, vmem_list)



# --- STN cell model files -------------------------------------------
MODEL_FOLDER = join("neuron_models", "MiocinovicEtAl2006")
CELL_FILE = "n17_full9_fem_type1RD_Gillies_mod.hoc"
REMOVE_AXON_FILE = join(MODEL_FOLDER, '..', 'remove_axon_complete.hoc')

# --- Simulation settings ---------------------------------------------
TSTOP = 2000            # ms
DT = 2 ** -5             # ms
AXON_TYPE = 'reduced_axon'
CONDUCTANCE_TYPE = 'active'

# --- Population geometry: cells distributed within a sphere ----------
RADIUS_UM = 600
DENSITY_PER_MM3 = 6000
CENTER = np.array([0, 0, 0])

# --- Linear recording electrode array (along z, through the sphere) --
ELECTRODE_Z = np.arange(-800, 800, 50)
LINEAR_ELECTRODE_POSITIONS = np.array([[0, 0, z] for z in ELECTRODE_Z])

# --- Sinusoidal ("beta-band") input drive -----------------------------
INPUT_FREQ_HZ = 23


def build_population_and_inputs():
    """
    Compute cell count/positions from population density and generate the
    shared sinusoidal rate profiles used to drive every cell's synapses.

    Returns
    -------
    cell_positions : ndarray, shape (n_cells, 3)
    """
    radius_mm = RADIUS_UM / 1000
    volume_mm3 = (4 / 3) * np.pi * (radius_mm ** 3)
    n_cells = int(DENSITY_PER_MM3 * volume_mm3)

    cell_positions = generate_random_positions_in_sphere(n_cells, CENTER, RADIUS_UM)

    global RATE_EXC, RATE_INH
    _, RATE_EXC, RATE_INH = sinusoidal_inputs_vectorized(
        n_cells, INPUT_FREQ_HZ,
        r_base_exc=3.5, r_base_inh=33,
        r_amp_exc=2.5, r_amp_inh=20,
        T_ms=TSTOP, phase_inh=np.pi, dt_ms=DT,
    )

    return cell_positions


np.random.seed(12345)
neuron.load_mechanisms(MODEL_FOLDER)

cell_positions = build_population_and_inputs()

(sum_lfp, rotation_array, exc_idxs_list, inh_idxs_list,
exc_spiketrains_list, inh_spiketrains_list, vmem_list) = parallel_lfp_sum(
    cell_positions, DT, TSTOP, AXON_TYPE, CONDUCTANCE_TYPE, CENTER, RADIUS_UM,
)

outputs = {
    'lfp_sum_beta_def.pkl': sum_lfp,
    'vmem_spatial_beta_def.pkl': vmem_list,
    'rotation_spatial_beta_def.pkl': rotation_array,
    'complete_exc_idxs_beta_def.pkl': exc_idxs_list,
    'complete_inh_idxs_beta_def.pkl': inh_idxs_list,
    'complete_exc_spiketrains_beta_def.pkl': exc_spiketrains_list,
    'complete_inh_spiketrains_beta_def.pkl': inh_spiketrains_list,
    'complete_electrode_positions_beta_def.pkl': cell_positions,
}
for filename, obj in outputs.items():
    with open(filename, 'wb') as f:
        pickle.dump(obj, f)

print("Simulation complete. Saved summed LFP and all other variables.")

