/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__HVA
#define _nrn_initial _nrn_initial__HVA
#define nrn_cur _nrn_cur__HVA
#define _nrn_current _nrn_current__HVA
#define nrn_jacob _nrn_jacob__HVA
#define nrn_state _nrn_state__HVA
#define _net_receive _net_receive__HVA 
#define _f_settables _f_settables__HVA 
#define setCadepLinact setCadepLinact__HVA 
#define settables settables__HVA 
#define states states__HVA 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gcaL _p[0]
#define gcaL_columnindex 0
#define gcaN _p[1]
#define gcaN_columnindex 1
#define iNCa _p[2]
#define iNCa_columnindex 2
#define iLCa _p[3]
#define iLCa_columnindex 3
#define q _p[4]
#define q_columnindex 4
#define u _p[5]
#define u_columnindex 5
#define h _p[6]
#define h_columnindex 6
#define eca _p[7]
#define eca_columnindex 7
#define cai _p[8]
#define cai_columnindex 8
#define cao _p[9]
#define cao_columnindex 9
#define Dq _p[10]
#define Dq_columnindex 10
#define Du _p[11]
#define Du_columnindex 11
#define Dh _p[12]
#define Dh_columnindex 12
#define ica _p[13]
#define ica_columnindex 13
#define qinf _p[14]
#define qinf_columnindex 14
#define uinf _p[15]
#define uinf_columnindex 15
#define hinf _p[16]
#define hinf_columnindex 16
#define qtau _p[17]
#define qtau_columnindex 17
#define utau _p[18]
#define utau_columnindex 18
#define htau _p[19]
#define htau_columnindex 19
#define _g _p[20]
#define _g_columnindex 20
#define _ion_cai	*_ppvar[0]._pval
#define _ion_cao	*_ppvar[1]._pval
#define _ion_eca	*_ppvar[2]._pval
#define _ion_ica	*_ppvar[3]._pval
#define _ion_dicadv	*_ppvar[4]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_ghkg(void);
 static void _hoc_setCadepLinact(void);
 static void _hoc_settables(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_HVA", _hoc_setdata,
 "ghkg_HVA", _hoc_ghkg,
 "setCadepLinact_HVA", _hoc_setCadepLinact,
 "settables_HVA", _hoc_settables,
 0, 0
};
#define ghkg ghkg_HVA
 extern double ghkg( double , double , double , double );
 /* declare global and static user variables */
#define Q10 Q10_HVA
 double Q10 = 1.94826;
#define activate_Q10 activate_Q10_HVA
 double activate_Q10 = 1;
#define gmax_k gmax_k_HVA
 double gmax_k = 0;
#define gmaxQ10 gmaxQ10_HVA
 double gmaxQ10 = 1.94826;
#define inactLmax inactLmax_HVA
 double inactLmax = 0.529129;
#define inactLtau inactLtau_HVA
 double inactLtau = 1220;
#define rate_k rate_k_HVA
 double rate_k = 0;
#define tempb tempb_HVA
 double tempb = 22;
#define temp2 temp2_HVA
 double temp2 = 30;
#define temp1 temp1_HVA
 double temp1 = 20;
#define usetable usetable_HVA
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_HVA", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "inactLtau_HVA", "ms",
 "temp1_HVA", "degC",
 "temp2_HVA", "degC",
 "tempb_HVA", "degC",
 "gcaL_HVA", "mho/cm2",
 "gcaN_HVA", "mho/cm2",
 "iNCa_HVA", "mA/cm2",
 "iLCa_HVA", "mA/cm2",
 0,0
};
 static double delta_t = 1;
 static double h0 = 0;
 static double q0 = 0;
 static double u0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "inactLtau_HVA", &inactLtau_HVA,
 "inactLmax_HVA", &inactLmax_HVA,
 "activate_Q10_HVA", &activate_Q10_HVA,
 "Q10_HVA", &Q10_HVA,
 "gmaxQ10_HVA", &gmaxQ10_HVA,
 "temp1_HVA", &temp1_HVA,
 "temp2_HVA", &temp2_HVA,
 "tempb_HVA", &tempb_HVA,
 "rate_k_HVA", &rate_k_HVA,
 "gmax_k_HVA", &gmax_k_HVA,
 "usetable_HVA", &usetable_HVA,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[5]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"HVA",
 "gcaL_HVA",
 "gcaN_HVA",
 "iNCa_HVA",
 "iLCa_HVA",
 0,
 0,
 "q_HVA",
 "u_HVA",
 "h_HVA",
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 21, _prop);
 	/*initialize range parameters*/
 	gcaL = 0.002;
 	gcaN = 0.012;
 	iNCa = 0;
 	iLCa = 0;
 	_prop->param = _p;
 	_prop->param_size = 21;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 6, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[2]._pval = &prop_ion->param[0]; /* eca */
 	_ppvar[3]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[4]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _HVA_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 21, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 HVA HVA.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define FARADAY _nrnunit_FARADAY[_nrnunit_use_legacy_]
static double _nrnunit_FARADAY[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
 
#define R _nrnunit_R[_nrnunit_use_legacy_]
static double _nrnunit_R[2] = {0x1.0a1013e8990bep+3, 8.3145}; /* 8.3144626181532395 */
 static double *_t_qinf;
 static double *_t_qtau;
 static double *_t_uinf;
 static double *_t_utau;
static int _reset;
static char *modelname = "calcium HVA channels for STh";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_settables(double);
static int setCadepLinact(double);
static int settables(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_settables(double);
 static int _slist1[3], _dlist1[3];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   settables ( _threadargscomma_ v ) ;
   Dq = ( qinf - q ) / qtau ;
   Du = ( uinf - u ) / utau ;
   setCadepLinact ( _threadargscomma_ cai ) ;
   Dh = ( hinf - h ) / htau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 settables ( _threadargscomma_ v ) ;
 Dq = Dq  / (1. - dt*( ( ( ( - 1.0 ) ) ) / qtau )) ;
 Du = Du  / (1. - dt*( ( ( ( - 1.0 ) ) ) / utau )) ;
 setCadepLinact ( _threadargscomma_ cai ) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / htau )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   settables ( _threadargscomma_ v ) ;
    q = q + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / qtau)))*(- ( ( ( qinf ) ) / qtau ) / ( ( ( ( - 1.0 ) ) ) / qtau ) - q) ;
    u = u + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / utau)))*(- ( ( ( uinf ) ) / utau ) / ( ( ( ( - 1.0 ) ) ) / utau ) - u) ;
   setCadepLinact ( _threadargscomma_ cai ) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / htau)))*(- ( ( ( hinf ) ) / htau ) / ( ( ( ( - 1.0 ) ) ) / htau ) - h) ;
   }
  return 0;
}
 static double _mfac_settables, _tmin_settables;
 static void _check_settables();
 static void _check_settables() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_celsius;
  if (!usetable) {return;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_settables =  - 100.0 ;
   _tmax =  100.0 ;
   _dx = (_tmax - _tmin_settables)/400.; _mfac_settables = 1./_dx;
   for (_i=0, _x=_tmin_settables; _i < 401; _x += _dx, _i++) {
    _f_settables(_x);
    _t_qinf[_i] = qinf;
    _t_qtau[_i] = qtau;
    _t_uinf[_i] = uinf;
    _t_utau[_i] = utau;
   }
   _sav_celsius = celsius;
  }
 }

 static int settables(double _lv){ _check_settables();
 _n_settables(_lv);
 return 0;
 }

 static void _n_settables(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_settables(_lv); return; 
}
 _xi = _mfac_settables * (_lv - _tmin_settables);
 if (isnan(_xi)) {
  qinf = _xi;
  qtau = _xi;
  uinf = _xi;
  utau = _xi;
  return;
 }
 if (_xi <= 0.) {
 qinf = _t_qinf[0];
 qtau = _t_qtau[0];
 uinf = _t_uinf[0];
 utau = _t_utau[0];
 return; }
 if (_xi >= 400.) {
 qinf = _t_qinf[400];
 qtau = _t_qtau[400];
 uinf = _t_uinf[400];
 utau = _t_utau[400];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 qinf = _t_qinf[_i] + _theta*(_t_qinf[_i+1] - _t_qinf[_i]);
 qtau = _t_qtau[_i] + _theta*(_t_qtau[_i+1] - _t_qtau[_i]);
 uinf = _t_uinf[_i] + _theta*(_t_uinf[_i+1] - _t_uinf[_i]);
 utau = _t_utau[_i] + _theta*(_t_utau[_i+1] - _t_utau[_i]);
 }

 
static int  _f_settables (  double _lv ) {
   qinf = 1.0 / ( 1.0 + exp ( ( - 16.3547869 - _lv ) / 11.3 ) ) ;
   qtau = ( 1.25 / ( cosh ( - 0.031 * ( _lv + 28.8547869 ) ) ) ) / rate_k ;
   uinf = 1.0 / ( 1.0 + exp ( ( _lv + 45.3326653 ) / 12.5 ) ) ;
   utau = ( 98.0 + cosh ( 0.021 * ( 24.7673347 - _lv ) ) ) / rate_k ;
    return 0; }
 
static void _hoc_settables(void) {
  double _r;
    _r = 1.;
 settables (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  setCadepLinact (  double _lcai ) {
   hinf = inactLmax + ( ( 1.0 - inactLmax ) / ( 1.0 + exp ( ( _lcai - 0.7 ) / 0.15 ) ) ) ;
   htau = inactLtau / rate_k ;
    return 0; }
 
static void _hoc_setCadepLinact(void) {
  double _r;
   _r = 1.;
 setCadepLinact (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double ghkg (  double _lv , double _lci , double _lco , double _lz ) {
   double _lghkg;
 double _lnu , _lf , _lenu , _lfnu ;
 _lf = ( 1.0e3 / _lz ) * R * ( celsius + 273.15 ) / FARADAY ;
   _lnu = _lv / _lf ;
   _lenu = exp ( _lnu ) ;
   if ( fabs ( _lnu ) < 1e-4 ) {
     _lfnu = 1.0 - _lnu / 2.0 ;
     }
   else {
     _lfnu = _lnu / ( _lenu - 1.0 ) ;
     }
   _lghkg = - _lf * ( 1.0 - ( _lci / _lco ) * _lenu ) * _lfnu ;
   
return _lghkg;
 }
 
static void _hoc_ghkg(void) {
  double _r;
   _r =  ghkg (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  cao = _ion_cao;
  eca = _ion_eca;
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  cao = _ion_cao;
  eca = _ion_eca;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 0);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 4, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  q = q0;
  u = u0;
 {
   double _lktemp , _lktempb , _lktemp1 , _lktemp2 ;
 if ( activate_Q10 > 0.0 ) {
     _lktemp = celsius + 273.0 ;
     _lktempb = tempb + 273.0 ;
     _lktemp1 = temp1 + 273.0 ;
     _lktemp2 = temp2 + 273.0 ;
     rate_k = exp ( log ( Q10 ) * ( ( 1.0 / _lktempb ) - ( 1.0 / _lktemp ) ) / ( ( 1.0 / _lktemp1 ) - ( 1.0 / _lktemp2 ) ) ) ;
     gmax_k = exp ( log ( gmaxQ10 ) * ( ( 1.0 / _lktempb ) - ( 1.0 / _lktemp ) ) / ( ( 1.0 / _lktemp1 ) - ( 1.0 / _lktemp2 ) ) ) ;
     }
   else {
     rate_k = 1.0 ;
     gmax_k = 1.0 ;
     }
   settables ( _threadargscomma_ v ) ;
   q = qinf ;
   u = uinf ;
   setCadepLinact ( _threadargscomma_ cai ) ;
   h = hinf ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  cai = _ion_cai;
  cao = _ion_cao;
  eca = _ion_eca;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   double _lvghk ;
 _lvghk = ghkg ( _threadargscomma_ v , cai , cao , 2.0 ) ;
   iNCa = gmax_k * ( gcaN * u ) * q * q * _lvghk ;
   iLCa = gmax_k * ( gcaL ) * q * q * h * _lvghk ;
   ica = iNCa + iLCa ;
   }
 _current += ica;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  cai = _ion_cai;
  cao = _ion_cao;
  eca = _ion_eca;
 _g = _nrn_current(_v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  cai = _ion_cai;
  cao = _ion_cao;
  eca = _ion_eca;
 { error =  states();
 if(error){fprintf(stderr,"at line 79 in file HVA.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = q_columnindex;  _dlist1[0] = Dq_columnindex;
 _slist1[1] = u_columnindex;  _dlist1[1] = Du_columnindex;
 _slist1[2] = h_columnindex;  _dlist1[2] = Dh_columnindex;
   _t_qinf = makevector(401*sizeof(double));
   _t_qtau = makevector(401*sizeof(double));
   _t_uinf = makevector(401*sizeof(double));
   _t_utau = makevector(401*sizeof(double));
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "HVA.mod";
static const char* nmodl_file_text = 
  "TITLE calcium HVA channels for STh\n"
  "\n"
  "COMMENT\n"
  " High threshold calcium channel (N/L-type), Brown et al. 1993. & Fox\n"
  " et al. (1989).  Both done at temperature 22degC.\n"
  "\n"
  " How the q10 works: There is a q10 for the rates (alpha and beta's)\n"
  " called Q10 and a Q10 for the maximum conductance called gmaxQ10.  The\n"
  " q10s should have been measured at specific temperatures temp1 and\n"
  " temp2 (that are 10degC apart). Ideally, as Q10 is temperature\n"
  " dependant, we should know these two temperatures.  We are going to\n"
  " follow the more formal Arrhenius derived Q10 approach.  The\n"
  " temperature at which this channel's kinetics were recorded is tempb\n"
  " (base temperature).  What we then need to calculate is the desired\n"
  " rate scale for now working at temperature celsius (rate_k).  This is\n"
  " given by the empirical Arrhenius equation, using the Q10. \n"
  "\n"
  " Adding CaL [Ca]i dependent inactivation.  This is only for the L-type\n"
  " component, and is called inactivation variable 'h'.  \n"
  "ENDCOMMENT\n"
  "\n"
  "UNITS {\n"
  "	(mM) = (milli/liter)\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "     FARADAY = (faraday) (coulomb)\n"
  "           R = (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX HVA\n"
  "	USEION ca READ cai,cao,eca WRITE ica\n"
  "	RANGE gcaN, gcaL, iNCa, iLCa\n"
  "	GLOBAL inactLtau,inactLmax,activate_Q10,Q10,gmaxQ10,rate_k,gmax_k,temp1,temp2,tempb\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "	dt (ms)\n"
  "        gcaL  = 0.002 (mho/cm2)\n"
  "	gcaN  = 0.012 (mho/cm2)\n"
  "	iNCa  = 0.0 (mA/cm2)\n"
  "	iLCa  = 0.0 (mA/cm2)\n"
  "	inactLtau = 1220.0 (ms)\n"
  "	inactLmax = 5.291291201e-01\n"
  "	eca\n"
  "	cai\n"
  "	cao\n"
  "	celsius\n"
  "\n"
  "	activate_Q10 = 1\n"
  "	Q10 = 1.948259241e+00\n"
  "	gmaxQ10 = 1.948259241e+00\n"
  "	temp1 = 20.0 (degC)\n"
  "	temp2 = 30.0 (degC)\n"
  "	tempb = 22.0 (degC)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "        q u h\n"
  "}\n"
  "\n"
  "ASSIGNED { \n"
  "        ica (mA/cm2)\n"
  "	qinf\n"
  "	uinf\n"
  "	hinf\n"
  "	qtau (ms)\n"
  "	utau (ms)\n"
  "	htau (ms)\n"
  "	rate_k\n"
  "	gmax_k\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	LOCAL vghk\n"
  "	SOLVE states METHOD cnexp\n"
  "	vghk = ghkg(v,cai,cao,2)\n"
  "	iNCa = gmax_k*(gcaN * u)*q*q*vghk\n"
  "	iLCa = gmax_k*(gcaL)*q*q*h*vghk\n"
  "	ica  = iNCa + iLCa\n"
  "}\n"
  "\n"
  "\n"
  "INITIAL {\n"
  "	LOCAL ktemp,ktempb,ktemp1,ktemp2\n"
  "	if (activate_Q10>0) {\n"
  "	  ktemp  = celsius+273.0\n"
  "	  ktempb = tempb+273.0\n"
  "	  ktemp1 = temp1+273.0\n"
  "	  ktemp2 = temp2+273.0\n"
  "	  rate_k = exp( log(Q10)*((1/ktempb)-(1/ktemp))/((1/ktemp1)-(1/ktemp2)) )\n"
  "	  gmax_k = exp( log(gmaxQ10)*((1/ktempb)-(1/ktemp))/((1/ktemp1)-(1/ktemp2)) )\n"
  "	}else{\n"
  "	  rate_k = 1.0\n"
  "	  gmax_k = 1.0\n"
  "	}\n"
  "\n"
  "        settables(v)\n"
  "	q = qinf\n"
  "	u = uinf\n"
  "	setCadepLinact(cai)\n"
  "	h = hinf\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  \n"
  "	settables(v)  \n"
  "	q' = (qinf-q)/qtau\n"
  "	u' = (uinf-u)/utau\n"
  "	setCadepLinact(cai)\n"
  "	h' = (hinf-h)/htau\n"
  "}\n"
  "\n"
  "PROCEDURE settables(v) {  :Computes rate and other constants at current v.\n"
  "                          :Call once from HOC to initialize inf at resting v.\n"
  "			  :Voltage shifts (for temp effects) of -8.25 and -14.67 added respt.\n"
  "        TABLE qinf, qtau, uinf, utau DEPEND celsius FROM -100 TO 100 WITH 400\n"
  "\n"
  "                :\"q\" N/L Ca activation system\n"
  "        qinf   = 1.0/(1.0 + exp((-16.3547869 - v)/11.3))\n"
  "        qtau   = (1.25/(cosh(-0.031 * (v + 28.8547869)))) /rate_k\n"
  "\n"
  "                :\"u\" N inactivation system - voltage dependent.\n"
  "        uinf   = 1.0/(1.0 + exp((v + 45.3326653)/12.5))\n"
  "        utau   = (98.0 + cosh(0.021*(24.7673347-v))) /rate_k\n"
  "}\n"
  "\n"
  "PROCEDURE setCadepLinact(cai) { : set Ca dependent L-type calcium channel inactivation\n"
  "                :\"h\" L inactivation system - [Ca]i dependent.\n"
  "	hinf   = inactLmax+((1.0-inactLmax)/(1.0 + exp((cai-0.7)/0.15)))\n"
  "        htau   = inactLtau /rate_k\n"
  "}\n"
  "\n"
  ":::INCLUDE \"ghk.inc\"\n"
  "\n"
  "\n"
  "FUNCTION ghkg(v(mV), ci(mM), co(mM), z) (mV) {\n"
  "        LOCAL nu,f,enu,fnu\n"
  "              : Here we calculate an effective drive from the GHK equation\n"
  "              : define\n"
  "              :    f   = 10^3 RT/(zF)\n"
  "              :    nu  = v/f  \n"
  "              :        = z v10^-3 F / (RT) \n"
  "              : note the 10e-3 converts [mV] to [V]\n"
  "              :    nu  = z V F / (RT)\n"
  "              :\n"
  "              :    enu = exp(nu)\n"
  "              :        = exp(z V F / (RT))\n"
  "              :\n"
  "              :    fnu = nu/(enu-1) \n"
  "              :        = (z V F / (RT)) / (exp(z V F / (RT))-1)\n"
  "              :        = (z V F / (RT))   (exp(-zV F / (RT))/(1-exp(-zV F / (RT))))\n"
  "              :\n"
  "              : now the effective drive is calculated as\n"
  "              :\n"
  "              :   ghkg = -f (1 - (ci/co)  enu) fnu\n"
  "              :        = -10^3 RT/(zF)  (1 - (ci/co) exp(z V F / (RT))) *\n"
  "              :         (z V F / (RT)) (exp(-zV F / (RT))/(1-exp(-zV F / (RT))))\n"
  "              :        = -10^3 V (1/co) (co - ci exp(z V F / (RT))) (exp(-zV F / (RT))/(1-exp(-zV F / (RT))))\n"
  "              :        = 10^3 V/co (ci - co exp(-zV F / (RT)))/(1-exp(-zV F / (RT)))\n"
  "	      :\n"
  "              : [note, the 10^3 converts back to mV]\n"
  "              : and you can see this is the ghk equation if the relationship\n"
  "              : between conductance and permeability is\n"
  "              :\n"
  "              :      g = rho z^2 co F^2/RT\n"
  "              :\n"
  "              : Then g*ghkg reduces to the GHK current equation\n"
  "              :\n"
  "        f   = (1.0e3/z)*R*(celsius+273.15)/FARADAY\n"
  "        nu  = v/f\n"
  "	enu = exp(nu)\n"
  "	if (fabs(nu) < 1e-4) {\n"
  "                fnu = 1 - nu/2\n"
  "        }else{\n"
  "                fnu = nu/(enu - 1) \n"
  "        }\n"
  "        ghkg= -f*(1 - (ci/co)*enu)*fnu\n"
  "}\n"
  ":::end INCLUDE ghk.inc\n"
  "\n"
  "\n"
  ;
#endif
