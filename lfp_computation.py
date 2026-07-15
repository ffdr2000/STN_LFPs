"""
Simulation utilities for generating synaptic input patterns for
subthalamic nucleus (STN) neuron models using LFPy/NEURON.

This script provides helper functions to:

    * Generate independent or correlated Poisson spike trains.
    * Generate temporally jittered spike trains.
    * Create excitatory and inhibitory synaptic input patterns.
    * Build and simulate STN neuron models.
    * Compute extracellular local field potentials (LFPs).

The code is intended for large-scale simulations of extracellular
recordings from morphologically detailed STN neurons.

Author: <Your Name>
"""

import numpy as np
import matplotlib.pyplot as plt
import random

import os
from os.path import join
import sys
import numpy as np
import matplotlib

import neuron
import LFPy
import matplotlib.pyplot as plt
from scipy.spatial import KDTree
from mpi4py import MPI  # MPI support (currently multiprocessing is used)
from tqdm import tqdm
import random


def generate_spike_trains(N, r, c, T):
    """
    Generate a population of homogeneous Poisson spike trains with
    configurable pairwise correlation.

    Correlation is generated using the classical "shared mother process"
    (or source process) approach:

        - A common Poisson process is generated.
        - Each daughter spike train independently inherits every source
          spike with probability ``c``.

    Consequently:
        * c = 0 produces completely independent Poisson processes.
        * c = 1 produces identical spike trains.

    Parameters
    ----------
    N : int
        Number of spike trains.

    r : float
        Mean firing rate of each output spike train (spikes per unit time).

    c : float
        Correlation coefficient between spike trains.
        Must satisfy 0 <= c <= 1.

    T : float
        Simulation duration.

    Returns
    -------
    list of numpy.ndarray
        One array of spike times for each generated spike train.
    """

    spike_trains = []

    # Ensure the requested correlation coefficient is valid.
    if c < 0 or c > 1:
        raise ValueError("Correlation coefficient c must be in the range (0, 1].")

    if c == 0:
        # ---------------------------------------------------------
        # Independent homogeneous Poisson processes
        # ---------------------------------------------------------
        for _ in range(N):
            num_spikes = np.random.poisson(r * T)
            spike_train = np.sort(np.random.uniform(0, T, num_spikes))
            spike_trains.append(spike_train)

    else:
        # ---------------------------------------------------------
        # Shared-source (mother process) construction.
        #
        # The source process has an increased firing rate such that,
        # after probabilistic thinning, each daughter process has
        # the desired average firing rate r.
        # ---------------------------------------------------------
        r_source = r / c

        # Generate the common source process.
        num_spikes_source = np.random.poisson(r_source * T)
        source_spike_train = np.sort(
            np.random.uniform(0, T, num_spikes_source)
        )

        # Generate daughter spike trains by independently retaining
        # each source spike with probability c.
        for _ in range(N):
            mask = np.random.uniform(
                0, 1, len(source_spike_train)
            ) < c

            target_spike_train = source_spike_train[mask]
            spike_trains.append(target_spike_train)

    return spike_trains


def truncated_exponential(mean, low, high, size=1):
    """
    Draw samples from an exponential distribution truncated to a
    specified interval.

    Rejection sampling is used by repeatedly drawing samples until
    enough values fall inside the requested bounds.

    Parameters
    ----------
    mean : float
        Mean of the exponential distribution.

    low : float
        Lower accepted value.

    high : float
        Upper accepted value.

    size : int, optional
        Number of samples to return.

    Returns
    -------
    numpy.ndarray
        Array containing the requested number of truncated samples.
    """

    lam = 1.0 / mean

    # Draw more samples than required to reduce recursion probability.
    x = np.random.exponential(1.0 / lam, size * 5)

    # Reject samples outside the specified interval.
    x = x[(x >= low) & (x <= high)]

    # If insufficient valid samples remain, repeat recursively.
    if len(x) < size:
        return truncated_exponential(mean, low, high, size)

    return x[:size]


def return_exc_inh_spiketimes(stim_type,
                              num_exc_syns_per_cell,
                              num_inh_syns_per_cell,
                              rate_exc=10,
                              rate_inh=10,
                              duration=1000,corr_inh=0,corr_exc=0):
    """
    Generate spike times for excitatory and inhibitory neurons based on stimulation type.

    Parameters:
    stim_type: str - Type of stimulation (e.g., "exc_wave", "inh_wave", etc.)
    num_exc_syns_per_cell: int - Number of excitatory synapses per cell.
    num_inh_syns_per_cell: int - Number of inhibitory synapses per cell.
    rate_exc: float - Poisson firing rate for excitatory neurons (Hz).
    rate_inh: float - Poisson firing rate for inhibitory neurons (Hz).
    duration: float - Simulation duration (ms).

    Returns:
    tuple - Excitatory and inhibitory spike times as lists of arrays.
    """
    if stim_type == "exc_wave":
        inh_spiketimes = [np.array([])] * num_inh_syns_per_cell
        exc_spiketimes = [np.random.normal(100, 10, 1)
                          for _ in range(num_exc_syns_per_cell)]
    elif stim_type == "inh_wave":
        inh_spiketimes = [np.random.normal(100, 10, 1)
                          for _ in range(num_inh_syns_per_cell)]
        exc_spiketimes = [np.array([])] * num_exc_syns_per_cell
    elif stim_type == "no_input":
        exc_spiketimes = [np.array([])] * num_exc_syns_per_cell
        inh_spiketimes = [np.array([])] * num_inh_syns_per_cell
    elif stim_type == "balanced_wave":
        inh_spiketimes = [np.random.normal(100, 10, 1)
                          for _ in range(num_inh_syns_per_cell)]
        exc_spiketimes = [np.random.normal(100, 10, 1)
                          for _ in range(num_exc_syns_per_cell)]
    elif stim_type == "poisson_spiking":
        exc_spiketimes = [np.cumsum(np.random.exponential(1000 / rate_exc, int(rate_exc * duration / 1000)))
                          for _ in range(num_exc_syns_per_cell)]
        inh_spiketimes = [np.cumsum(np.random.exponential(1000 / rate_inh, int(rate_inh * duration / 1000)))
                          for _ in range(num_inh_syns_per_cell)]
   

        # Shuffle the final list
        random.shuffle(inh_spiketimes)
   

    elif stim_type=="corr":
        
        exc_spiketimes=generate_spike_trains(num_exc_syns_per_cell,rate_exc/1000,corr_exc,duration)


        synapse_per_presynaptic_cell=1        
        num_inh_syns_grouped = int(num_inh_syns_per_cell / synapse_per_presynaptic_cell)

        # Generate unique spike processes for the grouped synapses
        unique_spiketimes=generate_spike_trains(num_inh_syns_grouped,rate_inh/1000,corr_inh,duration)

        # Expand the list by sampling spike processes to match the total number of synapses
        inh_spiketimes = random.choices(unique_spiketimes, k=num_inh_syns_per_cell)
 
        # Shuffle the final list
        random.shuffle(inh_spiketimes)
        
    elif stim_type == "spatial_corr":
        # --- Excitatory pool ---
        npool_exc = max(num_exc_syns_per_cell, int(num_exc_syns_per_cell / max(corr_exc, 1e-6)))
        exc_pool = generate_spike_trains(npool_exc,rate_exc/1000,corr_exc,duration)
        exc_spiketimes = random.sample(exc_pool, num_exc_syns_per_cell)  # without replacement

        # --- Inhibitory pool ---
        npool_inh = max(num_inh_syns_per_cell, int(num_inh_syns_per_cell / max(corr_inh, 1e-6)))
        inh_pool = generate_spike_trains(npool_inh,rate_inh/1000,corr_inh,duration)
        inh_spiketimes = random.sample(inh_pool, num_inh_syns_per_cell)
    
     
    

    return exc_spiketimes, inh_spiketimes

# =============================================================================
# Geometry and cell model utilities
# =============================================================================

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


def remove_active_mechanisms(cell):
    """
    Remove all voltage-dependent membrane mechanisms from a NEURON cell.

    This utility converts the original active conductance model into a
    passive membrane model by removing the major ionic channel mechanisms.
    Passive leak reversal potentials are assigned separately after this
    function is called.

    Parameters
    ----------
    cell : LFPy.Cell
        Instantiated neuron model.

    Returns
    -------
    LFPy.Cell
        The same cell instance after removal of the active mechanisms.
    """

    # List of membrane mechanisms to remove.
    remove_list = [
        'myions', 'Cacum', 'CaT', 'HVA', 'sKCa',
        'KDR', 'Kv31', 'Na', 'NaL', 'Ih', 'axnode75'
    ]

    mt = neuron.h.MechanismType(0)

    # Iterate through every section and remove each active mechanism.
    for sec in neuron.h.allsec():
        for seg in sec:
            for mech in remove_list:
                mt.select(mech)
                mt.remove(sec=sec)

    return cell


def return_stn_cell_model(dt, tstart, tstop, axon_type, conductance_type):
    """
    Construct an STN neuron model using LFPy.

    The morphology is based on the Miocinovic et al. reconstruction. The
    function optionally removes the original axon and can return either the
    fully active conductance model or a passive version.

    Parameters
    ----------
    dt : float
        Simulation time step (ms).

    tstart : float
        Simulation start time (ms).

    tstop : float
        Simulation end time (ms).

    axon_type : {'reduced_axon', 'original_axon'}
        Determines whether the reconstructed axon is replaced with the
        reduced axon morphology.

    conductance_type : {'active', 'passive'}
        Specifies whether voltage-gated conductances are retained.

    Returns
    -------
    LFPy.Cell
        Initialized neuron model.
    """

    # Parameters passed directly to the LFPy Cell constructor.
    cell_parameters = {
        'morphology': join(model_folder, cell_file),
        'passive': False,
        'nsegs_method': None,
        'dt': dt,
        'tstart': tstart,
        'tstop': tstop,

        # Randomize the initial membrane potential to reduce synchronization
        # artifacts across independently simulated neurons.
        'v_init': np.random.uniform(-70, -50),

        'pt3d': True,
        'extracellular': True,
    }

    # Optionally replace the reconstructed axon with a simplified version.
    if axon_type == 'reduced_axon':
        cell_parameters['custom_code'] = [remove_axon_file]
    elif axon_type == 'original_axon':
        pass
    else:
        raise RuntimeError("Axon type not recognized!")

    # Instantiate the neuron model.
    cell = LFPy.Cell(**cell_parameters)

    # Select between the active and passive membrane model.
    if conductance_type == 'active':
        pass

    elif conductance_type == 'passive':

        # Remove voltage-dependent ion channels.
        remove_active_mechanisms(cell)

        # Assign a uniform leak reversal potential wherever applicable.
        for sec in cell.allseclist:
            if hasattr(sec, "e_pas"):
                sec.e_pas = -60
            if hasattr(sec, "epas_STh"):
                sec.epas_STh = -60

    else:
        raise RuntimeError("conductance_type not recognized")

    return cell


def return_exc_inh_target_idxs(cell, perisomatic_dist_limit=100):
    """
    Partition neuronal compartments into excitatory and inhibitory target
    regions based on their distance from the soma.

    In this model, inhibitory synapses are restricted to the soma and
    proximal dendrites, whereas excitatory synapses are placed on distal
    dendritic compartments.

    Parameters
    ----------
    cell : LFPy.Cell
        Instantiated neuron model.

    perisomatic_dist_limit : float, optional
        Maximum soma distance (µm) defining the inhibitory region.

    Returns
    -------
    tuple
        (exc_target_idxs, inh_target_idxs), where each element is a list of
        compartment indices.
    """

    inh_target_idxs = []
    exc_target_idxs = []

    for c_idx in range(cell.totnsegs):

        # Distance between the current compartment and the soma.
        soma_dist = cell.get_intersegment_distance(0, c_idx)

        # Name of the anatomical section containing this segment.
        sec_name = cell.get_idx_name(c_idx)[1]

        # Synapses are only assigned to the soma and dendrites.
        if not (("dend" in sec_name) or ("soma" in sec_name)):
            continue

        # Proximal compartments receive inhibitory inputs.
        if soma_dist < perisomatic_dist_limit:
            inh_target_idxs.append(c_idx)

        # Distal dendrites receive excitatory inputs.
        else:
            exc_target_idxs.append(c_idx)

    return exc_target_idxs, inh_target_idxs


# =============================================================================
# Global simulation configuration
# =============================================================================

# Set a global random seed to ensure reproducibility of the simulation.
np.random.seed(12345)

# Directory containing the NEURON morphology and mechanism files.
model_folder = join("neuron_models", "MiocinovicEtAl2006")

###############################################################################
# Load the STN morphology and associated membrane mechanisms.
###############################################################################

cell_file = "n17_full9_fem_type1RD_Gillies_mod.hoc"

# HOC script used to replace the original reconstructed axon with the reduced
# axon morphology employed throughout these simulations.
remove_axon_file = join(model_folder, '..', 'remove_axon_complete.hoc')

# Compile/load all membrane mechanisms required by the model.
neuron.load_mechanisms(model_folder)

print(model_folder)

# Identifier of the neuron model used throughout the simulation.
model_name = "MiocinovicEtAl2006"
# Get the directory above the current file directory
import os

root_folder = os.path.dirname(os.getcwd())

# =============================================================================
# Simulation parameters
# =============================================================================

# Determine the project root directory. This can be useful when building
# paths relative to the repository location.
import os

root_folder = os.path.dirname(os.getcwd())


# =============================================================================
# Synaptic organization
# =============================================================================
#
# Synaptic inputs are spatially segregated according to their distance from
# the soma:
#
#   - Inhibitory synapses are restricted to the soma and proximal dendrites.
#   - Excitatory synapses are placed on distal dendrites.
#
# The threshold defining the perisomatic region is expressed in micrometers.
#
perisomatic_dist_limit = 100


# =============================================================================
# Simulation configuration
# =============================================================================

# Total simulation duration (ms).
tstop = 2000

# Numerical integration time step (ms).
dt = 2**-5

# Morphology to simulate.
axon_type = 'reduced_axon'
# axon_type = 'original_axon'

# Membrane model.
conductance_type = 'active'


import pickle


# =============================================================================
# Virtual electrode placement
# =============================================================================
#
# A population of recording electrodes is distributed uniformly inside a
# spherical volume centered on the origin. Each simulated neuron is placed at
# one of these locations, allowing the generation of a spatially distributed
# database of extracellular recordings.
#

# Radius of the spherical recording volume (µm).
radius_um = 600

# Desired spatial density of recording locations (electrodes/mm³).
density_per_mm3 = 6000

# Convert the sphere radius from micrometers to millimeters.
radius_mm = radius_um / 1000

# Compute the volume of the sphere.
volume_mm3 = (4 / 3) * np.pi * (radius_mm ** 3)

# Determine the number of recording locations required to achieve the desired
# spatial density.
num_electrodes = 20 #int(density_per_mm3 * volume_mm3)

print(f"Number of electrodes to place: {num_electrodes}")

# Sphere center.
center = np.array([0, 0, 0])

# Generate uniformly distributed recording locations.
electrode_positions = generate_random_positions_in_sphere(
    num_electrodes,
    center,
    radius_um,
)

'''
Previously generated electrode positions can be reloaded instead of being
generated randomly.

with open('/home/federico/Downloads/complete_lfp_simulations/def_lfp/complete_electrode_positions_005_new.pkl','rb') as f:
    electrode_positions = pickle.load(f)
'''

electrode_positions = electrode_positions[:num_electrodes]

import pickle

import multiprocessing as mp
from functools import partial
from tqdm import tqdm


# =============================================================================
# Single-cell simulation
# =============================================================================

def process_cell(cell_tuple, dt, tstop, axon_type,
                 conductance_type, center, radius_um):
    """
    Simulate one STN neuron and compute its extracellular potential.

    Each worker process executes this function independently. The neuron is

        1. instantiated,
        2. randomly rotated,
        3. positioned at the assigned recording location,
        4. assigned excitatory and inhibitory synapses,
        5. simulated with LFPy,
        6. used to compute the extracellular potential.

    Parameters
    ----------
    cell_tuple : tuple
        Tuple containing the neuron index and its spatial position.

    Returns
    -------
    tuple
        LFP trace, cell orientation, synapse locations, spike trains,
        and somatic membrane potential.
    """

    cell_index, cell_pos = cell_tuple

    # Use deterministic random seeds so each neuron is reproducible while
    # remaining statistically independent from every other neuron.
    np.random.seed(cell_index)
    random.seed(cell_index)

    # Instantiate the neuron model.
    cell = return_stn_cell_model(
        dt,
        -100,
        tstop,
        axon_type,
        conductance_type,
    )

    # Determine compartments eligible for excitatory and inhibitory synapses.
    exc_target_idx_list, inh_target_idx_list = \
        return_exc_inh_target_idxs(cell)

    # -------------------------------------------------------------------------
    # Synaptic placement
    # -------------------------------------------------------------------------
    # Synapses are sampled with probability proportional to compartment
    # membrane area so that larger compartments receive proportionally more
    # synaptic contacts.
    area_weights_exc = cell.area[exc_target_idx_list]
    area_weights_inh = cell.area[inh_target_idx_list]

    area_weights_exc /= area_weights_exc.sum()
    area_weights_inh /= area_weights_inh.sum()

    # Number of excitatory and inhibitory synapses.
    num_exc_syns_per_cell = int(883 / 8 * 20)
    num_inh_syns_per_cell = 883

    # -------------------------------------------------------------------------
    # Random orientation
    # -------------------------------------------------------------------------
    # Each neuron is independently rotated to remove orientation bias in the
    # generated extracellular dataset.
    anglex = random.uniform(0, 2 * np.pi)
    angley = random.uniform(0, 2 * np.pi)
    anglez = random.uniform(0, 2 * np.pi)

    rotation = {
        'x': anglex,
        'y': angley,
        'z': anglez
    }

    rotation_array = [anglex, angley, anglez]

    cell.set_rotation(**rotation)

    # Position the neuron at its assigned location.
    cell.set_pos(cell_pos[0], cell_pos[1], cell_pos[2])

    # Randomly assign synaptic locations according to the area-weighted
    # probability distributions.
    exc_idxs = np.random.choice(
        exc_target_idx_list,
        num_exc_syns_per_cell,
        replace=True,
        p=area_weights_exc
    )

    inh_idxs = np.random.choice(
        inh_target_idx_list,
        num_inh_syns_per_cell,
        replace=True,
        p=area_weights_inh
    )

    # -------------------------------------------------------------------------
    # Generate presynaptic activity
    # -------------------------------------------------------------------------
    stim_type = "corr"

    np.random.seed(cell_index)
    random.seed(cell_index)

    exc_spiketrains, inh_spiketrains = return_exc_inh_spiketimes(
        stim_type,
        num_exc_syns_per_cell,
        num_inh_syns_per_cell,
        rate_exc=3.5,
        rate_inh=33,
        duration=tstop + 1000,
        corr_inh=0.05,
        corr_exc=0.05,
    )

    # Create excitatory synapses.
    for i_, syn_idx in enumerate(exc_idxs):

        syn = LFPy.Synapse(
            cell,
            idx=syn_idx,
            syntype="Exp2Syn",
            e=0,
            weight=0.015,
            tau1=0.1,
            tau2=3,
            record_current=False,
        )

        syn.set_spike_times(exc_spiketrains[i_])

    # Create inhibitory synapses.
    for i_, syn_idx in enumerate(inh_idxs):

        syn = LFPy.Synapse(
            cell,
            idx=syn_idx,
            syntype="Exp2Syn",
            e=-80,
            weight=0.00028,
            tau1=1.1,
            tau2=7.8,
            record_current=False,
        )

        syn.set_spike_times(inh_spiketrains[i_])

    # Run the membrane simulation while recording transmembrane currents and
    # membrane voltages.
    cell.simulate(rec_vmem=True, rec_imem=True)

    # -------------------------------------------------------------------------
    # Extracellular potential calculation
    # -------------------------------------------------------------------------
    # Compute the extracellular potential at the origin using the line-source
    # approximation implemented in LFPy.
    elec_params = dict(
        sigma=0.3,
        x=0,
        y=0,
        z=0,
        method="linesource",
        r=25,
        n=15,
    )

    elec = LFPy.RecExtElectrode(cell, **elec_params)

    M_elec = elec.get_transformation_matrix()

    # Convert from mV to µV.
    LFP = M_elec @ cell.imem * 1000

    # Store the somatic membrane potential.
    vmem = cell.vmem[0]

    # Explicitly free memory since many cells are simulated in parallel.
    del cell
    del elec

    import gc
    gc.collect()

    return (
        LFP[0],
        rotation_array,
        exc_idxs,
        inh_idxs,
        exc_spiketrains,
        inh_spiketrains,
        vmem,
    )

def parallel_lfp_calculation(electrode_positions, dt, tstop, axon_type,
                             conductance_type, radius_um):
        """
        Parallelize the LFP calculation across multiple neurons.

        Each neuron is simulated independently in a separate worker process.
        The function distributes the electrode positions among workers, executes
        process_cell(), and collects the simulated LFPs and associated metadata.

        Parameters
        ----------
        electrode_positions : array-like
            Spatial positions where neurons are placed.
        dt : float
            Simulation time step.
        tstop : float
            Total simulation duration.
        axon_type : str
            Axonal morphology/type used in the neuron model.
        conductance_type : str
            Conductance configuration used in the neuron model.
        radius_um : float
            Radius parameter defining the spatial distribution of neurons.

        Returns
        -------
        list
            List containing the simulation output of every neuron.
        """

        # Create a multiprocessing context using fork.
        # Fork is efficient on Linux because worker processes inherit the parent
        # memory space, which reduces the overhead of copying large objects.
        ctx = mp.get_context("fork")

        # Create a pool of worker processes.
        # Each process independently executes process_cell().
        pool = ctx.Pool(5)

        # Create a partially initialized version of process_cell().
        # The fixed simulation parameters are passed automatically to each worker,
        # while the individual neuron index and position are provided by imap().
        func = partial(
            process_cell,
            dt=dt,
            tstop=tstop,
            axon_type=axon_type,
            conductance_type=conductance_type,
            center=center,
            radius_um=radius_um
        )

        # Distribute neurons across workers.
        # enumerate(electrode_positions) provides each neuron with:
        #   - a unique index (used as a random seed)
        #   - its assigned spatial position
        #
        # tqdm provides a progress bar showing simulation completion.
        results = list(
            tqdm(
                pool.imap(func, enumerate(electrode_positions)),
                total=len(electrode_positions),
                desc="Processing Cells"
            )
        )

        # Properly close the multiprocessing pool after all simulations finish.
        pool.close()
        pool.join()

        return results


# Run the parallelized neuron simulations.
# Each element of lfp_single contains:
#   - extracellular potential trace (LFP)
#   - neuron rotation
#   - excitatory synapse locations
#   - inhibitory synapse locations
#   - excitatory spike trains
#   - inhibitory spike trains
#   - somatic membrane voltage
lfp_single = parallel_lfp_calculation(
    electrode_positions,
    dt,
    tstop,
    axon_type,
    conductance_type,
    radius_um
)


import pickle


# -------------------------------------------------------------------------
# Collect simulation outputs
# -------------------------------------------------------------------------
# Initialize containers for storing results from all simulated neurons.
lfp_array = []
rotation_array = []
exc_idxs_list = []
inh_idxs_list = []
exc_spiketrains_list = []
inh_spiketrains_list = []
vmem_list = []


# Iterate through the output of every worker process and separate each
# returned quantity into its corresponding list.
for lfp, rotation, exc_idxs, inh_idxs, exc_spikes, inh_spikes, vmem in lfp_single:

    # Store extracellular potentials.
    lfp_array.append(lfp)

    # Store random orientation angles applied to the neuron morphology.
    rotation_array.append(rotation)

    # Store excitatory and inhibitory synaptic compartment indices.
    exc_idxs_list.append(exc_idxs)
    inh_idxs_list.append(inh_idxs)

    # Store the generated presynaptic spike trains.
    exc_spiketrains_list.append(exc_spikes)
    inh_spiketrains_list.append(inh_spikes)

    # Store somatic membrane voltage traces.
    vmem_list.append(vmem)



# Convert the LFP and rotation information into NumPy arrays for easier
# processing and analysis.
#
# Resulting shapes:
#   lfp_array      -> (number_of_cells, simulation_time)
#   rotation_array -> (number_of_cells, 3)
lfp_array = np.array(lfp_array)
rotation_array = np.array(rotation_array)



# -------------------------------------------------------------------------
# Save simulation results
# -------------------------------------------------------------------------
# Save the extracellular potentials generated by all neurons.
# Pickle is used because it preserves NumPy arrays efficiently.
with open('lfps.pkl', 'wb') as f:
    pickle.dump(lfp_array, f)



# Additional simulation outputs can also be saved if required,
# including:
#   - membrane voltages
#   - neuron orientations
#   - synaptic locations
#   - presynaptic activity patterns
#

'''
with open('vmem.pkl', 'wb') as f:
    pickle.dump(vmem_list, f)

with open('rotation_array.pkl', 'wb') as f:
    pickle.dump(rotation_array, f)

with open('complete_exc_idxs.pkl', 'wb') as f:
    pickle.dump(exc_idxs_list, f)

with open('complete_inh_idxs.pkl', 'wb') as f:
    pickle.dump(inh_idxs_list, f)


with open('complete_exc_spiketrains.pkl', 'wb') as f:
    pickle.dump(exc_spiketrains_list, f)

with open('complete_inh_spiketrains.pkl', 'wb') as f:
    pickle.dump(inh_spiketrains_list, f)

with open('complete_electrode_positions.pkl', 'wb') as f:
    pickle.dump(electrode_positions, f)


'''