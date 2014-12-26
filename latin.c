#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "latin.h"
#include "data.h"
#include "nominal.h"
#include "verb.h"

char *ttnnum[2] = { "sing.", "plur." };
char *ttncasus[5] = { "nom.", "acc.", "gen.", "dat.", "abl." };
char *ttngen[3] = { "m", "f", "n" };
char *ttgradus[3] = { "", "comparat.", "superlat." };
char *ttvnum[2] = { "sing.", "plur." };
char *ttvgen[2] = { "act.", "pass." };
char *ttvmod[2] = { "ind.", "con." };
char *ttvtemp[3] = { "praes.", "praet.", "fut." }; 
char *ttvact[3] = { "imp.", "perf.", "inst." };
char *ttadv = "adverbium";
char *ttpart = "part.";
char *ttcon = "coniunctio";
char *ttinterie = "interiectio";
char *ttpraep = "praepositio";
char *ttpron = "pronomen";

int pick_words(const char *arg, char *first, char *second)
{
     second[0] = 0;
     return(sscanf(arg, "%s %s", first, second));
}

void resappend(lat_res **res, char* form, char *meaning, char **det)
{
     int i;

     *res = (lat_res *) malloc(sizeof(lat_res));
     (*res)->form = (char *) malloc(strlen(form) + 1);
     strcpy((*res)->form , form);
     (*res)->meaning = (char *) malloc(strlen(meaning) + 1);
     strcpy((*res)->meaning , meaning);
     (*res)->det = (char **) malloc(10 * sizeof(char *));
     for(i = 0; det[i] != NULL; ++i)
     {
	  (*res)->det[i] = (char *) malloc(strlen(det[i]) + 1);
	  strcpy((*res)->det[i], det[i]);
     }
     (*res)->det[i] = NULL;
}

char **ngenerate_dets(noun_det **ndet)
{
     int i;
     char **det;
     
     det = (char **) malloc(10 * sizeof(char *));
     for(i = 0; ndet[i] != NULL; ++i)
     {
	  det[i] = (char *)malloc(50);
	  sprintf(det[i], "%s %s", ttnnum[ndet[i]->num],
		  ttncasus[ndet[i]->casus]);
     }
     det[i] = NULL;
     return det;
}

char **agenerate_dets(adj_det **adet)
{
     int i, j = 0;
     char **det;
     genus_type gen;
     
     det = (char **) malloc(10 * sizeof(char *));
     if(adet && adet[0]->genus == ADV)
     {
	  for(i = 0; adet[i] != NULL; ++i)
	  {
	       det[j] = (char *)malloc(50);
	       if(adet[i]->gradus == POSIT)
	       {
		    sprintf(det[j], "%s", ttadv);
	       } else
	       {
		    sprintf(det[j], "%s %s", ttadv, ttgradus[adet[i]->gradus]);
	       }
	       ++j;
	  }
     } else
     {
	  for(gen = MASC; gen <= NEUT; ++gen)
	  {	  
	       for(i = 0; adet[i] != NULL; ++i)
	       {
		    if(adet[i]->genus == gen)
		    {
			 det[j] = (char *)malloc(50);
			 if(adet[i]->gradus == POSIT)
			 {
			      sprintf(det[j], "%s %s %s",
				      ttngen[adet[i]->genus],
				      ttnnum[adet[i]->num],
				      ttncasus[adet[i]->casus]);
			 } else
			 {
			      sprintf(det[j], "%s %s %s %s",
				      ttgradus[adet[i]->gradus],
				      ttngen[adet[i]->genus],
				      ttnnum[adet[i]->num],
				      ttncasus[adet[i]->casus]);
			 }
			 ++j;
		    }
	       }
	  }
     }
     det[j] = NULL;
     return det;
}

char **vgenerate_dets(verb_det **vdet)
{
     int i;
     char **det;
     
     det = (char **) malloc(10 * sizeof(char *));
     for(i = 0; vdet[i] != NULL; ++i)
     {
	  det[i] = (char *)malloc(50);
	  if(vdet[i]->modus <= CON)
	  {
	       sprintf(det[i], "%s %s %s %s %s %d",
		       ttvgen[vdet[i]->genus],
		       ttvmod[vdet[i]->modus],
		       ttvtemp[vdet[i]->tempus],
		       ttvact[vdet[i]->actio],
		       ttvnum[vdet[i]->num],
		       vdet[i]->pers + 1);
	  }
	  else if(vdet[i]->modus == IMPTIV1)
	  {
	       sprintf(det[i], "%s imperat1 %s %d",
		       ttvgen[vdet[i]->genus],
		       ttvnum[vdet[i]->num], vdet[i]->pers + 1);
	  }
	  else if(vdet[i]->modus == IMPTIV2)
	  {
	       sprintf(det[i], "%s imperat2 %s %d",
		       ttvgen[vdet[i]->genus],
		       ttvnum[vdet[i]->num], vdet[i]->pers + 1);
	  }
     }
     det[i] = NULL;
     return det;
}

char **pgenerate_dets(part_det **pdet)
{
     int i;
     char **det;

     det = (char **) malloc(10 * sizeof(char *));
     for(i = 0; pdet[i] != NULL; ++i)
     {
	  det[i] = (char *) malloc(50);
	  if(pdet[i]->gradus == POSIT)
	  {       
	       sprintf(det[i], "%s %s %s %s %s %s", ttpart,
		       ttvact[pdet[i]->actio],
		       ttvgen[pdet[i]->vgenus],
		       ttvnum[pdet[i]->num],
		       ttncasus[pdet[i]->casus],
		       ttngen[pdet[i]->ngenus]);
	  } else
	  {
	       sprintf(det[i], "%s %s %s %s %s %s %s", ttpart,
		       ttvact[pdet[i]->actio],
		       ttvgen[pdet[i]->vgenus],
		       ttvnum[pdet[i]->num],
		       ttncasus[pdet[i]->casus],
		       ttngen[pdet[i]->ngenus],
		       ttgradus[pdet[i]->gradus]);
	  }
     }
     det[i] = NULL;
     return det;
}

char **igenerate_dets(inf_det *idet)
{
     char **det;

     det = (char **) malloc(2 * sizeof(char *));
     det[0] = (char *) malloc(50);
     sprintf(det[0], "inf. %s %s", ttvact[idet->actio], ttvgen[idet->genus]);
     det[1] = NULL;
     return det;
}

char **ggenerate_dets(ger_det **gdet)
{
     int i;
     char **det;
     
     det = (char **) malloc(10 * sizeof(char *));
     for(i = 0; gdet[i] != NULL; ++i)
     {
	  det[i] = (char *) malloc(50);
	  sprintf(det[i], "gerundium %s", ttncasus[gdet[i]->casus]);
     }
     det[i] = NULL;
     return det;
}

char **sgenerate_dets(sup_det *sdet)
{
     char **det;

     det = (char **) malloc(2 * sizeof(char *));
     det[0] = (char *) malloc(50);
     sprintf(det[0], "sup. %s", ttncasus[sdet->casus]);
     det[1] = NULL;
     return det;
}


lat_res **latsearch(const char *arg)
{
     char lword[50], lword2[50], lroot1[50], lroot2[50], lroot3[50], nom[50];
     char mean[200], form[50];
     int lclass, ltype, lgen, i, j = 0, k;
     noun_det **ndet;
     adj_det **adet;
     verb_det **vdet;
     part_det **pdet;
     inf_det *idet;
     sup_det *sdet;
     ger_det **gdet;
     adv_det *advdet;
     int simple;
     lat_res **res;
     int found;
     char **det, **tmpdet, *tmpform;

     res = (lat_res **) malloc(10 * sizeof(lat_res *));
     /* Ha nincs adatfájl */
     pick_words(arg, lword, lword2);
     if(open_dict(lword[0]) == -1)
     {
	  res[0] = NULL;
	  return res;
     }
     simple = (strlen(lword2) == 0);
     if(simple)
     {
	  /* Illesztés a létigére */
	  vdet = sum_match(lword);
	  if(vdet[0])
	  {
	       strcpy(form, SUM_FORM);
	       strcpy(mean, SUM_MEAN);
	       det = vgenerate_dets(vdet);
	       resappend(res + j, form, mean, det);
	       ++j;
	       for(i = 0; det[i]; ++i) free(det[i]);
	       free(det);
	  }
	  for(i = 0; vdet[i]; ++i) free(vdet[i]);	       
	  free(vdet);
	  idet = sum_inf_match_simple(lword);
	  if(idet)
	  {
	       strcpy(form, SUM_FORM);
	       strcpy(mean, SUM_MEAN);
	       det = igenerate_dets(idet);
	       resappend(res + j, form, mean, det);
	       ++j;
	       free(idet);
	       for(i = 0; det[i]; ++i) free(det[i]);
	       free(det);
	  }
     }
     while(read_item(&lclass, &ltype, &lgen, lroot1, lroot2, lroot3,
		     nom, mean) != EOF)
     {
/*	  printf("debug: %d %s\n", lclass, lroot1);*/
	  found = 0;
	  /* Fõnév */
	  if(lclass == NOUN && simple)
	  {
	       ndet = noun_match(lword, lroot1, ltype, lgen, nom);
	       if(ndet[0])
	       {
		    tmpform = noun_form(lroot1, ltype, lgen, nom);
		    strcpy(form, tmpform);
		    free(tmpform);
		    det = ngenerate_dets(ndet);
		    found = 1;
	       }
	       for(i = 0; ndet[i]; ++i) free(ndet[i]);
	       free(ndet);
	  }
	  /* Melléknév és adverbium */
	  else if(lclass == ADJ && simple)
	  {
	       adet = adj_match(lword, lroot1, ltype, nom);
	       if(adet[0])
	       {
		    tmpform = adj_form(lroot1, ltype, nom);
		    strcpy(form, tmpform);
		    free(tmpform);
		    det = agenerate_dets(adet);
		    found = 1;
	       }
	       advdet = adv_match(lword, lroot1, ltype);
	       if(advdet)
	       {
		    /* Ha nem illeszkedik melléknévre */
		    if(!found)
		    {
			 tmpform = adj_form(lroot1, ltype, nom);
			 strcpy(form, tmpform);
			 free(tmpform);
			 found = 1;
			 det = (char **) malloc(2 * sizeof(char *));
			 det[0] = NULL;
		    }
 		    /* Hozzáfûzzük a végére */
		    for(i = 0; det[i] != NULL; ++i);
		    det[i] = (char *) malloc(50);
		    if(advdet->gradus == POSIT)
		    {
			 sprintf(det[i], "%s\n", ttadv);
		    } else
		    {
			 sprintf(det[i], "%s %s", ttadv,
				 ttgradus[advdet->gradus]);
		    }
		    det[i + 1] = NULL;
		    free(advdet);
	       }
	       for(i = 0; adet[i]; ++i) free(adet[i]);
	       free(adet);
	  }
	  /* Ige */
	  else if(lclass == VERB)
	  {
	       /* -are, -avi, -atum ragozás */
	       if((ltype & CONI_INFO) == 1 && !(ltype & CONI1_IRR))
	       {
		    sprintf(lroot2, "%s%s", lroot1, CONI1_PERF);
		    sprintf(lroot3, "%s%s", lroot1, CONI1_SUP);
	       }
	       /* Egyszerû */
	       if(simple)
	       {
		    vdet = verb_match_simple(lword, lroot1, lroot2, ltype);
		    pdet = part_match(lword, lroot1, lroot3, ltype);
		    idet = inf_match_simple(lword, lroot1, lroot2, ltype);
		    gdet = ger_match(lword, lroot1, ltype);
		    sdet = sup_match(lword, lroot3, ltype);
		    if(vdet[0] || pdet[0] || idet || sdet || gdet[0])
		    {
			 tmpform = verb_form(lroot1, lroot2, lroot3, ltype);
			 strcpy(form, tmpform);
			 free(tmpform);
			 found = 1;
			 det = (char **) malloc(20 * sizeof(char *));
			 k = 0;			 
		    }
		    /* Igére illeszkedett */
		    if(vdet[0])
		    {
			 tmpdet = vgenerate_dets(vdet);
			 for(i = 0; tmpdet[i]; ++i)
			 {
			      det[k] = tmpdet[i];
			      ++k;
			 }
			 free(tmpdet);
			 det[k] = NULL;
		    }
		    /* Participiumra illeszkedett */
		    if(pdet[0])
		    {
			 tmpdet = pgenerate_dets(pdet);
			 for(i = 0; tmpdet[i]; ++i)
			 {
			      det[k] = tmpdet[i];
			      ++k;
			 }
			 free(tmpdet);
			 det[k] = NULL;
		    }
		    /* Infinitivusra illeszkedett */
		    if(idet)
		    {
			 tmpdet = igenerate_dets(idet);
			 for(i = 0; tmpdet[i]; ++i)
			 {
			      det[k] = tmpdet[i];
			      ++k;
			 }
			 free(tmpdet);
			 free(idet);
			 det[k] = NULL;
		    }
		    /* Supinumra illeszkedett */
		    if(sdet)
		    {
			 tmpdet = sgenerate_dets(sdet);
			 for(i = 0; tmpdet[i]; ++i)
			 {
			      det[k] = tmpdet[i];
			      ++k;
			 }
			 free(tmpdet);
			 free(sdet);
			 det[k] = NULL;
		    }
		    /* Gerundiumra illeszkedett */
		    if(gdet[0])
		    {
			 tmpdet = ggenerate_dets(gdet);
			 for(i = 0; tmpdet[i]; ++i)
			 {
			      det[k] = tmpdet[i];
			      ++k;
			 }
			 free(tmpdet);
			 det[k] = NULL;
		    }
		    for(i = 0; vdet[i]; ++i) free(vdet[i]);
		    free(vdet);
		    for(i = 0; gdet[i]; ++i) free(gdet[i]);
		    free(gdet);
		    for(i = 0; pdet[i]; ++i) free(pdet[i]);
		    free(pdet);
	       } else		   
	       {
		    /* Összetett (participium + létige) */
		    vdet = verb_match_compound(lword, lword2, lroot1, lroot3,
					       ltype);
		    idet = inf_match_compound(lword, lword2, lroot1, lroot3,
					       ltype);
		    if(vdet[0] || idet)
		    {
			 tmpform = verb_form(lroot1, lroot2, lroot3, ltype);
			 strcpy(form, tmpform);
			 free(tmpform);
			 found = 1;
			 k = 0;
		    }			 
		    if(vdet[0])
		    {
			 det = vgenerate_dets(vdet);
		    }
		    if(idet)
		    {
			 det = igenerate_dets(idet);
			 free(idet);
		    }
		    for(i = 0; vdet[i]; ++i) free(vdet[i]);
		    free(vdet);
	       }
	  }
	  /* Egyéb, ragozhatatlan szófajok */
	  else if(lclass == POADV || lclass == PRAEP || lclass == INTIE ||
	       lclass == POCON || lclass == CET)
	  {
	       if(strcmp(lword, lroot1) == 0)
	       {
		    found = 1;
		    det = (char **) malloc(2 * sizeof(char *));
		    det[0] = NULL;
		    sprintf(form, lroot1);
	       }
	  }
	  /* Névmás, számnév */
	  else if(lclass == PRON || lclass == NUMER)
	  {
	       det = (char **) malloc(2 * sizeof(char *));
	       det[0] = NULL;
	       if(lroot2[0] && lroot3[0])
	       {
		    /* Három végû */
		    if(strcmp(lword, lroot1) == 0 ||
		       strcmp(lword, lroot2) == 0 ||
		       strcmp(lword, lroot3) == 0)
		    {
			 found = 1;
			 sprintf(form, "%s, %s, %s", lroot1, lroot2, lroot3);
		    }
	       }
	       /* Két végû */
	       else if(lroot2[0])
	       {
		    if(strcmp(lword, lroot1) == 0 ||
		       strcmp(lword, lroot2) == 0)
		    {
			 found = 1;
			 sprintf(form, "%s, %s", lroot1, lroot2);
		    }
		    /* Egy végû */
	       } else
	       {
		    if(strcmp(lword, lroot1) == 0)
		    {
			 found = 1;
			 sprintf(form, "%s", lroot1);
		    }
	       }
	  }
	  if(found)
	  {
	       resappend(res + j, form, mean, det);
	       ++j;
	       for(i = 0; det[i]; ++i) free(det[i]);
	       free(det);
	  }
     }
     close_dict();
     res[j] = NULL;
     return res;
}

lat_res **husearch(const char *word)
{
     int lclass, ltype, lgen;
     char lroot1[50], lroot2[50], lroot3[50], nom[50], mean[200], form[80];
     char **det;
     lat_res **res;
     char *tmp, *tmpform;
     int j = 0;
     
     res = (lat_res **) malloc(100 * sizeof(lat_res *));
     det = (char **) malloc(sizeof(char *));
     *det = NULL;
     /* Létige */
     if((tmp = strstr(SUM_MEAN, word)) != NULL &&
	(tmp == SUM_MEAN || *(tmp - 1) == ' ') &&
	(*(tmp + strlen(word)) == '\0' || *(tmp + strlen(word)) == ' ' ||
	 *(tmp + strlen(word)) == ',' || *(tmp + strlen(word)) == ';'))
     {
	resappend(res + j, SUM_FORM, SUM_MEAN, det);
	++j;
     }
     /* Ha nincs adatfájl */
     if(open_dict(0) == -1)
     {
	  res[0] = NULL;
	  return res;
     }
     while(read_item(&lclass, &ltype, &lgen, lroot1, lroot2, lroot3,
		     nom, mean) != EOF)
     {
	  if((tmp = strstr(mean, word)) != NULL &&
	     (tmp == mean || *(tmp - 1) == ' ') &&
	     (*(tmp + strlen(word)) == '\0' || *(tmp + strlen(word)) == ' ' ||
	      *(tmp + strlen(word)) == ',' || *(tmp + strlen(word)) == ';'))
	  {
	       if(lclass == NOUN)
	       {
		    tmpform = noun_form(lroot1, ltype, lgen, nom);
		    strcpy(form, tmpform);
		    free(tmpform);
	       }
	       else if(lclass == ADJ)
	       {
		    tmpform = adj_form(lroot1, ltype, nom);
		    strcpy(form, tmpform);
		    free(tmpform);
	       }
	       else if(lclass == VERB)
	       {
		    if((ltype & CONI_INFO) == 1 && !(ltype & CONI1_IRR))
		    {
			 sprintf(lroot2, "%s%s", lroot1, CONI1_PERF);
			 sprintf(lroot3, "%s%s", lroot1, CONI1_SUP);
		    }
		    strcpy(form, verb_form(lroot1, lroot2, lroot3, ltype));
	       }
	       else if(lclass == POADV || lclass == PRAEP || lclass == POCON ||
		       lclass == INTIE || lclass == CET)
	       {
		    strcpy(form, lroot1);
	       }
	       else if(lclass == PRON || lclass == NUMER)
	       {
		    strcpy(form, lroot1);
		    if(lroot2[0])
		    {
			 strcat(form, ", ");
			 strcat(form, lroot2);
			 if(lroot3[0])
			 {
			      strcat(form, ", ");
			      strcat(form, lroot3);
			 }
		    }
	       }
	       resappend(res + j, form, mean, det);
	       ++j;
	  }
     }
     free(*det);
     free(det);
     close_dict();
     res[j] = NULL;
     return res;
}

