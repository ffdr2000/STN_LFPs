#include <stdio.h>
#include "hocdec.h"
#define IMPORT extern __declspec(dllimport)
IMPORT int nrnmpi_myid, nrn_nobanner_;

extern void _AXNODE75_reg();
extern void _CaT_reg();
extern void _Cacum_reg();
extern void _HVA_reg();
extern void _Ih_reg();
extern void _KDR_reg();
extern void _Kv31_reg();
extern void _Na_reg();
extern void _NaL_reg();
extern void _PARAK75_reg();
extern void _STh_reg();
extern void _ampa_reg();
extern void _gabaa_reg();
extern void _myions_reg();
extern void _sKCa_reg();
extern void _train_reg();

void modl_reg(){
	//nrn_mswindll_stdio(stdin, stdout, stderr);
    if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
	fprintf(stderr, "Additional mechanisms from files\n");

fprintf(stderr," AXNODE75.mod");
fprintf(stderr," CaT.mod");
fprintf(stderr," Cacum.mod");
fprintf(stderr," HVA.mod");
fprintf(stderr," Ih.mod");
fprintf(stderr," KDR.mod");
fprintf(stderr," Kv31.mod");
fprintf(stderr," Na.mod");
fprintf(stderr," NaL.mod");
fprintf(stderr," PARAK75.mod");
fprintf(stderr," STh.mod");
fprintf(stderr," ampa.mod");
fprintf(stderr," gabaa.mod");
fprintf(stderr," myions.mod");
fprintf(stderr," sKCa.mod");
fprintf(stderr," train.mod");
fprintf(stderr, "\n");
    }
_AXNODE75_reg();
_CaT_reg();
_Cacum_reg();
_HVA_reg();
_Ih_reg();
_KDR_reg();
_Kv31_reg();
_Na_reg();
_NaL_reg();
_PARAK75_reg();
_STh_reg();
_ampa_reg();
_gabaa_reg();
_myions_reg();
_sKCa_reg();
_train_reg();
}
