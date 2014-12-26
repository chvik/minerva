#ifndef _VERB_H_
#define _VERB_H_

typedef int coni_type;

typedef struct
{
     int genus;
     int modus;
     int tempus;
     int actio;
     int num;
     int pers;
} verb_det;

#define CONI_INFO 7

#define CONI1    1
#define CONI2    2
#define CONI3    3
#define CONI3I   5
#define CONI4    4
#define FERO_TYPE 6
#define CONI1_IRR 8

#define DEPONENS 16
#define SEMI_DEPONENS 32
#define SHORT_IMPTIV 64
#define NO_SUPINUM 128
#define NO_PERFECTUM 256

#define ACT  0
#define PASS 1

#define IND  0
#define CON  1
#define IMPTIV1 2
#define IMPTIV2 3

#define PRAES 0
#define PRAET 1
#define FUT   2

#define IMP  0
#define PERF 1
#define INST 2

#define SING 0
#define PLUR 1

#define P1 0
#define P2 1
#define P3 2

#define CONI1_ROOT "a"
#define CONI2_ROOT "e"
#define VOICE_I "i"
#define VOICE_U "u"
#define VOICE_E "e"

#define CONI4_ROOT "i"

#define CONI1_PERF "av"
#define CONI1_SUP  "at"

#define CONI1_INF_ACT "are"
#define CONI2_INF_ACT "ere"
#define CONI3_INF_ACT "ere"
#define CONI4_INF_ACT "ire"

#define CONI1_INF_PASS "ari"
#define CONI2_INF_PASS "eri"
#define CONI3_INF_PASS "i"
#define CONI4_INF_PASS "iri"

#define INF_PERF_ACT "isse"

#define SUP_ACC "um"
#define SUP_ABL "u"


/* persona-numerus-actio-tempus-modus-genus order */

char *coni1_table[2][2][3][2][2][2]; 
char *coni2_table[2][2][3][2][2][2];
char *coni3_table[2][2][3][2][2][2];
char *coni4_table[2][2][3][2][2][2]; 

char *coni_table[4][2][2][3][2][2][2];


#define SUM_PERF "fu"
#define SUM_FORM "sum, esse, fui"
#define SUM_MEAN "van, létezik"
#define SUM_INF_ACT "esse"

#define FERO_INF_ACT  "ferre"
#define FERO_INF_PASS "ferri"
#define FERO_IMP  "fer"
#define FERO_PERF "tul"
#define FERO_SUP  "lat"
#define FERO_MEAN "hoz, visz, terem, szül, elvisel; híresztel, vél; (pass.) jár, siet"

char *verb_form(char *imp_root, char *perf_root, char *sup_root,
		coni_type typ);
verb_det **verb_match_simple(char *vword, char *imp_root, char *perf_root,
			     coni_type typ);
verb_det **verb_match_compound(char *vword, char *vword2, char *imp_root,
		      char *sup_root, coni_type typ);
verb_det **sum_match(char *vword);

char *fero_form(char *imp_pref, char *perf_pref, char *sup_pref);

verb_det **fero_match_simple(char *vword, char *imp_pref, char *perf_pref);

verb_det **fero_match_compound(char *vword, char *vword2, char *imp_pref,
			  char *sup_pref);

#endif
