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
 
#define nrn_init _nrn_init__Na
#define _nrn_initial _nrn_initial__Na
#define nrn_cur _nrn_cur__Na
#define _nrn_current _nrn_current__Na
#define nrn_jacob _nrn_jacob__Na
#define nrn_state _nrn_state__Na
#define _net_receive _net_receive__Na 
#define _f_settables _f_settables__Na 
#define settables settables__Na 
#define states states__Na 
 
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
#define gna _p[0]
#define gna_columnindex 0
#define m _p[1]
#define m_columnindex 1
#define h _p[2]
#define h_columnindex 2
#define ena _p[3]
#define ena_columnindex 3
#define nai _p[4]
#define nai_columnindex 4
#define Dm _p[5]
#define Dm_columnindex 5
#define Dh _p[6]
#define Dh_columnindex 6
#define ina _p[7]
#define ina_columnindex 7
#define alpham _p[8]
#define alpham_columnindex 8
#define betam _p[9]
#define betam_columnindex 9
#define alphah _p[10]
#define alphah_columnindex 10
#define betah _p[11]
#define betah_columnindex 11
#define _g _p[12]
#define _g_columnindex 12
#define _ion_nai	*_ppvar[0]._pval
#define _ion_ena	*_ppvar[1]._pval
#define _ion_ina	*_ppvar[2]._pval
#define _ion_dinadv	*_ppvar[3]._pval
 
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
 static void _hoc_vtrap(void);
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
 "setdata_Na", _hoc_setdata,
 "settables_Na", _hoc_settables,
 "vtrap_Na", _hoc_vtrap,
 0, 0
};
#define vtrap vtrap_Na
 extern double vtrap( double , double );
 /* declare global and static user variables */
#define Q10 Q10_Na
 double Q10 = 1.98011;
#define activate_Q10 activate_Q10_Na
 double activate_Q10 = 1;
#define gmax_k gmax_k_Na
 double gmax_k = 0;
#define gmaxQ10 gmaxQ10_Na
 double gmaxQ10 = 1.98011;
#define rate_k rate_k_Na
 double rate_k = 0;
#define rest rest_Na
 double rest = -60;
#define tempb tempb_Na
 double tempb = 23;
#define temp2 temp2_Na
 double temp2 = 29;
#define temp1 temp1_Na
 double temp1 = 19;
#define usetable usetable_Na
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_Na", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "rest_Na", "mV",
 "temp1_Na", "degC",
 "temp2_Na", "degC",
 "tempb_Na", "degC",
 "gna_Na", "mho/cm2",
 0,0
};
 static double delta_t = 1;
 static double h0 = 0;
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "rest_Na", &rest_Na,
 "activate_Q10_Na", &activate_Q10_Na,
 "Q10_Na", &Q10_Na,
 "gmaxQ10_Na", &gmaxQ10_Na,
 "temp1_Na", &temp1_Na,
 "temp2_Na", &temp2_Na,
 "tempb_Na", &tempb_Na,
 "rate_k_Na", &rate_k_Na,
 "gmax_k_Na", &gmax_k_Na,
 "usetable_Na", &usetable_Na,
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
"Na",
 "gna_Na",
 0,
 0,
 "m_Na",
 "h_Na",
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 13, _prop);
 	/*initialize range parameters*/
 	gna = 1e-07;
 	_prop->param = _p;
 	_prop->param_size = 13;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* nai */
 	_ppvar[1]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
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

 void _Na_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 13, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Na Na.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double *_t_alpham;
 static double *_t_betam;
 static double *_t_alphah;
 static double *_t_betah;
static int _reset;
static char *modelname = "sodium membrane channels for STh";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_settables(double);
static int settables(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_settables(double);
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   settables ( _threadargscomma_ v ) ;
   Dm = alpham * ( 1.0 - m ) - betam * m ;
   Dh = alphah * ( 1.0 - h ) - betah * h ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 settables ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( alpham )*( ( ( - 1.0 ) ) ) - ( betam )*( 1.0 ) )) ;
 Dh = Dh  / (1. - dt*( ( alphah )*( ( ( - 1.0 ) ) ) - ( betah )*( 1.0 ) )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   settables ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( alpham )*( ( ( - 1.0 ) ) ) - ( betam )*( 1.0 ))))*(- ( ( alpham )*( ( 1.0 ) ) ) / ( ( alpham )*( ( ( - 1.0 ) ) ) - ( betam )*( 1.0 ) ) - m) ;
    h = h + (1. - exp(dt*(( alphah )*( ( ( - 1.0 ) ) ) - ( betah )*( 1.0 ))))*(- ( ( alphah )*( ( 1.0 ) ) ) / ( ( alphah )*( ( ( - 1.0 ) ) ) - ( betah )*( 1.0 ) ) - h) ;
   }
  return 0;
}
 static double _mfac_settables, _tmin_settables;
 static void _check_settables();
 static void _check_settables() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_rest;
  static double _sav_celsius;
  if (!usetable) {return;}
  if (_sav_rest != rest) { _maktable = 1;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_settables =  - 100.0 ;
   _tmax =  100.0 ;
   _dx = (_tmax - _tmin_settables)/400.; _mfac_settables = 1./_dx;
   for (_i=0, _x=_tmin_settables; _i < 401; _x += _dx, _i++) {
    _f_settables(_x);
    _t_alpham[_i] = alpham;
    _t_betam[_i] = betam;
    _t_alphah[_i] = alphah;
    _t_betah[_i] = betah;
   }
   _sav_rest = rest;
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
  alpham = _xi;
  betam = _xi;
  alphah = _xi;
  betah = _xi;
  return;
 }
 if (_xi <= 0.) {
 alpham = _t_alpham[0];
 betam = _t_betam[0];
 alphah = _t_alphah[0];
 betah = _t_betah[0];
 return; }
 if (_xi >= 400.) {
 alpham = _t_alpham[400];
 betam = _t_betam[400];
 alphah = _t_alphah[400];
 betah = _t_betah[400];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 alpham = _t_alpham[_i] + _theta*(_t_alpham[_i+1] - _t_alpham[_i]);
 betam = _t_betam[_i] + _theta*(_t_betam[_i+1] - _t_betam[_i]);
 alphah = _t_alphah[_i] + _theta*(_t_alphah[_i+1] - _t_alphah[_i]);
 betah = _t_betah[_i] + _theta*(_t_betah[_i+1] - _t_betah[_i]);
 }

 
static int  _f_settables (  double _lv ) {
   double _lvadj ;
 _lvadj = _lv - rest ;
   alpham = rate_k * 0.2 * vtrap ( _threadargscomma_ ( 13.1 - _lvadj ) , 4.0 ) ;
   betam = rate_k * 0.175 * vtrap ( _threadargscomma_ ( _lvadj - 40.1 ) , 1.0 ) ;
   alphah = rate_k * 0.08 * exp ( ( 17.0 - _lvadj ) / 18.0 ) ;
   betah = rate_k * 2.5 / ( exp ( ( 40.0 - _lvadj ) / 5.0 ) + 1.0 ) ;
    return 0; }
 
static void _hoc_settables(void) {
  double _r;
    _r = 1.;
 settables (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double vtrap (  double _lx , double _ly ) {
   double _lvtrap;
 if ( fabs ( _lx / _ly ) < 1e-6 ) {
     _lvtrap = _ly * ( 1.0 - _lx / _ly / 2.0 ) ;
     }
   else {
     _lvtrap = _lx / ( exp ( _lx / _ly ) - 1.0 ) ;
     }
   
return _lvtrap;
 }
 
static void _hoc_vtrap(void) {
  double _r;
   _r =  vtrap (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  nai = _ion_nai;
  ena = _ion_ena;
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
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
  nai = _ion_nai;
  ena = _ion_ena;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 3, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  m = m0;
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
     rate_k = 1.60 ;
     gmax_k = 1.60 ;
     }
   settables ( _threadargscomma_ v ) ;
   m = alpham / ( alpham + betam ) ;
   h = alphah / ( alphah + betah ) ;
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
  nai = _ion_nai;
  ena = _ion_ena;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ina = ( gna * gmax_k ) * m * m * h * ( v - ena ) ;
   }
 _current += ina;

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
  nai = _ion_nai;
  ena = _ion_ena;
 _g = _nrn_current(_v + .001);
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
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
  nai = _ion_nai;
  ena = _ion_ena;
 { error =  states();
 if(error){fprintf(stderr,"at line 67 in file Na.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_columnindex;  _dlist1[0] = Dm_columnindex;
 _slist1[1] = h_columnindex;  _dlist1[1] = Dh_columnindex;
   _t_alpham = makevector(401*sizeof(double));
   _t_betam = makevector(401*sizeof(double));
   _t_alphah = makevector(401*sizeof(double));
   _t_betah = makevector(401*sizeof(double));
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "Na.mod";
static const char* nmodl_file_text = 
  "TITLE sodium membrane channels for STh\n"
  "\n"
  "COMMENT\n"
  " Sodium from pyramidal, Traub 91.  He based them on Sah (1988) data,\n"
  " which were at 22degC, but he scaled them so that they \"were fast\n"
  " enough\"?  The Q10 measured from Sah (at least for the peak\n"
  " conductance) was 1.5\n"
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
  "	SUFFIX Na\n"
  "	USEION na READ nai,ena WRITE ina\n"
  "	RANGE gna, m, h\n"
  "	GLOBAL rest,activate_Q10,Q10,gmaxQ10,rate_k,gmax_k,temp1,temp2,tempb\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "	dt (ms)\n"
  "	gna   = 1.0e-7 (mho/cm2)\n"
  "	rest  = -60.0 (mV) : for conversion from Traub WAS -60\n"
  "	ena\n"
  "	nai\n"
  "	celsius\n"
  "	\n"
  "	activate_Q10 = 1\n"
  "	Q10 = 1.980105147e+00\n"
  "	gmaxQ10 = 1.980105147e+00\n"
  "	temp1 = 19.0 (degC)\n"
  "	temp2 = 29.0 (degC)\n"
  "	tempb = 23.0 (degC)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "        m h  \n"
  "}\n"
  "\n"
  "ASSIGNED { \n"
  "        ina (mA/cm2)\n"
  "	alpham (/ms)\n"
  "	betam (/ms)\n"
  "	alphah (/ms)\n"
  "	betah (/ms)\n"
  "	rate_k\n"
  "	gmax_k\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	ina  = (gna*gmax_k)*m*m*h*(v-ena)\n"
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
  "	  : Note, its not 1.0, as we have rescaled the kinetics\n"
  "          :  (reverting the scaleing Traub did), the original is\n"
  "          :  acheived using this rate\n"
  "	  rate_k = 1.60\n"
  "	  gmax_k = 1.60\n"
  "	}\n"
  "        settables(v)\n"
  "        m = alpham/(alpham+betam)\n"
  "        h = alphah/(alphah+betah)\n"
  "\n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "	settables(v)      :Computes state variables at the current v and dt.\n"
  "	m' = alpham * (1-m) - betam * m\n"
  "	h' = alphah * (1-h) - betah * h\n"
  "}\n"
  "\n"
  "PROCEDURE settables(v) {  :Computes rate and other constants at current v.\n"
  "                      :Call once from HOC to initialize inf at resting v.\n"
  "        LOCAL vadj\n"
  "        TABLE alpham, betam, alphah, betah DEPEND rest,celsius FROM -100 TO 100 WITH 400\n"
  "	vadj  = v - rest\n"
  "\n"
  "		:\"m\" sodium activation system\n"
  "	alpham = rate_k * 0.2 * vtrap((13.1-vadj),4.0)\n"
  "        betam =  rate_k * 0.175 * vtrap((vadj-40.1),1.0)\n"
  "\n"
  "                :\"h\" sodium inactivation system\n"
  "        alphah = rate_k * 0.08 * exp((17.0-vadj)/18.0)\n"
  "        betah = rate_k * 2.5 / (exp((40.0-vadj)/5.0) + 1)\n"
  "}\n"
  "\n"
  "FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.\n"
  "        if (fabs(x/y) < 1e-6) {\n"
  "                vtrap = y*(1 - x/y/2)\n"
  "        }else{\n"
  "                vtrap = x/(exp(x/y) - 1)\n"
  "        }\n"
  "}\n"
  " \n"
  "UNITSON\n"
  "\n"
  ;
#endif
