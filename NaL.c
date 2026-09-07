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
 
#define nrn_init _nrn_init__NaL
#define _nrn_initial _nrn_initial__NaL
#define nrn_cur _nrn_cur__NaL
#define _nrn_current _nrn_current__NaL
#define nrn_jacob _nrn_jacob__NaL
#define nrn_state _nrn_state__NaL
#define _net_receive _net_receive__NaL 
 
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
#define inaL _p[1]
#define inaL_columnindex 1
#define ena _p[2]
#define ena_columnindex 2
#define nai _p[3]
#define nai_columnindex 3
#define ina _p[4]
#define ina_columnindex 4
#define _g _p[5]
#define _g_columnindex 5
#define _ion_ena	*_ppvar[0]._pval
#define _ion_nai	*_ppvar[1]._pval
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
 "setdata_NaL", _hoc_setdata,
 0, 0
};
 /* declare global and static user variables */
#define activate_Q10 activate_Q10_NaL
 double activate_Q10 = 1;
#define gmax_k gmax_k_NaL
 double gmax_k = 0;
#define gmaxQ10 gmaxQ10_NaL
 double gmaxQ10 = 1.5;
#define tempb tempb_NaL
 double tempb = 23;
#define temp2 temp2_NaL
 double temp2 = 35;
#define temp1 temp1_NaL
 double temp1 = 25;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "temp1_NaL", "degC",
 "temp2_NaL", "degC",
 "tempb_NaL", "degC",
 "gna_NaL", "mho/cm2",
 "inaL_NaL", "mA/cm2",
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "activate_Q10_NaL", &activate_Q10_NaL,
 "gmaxQ10_NaL", &gmaxQ10_NaL,
 "temp1_NaL", &temp1_NaL,
 "temp2_NaL", &temp2_NaL,
 "tempb_NaL", &tempb_NaL,
 "gmax_k_NaL", &gmax_k_NaL,
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
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"NaL",
 "gna_NaL",
 "inaL_NaL",
 0,
 0,
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 6, _prop);
 	/*initialize range parameters*/
 	gna = 8.1e-06;
 	inaL = 0;
 	_prop->param = _p;
 	_prop->param_size = 6;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[1]; /* nai */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _NaL_reg() {
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
  hoc_register_prop_size(_mechtype, 6, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "na_ion");
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 NaL NaL.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "sodium leak";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 1);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 3, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
{
 {
   double _lktemp , _lktempb , _lktemp1 , _lktemp2 ;
 if ( activate_Q10 > 0.0 ) {
     _lktemp = celsius + 273.0 ;
     _lktempb = tempb + 273.0 ;
     _lktemp1 = temp1 + 273.0 ;
     _lktemp2 = temp2 + 273.0 ;
     gmax_k = exp ( log ( gmaxQ10 ) * ( ( 1.0 / _lktempb ) - ( 1.0 / _lktemp ) ) / ( ( 1.0 / _lktemp1 ) - ( 1.0 / _lktemp2 ) ) ) ;
     }
   else {
     gmax_k = 1.0 ;
     }
   }

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
  ena = _ion_ena;
  nai = _ion_nai;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ina = gna * gmax_k * ( v - ena ) ;
   inaL = ina ;
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
  ena = _ion_ena;
  nai = _ion_nai;
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

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "NaL.mod";
static const char* nmodl_file_text = 
  "TITLE sodium leak\n"
  "\n"
  "COMMENT \n"
  "\n"
  " Sodium leak.  This TTX sensitive sodium current is active\n"
  " between spikes and has some voltage dependence (although no\n"
  " inactivation that I know of) (Do & Bean 2003).  I based the\n"
  " voltage dependence of this channel on the Do & Bean data, but found a\n"
  " pure leak had the same effect, so I stuck to the pure leak..\n"
  "\n"
  " How the q10 works: There is a q10 for the rates (alpha and beta's)\n"
  " called Q10 and a Q10 for the maximum conductance called gmaxQ10.\n"
  " Here, we only use gmaxQ10.  The q10s should have been measured at\n"
  " specific temperatures temp1 and temp2 (that are 10degC\n"
  " apart). Ideally, as Q10 is temperature dependant, we should know\n"
  " these two temperatures.  We are going to follow the more formal\n"
  " Arrhenius derived Q10 approach.  The temperature at which this\n"
  " channel's kinetics were recorded is tempb (base temperature).  What\n"
  " we then need to calculate is the desired rate scale for now working\n"
  " at temperature celsius (rate_k).  This is given by the empirical\n"
  " Arrhenius equation, using the Q10. \n"
  "ENDCOMMENT\n"
  "\n"
  "UNITS {\n"
  "      (mv) = (millivolt)\n"
  "      (mA) = (milliamp)\n"
  "}\n"
  "\n"
  "NEURON {\n"
  "       SUFFIX NaL\n"
  "       USEION na READ ena,nai WRITE ina\n"
  "       RANGE gna,inaL\n"
  "       GLOBAL activate_Q10,gmaxQ10,gmax_k,temp1,temp2,tempb\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "	gna = 0.81e-5 (mho/cm2)\n"
  "	inaL = 0.0 (mA/cm2)\n"
  "	ena\n"
  "	nai\n"
  "	celsius\n"
  "\n"
  "	activate_Q10 = 1\n"
  "	gmaxQ10 = 1.5\n"
  "	temp1 = 25.0 (degC)\n"
  "	temp2 = 35.0 (degC)\n"
  "	tempb = 23.0 (degC)	\n"
  "}\n"
  "\n"
  "ASSIGNED { \n"
  "        ina (mA/cm2)\n"
  "	gmax_k\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	   ina	= gna*gmax_k*(v-ena)\n"
  "	   inaL = ina\n"
  "}\n"
  "UNITSOFF\n"
  "\n"
  "INITIAL {\n"
  "	LOCAL ktemp,ktempb,ktemp1,ktemp2\n"
  "	if (activate_Q10>0) {\n"
  "	  ktemp  = celsius+273.0\n"
  "	  ktempb = tempb+273.0\n"
  "	  ktemp1 = temp1+273.0\n"
  "	  ktemp2 = temp2+273.0\n"
  "	  gmax_k = exp( log(gmaxQ10)*((1/ktempb)-(1/ktemp))/((1/ktemp1)-(1/ktemp2)) )\n"
  "	}else{\n"
  "	  gmax_k = 1.0\n"
  "	}\n"
  "}	\n"
  "UNITSON\n"
  ;
#endif
