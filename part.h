#ifndef _PART_H_
#define _PART_H_

typedef struct
{
     int vgenus;
     int actio;
     int num;
     int casus;
     genus_type ngenus;
     int gradus;
} part_det;

typedef struct
{
     int genus;
     int actio;
} inf_det;

typedef struct
{
     int casus;
} ger_det;

typedef struct
{
     int casus;
} sup_det;

#define PART_IMP1_NOM "ans"
#define PART_IMP1_ROOT "ant"
#define PART_IMP2_NOM "ens"
#define PART_IMP2_ROOT "ent"
#define PART_IMP3_NOM "ens"
#define PART_IMP3_ROOT "ent"
#define PART_IMP3I_NOM "iens"
#define PART_IMP3I_ROOT "ient"
#define PART_IMP4_NOM "iens"
#define PART_IMP4_ROOT "ient"

#define PART_INST_ACT_ROOT "ur"
#define PART_INST_PASS1_ROOT "and"
#define PART_INST_PASS2_ROOT "end"
#define PART_INST_PASS3_ROOT "end"
#define PART_INST_PASS3I_ROOT "iend"
#define PART_INST_PASS4_ROOT "iend"

#define IRI      "iri"
#define ESSE     "esse"

part_det **part_match(char *vword, char *imp_root, char *sup_root, 
		      coni_type typ);
inf_det *inf_match_simple(char *vword, char *imp_root, char *perf_root,
			  coni_type typ);
inf_det *inf_match_compound(char *vword, char *iword2, char *imp_root,
			    char *sup_root, coni_type typ);
ger_det **ger_match(char *vword, char *imp_root, coni_type typ);
sup_det *sup_match(char *vword, char *sup_root, coni_type typ);

part_det **fero_part_match(char *vword, char *imp_pref, char *sup_pref);
inf_det *fero_inf_match_compound(char *vword, char *vword2, char *imp_pref,
				 char *sup_pref);
inf_det *fero_inf_match_simple(char *vword, char *imp_pref, char *perf_pref);
ger_det **fero_ger_match(char *vword, char *imp_pref);
sup_det *fero_sup_match(char *vword, char *sup_pref);

inf_det *sum_inf_match_simple(char *vword);

#endif
