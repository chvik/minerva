#include <stdlib.h>
#include <string.h>
#include "nominal.h"
#include "verb.h"
#include "latin.h"
#include "part.h"

void pdetappend(part_det **det, int vgenus, int actio, int num, int casus,
		genus_type ngenus, int gradus)
{
     *det = (part_det *) malloc(sizeof(part_det));
     (*det)->vgenus = vgenus;
     (*det)->actio = actio;
     (*det)->num = num;
     (*det)->casus = casus;
     (*det)->ngenus = ngenus;
     (*det)->gradus = gradus;
}

part_det **part_match(char *vword, char *imp_root, char *sup_root,
		      coni_type typ)
{
     char aroot[50];
     char nom[50];
     char *suffnom, *suffroot;
     int i, j = 0;
     part_det **pdet;
     adj_det **adet;

     if((typ & CONI_INFO) == FERO_TYPE)
     {
	  return fero_part_match(vword, imp_root, sup_root);
     }
     
     pdet = (part_det **) malloc(10 * sizeof(part_det *));

     /* Imp. act. */

     switch(typ & CONI_INFO)
     {
     case CONI1: 
	  suffnom = PART_IMP1_NOM;
	  suffroot = PART_IMP1_ROOT;
	  break;
     case CONI2: 
	  suffnom = PART_IMP2_NOM;
	  suffroot = PART_IMP2_ROOT;
	  break;
     case CONI3: 
	  suffnom = PART_IMP3_NOM;
	  suffroot = PART_IMP3_ROOT;
	  break;
     case CONI3I: 
	  suffnom = PART_IMP3I_NOM;
	  suffroot = PART_IMP3I_ROOT;
	  break;
     case CONI4: 
	  suffnom = PART_IMP4_NOM;
	  suffroot = PART_IMP4_ROOT;
	  break;
     }
     strcpy(aroot, imp_root);
     strcat(aroot, suffroot);
     strcpy(nom, imp_root);
     strcat(nom, suffnom);
     adet = adj_match(vword, aroot, DECL3_END1, nom);
     for(i = 0; adet[i] != NULL; ++i)
     {
	  pdetappend(pdet + j, ACT, IMP,  adet[i]->num, adet[i]->casus,
		     adet[i]->genus, adet[i]->gradus);
	  ++j;
	  free(adet[i]);
     }
     free(adet);

     if(!(typ & NO_SUPINUM))
     {
	  /* Inst. act. */
	  strcpy(aroot, sup_root);
	  strcat(aroot, PART_INST_ACT_ROOT);
	  adet = adj_match(vword, aroot, END3);
	  for(i = 0; adet[i] != NULL; ++i)
	  {
	       pdetappend(pdet + j, ACT, INST,  adet[i]->num, adet[i]->casus,
			  adet[i]->genus, adet[i]->gradus);
	       ++j;
	       free(adet[i]);
	  }
	  free(adet);
	  
	  /* Perf. pass. */	  
	  strcpy(aroot, sup_root);
	  adet = adj_match(vword, aroot, END3);
	  for(i = 0; adet[i] != NULL; ++i)
	  {
	       pdetappend(pdet + j, PASS, PERF,  adet[i]->num, adet[i]->casus,
			  adet[i]->genus, adet[i]->gradus);
	       ++j;
	       free(adet[i]);
	  }
	  free(adet);
     }
     
     /* Inst. pass. */
     switch(typ & CONI_INFO)
     {
     case CONI1: 
	  suffroot = PART_INST_PASS1_ROOT;
	  break;
     case CONI2: 
	  suffroot = PART_INST_PASS2_ROOT;
	  break;
     case CONI3: 
	  suffroot = PART_INST_PASS3_ROOT;
	  break;
     case CONI3I: 
	  suffroot = PART_INST_PASS3I_ROOT;
	  break;
     case CONI4: 
	  suffroot = PART_INST_PASS4_ROOT;
	  break;
     }
     strcpy(aroot, imp_root);
     strcat(aroot, suffroot);
     adet = adj_match(vword, aroot, END3);
     for(i = 0; adet[i] != NULL; ++i)
     {
	  pdetappend(pdet + j, PASS, INST,  adet[i]->num, adet[i]->casus,
		     adet[i]->genus, adet[i]->gradus);
	  ++j;
	  free(adet[i]);
     }
     free(adet);

     pdet[j] = NULL;
     return pdet;
}

void idetappend(inf_det **det, int genus, int actio)
{
     *det = (inf_det *) malloc(sizeof(inf_det));
     (*det)->genus = genus;
     (*det)->actio = actio;
}

inf_det *inf_match_simple(char *vword, char *imp_root, char *perf_root,
			  coni_type typ)
{
     char suff[50];
     inf_det *idet;

     if((typ & CONI_INFO) == FERO_TYPE)
     {
	  return fero_inf_match_simple(vword, imp_root, perf_root);
     }
     idet = NULL;
     if(strstr(vword, imp_root) == vword)
     {
	  strcpy(suff, vword + strlen(imp_root));
	  if((typ & CONI_INFO) == CONI1)
	  {
	       if(strcmp(suff, CONI1_INF_ACT) == 0)
	       {
		    idetappend(&idet, ACT, IMP);
	       }
	       else if(strcmp(suff, CONI1_INF_PASS) == 0)
	       {
		    idetappend(&idet, PASS, IMP);
	       }
	  }
	  else if((typ & CONI_INFO) == CONI2)
	  {
	       if(strcmp(suff, CONI2_INF_ACT) == 0)
	       {
		    idetappend(&idet, ACT, IMP);
	       }
	       else if(strcmp(suff, CONI2_INF_PASS) == 0)
	       {
		    idetappend(&idet, PASS, IMP);
	       }
	  }
	  else if((typ & CONI_INFO) == CONI3)
	  {
	       if(strcmp(suff, CONI3_INF_ACT) == 0)
	       {
		    idetappend(&idet, ACT, IMP);
	       }
	       else if(strcmp(suff, CONI3_INF_PASS) == 0)
	       {
		    idetappend(&idet, PASS, IMP);
	       }
	  }
	  else if((typ & CONI_INFO) == CONI4)
	  {
	       if(strcmp(suff, CONI4_INF_ACT) == 0)
	       {
		    idetappend(&idet, ACT, IMP);
	       }
	       else if(strcmp(suff, CONI4_INF_PASS) == 0)
	       {
		    idetappend(&idet, PASS, IMP);
	       }
	  }
     }
     if(strstr(vword, perf_root) == vword)
     {
	  strcpy(suff, vword + strlen(perf_root));
	  if(strcmp(suff, INF_PERF_ACT) == 0)
	  {
	       idetappend(&idet, ACT, PERF);
	  }
     }
     return idet;
}

inf_det *inf_match_compound(char *vword, char *vword2, char *imp_root,
			 char *sup_root, coni_type typ)
{
     char str[50];
     inf_det *idet;
     part_det **pdet;
     int i;

     if((typ & CONI_INFO) == FERO_TYPE)
     {
	  return fero_inf_match_compound(vword, vword2, imp_root, sup_root);
     }     
     idet = NULL;
     pdet = NULL;
     if(typ & NO_SUPINUM)
     {
	  return idet;
     }
     if(strcmp(vword2, ESSE) == 0)
     {
	  pdet = part_match(vword, imp_root, sup_root, typ);
     }
     else if(strcmp(vword, ESSE) == 0)
     {
	  pdet = part_match(vword2, imp_root, sup_root, typ);
     }
     if(pdet != NULL)
     {
	  for(i = 0; pdet[i] != NULL; ++i)
	  {
	       if(pdet[i]->actio == INST && pdet[i]->vgenus == ACT &&
		  pdet[i]->casus <= ACC)
	       {
		    idetappend(&idet, ACT, INST);
	       }
	       if(pdet[i]->actio == PERF && pdet[i]->casus <= ACC)
	       {
		    idetappend(&idet, PASS, PERF);
	       }
	       free(pdet[i]);
	  }
	  free(pdet);
     }
     strcpy(str, sup_root);
     strcat(str, SUP_ACC);
     if((strcmp(vword,str) == 0 && strcmp(vword2, IRI) == 0) ||
	(strcmp(vword2, str) == 0 && strcmp(vword, IRI) == 0))
     {
	  idetappend(&idet, PASS, INST);
     }
     return idet;
}

void gdetappend(ger_det **det, int casus)
{
     *det = (ger_det *) malloc(sizeof(ger_det));
     (*det)->casus = casus;
}

ger_det **ger_match(char *vword, char *imp_root, coni_type typ)
{
     char *suffroot;
     char aroot[50];
     adj_det **adet;
     ger_det **gdet;
     int i, j = 0;

     if((typ & CONI_INFO) == FERO_TYPE)
     {
	  return fero_ger_match(vword, imp_root);
     }     
     gdet = (ger_det **) malloc(3 * sizeof(ger_det *));
     switch(typ & CONI_INFO)
     {
     case CONI1: 
	  suffroot = PART_INST_PASS1_ROOT;
	  break;
     case CONI2: 
	  suffroot = PART_INST_PASS2_ROOT;
	  break;
     case CONI3: 
	  suffroot = PART_INST_PASS3_ROOT;
	  break;
     case CONI3I: 
	  suffroot = PART_INST_PASS3I_ROOT;
	  break;
     case CONI4: 
	  suffroot = PART_INST_PASS4_ROOT;
	  break;
     }
     strcpy(aroot, imp_root);
     strcat(aroot, suffroot);
     adet = adj_match(vword, aroot, END3);
     for(i = 0; adet[i] != NULL; ++i)
     {
	  if(adet[i]->genus == NEUT && adet[i]->casus >= ACC)
	  {
	       gdetappend((ger_det **)(gdet + j), adet[i]->casus);
	       ++j;
	  }
	  free(adet[i]);
     }     
     free(adet);
     gdet[j] = NULL;
     return gdet;
}

void sdetappend(sup_det **det, int casus)
{
     *det = (sup_det *) malloc(sizeof(sup_det));
     (*det)->casus = casus;
}

sup_det *sup_match(char *vword, char *sup_root, coni_type typ)
{
     char str[50];
     sup_det *sdet;

     if((typ & CONI_INFO) == FERO_TYPE)
     {
	  return fero_sup_match(vword, sup_root);
     }
     sdet = NULL;
     strcpy(str, sup_root);
     strcat(str, SUP_ACC);
     if(strcmp(vword, str) == 0)
     {
	  sdetappend(&sdet, ACC);
     }
     strcpy(str, sup_root);
     strcat(str, SUP_ABL);
     if(strcmp(vword, str) == 0)
     {
	  sdetappend(&sdet, ABL);
     }
     return sdet;
}

part_det **fero_part_match(char *vword, char *imp_pref, char *sup_pref)
{
     char imp_root[100], sup_root[100];
     
     strcpy(imp_root, imp_pref);
     strcat(imp_root, FERO_IMP);
     strcpy(sup_root, sup_pref);
     strcat(sup_root, FERO_SUP);
     return part_match(vword, imp_root, sup_root, CONI3);
}

inf_det *fero_inf_match_simple(char *vword, char *imp_pref, char *perf_pref)
{
     inf_det *idet;

     idet = NULL;
     if(strstr(vword, imp_pref) == vword)
     {
	  if(strcmp(vword + strlen(imp_pref), FERO_INF_ACT) == 0)
	  {
	       idetappend(&idet, ACT, IMP);
	  }
	  else if(strcmp(vword + strlen(imp_pref), FERO_INF_PASS) == 0)
	  {
	       idetappend(&idet, PASS, IMP);
	  }
     }
     else if(strstr(vword, perf_pref) == vword)
     {
	  vword += strlen(perf_pref);
	  if(strstr(vword, FERO_PERF) == vword)
	  {
	       vword += strlen(FERO_PERF);
	       if(strcmp(vword, INF_PERF_ACT) == 0)
	       {
		    idetappend(&idet, ACT, PERF);
	       }
	  }
     }
     return idet;
}
     
inf_det *fero_inf_match_compound(char *vword, char *vword2, char *imp_pref,
				 char *sup_pref)
{
     char imp_root[100], sup_root[100];
     
     strcpy(imp_root, imp_pref);
     strcat(imp_root, FERO_IMP);
     strcpy(sup_root, sup_pref);
     strcat(sup_root, FERO_SUP);
     return inf_match_compound(vword, vword2, imp_root, sup_root, CONI3);
}

ger_det **fero_ger_match(char *vword, char *imp_pref)
{
     char imp_root[100];
     
     strcpy(imp_root, imp_pref);
     strcat(imp_root, FERO_IMP);
     return ger_match(vword, imp_root, CONI3);
}

sup_det *fero_sup_match(char *vword, char *sup_pref)
{
     char sup_root[100];
     
     strcpy(sup_root, sup_pref);
     strcat(sup_root, FERO_SUP);
     return sup_match(vword, sup_root, CONI3);
}

inf_det *sum_inf_match_simple(char *vword)
{
     inf_det *idet;

     idet = NULL;
     if(strstr(vword, SUM_INF_ACT) == vword)
     {
	  idetappend(&idet, ACT, IMP);
     }
     if(strstr(vword, SUM_PERF) == vword)
     {
	  vword += strlen(SUM_PERF);
	  if(strcmp(vword, INF_PERF_ACT) == 0)
	  {
	       idetappend(&idet, ACT, PERF);
	  }
     }
     return idet;
}
