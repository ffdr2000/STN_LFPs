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
 
#define nrn_init _nrn_init__Cacum
#define _nrn_initial _nrn_initial__Cacum
#define nrn_cur _nrn_cur__Cacum
#define _nrn_current _nrn_current__Cacum
#define nrn_jacob _nrn_jacob__Cacum
#define nrn_state _nrn_state__Cacum
#define _net_receive _net_receive__Cacum 
#define integrate integrate__Cacum 
 
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
#define ica _p[0]
#define ica_columnindex 0
#define tau _p[1]
#define tau_columnindex 1
#define cai _p[2]
#define cai_columnindex 2
#define Dcai _p[3]
#define Dcai_columnindex 3
#define _g _p[4]
#define _g_columnindex 4
#define _ion_ica	*_ppvar[0]._pval
#define _ion_cai	*_ppvar[1]._pval
#define _style_ca	*((int*)_ppvar[2]._pvoid)
 
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
 "setdata_Cacum", _hoc_setdata,
 0, 0
};
 /* declare global and static user variables */
#define Avo Avo_Cacum
 double Avo = 6.02e+23;
#define Q10 Q10_Cacum
 double Q10 = 1.2;
#define activate_Q10 activate_Q10_Cacum
 double activate_Q10 = 1;
#define buftau buftau_Cacum
 double buftau = 185.746;
#define cai0_ca_ion cai0_ca_ion_Cacum
 double cai0_ca_ion = 0;
#define cai0 cai0_Cacum
 double cai0 = 0.0001;
#define con con_Cacum
 double con = 0;
#define depth depth_Cacum
 double depth = 200;
#define elc elc_Cacum
 double elc = 1.602e-19;
#define rate_k rate_k_Cacum
 double rate_k = 0;
#define tempb tempb_Cacum
 double tempb = 23;
#define temp2 temp2_Cacum
 double temp2 = 29;
#define temp1 temp1_Cacum
 double temp1 = 19;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "elc_Cacum", "coulombs",
 "depth_Cacum", "nm",
 "cai0_Cacum", "mM",
 "buftau_Cacum", "ms",
 "temp1_Cacum", "degC",
 "temp2_Cacum", "degC",
 "tempb_Cacum", "degC",
 0,0
};
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "con_Cacum", &con_Cacum,
 "Avo_Cacum", &Avo_Cacum,
 "elc_Cacum", &elc_Cacum,
 "depth_Cacum", &depth_Cacum,
 "cai0_Cacum", &cai0_Cacum,
 "buftau_Cacum", &buftau_Cacum,
 "cai0_ca_ion_Cacum", &cai0_ca_ion_Cacum,
 "activate_Q10_Cacum", &activate_Q10_Cacum,
 "Q10_Cacum", &Q10_Cacum,
 "temp1_Cacum", &temp1_Cacum,
 "temp2_Cacum", &temp2_Cacum,
 "tempb_Cacum", &tempb_Cacum,
 "rate_k_Cacum", &rate_k_Cacum,
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
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Cacum",
 0,
 0,
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 5, _prop);
 	/*initialize range parameters*/
 	_prop->param = _p;
 	_prop->param_size = 5;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[1]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[2]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for ca */
 
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

 void _Cacum_reg() {
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
  hoc_register_prop_size(_mechtype, 5, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "#ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Cacum Cacum.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define F _nrnunit_F[_nrnunit_use_legacy_]
static double _nrnunit_F[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
static int _reset;
static char *modelname = "calcium accumulation for STh";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int integrate(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   Dcai = - ica * con + ( cai0 - cai ) / tau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 Dcai = Dcai  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau )) ;
  return 0;
}
 /*END CVODE*/
 static int integrate () {_reset=0;
 {
    cai = cai + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau)))*(- ( ( - ica )*( con ) + ( ( cai0 ) ) / tau ) / ( ( ( ( - 1.0 ) ) ) / tau ) - cai) ;
   }
  return 0;
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
  ica = _ion_ica;
  cai = _ion_cai;
     _ode_spec1 ();
  _ion_cai = cai;
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 	_pv[0] = &(_ion_cai);
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
  ica = _ion_ica;
  cai = _ion_cai;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 1);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
 {
   double _lktemp , _lktempb , _lktemp1 , _lktemp2 ;
 if ( activate_Q10 > 0.0 ) {
     _lktemp = celsius + 273.0 ;
     _lktempb = tempb + 273.0 ;
     _lktemp1 = temp1 + 273.0 ;
     _lktemp2 = temp2 + 273.0 ;
     rate_k = exp ( log ( Q10 ) * ( ( 1.0 / _lktempb ) - ( 1.0 / _lktemp ) ) / ( ( 1.0 / _lktemp1 ) - ( 1.0 / _lktemp2 ) ) ) ;
     }
   else {
     rate_k = 1.0 ;
     }
   con = 1e7 / ( depth * 2.0 * Avo * elc ) ;
   tau = buftau / rate_k ;
   cai = cai0 ;
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
  ica = _ion_ica;
  cai = _ion_cai;
 initmodel();
  _ion_cai = cai;
  nrn_wrote_conc(_ca_sym, (&(_ion_cai)) - 1, _style_ca);
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{
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
  ica = _ion_ica;
  cai = _ion_cai;
 { error =  integrate();
 if(error){fprintf(stderr,"at line 64 in file Cacum.mod:\n	SOLVE integrate METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 } {
   }
  _ion_cai = cai;
}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = cai_columnindex;  _dlist1[0] = Dcai_columnindex;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "Cacum.mod";
static const char* nmodl_file_text = 
  "TITLE calcium accumulation for STh\n"
  "\n"
  "COMMENT \n"
  "\n"
  " Calcium accumulation into a volume of area*depth next to the\n"
  " membrane with an exponential decay (time constant tau) to resting\n"
  " level (given by the global calcium variable cai0_ca_ion).\n"
  "\n"
  " How the q10 works:\n"
  "There is a q10 for the rates (alpha and beta's) called Q10.  The q10s\n"
  "should have been measured at specific temperatures temp1 and temp2\n"
  "(that are 10degC apart). Ideally, as Q10 is temperature dependant, we\n"
  "should know these two temperatures.  We are going to follow the\n"
  "more formal Arrhenius derived Q10 approach.   The temperature at\n"
  "which this channel's kinetics were recorded is tempb (base\n"
  "temperature).  What we then need to calculate is the desired rate\n"
  "scale for now working at temperature celsius (rate_k).  This is given\n"
  "by the empirical Arrhenius equation, using the Q10.  \n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX Cacum\n"
  "	USEION ca READ ica WRITE cai\n"
  "	GLOBAL con,cai0,buftau,activate_Q10,Q10,rate_k,temp1,temp2,tempb,depth\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mM) = (milli/liter)\n"
  "	(mA) = (milliamp)\n"
  "	F = (faraday) (coulombs)	: Faradays constant \n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "	dt (ms)\n"
  "	con   = 0.0			: conversion constant (see INITIAL block)\n"
  "        Avo   = 6.02e23			: Avogadro's number\n"
  "	elc   = 1.602e-19 (coulombs)	: elementrary charge\n"
  "	depth = 200.0 (nm)		: assume volume = area*depth\n"
  "	cai0  = 0.0001(mM)		: replace cai0_ca_ion \n"
  "	buftau = 1.857456645e+02 (ms)\n"
  "	cai0_ca_ion\n"
  "	celsius\n"
  "\n"
  "	activate_Q10 = 1\n"
  "	Q10 = 1.2\n"
  "	temp1 = 19.0 (degC)\n"
  "	temp2 = 29.0 (degC)\n"
  "	tempb = 23.0 (degC)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ica (mA/cm2)\n"
  "        tau (ms)\n"
  "	rate_k\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	cai (mM)\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE integrate METHOD cnexp\n"
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
  "	}else{\n"
  "	  rate_k = 1.0\n"
  "	}\n"
  "\n"
  "	con=1e7/(depth*2.0*Avo*elc)	  : UNITS (derivation)\n"
  " 			: ica             = (mA/cm2)\n"
  "			:                 = (A/1e3cm2) \n"
  "			:                 = ((C/s)/1e3cm2)\n"
  "			: depth           = (nm) = (1e-7cm)\n"
  "			: ica/depth       = ((C/s)/1e3cm2) * 1/(1e-7cm)\n"
  "			:                 = ((C/s)/1e3cm2) * 1e7/(cm)\n"
  "			:                 = (1e7(C/s) * 1/(1e3cm3))\n"
  "			:                 = (1e7(C/s) * 1/(litres))\n"
  "			: 1e7*ica/depth   = ((C/s) * 1/(litres))\n"
  "			:                 = ((C/litres) * 1/(s))\n"
  "			:                 = ((C/litres) * 1/(1e3msec))\n"
  "			:                 = ((C/litres) * 1e-3/(msec))\n"
  "			: 1e4*ica/depth   = ((C/litres) * 1/(msec))\n"
  "			: 1/(2*Avo*elc)   = (mol/C)\n"
  "			:                 = (1e3mmol/C)\n"
  "			: 1e3/(2*Avo*elc) = (mmol/C)\n"
  "			: 1e4*ica/depth * 1e3/(2*Avo*elc) = ((C/litres) * 1/(msec)) \n"
  "			:                                   * (mmol/C)\n"
  "			: ica*1e7/(depth*2*Avo*elc) = (mmol/litres) * (1/msec)\n"
  "			: ica*con         = (mM) * (1/msec)\n"
  "	tau=buftau/rate_k\n"
  "	cai=cai0\n"
  "}\n"
  "\n"
  "DERIVATIVE integrate {\n"
  "	cai' = -ica*con + (cai0 - cai)/tau\n"
  "}\n"
  "\n"
  "UNITSON\n"
  ;
#endif
