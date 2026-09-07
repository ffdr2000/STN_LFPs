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
 
#define nrn_init _nrn_init__CaT
#define _nrn_initial _nrn_initial__CaT
#define nrn_cur _nrn_cur__CaT
#define _nrn_current _nrn_current__CaT
#define nrn_jacob _nrn_jacob__CaT
#define nrn_state _nrn_state__CaT
#define _net_receive _net_receive__CaT 
#define _f_settables _f_settables__CaT 
#define settables settables__CaT 
#define states states__CaT 
 
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
#define gcaT _p[0]
#define gcaT_columnindex 0
#define iCaT _p[1]
#define iCaT_columnindex 1
#define r _p[2]
#define r_columnindex 2
#define s _p[3]
#define s_columnindex 3
#define d _p[4]
#define d_columnindex 4
#define eca _p[5]
#define eca_columnindex 5
#define cai _p[6]
#define cai_columnindex 6
#define cao _p[7]
#define cao_columnindex 7
#define Dr _p[8]
#define Dr_columnindex 8
#define Ds _p[9]
#define Ds_columnindex 9
#define Dd _p[10]
#define Dd_columnindex 10
#define ica _p[11]
#define ica_columnindex 11
#define ralpha _p[12]
#define ralpha_columnindex 12
#define rbeta _p[13]
#define rbeta_columnindex 13
#define salpha _p[14]
#define salpha_columnindex 14
#define sbeta _p[15]
#define sbeta_columnindex 15
#define dalpha _p[16]
#define dalpha_columnindex 16
#define dbeta _p[17]
#define dbeta_columnindex 17
#define _g _p[18]
#define _g_columnindex 18
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
 "setdata_CaT", _hoc_setdata,
 "ghkg_CaT", _hoc_ghkg,
 "settables_CaT", _hoc_settables,
 0, 0
};
#define ghkg ghkg_CaT
 extern double ghkg( double , double , double , double );
 /* declare global and static user variables */
#define Q10 Q10_CaT
 double Q10 = 1.5158;
#define activate_Q10 activate_Q10_CaT
 double activate_Q10 = 1;
#define gmax_k gmax_k_CaT
 double gmax_k = 0;
#define gmaxQ10 gmaxQ10_CaT
 double gmaxQ10 = 1.5158;
#define rate_k rate_k_CaT
 double rate_k = 0;
#define tempb tempb_CaT
 double tempb = 23;
#define temp2 temp2_CaT
 double temp2 = 29;
#define temp1 temp1_CaT
 double temp1 = 19;
#define usetable usetable_CaT
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_CaT", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "temp1_CaT", "degC",
 "temp2_CaT", "degC",
 "tempb_CaT", "degC",
 "gcaT_CaT", "mho/cm2",
 "iCaT_CaT", "mA/cm2",
 0,0
};
 static double delta_t = 1;
 static double d0 = 0;
 static double r0 = 0;
 static double s0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "activate_Q10_CaT", &activate_Q10_CaT,
 "Q10_CaT", &Q10_CaT,
 "gmaxQ10_CaT", &gmaxQ10_CaT,
 "temp1_CaT", &temp1_CaT,
 "temp2_CaT", &temp2_CaT,
 "tempb_CaT", &tempb_CaT,
 "rate_k_CaT", &rate_k_CaT,
 "gmax_k_CaT", &gmax_k_CaT,
 "usetable_CaT", &usetable_CaT,
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
"CaT",
 "gcaT_CaT",
 "iCaT_CaT",
 0,
 0,
 "r_CaT",
 "s_CaT",
 "d_CaT",
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 19, _prop);
 	/*initialize range parameters*/
 	gcaT = 0.001;
 	iCaT = 0;
 	_prop->param = _p;
 	_prop->param_size = 19;
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

 void _CaT_reg() {
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
  hoc_register_prop_size(_mechtype, 19, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 CaT CaT.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define FARADAY _nrnunit_FARADAY[_nrnunit_use_legacy_]
static double _nrnunit_FARADAY[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
 
#define R _nrnunit_R[_nrnunit_use_legacy_]
static double _nrnunit_R[2] = {0x1.0a1013e8990bep+3, 8.3145}; /* 8.3144626181532395 */
 static double *_t_ralpha;
 static double *_t_rbeta;
 static double *_t_salpha;
 static double *_t_sbeta;
 static double *_t_dalpha;
 static double *_t_dbeta;
static int _reset;
static char *modelname = "calcium T channel for STh";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_settables(double);
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
   Dr = ( ( ralpha * ( 1.0 - r ) ) - ( rbeta * r ) ) ;
   Dd = ( ( dbeta * ( 1.0 - s - d ) ) - ( dalpha * d ) ) ;
   Ds = ( ( salpha * ( 1.0 - s - d ) ) - ( sbeta * s ) ) ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 settables ( _threadargscomma_ v ) ;
 Dr = Dr  / (1. - dt*( ( ( ( ralpha )*( ( ( - 1.0 ) ) ) ) - ( ( rbeta )*( 1.0 ) ) ) )) ;
 Dd = Dd  / (1. - dt*( ( ( ( dbeta )*( ( ( - 1.0 ) ) ) ) - ( ( dalpha )*( 1.0 ) ) ) )) ;
 Ds = Ds  / (1. - dt*( ( ( ( salpha )*( ( ( - 1.0 ) ) ) ) - ( ( sbeta )*( 1.0 ) ) ) )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   settables ( _threadargscomma_ v ) ;
    r = r + (1. - exp(dt*(( ( ( ralpha )*( ( ( - 1.0 ) ) ) ) - ( ( rbeta )*( 1.0 ) ) ))))*(- ( ( ( ( ralpha )*( ( 1.0 ) ) ) ) ) / ( ( ( ( ralpha )*( ( ( - 1.0 ) ) ) ) - ( ( rbeta )*( 1.0 ) ) ) ) - r) ;
    d = d + (1. - exp(dt*(( ( ( dbeta )*( ( ( - 1.0 ) ) ) ) - ( ( dalpha )*( 1.0 ) ) ))))*(- ( ( ( ( dbeta )*( ( 1.0 - s ) ) ) ) ) / ( ( ( ( dbeta )*( ( ( - 1.0 ) ) ) ) - ( ( dalpha )*( 1.0 ) ) ) ) - d) ;
    s = s + (1. - exp(dt*(( ( ( salpha )*( ( ( - 1.0 ) ) ) ) - ( ( sbeta )*( 1.0 ) ) ))))*(- ( ( ( ( salpha )*( ( 1.0 - d ) ) ) ) ) / ( ( ( ( salpha )*( ( ( - 1.0 ) ) ) ) - ( ( sbeta )*( 1.0 ) ) ) ) - s) ;
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
    _t_ralpha[_i] = ralpha;
    _t_rbeta[_i] = rbeta;
    _t_salpha[_i] = salpha;
    _t_sbeta[_i] = sbeta;
    _t_dalpha[_i] = dalpha;
    _t_dbeta[_i] = dbeta;
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
  ralpha = _xi;
  rbeta = _xi;
  salpha = _xi;
  sbeta = _xi;
  dalpha = _xi;
  dbeta = _xi;
  return;
 }
 if (_xi <= 0.) {
 ralpha = _t_ralpha[0];
 rbeta = _t_rbeta[0];
 salpha = _t_salpha[0];
 sbeta = _t_sbeta[0];
 dalpha = _t_dalpha[0];
 dbeta = _t_dbeta[0];
 return; }
 if (_xi >= 400.) {
 ralpha = _t_ralpha[400];
 rbeta = _t_rbeta[400];
 salpha = _t_salpha[400];
 sbeta = _t_sbeta[400];
 dalpha = _t_dalpha[400];
 dbeta = _t_dbeta[400];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 ralpha = _t_ralpha[_i] + _theta*(_t_ralpha[_i+1] - _t_ralpha[_i]);
 rbeta = _t_rbeta[_i] + _theta*(_t_rbeta[_i+1] - _t_rbeta[_i]);
 salpha = _t_salpha[_i] + _theta*(_t_salpha[_i+1] - _t_salpha[_i]);
 sbeta = _t_sbeta[_i] + _theta*(_t_sbeta[_i+1] - _t_sbeta[_i]);
 dalpha = _t_dalpha[_i] + _theta*(_t_dalpha[_i+1] - _t_dalpha[_i]);
 dbeta = _t_dbeta[_i] + _theta*(_t_dbeta[_i+1] - _t_dbeta[_i]);
 }

 
static int  _f_settables (  double _lv ) {
   double _lbd ;
 ralpha = rate_k * 1.0 / ( 1.7 + exp ( - ( _lv + 26.2722 ) / 13.5 ) ) ;
   rbeta = rate_k * exp ( - ( _lv + 61.0722 ) / 7.8 ) / ( exp ( - ( _lv + 26.8722 ) / 13.1 ) + 1.7 ) ;
   salpha = rate_k * exp ( - ( _lv + 158.3722 ) / 17.8 ) ;
   sbeta = rate_k * ( sqrt ( 0.25 + exp ( ( _lv + 81.5722 ) / 6.3 ) ) - 0.5 ) * ( exp ( - ( _lv + 158.3722 ) / 17.8 ) ) ;
   _lbd = sqrt ( 0.25 + exp ( ( _lv + 81.5722 ) / 6.3 ) ) ;
   dalpha = rate_k * ( 1.0 + exp ( ( _lv + 35.4722 ) / 30.0 ) ) / ( 240.0 * ( 0.5 + _lbd ) ) ;
   dbeta = rate_k * ( _lbd - 0.5 ) * dalpha ;
    return 0; }
 
static void _hoc_settables(void) {
  double _r;
    _r = 1.;
 settables (  *getarg(1) );
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
  d = d0;
  r = r0;
  s = s0;
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
   r = ralpha / ( ralpha + rbeta ) ;
   s = ( salpha * ( dbeta + dalpha ) - ( salpha * dbeta ) ) / ( ( salpha + sbeta ) * ( dalpha + dbeta ) - ( salpha * dbeta ) ) ;
   d = ( dbeta * ( salpha + sbeta ) - ( salpha * dbeta ) ) / ( ( salpha + sbeta ) * ( dalpha + dbeta ) - ( salpha * dbeta ) ) ;
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
   ica = ( gcaT * gmax_k ) * r * r * r * s * ghkg ( _threadargscomma_ v , cai , cao , 2.0 ) ;
   iCaT = ica ;
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
 if(error){fprintf(stderr,"at line 70 in file CaT.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = r_columnindex;  _dlist1[0] = Dr_columnindex;
 _slist1[1] = d_columnindex;  _dlist1[1] = Dd_columnindex;
 _slist1[2] = s_columnindex;  _dlist1[2] = Ds_columnindex;
   _t_ralpha = makevector(401*sizeof(double));
   _t_rbeta = makevector(401*sizeof(double));
   _t_salpha = makevector(401*sizeof(double));
   _t_sbeta = makevector(401*sizeof(double));
   _t_dalpha = makevector(401*sizeof(double));
   _t_dbeta = makevector(401*sizeof(double));
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "CaT.mod";
static const char* nmodl_file_text = 
  "TITLE calcium T channel for STh\n"
  "\n"
  "COMMENT\n"
  " Low threshold calcium channel (T-type), Wang et al. 1991 \n"
  " & Coulter et al 1989.  The original data was recorded at 22-24degC. \n"
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
  "     FARADAY = (faraday) (coulomb)\n"
  "           R = (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX CaT\n"
  "	USEION ca READ cai,cao,eca WRITE ica\n"
  "	RANGE gcaT, iCaT\n"
  "	GLOBAL activate_Q10,Q10,gmaxQ10,rate_k,gmax_k,temp1,temp2,tempb\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "	dt (ms)\n"
  "	gcaT  = 0.001 (mho/cm2)\n"
  "	iCaT  = 0.0 (mA/cm2)\n"
  "	eca\n"
  "	cai\n"
  "	cao\n"
  "	celsius\n"
  "\n"
  "	activate_Q10 = 1\n"
  "	Q10 = 1.515804730e+00\n"
  "	gmaxQ10 = 1.515804730e+00\n"
  "	temp1 = 19.0 (degC)\n"
  "	temp2 = 29.0 (degC)\n"
  "	tempb = 23.0 (degC)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "        r s d\n"
  "}\n"
  "\n"
  "ASSIGNED { \n"
  "        ica (mA/cm2)\n"
  "	ralpha (/ms)\n"
  "	rbeta (/ms)\n"
  "	salpha (/ms)\n"
  "	sbeta (/ms)\n"
  "	dalpha (/ms)\n"
  "	dbeta (/ms)\n"
  "	rate_k\n"
  "	gmax_k\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	ica  = (gcaT*gmax_k)*r*r*r*s*ghkg(v,cai,cao,2)\n"
  "	iCaT = ica\n"
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
  "        r = ralpha/(ralpha+rbeta)\n"
  "        s = (salpha*(dbeta+dalpha) - (salpha*dbeta))/((salpha+sbeta)*(dalpha+dbeta) - (salpha*dbeta))\n"
  "	d = (dbeta*(salpha+sbeta) - (salpha*dbeta))/((salpha+sbeta)*(dalpha+dbeta) - (salpha*dbeta))\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  \n"
  "	settables(v)      :Computes state variables at the current v and dt.\n"
  "	r' = ((ralpha*(1-r)) - (rbeta*r))\n"
  "	d' = ((dbeta*(1-s-d)) - (dalpha*d))\n"
  "	s' = ((salpha*(1-s-d)) - (sbeta*s))\n"
  "}\n"
  "\n"
  "PROCEDURE settables(v) {  :Computes rate and other constants at current v.\n"
  "                          :Call once from HOC to initialize inf at resting v.\n"
  "			  :Voltage shift (for temp effects) of -1.9278 added\n"
  "        LOCAL   bd\n"
  "        TABLE ralpha, rbeta, salpha, sbeta, dalpha, dbeta DEPEND celsius FROM -100 TO 100 WITH 400\n"
  "\n"
  "		:\"r\" CaT activation system\n"
  "	ralpha = rate_k * 1.0/(1.7+exp(-(v + 26.2722)/13.5))\n"
  "	rbeta  = rate_k * exp(-(v + 61.0722)/7.8)/(exp(-(v + 26.8722)/13.1)+1.7)\n"
  "\n"
  "                :\"s\" CaT fast inactivation system\n"
  "        salpha = rate_k * exp(-(v + 158.3722)/17.8)\n"
  "        sbeta  = rate_k * (sqrt(0.25+exp((v + 81.5722)/6.3))-0.5) * (exp(-(v + 158.3722)/17.8))\n"
  "\n"
  "	        :\"d\" CaT slow inactivation system\n"
  "	bd     = sqrt(0.25+exp((v + 81.5722)/6.3))\n"
  "	dalpha = rate_k * (1.0+exp((v + 35.4722)/30.0))/(240.0*(0.5+bd))\n"
  "        dbeta  = rate_k * (bd-0.5)*dalpha\n"
  "}\n"
  "\n"
  "UNITSON\n"
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
  ;
#endif
