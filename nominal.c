#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "nominal.h"
#include "latin.h"
#include "nomtab.h"

#define SING_NEUT_2  "um"
#define SING_NEUT_4  "u"
#define PLUR_NEUT    "a"
#define PLUR_NEUT_4  "ua"
#define SING_MASC_ER "er"
#define SING_FEMI_IS "is"
#define SING_NEUT_E  "e"
#define SING_ABL_I   "i"
#define PLUR_GEN_I   "ium"
#define PLUR_NEUT_I  "ia"

#define COMPAR_MF "ior"
#define COMPAR_N "ius"
#define SUPER "issim"
#define SUPER_R "rim"
#define SUPER_L "lim"

#define ADVERB      "e"
#define ADVERB_COMP "iter"
#define ADVERB_COMP_PART "er"

extern char *ttngen[];

char *noun_form(char *nroot, decl_type typ, genus_type genus, ...)
/* További argumentum: char *nom */
{
     char *form;
     char nom[50], genit[50];
     va_list args;

     form = (char *) malloc(70);
     if((typ & DECL_INFO) == DECL1)
     {
	  strcpy(nom, nroot);
	  strcat(nom, decl1_table[SING][NOM]);
	  sprintf(genit, "-%s", decl1_table[SING][GEN]);
     }
     else if((typ & DECL_INFO) == DECL2)
     {
	  sprintf(genit, "-%s", decl2_table[SING][GEN]);
	  if(genus == NEUT)
	  {
	       strcpy(nom, nroot);
	       strcat(nom, SING_NEUT_2);
	  }
	  else if(typ & DECL2_0)
	  {
	       strcpy(nom, nroot);
	  }
	  else if(typ & DECL2_ER)
	  {
	       strncpy(nom, nroot, strlen(nroot) - 1);
	       nom[strlen(nroot) - 1] = 0;
	       strcat(nom, SING_MASC_ER);
	       strcpy(genit, nroot);
	       strcat(genit, decl2_table[SING][GEN]);
	  } else
	  {
	       strcpy(nom, nroot);
	       strcat(nom, decl2_table[SING][NOM]);
	  }
     }
     else if((typ & DECL_INFO) == DECL3)
     {
	  va_start(args, genus);
	  //strcpy(nom, *(char **)args);
	  strcpy(nom, va_arg(args, char *));
	  strcpy(genit, nroot);
	  strcat(genit, decl3_table[SING][GEN]);
     }
     else if((typ & DECL_INFO) == DECL4)
     {
	  strcpy(nom, nroot);
	  if(genus == NEUT)
	  {
	       strcat(nom, SING_NEUT_4);
	  } else
	  {
	       strcat(nom, decl4_table[SING][NOM]);
	  }
	  strcpy(genit, nroot);
	  strcat(genit, decl4_table[SING][GEN]);
     }
     else if((typ & DECL_INFO) == DECL5)
     {
	  strcpy(nom, nroot);
	  strcat(nom, decl5_table[SING][NOM]);
	  strcpy(genit, nroot);
	  strcat(genit, decl5_table[SING][GEN]);
     }
     sprintf(form, "%s, %s %s", nom, 
 	     genit, ttngen[genus]);
     return form;
}

char *adj_form(char *aroot, decl_type typ, ...)
/* Tovabbi argumentum: char *nom */
{
     char *form;
     char s[70];
     va_list args;

     form = (char *) malloc(70);
     if((typ & END_INFO) == END3)
     {
	  if(typ & END3_0)
	  {
	       sprintf(form, "%s, %s%s, %s%s", aroot, aroot,
		       decl1_table[SING][NOM], aroot, SING_NEUT_2);
	  }
	  else if(typ & END3_ER)
	  {
	       strncpy(form, aroot, strlen(aroot) - 1);
	       form[strlen(aroot) - 1] = 0;
	       sprintf(s, "%s, %s%s, %s%s", SING_MASC_ER, aroot,
		       decl1_table[SING][NOM], aroot, SING_NEUT_2);
	       strcat(form, s);
	  } else
	  {
	       sprintf(form, "%s%s 3", aroot, decl2_table[SING][NOM]);
	  }
     }
     else if((typ & END_INFO) == DECL3_END1)
     {
	  va_start(args, typ);
	  sprintf(form, "%s, (%s%s)", va_arg(args, char *), aroot,
		  decl3_table[SING][GEN]);
     }
     else if((typ & END_INFO) == DECL3_END2)
     {
	  sprintf(form, "%s%s 2", aroot, SING_FEMI_IS);
     }
     else if((typ & END_INFO) == DECL3_END3)
     {
	  if(typ & DECL3_END3_ER)
	  {
	       strncpy(s, aroot, strlen(aroot) - 1);
	       s[strlen(aroot) - 1] = 0;
	       strcat(s, SING_MASC_ER);
	  } else
	  {
	       strcpy(s, aroot);
	  }
	  sprintf(form, "%s, %s%s, %s%s", s, aroot, SING_FEMI_IS,
		  aroot, SING_NEUT_E);
     }
     return form;
}

void ndetappend(noun_det **ndet, int num, int cas)
{
     *ndet = (noun_det *) malloc(sizeof(noun_det));
     (*ndet)->num = num;
     (*ndet)->casus = cas;
}

noun_det **decl1_match(char *sword, char *nroot)
{
     int i, j, k = 0;
     char *suff;
     noun_det **ndet;

     ndet = (noun_det **) malloc(4 * sizeof(noun_det *));
     if(strstr(sword, nroot) == sword)
     {
	  suff = sword + strlen(nroot);
	  for(i = SING; i <= PLUR; ++i)
	  {
	       for(j = NOM; j <= ABL; ++j)
	       {
		    if(strcmp(suff, decl1_table[i][j]) == 0)
		    {
			 ndetappend(&(ndet[k++]), i, j);
		    }
	       }
	  }
     }
     ndet[k] = NULL;
     return ndet;
}

noun_det **decl2_match(char *sword, char *nroot, decl_type typ, genus_type gen)
{
     int i, j, k = 0;
     char *suff, s[50];
     noun_det **ndet;
     
     ndet = (noun_det **) malloc(4 * sizeof(noun_det *));
     suff = sword + strlen(nroot);
     if(typ & DECL2_ER)
     {
	  strncpy(s, nroot, strlen(nroot) - 1);
	  s[strlen(nroot) - 1] = 0;
	  strcat(s, SING_MASC_ER);
	  if(strcmp(sword, s) == 0)
	  {
	       ndetappend(&(ndet[k++]), SING, NOM);
	  }
     }
     if((typ & DECL2_0) && strcmp(sword, nroot) == 0)
     {
	  ndetappend(&(ndet[k++]), SING, NOM);
     }
     if(strstr(sword, nroot) == sword)
     {
	  if(gen != NEUT)
	  {
	       if(strcmp(suff, decl2_table[SING][NOM]) == 0)
	       {
		    ndetappend(&(ndet[k++]), SING, NOM);
	       }
	       for(i = SING; i <= PLUR; ++i)
	       {
		    for(j = (i == SING) ? ACC : NOM; j <= ABL; ++j)
		    {
			 if(strcmp(suff, decl2_table[i][j]) == 0)
			 {
			      ndetappend(&(ndet[k++]), i, j);
			 }
		    }
	       }
	  } else
	  {
	       for(i = SING; i <= PLUR; ++i)
	       {
		    for(j = GEN; j <= ABL; ++j)
		    {
			 if(strcmp(suff, decl2_table[i][j]) == 0)
			 {
			      ndetappend(&(ndet[k++]), i, j);
			 }
		    }
	       }
	       if(strcmp(suff, SING_NEUT_2) == 0)
	       {
		    ndetappend(&(ndet[k++]), SING, NOM);
		    ndetappend(&(ndet[k++]), SING, ACC);
	       }
	       if(strcmp(suff, PLUR_NEUT) == 0)
	       {
		    ndetappend(&(ndet[k++]), PLUR, NOM);
		    ndetappend(&(ndet[k++]), PLUR, ACC);
	       }
	  }
     }
     ndet[k] = NULL;
     return ndet;
}

noun_det **decl3_match(char *sword, char *nroot, decl_type typ, genus_type gen,
		       char *nom)
{
     char *suff;
     int k = 0;
     noun_det **ndet;
	
     ndet = (noun_det **) malloc(4 * sizeof(noun_det *));
     suff = sword + strlen(nroot);
     if(strcmp(sword, nom) == 0)
     {
	  ndetappend(&(ndet[k++]), SING, NOM);
	  if(gen == NEUT)
	  {
	       ndetappend(&(ndet[k++]), SING, ACC);
	  }
     }
     if(strstr(sword, nroot) == sword)
     {
	  if(gen != NEUT)
	  {
	       if(strcmp(suff, decl3_table[SING][ACC]) == 0)
	       {
		    ndetappend(&(ndet[k++]), SING, ACC);
	       }
	  }
	  if(strcmp(suff, decl3_table[SING][GEN]) == 0)
	  {
	       ndetappend(&(ndet[k++]), SING, GEN);
	  }
	  if(strcmp(suff, decl3_table[SING][DAT]) == 0)
	  {
	       ndetappend(&(ndet[k++]), SING, DAT);
	  }
	  if(typ & DECL3_I2)
	  {
	       if(strcmp(suff, SING_ABL_I) == 0)
	       {
		    ndetappend(&(ndet[k++]), SING, ABL);
	       }
	  } else
	  {
	       if(strcmp(suff, decl3_table[SING][ABL]) == 0)
	       {
		    ndetappend(&(ndet[k++]), SING, ABL);
	       }
	  }
	  if(gen == NEUT)
	  {
	       if(((typ & DECL3_I) && strcmp(suff, PLUR_NEUT_I) == 0) ||
		  (!(typ & DECL3_I) && strcmp(suff, PLUR_NEUT) == 0))
	       {
		    ndetappend(&(ndet[k++]), PLUR, NOM);
		    ndetappend(&(ndet[k++]), PLUR, ACC);
	       }
	  }
	  else if(strcmp(suff, decl3_table[PLUR][NOM]) == 0)
	  {
	       ndetappend(&(ndet[k++]), PLUR, NOM);
	       ndetappend(&(ndet[k++]), PLUR, ACC);
	  }
	  if(((typ & DECL3_I) && strcmp(suff, PLUR_GEN_I) == 0) ||
	     (!(typ & DECL3_I) && (strcmp(suff, decl3_table[PLUR][GEN]) == 0)))
	  {
	       ndetappend(&(ndet[k++]), PLUR, GEN);
	  }
	  if(strcmp(suff, decl3_table[PLUR][DAT]) == 0)
	  {
	       ndetappend(&(ndet[k++]), PLUR, DAT);
	       ndetappend(&(ndet[k++]), PLUR, ABL);
	  }
     }
     ndet[k] = NULL;
     return ndet;
}

noun_det **decl4_match(char *sword, char *nroot, decl_type typ, genus_type gen)
{
     int i, j, k = 0;
     char *suff;
     noun_det **ndet;
	
     ndet = (noun_det **) malloc(5 * sizeof(noun_det *));
     if(strstr(sword, nroot) == sword)
     {
	  suff = sword + strlen(nroot);
	  if(gen != NEUT)
	  {
	       for(i = SING; i <= PLUR; ++i)
	       {
		    for(j = NOM; j <= ABL; ++j)
		    {
			 if(strcmp(suff, decl4_table[i][j]) == 0)
			 {
			      ndetappend(&(ndet[k++]), i, j);
			 }
		    }
	       }
	  } else
	  {
	       if(strcmp(suff, SING_NEUT_4) == 0)
	       {
		    ndetappend(&(ndet[k++]), SING, NOM);
		    ndetappend(&(ndet[k++]), SING, ACC);
		    ndetappend(&(ndet[k++]), SING, DAT);
		    ndetappend(&(ndet[k++]), SING, ABL);
	       }
	       if(strcmp(suff, decl4_table[SING][GEN]) == 0)
	       {
		    ndetappend(&(ndet[k++]), SING, GEN);
	       }
	       if(strcmp(suff, PLUR_NEUT_4) == 0)
	       {
		    ndetappend(&(ndet[k++]), PLUR, NOM);
		    ndetappend(&(ndet[k++]), PLUR, ACC);
	       }
	       if(strcmp(suff, decl4_table[PLUR][GEN]) == 0)
	       {
		    ndetappend(&(ndet[k++]), PLUR, GEN);
	       }
	       if(strcmp(suff, decl4_table[PLUR][DAT]) == 0)
	       {
		    ndetappend(&(ndet[k++]), PLUR, DAT);
		    ndetappend(&(ndet[k++]), PLUR, ABL);
	       }
	  }
     }
     ndet[k] = NULL;
     return ndet;
}

noun_det **decl5_match(char *sword, char *nroot)
{
     int i, j, k = 0;
     char *suff;
     noun_det **ndet;
	
     ndet = (noun_det **) malloc(4 * sizeof(noun_det *));
     if(strstr(sword, nroot) == sword)
     {
	  suff = sword + strlen(nroot);
	  for(i = SING; i <= PLUR; ++i)
	  {
	       for(j = NOM; j <= ABL; ++j)
	       {
		    if(strcmp(suff, decl5_table[i][j]) == 0)
		    {
			 ndetappend(&(ndet[k++]), i, j);
		    }
	       }
	  }
     }
     ndet[k] = NULL;
     return ndet;
}

noun_det **noun_match(char *sword, char *nroot, decl_type typ, genus_type gen,
		      ...)
     /* További argumentum: char *nom */
{
     char nom[50];
     noun_det **det;
     va_list args;

     if((typ & DECL_INFO) == DECL1)
     {
	  det = decl1_match(sword, nroot);
     }
     else if((typ & DECL_INFO) == DECL2)
     {
	  det = decl2_match(sword, nroot, typ, gen);
     }
     else if((typ & DECL_INFO) == DECL3)
     {
	  va_start(args, gen);
	  //strcpy(nom, *(char **)args);
	  strcpy(nom, va_arg(args, char *));
	  det = decl3_match(sword, nroot, typ, gen, nom);
     }
     else if((typ & DECL_INFO) == DECL4)
     {
	  det = decl4_match(sword, nroot, typ, gen);
     }
     else if((typ & DECL_INFO) == DECL5)
     {
	  det = decl5_match(sword, nroot);
     }
     return det;
}

adj_det **grad_match(char *aword, char *aroot, decl_type typ)
{
     adj_det *tmpdet, **adet;
     noun_det **ndet;
     int i, j = 0;
     char root[50], nom[50];
     
     adet = (adj_det **) malloc(10 * sizeof(adj_det *));
     if(!(typ & NO_COMP) && !(typ & COMP_IRREG))
     {
	  strcpy(root, aroot);
	  strcat(root, COMPAR_MF);
	  ndet = decl3_match(aword, root, (typ & DECL3_NOT_I) ? 0 : DECL3_I2,
			     MASC, root);
	  for(i = 0; ndet[i] != NULL; ++i)
	  {
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = COMPAR;
	       tmpdet->genus = MASC;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = COMPAR;
	       tmpdet->genus = FEMI;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       free(ndet[i]);
	  }
	  free(ndet);
	  strcpy(nom, aroot);
	  strcat(nom, COMPAR_N);
	  ndet = decl3_match(aword, root, (typ & DECL3_NOT_I) ? 0 : DECL3_I2,
			     NEUT, nom);
	  for(i = 0; ndet[i] != NULL; ++i)
	  {
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = COMPAR;
	       tmpdet->genus = NEUT;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       free(ndet[i]);
	  }
	  free(ndet);
     }
     if(!(typ & NO_SUPER) && !(typ & SUPER_IRREG))
     {
	  if(((typ & END_INFO) == DECL3_END3 && (typ & DECL3_END3_ER)) ||
	     ((typ & END_INFO) == END3 && (typ & END3_ER)))
	  {
	       strncpy(root, aroot, strlen(aroot) - 1);
	       root[strlen(aroot) - 1] = 0;
	       strcat(root, SING_MASC_ER);
	  } else
	  {
	       strcpy(root, aroot);
	  }
	  if((typ & END_INFO) == DECL3_END3 || ((typ & END_INFO) == END3 &&
	     ((typ & END3_ER) || (typ & END3_0))))
	  {
	       strcat(root, SUPER_R);
	  }
	  else if((typ & END_INFO) == DECL3_END2 || (typ & SUPER_IRREG_L))
	  {
	       strcat(root, SUPER_L);
	  } else
	  {
	       strcat(root, SUPER);
	  }
	  ndet = decl2_match(aword, root, typ, MASC);
	  for(i = 0; ndet[i] != NULL; ++i)
	  {
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = SUPERLAT;
	       tmpdet->genus = MASC;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       free(ndet[i]);
	  }
	  free(ndet);
	  ndet = decl1_match(aword, root);
	  for(i = 0; ndet[i] != NULL; ++i)
	  {
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = SUPERLAT;
	       tmpdet->genus = FEMI;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       free(ndet[i]);
	  }
	  free(ndet);
	  ndet = decl2_match(aword, root, typ, NEUT);
	  for(i = 0; ndet[i] != NULL; ++i)
	  {
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = SUPERLAT;
	       tmpdet->genus = NEUT;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       free(ndet[i]);
	  }
	  free(ndet);
     }
     adet[j] = NULL;
     return adet;
}

adj_det **end3_match(char *aword, char *aroot, decl_type typ, ...)
{
     adj_det **adet, *tmpdet;
     noun_det **ndet;
     int i, j = 0;
     
     adet = (adj_det **) malloc(10 * sizeof(adj_det *));
     if((typ & END_INFO) == END3)
     {
	  ndet = decl2_match(aword, aroot, typ, MASC);
	  for(i = 0; ndet[i] != NULL; ++i)
	  {
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = POSIT;
	       tmpdet->genus = MASC;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       free(ndet[i]);
	  }
	  free(ndet);
	  ndet = decl1_match(aword, aroot);
	  for(i = 0; ndet[i] != NULL; ++i)
	  {
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = POSIT;
	       tmpdet->genus = FEMI;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       free(ndet[i]);
	  }
	  free(ndet);
	  ndet = decl2_match(aword, aroot, typ, NEUT);
	  for(i = 0; ndet[i] != NULL; ++i)
	  {
	       tmpdet = (adj_det *) malloc(sizeof(adj_det));
	       tmpdet->gradus = POSIT;
	       tmpdet->genus = NEUT;
	       tmpdet->num = ndet[i]->num;
	       tmpdet->casus = ndet[i]->casus;
	       adet[j] = tmpdet;
	       ++j;
	       free(ndet[i]);
	  }
	  free(ndet);
     }
     adet[j] = NULL;
     return adet;
}

adj_det **decl3_end1_match(char *aword, char *aroot, decl_type typ, char *nom)
{
     adj_det **adet, *tmpdet;
     noun_det **ndet;
     int i, j = 0;
     
     adet = (adj_det **) malloc(10 * sizeof(adj_det *));
     ndet = decl3_match(aword, aroot, (typ & DECL3_NOT_I) ? 0 : DECL3_I2,
			MASC, nom);
     for(i = 0; ndet[i] != NULL; ++i)
     {
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = MASC;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = FEMI;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  free(ndet[i]);
     }
     free(ndet);
     ndet = decl3_match(aword, aroot, (typ & DECL3_NOT_I) ? 0 : DECL3_I2,
			NEUT, nom);
     for(i = 0; ndet[i] != NULL; ++i)
     {
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = NEUT;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  free(ndet[i]);
     }
     free(ndet);
     adet[j] = NULL;
     return adet;
}

adj_det **decl3_end2_match(char *aword, char *aroot, decl_type typ, ...)
{
     adj_det **adet, *tmpdet;
     noun_det **ndet;
     int i, j = 0;
     char nom[50];
     
     adet = (adj_det **) malloc(10 * sizeof(adj_det *));     
     strcpy(nom, aroot);
     strcat(nom, SING_FEMI_IS);
     ndet = decl3_match(aword, aroot, (typ & DECL3_NOT_I) ? 0 : DECL3_I2,
			MASC, nom);
     for(i = 0; ndet[i] != NULL; ++i)
     {
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = MASC;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = FEMI;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  free(ndet[i]);
     }
     free(ndet);
     strcpy(nom, aroot);
     strcat(nom, SING_NEUT_E);
     ndet = decl3_match(aword, aroot, (typ & DECL3_NOT_I) ? 0 : DECL3_I2,
			NEUT, nom);
     for(i = 0; ndet[i] != NULL; ++i)
     {
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = NEUT;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  free(ndet[i]);
     }
     free(ndet);
     adet[j] = NULL;
     return adet;
}

adj_det **decl3_end3_match(char *aword, char *aroot, decl_type typ)
{
     adj_det **adet, *tmpdet;
     noun_det **ndet;
     int i, j = 0;
     char nom[50];
     
     adet = (adj_det **) malloc(10 * sizeof(adj_det *));     
     if(typ & DECL3_END3_ER)
     {
	  strncpy(nom, aroot, strlen(aroot) - 1);
	  nom[strlen(aroot) - 1] = 0;
	  strcat(nom, SING_MASC_ER);
     } else
     {
	  strcpy(nom, aroot);
     }
     ndet = decl3_match(aword, aroot, (typ & DECL3_NOT_I) ? 0 : DECL3_I2,
			MASC, nom);
     for(i = 0; ndet[i] != NULL; ++i)
     {
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = MASC;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  free(ndet[i]);
     }
     free(ndet);
     strcpy(nom, aroot);
     strcat(nom, SING_FEMI_IS);
     ndet = decl3_match(aword, aroot,
			(typ & DECL3_NOT_I) ? 0 : DECL3_I2, FEMI, nom);
     for(i = 0; ndet[i] != NULL; ++i)
     {
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = FEMI;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  free(ndet[i]);
     }
     free(ndet);
     strcpy(nom, aroot);
     strcat(nom, SING_NEUT_E);
     ndet = decl3_match(aword, aroot, (typ & DECL3_NOT_I) ? 0 : DECL3_I2,
			NEUT, nom);
     for(i = 0; ndet[i] != NULL; ++i)
     {
	  tmpdet = (adj_det *) malloc(sizeof(adj_det));
	  tmpdet->gradus = POSIT;
	  tmpdet->genus = NEUT;
	  tmpdet->num = ndet[i]->num;
	  tmpdet->casus = ndet[i]->casus;
	  adet[j] = tmpdet;
	  ++j;
	  free(ndet[i]);
     }
     free(ndet);
     adet[j] = NULL;
     return adet;
}
     
adj_det **adj_match(char *aword, char *aroot, decl_type typ, ...)
/* További argumentum: nom *char */
{
     char nom[50];
     adj_det **adet, **tmpdet;
     int i, j = 0;
     va_list args;

     adet = (adj_det **) malloc(10 * sizeof(adj_det *));
     if((typ & END_INFO) == END3)
     {
	  tmpdet = end3_match(aword, aroot, typ);
	  for(i = 0; tmpdet[i] != NULL; ++i)
	  {
	       adet[j] = tmpdet[i];
	       ++j;
	  }
	  free(tmpdet);
     }
     else if((typ & END_INFO) == DECL3_END1)
     {
	  va_start(args, typ);
	  //strcpy(nom, *(char **)args);
	  strcpy(nom, va_arg(args, char *));
	  tmpdet = decl3_end1_match(aword, aroot, typ, nom);
	  for(i = 0; tmpdet[i] != NULL; ++i)
	  {
	       adet[j] = tmpdet[i];
	       ++j;
	  }
	  free(tmpdet);
     }	  
     else if((typ & END_INFO) == DECL3_END2)
     {
	  tmpdet = decl3_end2_match(aword, aroot, typ, nom);
	  for(i = 0; tmpdet[i] != NULL; ++i)
	  {
	       adet[j] = tmpdet[i];
	       ++j;
	  }
	  free(tmpdet);
     }
     else if((typ & END_INFO) == DECL3_END3)
     {
	  tmpdet = decl3_end3_match(aword, aroot, typ);
	  for(i = 0; tmpdet[i] != NULL; ++i)
	  {
	       adet[j] = tmpdet[i];
	       ++j;
	  }
	  free(tmpdet);
     }
     if((!(typ & COMP_IRREG) && !(typ & SUPER_IRREG)) ||
	(!(typ & NO_COMP) && !(typ & NO_SUPER)))
     {
	  tmpdet = grad_match(aword, aroot, typ);
	  for(i = 0; tmpdet[i] != NULL; ++i)
	  {
	       adet[j] = tmpdet[i];
	       ++j;
	  }
	  free(tmpdet);
     }
     adet[j] = NULL;     
     return adet;
}

adv_det *adv_match(char *aword, char *aroot, decl_type typ)
{
     adv_det *adet;
     char s[50];

     adet = NULL;
     if((typ & ADV_IRREG))
     {
	  return adet;
     }
     if((typ & END_INFO) == END3)
     {
	  strcpy(s, aroot);
	  strcat(s, ADVERB);
     }
     else if((typ & END_INFO) == DECL3_END3 ||
	     (typ & END_INFO) == DECL3_END2 ||
	     (typ & END_INFO) == DECL3_END1)
     {
	  if(strcmp(aroot + strlen(aroot) - 2, "nt") == 0)
	  {
	       strcpy(s, aroot);
	       strcat(s, ADVERB_COMP_PART);
	  } else
	  {
	       strcpy(s, aroot);
	       strcat(s, ADVERB_COMP);
	  }
     }     
     if(strcmp(aword, s) == 0)
     {
	  adet = (adv_det *) malloc(sizeof(adv_det));
	  adet->gradus = POSIT;
     }
     if(!(typ & COMP_IRREG) && !(typ & NO_COMP))
     {
	  strcpy(s, aroot);
	  strcat(s, COMPAR_N);
	  if(strcmp(aword, s) == 0)
	  {
	       adet = (adv_det *) malloc(sizeof(adv_det));
	       adet->gradus = COMPAR;
	  }
	  if(((typ & END_INFO) == DECL3_END3 && (typ & DECL3_END3_ER)) ||
	     ((typ & END_INFO) == END3 && (typ & END3_ER)))
	  {
	       strncpy(s, aroot, strlen(aroot) - 1);
	       s[strlen(aroot) - 1] = 0;
	       strcat(s, SING_MASC_ER);
	  } else
	  {
	       strcpy(s, aroot);
	  }
	  if((typ & END_INFO) == DECL3_END3 || ((typ & END_INFO) == END3 &&
	     ((typ & END3_ER) || (typ & END3_0))))
	  {
	       strcat(s, SUPER_R);
	  }
	  else if((typ & END_INFO) == DECL3_END2 || (typ & SUPER_IRREG_L))
          {
              strcat(s, SUPER_L);
          } else
	  {
	       strcat(s, SUPER);
	  }
	  strcat(s, ADVERB);
	  if(strcmp(aword, s) == 0)
	  {
	       adet = (adv_det *) malloc(sizeof(adv_det));
	       adet->gradus = SUPERLAT;
	  }
     }
     return adet;
}
