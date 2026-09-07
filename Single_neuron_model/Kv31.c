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
 
#define nrn_init _nrn_init__Kv31
#define _nrn_initial _nrn_initial__Kv31
#define nrn_cur _nrn_cur__Kv31
#define _nrn_current _nrn_current__Kv31
#define nrn_jacob _nrn_jacob__Kv31
#define nrn_state _nrn_state__Kv31
#define _net_receive _net_receive__Kv31 
#define _f_settables _f_settables__Kv31 
#define settables settables__Kv31 
#define states states__Kv31 
 
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
#define gk _p[0]
#define gk_columnindex 0
#define p _p[1]
#define p_columnindex 1
#define ek _p[2]
#define ek_columnindex 2
#define ki _p[3]
#define ki_columnindex 3
#define Dp _p[4]
#define Dp_columnindex 4
#define ik _p[5]
#define ik_columnindex 5
#define pinf _p[6]
#define pinf_columnindex 6
#define ptau _p[7]
#define ptau_columnindex 7
#define _g _p[8]
#define _g_columnindex 8
#define _ion_ki	*_ppvar[0]._pval
#define _ion_ek	*_ppvar[1]._pval
#define _ion_ik	*_ppvar[2]._pval
#define _ion_dikdv	*_ppvar[3]._pval
 
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
 "setdata_Kv31", _hoc_setdata,
 "settables_Kv31", _hoc_settables,
 0, 0
};
 /* declare global and static user variables */
#define Q10 Q10_Kv31
 double Q10 = 1.70003;
#define activate_Q10 activate_Q10_Kv31
 double activate_Q10 = 1;
#define gmax_k gmax_k_Kv31
 double gmax_k = 0;
#define gmaxQ10 gmaxQ10_Kv31
 double gmaxQ10 = 1.70003;
#define rate_k rate_k_Kv31
 double rate_k = 0;
#define tempb tempb_Kv31
 double tempb = 32;
#define temp2 temp2_Kv31
 double temp2 = 30;
#define temp1 temp1_Kv31
 double temp1 = 20;
#define usetable usetable_Kv31
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_Kv31", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "temp1_Kv31", "degC",
 "temp2_Kv31", "degC",
 "tempb_Kv31", "degC",
 "gk_Kv31", "mho/cm2",
 0,0
};
 static double delta_t = 1;
 static double p0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "activate_Q10_Kv31", &activate_Q10_Kv31,
 "Q10_Kv31", &Q10_Kv31,
 "gmaxQ10_Kv31", &gmaxQ10_Kv31,
 "temp1_Kv31", &temp1_Kv31,
 "temp2_Kv31", &temp2_Kv31,
 "tempb_Kv31", &tempb_Kv31,
 "rate_k_Kv31", &rate_k_Kv31,
 "gmax_k_Kv31", &gmax_k_Kv31,
 "usetable_Kv31", &usetable_Kv31,
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
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Kv31",
 "gk_Kv31",
 0,
 0,
 "p_Kv31",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 9, _prop);
 	/*initialize range parameters*/
 	gk = 0.015;
 	_prop->param = _p;
 	_prop->param_size = 9;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* ki */
 	_ppvar[1]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
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

 void _Kv31_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 9, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Kv31 Kv31.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double *_t_pinf;
 static double *_t_ptau;
static int _reset;
static char *modelname = "potassium Kv3.1 membrane channel for STh";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_settables(double);
static int settables(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_settables(double);
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   settables ( _threadargscomma_ v ) ;
   Dp = ( pinf - p ) / ptau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 settables ( _threadargscomma_ v ) ;
 Dp = Dp  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ptau )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   settables ( _threadargscomma_ v ) ;
    p = p + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ptau)))*(- ( ( ( pinf ) ) / ptau ) / ( ( ( ( - 1.0 ) ) ) / ptau ) - p) ;
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
    _t_pinf[_i] = pinf;
    _t_ptau[_i] = ptau;
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
  pinf = _xi;
  ptau = _xi;
  return;
 }
 if (_xi <= 0.) {
 pinf = _t_pinf[0];
 ptau = _t_ptau[0];
 return; }
 if (_xi >= 400.) {
 pinf = _t_pinf[400];
 ptau = _t_ptau[400];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 pinf = _t_pinf[_i] + _theta*(_t_pinf[_i+1] - _t_pinf[_i]);
 ptau = _t_ptau[_i] + _theta*(_t_ptau[_i+1] - _t_ptau[_i]);
 }

 
static int  _f_settables (  double _lv ) {
   pinf = 1.0 / ( 1.0 + exp ( ( _lv + - 0.083699749 ) / - 9.0 ) ) ;
   ptau = ( ( 7.3 / ( exp ( ( _lv + 32.9163003 ) / - 14.0 ) + exp ( ( _lv + 2.91630025 ) / 16.0 ) ) ) + 1.0 ) / rate_k ;
    return 0; }
 
static void _hoc_settables(void) {
  double _r;
    _r = 1.;
 settables (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ki = _ion_ki;
  ek = _ion_ek;
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
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
  ki = _ion_ki;
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 3, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  p = p0;
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
   p = pinf ;
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
  ki = _ion_ki;
  ek = _ion_ek;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ik = ( gk * gmax_k ) * p * ( v - ek ) ;
   }
 _current += ik;

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
  ki = _ion_ki;
  ek = _ion_ek;
 _g = _nrn_current(_v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
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
  ki = _ion_ki;
  ek = _ion_ek;
 { error =  states();
 if(error){fprintf(stderr,"at line 63 in file Kv31.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = p_columnindex;  _dlist1[0] = Dp_columnindex;
   _t_pinf = makevector(401*sizeof(double));
   _t_ptau = makevector(401*sizeof(double));
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "Kv31.mod";
static const char* nmodl_file_text = 
  "TITLE potassium Kv3.1 membrane channel for STh\n"
  "\n"
  "COMMENT\n"
  " Potassium Kv3.1 membrane channel for STh.  Based on derived kinetics\n"
  " from Wigmore & Lacey 2000.  Their primary experiments were performed\n"
  " at 32degC\n"
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
  "ENDCOMMENT\n"
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "}\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX Kv31\n"
  "	USEION k READ ki,ek WRITE ik\n"
  "	RANGE gk\n"
  "	GLOBAL activate_Q10,Q10,gmaxQ10,rate_k,gmax_k,temp1,temp2,tempb\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "	dt (ms)\n"
  "	gk   = 0.015 (mho/cm2)\n"
  "	ek\n"
  "	ki\n"
  "	celsius\n"
  "\n"
  "	activate_Q10 = 1\n"
  "	Q10 = 1.700025939e+00\n"
  "	gmaxQ10 = 1.700025939e+00\n"
  "	temp1 = 20.0 (degC)\n"
  "	temp2 = 30.0 (degC)\n"
  "	tempb = 32.0 (degC)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "        p \n"
  "}\n"
  "\n"
  "ASSIGNED { \n"
  "	ik (mA/cm2)\n"
  "	pinf\n"
  "	ptau (ms)\n"
  "	rate_k\n"
  "	gmax_k\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	ik   = (gk*gmax_k)*p*(v-ek)\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
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
  "        settables(v)\n"
  "	p = pinf\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  \n"
  "        settables(v)\n"
  "	p' = (pinf-p)/ptau\n"
  "}\n"
  "\n"
  "PROCEDURE settables(v) {:Computes rate and other constants at current v.\n"
  "                        :Call once from HOC to initialize inf at resting v.\n"
  "			:Voltage shift (for temp effects) of -5.08\n"
  "	TABLE pinf, ptau DEPEND celsius FROM -100 TO 100 WITH 400\n"
  "\n"
  "	pinf = 1.0/(1.0+exp((v + -0.083699749)/ -9.0))\n"
  "	ptau = ((7.3/(exp((v + 32.9163003)/-14.0)+exp((v + 2.91630025)/16.0)))+1) / rate_k\n"
  "\n"
  "}\n"
  "\n"
  "UNITSON\n"
  "\n"
  ;
#endif
