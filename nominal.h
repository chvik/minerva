#ifndef _NOMINAL_H_
#define _NOMINAL_H_

typedef int decl_type;

typedef int genus_type;

typedef struct 
{
     int num;
     int casus;
} noun_det;

typedef struct
{
     int gradus;
     genus_type genus;
     int num;
     int casus;
} adj_det;

typedef struct
{
     int gradus;
} adv_det;

#define DECL_INFO 7

#define DECL1     1
#define DECL2     2
#define DECL2_0   8
#define DECL2_ER 16
#define DECL3     3
#define DECL3_I1  8 /* Csak plur. gen-ban. */
#define DECL3_I2 16 /* Sing. abl-ban is. */
#define DECL3_I  (DECL3_I1 | DECL3_I2)
#define DECL4     4
#define DECL5     5

#define END_INFO 7

#define END3        1
#define END3_0      8
#define END3_ER    16
#define DECL3_END3  2
#define DECL3_END3_ER 8
#define DECL3_END2  3
#define DECL3_END1  4
#define DECL3_NOT_I 8
#define COMP_IRREG 32
#define SUPER_IRREG 1024
#define SUPER_IRREG_L 64
#define ADV_IRREG 128
#define NO_COMP   256
#define NO_SUPER  512

#define MASC  0
#define FEMI  1
#define NEUT  2
#define ADV  10

#define SING  0
#define PLUR  1

#define NOM   0
#define ACC   1
#define GEN   2
#define DAT   3
#define ABL   4

#define POSIT    0
#define COMPAR   1
#define SUPERLAT 2

noun_det **noun_match(char *sword, char *nroot, decl_type typ, genus_type gen,
		      ...);
adj_det **adj_match(char *aword, char *aroot, decl_type typ, ...);
char *noun_form(char *nroot, decl_type typ, genus_type genus, ...);
char *adj_form(char *aroot, decl_type typ, ...);
adv_det *adv_match(char *aword, char *aroot, decl_type typ);

#endif
