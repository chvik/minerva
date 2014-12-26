#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "verb.h"
#include "latin.h"
#include "verbtab.h"
#include "nominal.h"

extern char *decl2_table[2][5];

char *verb_form(char *imp_root, char *perf_root, char *sup_root, coni_type typ)
{
     char *form;
     char str[70];
     int gen;

     if((typ & CONI_INFO) == FERO_TYPE)
     {
	  return fero_form(imp_root, perf_root, sup_root);
     }
     form = (char *) malloc(70);
     strcpy(form, imp_root);
     if(typ & DEPONENS)
     {
	  gen = PASS;
     } else
     {
	  gen = ACT;
     }
     switch(typ & CONI_INFO)
     {
     case CONI1:
	  strcat(form, coni1_ind_imp[gen][PRAES][SING][P1]);
	  strcat(form, " 1");
	  break;
     case CONI2:
	  strcat(form, coni2_ind_imp[gen][PRAES][SING][P1]);
	  strcat(form, " 2");
	  break;
     case CONI3:
	  strcat(form, coni3_ind_imp[gen][PRAES][SING][P1]);
	  strcat(form, " 3");
	  break;
     case CONI3I:
	  strcat(form, coni3i_ind_imp[gen][PRAES][SING][P1]);
	  strcat(form, " 3");
	  break;
     case CONI4:
	  strcat(form, coni4_ind_imp[gen][PRAES][SING][P1]);
	  strcat(form, " 4");
	  break;
     }
     if((typ & DEPONENS) || (typ & SEMI_DEPONENS))	  
     {
	  if(!(typ & NO_SUPINUM))
	  {
	       sprintf(str, ", %s%s %s", sup_root, decl2_table[SING][NOM],
		       sum_ind_imp[PRAES][SING][P1]);
	       strcat(form, str);
	  }
     } else if(!(typ & NO_PERFECTUM))
     {
	  sprintf(str, ", %s%s", perf_root, act_ind_perf[IMP][SING][P1]);
	  strcat(form, str);
	  if(!(typ & NO_SUPINUM))
	  {	       
	       sprintf(str, ", %s%s", sup_root, SUP_ACC);
	       strcat(form, str);
	  }
     }
     return form;
}

void vdetappend(verb_det **det, int genus, int modus, int tempus, int actio,
		int numerus, int persona)
{
     *det = (verb_det *) malloc(sizeof(verb_det));
     (*det)->genus = genus;
     (*det)->modus = modus;
     (*det)->tempus = tempus;
     (*det)->actio = actio;
     (*det)->num = numerus;
     (*det)->pers = persona;
}

verb_det **ind_imp_match(char *suff, coni_type typ)
{
     int pers, num, temp, gen, i = 0;
     char *(*ind_imp_table)[3][2][3];
     verb_det **det;

     det = (verb_det **) malloc(10 * sizeof(verb_det *));
     switch(typ & CONI_INFO)
     {
     case CONI1: ind_imp_table = coni1_ind_imp; break;
     case CONI2: ind_imp_table = coni2_ind_imp; break;
     case CONI3: ind_imp_table = coni3_ind_imp; break;
     case CONI3I: ind_imp_table = coni3i_ind_imp; break;
     case CONI4: ind_imp_table = coni4_ind_imp; break;
     }
     for(gen = (typ & DEPONENS) ? PASS : ACT; gen <= PASS; ++gen)
     {
	  for(temp = PRAES; temp <= FUT; ++temp)
	  {
	       for(num = SING; num <= PLUR; ++num)
	       {
		    for(pers = P1; pers <= P3; ++pers)
		    {
			 if(strcmp(
			      suff, ind_imp_table[gen][temp][num][pers])
			    == 0)
			 {			   
			      vdetappend(det + i, gen, IND, temp, IMP,
					 num, pers);
			      ++i;
			 }
		    }
	       }
	  }
     }
     det[i] = NULL;
     return det;
}

verb_det **con_imp_match(char *suff, coni_type typ)
{
     int pers, num, temp, gen, i = 0;
     char *(*con_imp_table)[2][2][3];
     verb_det **det;

     det = (verb_det **) malloc(10 * sizeof(verb_det *));
     switch(typ & CONI_INFO)
     {
     case CONI1: con_imp_table = coni1_con_imp; break;
     case CONI2: con_imp_table = coni2_con_imp; break;
     case CONI3: con_imp_table = coni3_con_imp; break;
     case CONI3I: con_imp_table = coni3i_con_imp; break;
     case CONI4: con_imp_table = coni4_con_imp; break;
     }
     for(gen = (typ & DEPONENS) ? PASS : ACT; gen <= PASS; ++gen)
     {
	  for(temp = PRAES; temp <= PRAET; ++temp)
	  {
	       for(num = SING; num <= PLUR; ++num)
	       {
		    for(pers = P1; pers <= P3; ++pers)
		    {
			 if(strcmp(
			      suff, con_imp_table[gen][temp][num][pers])
			    == 0)
			 {
			      vdetappend(det + i, gen, CON, temp, IMP,
					 num, pers);
			      ++i;
			 }
		    }
	       }
	  }
     }
     det[i] = NULL;
     return det;
}

verb_det **act_ind_perf_match(char *suff)
{
     int pers, num, temp, i = 0;
     verb_det **det;

     det = (verb_det **) malloc(10 * sizeof(verb_det *));     
     for(temp = PRAES; temp <= FUT; ++temp)
     {
	  for(num = SING; num <= PLUR; ++num)
	  {
	       for(pers = P1; pers <= P3; ++pers)
	       {
		    if(strcmp(suff, act_ind_perf[temp][num][pers]) == 0)
		    {
			 vdetappend(det + i, ACT, IND, temp, PERF, num, pers);
			 ++i;
		    }
	       }
	  }
     }
     det[i] = NULL;
     return det;
}

verb_det **act_con_perf_match(char *suff)
{
     int temp, num, pers, i = 0;
     verb_det **det;

     det = (verb_det **) malloc(10 * sizeof(verb_det *));
     for(temp = PRAES; temp <= PRAET; ++temp)
     {
	  for(num = SING; num <= PLUR; ++num)
	  {
	       for(pers = P1; pers <= P3; ++pers)
	       {
		    if(strcmp(suff, act_con_perf[temp][num][pers]) == 0)
		    {
			 vdetappend(det + i, ACT, CON, temp, PERF, num, pers);
			 ++i;
		    }
	       }
	  }
     }
     det[i] = NULL;
     return det;
}

verb_det **imptiv1_match(char *suff, coni_type typ)
{
     int num, gen, i = 0;
     char *(*imptiv1_table)[2];
     verb_det **det;

     det = (verb_det **) malloc(10 * sizeof(verb_det *));
     switch(typ & CONI_INFO)
     {
     case CONI1: imptiv1_table = coni1_imptiv1; break;
     case CONI2: imptiv1_table = coni2_imptiv1; break;
     case CONI3: imptiv1_table = coni3_imptiv1; break;
     case CONI3I: imptiv1_table = coni3i_imptiv1; break;
     case CONI4: imptiv1_table = coni4_imptiv1; break;
     }
     for(gen = ACT; gen <= PASS; ++gen)
     {
	  for(num = SING; num <= PLUR; ++num)
	  {
	       if(typ & SHORT_IMPTIV)
	       {
		    if(gen == ACT && num == SING && strcmp(suff, "") == 0)
		    {
			 vdetappend(det + i, gen, IMPTIV1, -1, -1, num, P2);
			 ++i;
		    }
	       }
	       else if(strcmp(suff, imptiv1_table[gen][num]) == 0)
	       {
		    vdetappend(det + i, gen, IMPTIV1, -1, -1, num, P2);
		    ++i;
	       }
	  }
     }
     det[i] = NULL;
     return det;
}

verb_det **imptiv2_match(char *suff, coni_type typ)
{
     int pers, num, gen, i = 0;
     char *(*imptiv2_table)[2][2];
     verb_det **det;

     det = (verb_det **) malloc(10 * sizeof(verb_det *));
     switch(typ & CONI_INFO)
     {
     case CONI1: imptiv2_table = coni1_imptiv2; break;
     case CONI2: imptiv2_table = coni2_imptiv2; break;
     case CONI3: imptiv2_table = coni3_imptiv2; break;
     case CONI3I: imptiv2_table = coni3i_imptiv2; break;
     case CONI4: imptiv2_table = coni4_imptiv2; break;
     }
     for(gen = ACT; gen <= PASS; ++gen)
     {
	  for(num = SING; num <= PLUR; ++num)
	  {
	       for(pers = P2; pers <= P3; ++pers)
	       {
		    if((gen != PASS || num != PLUR || pers != P2) &&
		       (strcmp(suff, imptiv2_table[gen][num][pers - 1]) == 0))
		    {
			 vdetappend(det + i, gen, IMPTIV2, -1, -1, num, pers);
			 ++i;
		    }
	       }
	  }
     }
     det[i] = NULL;
     return det;
}

verb_det **verb_match_simple(char *vword, char *imp_root, char *perf_root,
			coni_type typ)
{
     char suff[50];
     verb_det **det, **vdet;
     int i, j = 0;

     if((typ & CONI_INFO) == FERO_TYPE)
     {
	  return fero_match_simple(vword, imp_root, perf_root);
     }
     vdet = (verb_det **) malloc(10 * sizeof(verb_det *));
     if(strstr(vword, imp_root) == vword)
     {
	  strcpy(suff, vword + strlen(imp_root));
	  det = ind_imp_match(suff, typ);
	  for(i = 0; det[i] != NULL; ++i)
	  {
	       vdet[j++] = det[i];
	  }
	  free(det);
	  det = con_imp_match(suff, typ);
	  for(i = 0; det[i] != NULL; ++i)
	  {
	       vdet[j++] = det[i];
	  }
	  free(det);
 	  det = imptiv1_match(suff, typ);
	  for(i = 0; det[i] != NULL; ++i)
	  {
	       vdet[j++] = det[i];
	  }
	  free(det);
	  det = imptiv2_match(suff, typ);
	  for(i = 0; det[i] != NULL; ++i)
	  {
	       vdet[j++] = det[i];
	  }
	  free(det);
     }
     if(!(typ & DEPONENS) && !(typ & SEMI_DEPONENS) && !(typ & NO_PERFECTUM) &&
	strstr(vword, perf_root) == vword)
     {
	  strcpy(suff, vword + strlen(perf_root));
	  det = act_ind_perf_match(suff);
	  for(i = 0; det[i] != NULL; ++i)
	  {
	       vdet[j++] = det[i];
	  }
	  free(det);
	  det = act_con_perf_match(suff);
	  for(i = 0; det[i] != NULL; ++i)
	  {
	       vdet[j++] = det[i];
	  }
	  free(det);
     }
     vdet[j] = NULL;
     return vdet;
}

verb_det **verb_match_compound(char *vword, char *vword2, char *imp_root,
			  char *sup_root, coni_type typ)
{
     verb_det **vdet, **sdet;
     part_det **pdet;
     int i, j, k = 0;

     if((typ & CONI_INFO) == FERO_TYPE)
     {
	  return fero_match_compound(vword, vword2, imp_root, sup_root);
     }
     vdet = (verb_det **) malloc(10 * sizeof(verb_det *));
     if(typ & NO_SUPINUM)
     {
	  vdet[0] = NULL;
	  return vdet;
     }
     pdet = part_match(vword, imp_root, sup_root, typ);
     sdet = sum_match(vword2);
     if(pdet[0] == NULL && sdet[0] == NULL)
     {
	  free(pdet);
	  free(sdet);
	  pdet = part_match(vword2, imp_root, sup_root, typ);
	  sdet = sum_match(vword);
     }
     for(i = 0; pdet[i] != NULL; ++i)
     {
	  if(pdet[i]->actio == PERF && pdet[i]->casus == NOM)
	  {
	       for(j = 0; sdet[j] != NULL; ++j)
	       {
		    if(sdet[j]->actio == IMP && pdet[i]->num == sdet[j]->num)
		    {
			 vdetappend(vdet + k, PASS, sdet[j]->modus,
				    sdet[j]->tempus, PERF, sdet[j]->num,
				    sdet[j]->pers);
			 ++k;
		    }
		    free(sdet[j]);
	       }
	  }
	  free(pdet[i]);
     }
     free(pdet);
     free(sdet);
     vdet[k] = NULL;
     return vdet;
}

verb_det **sum_match(char *vword)
{
     verb_det **det, **tmpdet;
     int pers, num, temp;
     int i, j = 0;

     det = (verb_det **) malloc(10 * sizeof(verb_det *));
     for(temp = PRAES; temp <= FUT; ++temp)
     {
	  for(num = SING; num <= PLUR; ++num)
	  {
	       for(pers = P1; pers <= P3; ++pers)
	       {
		    if(strcmp(vword, sum_ind_imp[temp][num][pers]) == 0)
		    {
			 vdetappend(det + j, ACT, IND, temp, IMP, num, pers);
			 ++j;
		    }
	       }
	  }
     }
     for(temp = PRAES; temp <= PRAET; ++temp)
     {
	  for(num = SING; num <= PLUR; ++num)
	  {
	       for(pers = P1; pers <= P3; ++pers)
	       {
		    if(strcmp(vword, sum_con_imp[temp][num][pers]) == 0)
		    {
			 vdetappend(det + j, ACT, CON, temp, IMP, num, pers);
			 ++j;
		    }
	       }
	  }
     }
     for(num = SING; num <= PLUR; ++num)
     {
	  if(strcmp(vword, sum_imptiv1[num]) == 0)
	  {
	       vdetappend(det + j, ACT, IMPTIV1, -1, -1, num, P2);
	       ++j;
	  }
     }
     for(num = SING; num <= PLUR; ++num)
     {
	  for(pers = P2; pers <= P3; ++pers)
	  {
	       if(strcmp(vword, sum_imptiv2[num][pers - 1]) == 0)
	       {
		    vdetappend(det + j, ACT, IMPTIV2, -1, -1, num, pers);
		    ++j;
	       }
	  }
     }
     if(strstr(vword, SUM_PERF) == vword)
     {
	  tmpdet = act_ind_perf_match(vword + strlen(SUM_PERF));
	  for(i = 0; tmpdet[i] != NULL; ++i)
	  {
	       det[j] = tmpdet[i];
	       ++j;
	  }
	  free(tmpdet);
	  tmpdet = act_con_perf_match(vword + strlen(SUM_PERF));
	  for(i = 0; tmpdet[i] != NULL; ++i)
	  {
	       det[j] = tmpdet[i];
	       ++j;
	  }
	  free(tmpdet);
     }
     det[j] = NULL;
     return det;
}

verb_det **fero_match_simple(char *vword, char *imp_pref, char *perf_pref)
{
     verb_det **det, **tmpdet;
     int pers, num, temp, gen;
     int i, j = 0;
     char *vw;

     det = (verb_det **) malloc(10 * sizeof(verb_det *));
     if(strstr(vword, imp_pref) == vword)
     {
	  vw = vword + strlen(imp_pref);
	  for(gen = ACT; gen <= PASS; ++gen)
	  {
	       for(temp = PRAES; temp <= FUT; ++temp)
	       {
		    for(num = SING; num <= PLUR; ++num)
		    {
			 for(pers = P1; pers <= P3; ++pers)
			 {
			      if(strcmp(
				   vw, fero_ind_imp[gen][temp][num][pers])
				 == 0)
			      {
				   vdetappend(
					det + j, gen, IND, temp, IMP, num,
					pers);
				   ++j;
			      }
			 }
		    }
	       }
	  }
	  for(gen = ACT; gen <= PASS; ++gen)
	  {     
	       for(temp = PRAES; temp <= PRAET; ++temp)
	       {
		    for(num = SING; num <= PLUR; ++num)
		    {
			 for(pers = P1; pers <= P3; ++pers)
			 {
			      if(strcmp(
				   vw, fero_con_imp[gen][temp][num][pers])
				 == 0)
			      {
				   vdetappend(
					det + j, gen, CON, temp, IMP, num,
					pers);
				   ++j;
			      }
			 }
		    }
	       }
	  }
	  for(gen = ACT; gen <= PASS; ++gen)
	  {
	       for(num = SING; num <= PLUR; ++num)
	       {
		    if(strcmp(vw, fero_imptiv1[gen][num]) == 0)
		    {
			 vdetappend(det + j, gen, IMPTIV1, -1, -1, num, P2);
			 ++j;
		    }
	       }
	  }     
	  for(gen = ACT; gen <= PASS; ++gen)
	  {
	       for(num = SING; num <= PLUR; ++num)
	       {
		    for(pers = P2; pers <= P3; ++pers)
		    {
			 if((gen != PASS || num != PLUR || pers != P2) &&
			    (strcmp(vw, fero_imptiv2[gen][num][pers - 1])
			     == 0))
			 {
			      vdetappend(det + j, gen, IMPTIV2, -1, -1, num,
					 pers);
			      ++j;
			 }
		    }
	       }
	  }
     }
     if(strstr(vword, perf_pref) == vword)
     {
	  vw = vword + strlen(perf_pref);
	  if(strstr(vw, FERO_PERF) == vw)
	  {
	       tmpdet = act_ind_perf_match(vw + strlen(FERO_PERF));
	       for(i = 0; tmpdet[i] != NULL; ++i)
	       {
		    det[j] = tmpdet[i];
		    ++j;
	       }
	       free(tmpdet);
	       tmpdet = act_con_perf_match(vw + strlen(FERO_PERF));
	       for(i = 0; tmpdet[i] != NULL; ++i)
	       {
		    det[j] = tmpdet[i];
		    ++j;
	       }
	       free(tmpdet);
	  }
     }
     det[j] = NULL;
     return det;
}

verb_det **fero_match_compound(char *vword, char *vword2, char *imp_pref,
			  char *sup_pref)
{
     char imp_root[100], sup_root[100];
     strcpy(imp_root, imp_pref);
     strcat(imp_root, FERO_IMP);
     strcpy(sup_root, sup_pref);
     strcat(sup_root, FERO_SUP);
     return verb_match_compound(vword, vword2, imp_root, sup_root, CONI3);
}

char *fero_form(char *imp_pref, char *perf_pref, char *sup_pref)
{
     char *form;
     
     form = (char *) malloc(70);
     sprintf(form, "%s%s, %s%s, %s%s%s, %s%s%s", imp_pref,
	     fero_ind_imp[ACT][PRAES][SING][P1], imp_pref, FERO_INF_ACT,
	     perf_pref, FERO_PERF, act_ind_perf[IMP][SING][P1],
	     sup_pref, FERO_SUP, SUP_ACC);
     return form;
}
