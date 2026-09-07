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
 
#define nrn_init _nrn_init__Ih
#define _nrn_initial _nrn_initial__Ih
#define nrn_cur _nrn_cur__Ih
#define _nrn_current _nrn_current__Ih
#define nrn_jacob _nrn_jacob__Ih
#define nrn_state _nrn_state__Ih
#define _net_receive _net_receive__Ih 
#define _f_setinf _f_setinf__Ih 
#define integrate integrate__Ih 
#define setinf setinf__Ih 
 
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
#define ih _p[1]
#define ih_columnindex 1
#define f _p[2]
#define f_columnindex 2
#define Df _p[3]
#define Df_columnindex 3
#define finf _p[4]
#define finf_columnindex 4
#define ftau _p[5]
#define ftau_columnindex 5
#define _g _p[6]
#define _g_columnindex 6
 
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
 static void _hoc_setinf(void);
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
 "setdata_Ih", _hoc_setdata,
 "setinf_Ih", _hoc_setinf,
 0, 0
};
 /* declare global and static user variables */
#define Q10 Q10_Ih
 double Q10 = 2;
#define activate_Q10 activate_Q10_Ih
 double activate_Q10 = 1;
#define eih eih_Ih
 double eih = -56.1105;
#define gmax_k gmax_k_Ih
 double gmax_k = 0;
#define gmaxQ10 gmaxQ10_Ih
 double gmaxQ10 = 2;
#define rate_k rate_k_Ih
 double rate_k = 0;
#define tempb tempb_Ih
 double tempb = 35.5;
#define temp2 temp2_Ih
 double temp2 = 35;
#define temp1 temp1_Ih
 double temp1 = 25;
#define usetable usetable_Ih
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_Ih", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "eih_Ih", "mV",
 "temp1_Ih", "degC",
 "temp2_Ih", "degC",
 "tempb_Ih", "degC",
 "gk_Ih", "mho/cm2",
 "ih_Ih", "mA/cm2",
 0,0
};
 static double delta_t = 1;
 static double f0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "eih_Ih", &eih_Ih,
 "activate_Q10_Ih", &activate_Q10_Ih,
 "Q10_Ih", &Q10_Ih,
 "gmaxQ10_Ih", &gmaxQ10_Ih,
 "temp1_Ih", &temp1_Ih,
 "temp2_Ih", &temp2_Ih,
 "tempb_Ih", &tempb_Ih,
 "rate_k_Ih", &rate_k_Ih,
 "gmax_k_Ih", &gmax_k_Ih,
 "usetable_Ih", &usetable_Ih,
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
 
#define _cvode_ieq _ppvar[0]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Ih",
 "gk_Ih",
 0,
 "ih_Ih",
 0,
 "f_Ih",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 7, _prop);
 	/*initialize range parameters*/
 	gk = 0.001;
 	_prop->param = _p;
 	_prop->param_size = 7;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 1, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Ih_reg() {
	int _vectorized = 0;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 7, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Ih Ih.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double *_t_finf;
 static double *_t_ftau;
static int _reset;
static char *modelname = "Potassium Ih channel for STh";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_setinf(double);
static int setinf(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_setinf(double);
 static int _slist1[1], _dlist1[1];
 static int integrate(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   setinf ( _threadargscomma_ v ) ;
   Df = ( finf - f ) / ftau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 setinf ( _threadargscomma_ v ) ;
 Df = Df  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ftau )) ;
  return 0;
}
 /*END CVODE*/
 static int integrate () {_reset=0;
 {
   setinf ( _threadargscomma_ v ) ;
    f = f + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ftau)))*(- ( ( ( finf ) ) / ftau ) / ( ( ( ( - 1.0 ) ) ) / ftau ) - f) ;
   }
  return 0;
}
 static double _mfac_setinf, _tmin_setinf;
 static void _check_setinf();
 static void _check_setinf() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_celsius;
  if (!usetable) {return;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_setinf =  - 100.0 ;
   _tmax =  100.0 ;
   _dx = (_tmax - _tmin_setinf)/400.; _mfac_setinf = 1./_dx;
   for (_i=0, _x=_tmin_setinf; _i < 401; _x += _dx, _i++) {
    _f_setinf(_x);
    _t_finf[_i] = finf;
    _t_ftau[_i] = ftau;
   }
   _sav_celsius = celsius;
  }
 }

 static int setinf(double _lv){ _check_setinf();
 _n_setinf(_lv);
 return 0;
 }

 static void _n_setinf(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_setinf(_lv); return; 
}
 _xi = _mfac_setinf * (_lv - _tmin_setinf);
 if (isnan(_xi)) {
  finf = _xi;
  ftau = _xi;
  return;
 }
 if (_xi <= 0.) {
 finf = _t_finf[0];
 ftau = _t_ftau[0];
 return; }
 if (_xi >= 400.) {
 finf = _t_finf[400];
 ftau = _t_ftau[400];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 finf = _t_finf[_i] + _theta*(_t_finf[_i+1] - _t_finf[_i]);
 ftau = _t_ftau[_i] + _theta*(_t_ftau[_i+1] - _t_ftau[_i]);
 }

 
static int  _f_setinf (  double _lv ) {
   finf = 1.0 / ( 1.0 + exp ( ( _lv + 80.0 ) / 5.5 ) ) ;
   ftau = ( 1.0 / ( exp ( - 15.02 - 0.086 * _lv ) + exp ( - 1.5195 + 0.0701 * _lv ) ) ) / rate_k ;
    return 0; }
 
static void _hoc_setinf(void) {
  double _r;
    _r = 1.;
 setinf (  *getarg(1) );
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
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  f = f0;
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
   setinf ( _threadargscomma_ v ) ;
   f = finf ;
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
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ih = ( gk * gmax_k ) * f * ( v - eih ) ;
   }
 _current += ih;

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
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
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
 { error =  integrate();
 if(error){fprintf(stderr,"at line 64 in file Ih.mod:\n	SOLVE integrate METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = f_columnindex;  _dlist1[0] = Df_columnindex;
   _t_finf = makevector(401*sizeof(double));
   _t_ftau = makevector(401*sizeof(double));
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "Ih.mod";
static const char* nmodl_file_text = 
  "TITLE Potassium Ih channel for STh\n"
  "\n"
  "COMMENT\n"
  " Ih from Huguenard & McCormick 92 LGN relay\n"
  " Magee (1998) shows Ih to have a reversal potential that is ionic non\n"
  " specific with a reversal potential of around -30mV.  \n"
  " Huguenard recordings at 35.5degC. \n"
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
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "}\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX Ih\n"
  "	NONSPECIFIC_CURRENT ih\n"
  "	RANGE gk\n"
  "	GLOBAL eih,activate_Q10,Q10,gmaxQ10,rate_k,gmax_k,temp1,temp2,tempb\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "	dt (ms)\n"
  "	gk    = 0.001 (mho/cm2)\n"
  "	eih   = -5.611047394e+01 (mV)\n"
  "	celsius\n"
  "\n"
  "	activate_Q10 = 1\n"
  "	Q10 = 2.0\n"
  "	gmaxQ10 = 2.0\n"
  "	temp1 = 25.0 (degC)\n"
  "	temp2 = 35.0 (degC)\n"
  "	tempb = 35.5 (degC)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "        f\n"
  "}\n"
  "\n"
  "ASSIGNED { \n"
  "        ih (mA/cm2)\n"
  "	finf  \n"
  "	ftau (ms)\n"
  "	rate_k\n"
  "	gmax_k\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE integrate METHOD cnexp\n"
  "	ih = (gk*gmax_k)*f*(v-eih)\n"
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
  "        setinf(v)\n"
  "	f = finf\n"
  "}\n"
  "\n"
  "DERIVATIVE integrate {\n"
  "        setinf(v)\n"
  "	f' = (finf - f)/ftau\n"
  "}\n"
  "\n"
  "PROCEDURE setinf(v) {\n"
  "                    :Voltage shift (for temp effects) of 5.0.\n"
  "	TABLE finf, ftau DEPEND celsius FROM -100 TO 100 WITH 400\n"
  "\n"
  "	finf = 1.0/(1+exp((v + 80 )/ 5.5))\n"
  "        ftau = (1.0/(exp(-15.02 - 0.086*v)+exp(-1.5195 + 0.0701*v))) /rate_k\n"
  "}\n"
  "\n"
  "UNITSON\n"
  ;
#endif
