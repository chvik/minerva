#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "latin.h"
#include "nominal.h"
#include "verb.h"

#define DATA_FILE "latin.dat"
#define INDEX_FILE_PREFIX "lat"
#define INDEX_FILE_POSTFIX ".ind"

#define STR_NOUN  "n"
#define STR_ADJ   "a"
#define STR_VERB  "v"
#define STR_POADV "adv"
#define STR_PRAEP "praep"
#define STR_POCON "c"
#define STR_INTIE "i"
#define STR_PRON  "pron"
#define STR_NUMER "num"
#define STR_CET   "cet"

#define STR_DECL1    "1"
#define STR_DECL2    "2"
#define STR_DECL2_0  "0"
#define STR_DECL2_ER "er"
#define STR_DECL3    "3"
#define STR_DECL3_I1 "i1" /* Csak plur. gen-ban. */
#define STR_DECL3_I2 "i2" /* Sing. abl-ban is. */
#define STR_DECL4    "4"
#define STR_DECL5    "5"

#define STR_END3          "3"
#define STR_END3_0        "0"
#define STR_END3_ER       "er"
#define STR_DECL3_END3    "33"
#define STR_DECL3_END3_ER "er"
#define STR_DECL3_END2    "2"
#define STR_DECL3_END1    "1"
#define STR_DECL3_NOT_I   "ni"
#define STR_COMP_IRREG    "ci"
#define STR_SUPER_IRREG   "si"
#define STR_SUPER_IRREG_L "sl"
#define STR_ADV_IRREG     "ai"
#define STR_NO_COMP       "nc"
#define STR_NO_SUPER      "ns"

#define STR_MASC "masc"
#define STR_FEMI "fem"
#define STR_NEUT "neut"

#define STR_CONI1  "1"
#define STR_CONI2  "2"
#define STR_CONI3  "3"
#define STR_CONI3I "3i"
#define STR_CONI4  "4"
#define STR_FERO_TYPE "f"
#define STR_CONI1_IRR "irr"

#define STR_DEPONENS      "dep"
#define STR_SEMI_DEPONENS "sdep"
#define STR_SHORT_IMPTIV  "sh"
#define STR_NO_SUPINUM    "ns"
#define STR_NO_PERFECTUM  "np"

FILE *indexf, *dataf;
int global;
long oldpos;

void convert(char *str)
{
     char tmp[100];
     int i, j;

     tmp[99] = 0;
     strncpy(tmp, str, 99);
     j = 0;
     for(i = 0; tmp[i]; ++i)
     {
	  if(!isdigit(tmp[i]))
	  {
	       str[j] = tmp[i];
	       ++j;
	  }
     }
     str[j] = 0;
}

int open_dict(char prefix)
{
     char fname[512];

     prefix = tolower(prefix);
     sprintf(fname, "%s/%s%c%s", DATA_DIR, INDEX_FILE_PREFIX, tolower(prefix),
	     INDEX_FILE_POSTFIX);
     if(prefix != 0)
     {
	  indexf = fopen(fname, "r");
	  global = 0;
	  oldpos = -1;
     }
     else
     {
	  indexf = NULL;
	  global = 1;
     }
     sprintf(fname, "%s/%s", DATA_DIR, DATA_FILE);
     if((dataf = fopen(fname, "r")) == NULL)
     {
	  fprintf(stderr, "Nem tudom megnyitni a(z) %s/%s fájlt: ", DATA_DIR,
		  DATA_FILE);
	  perror("");
	  exit(-1);
     }
     return 0;
}

void close_dict()
{
    if(indexf) fclose(indexf);
    if(dataf) fclose(dataf);
}

int read_item(int *lclass, int *ltype, int *lgen, char *lroot1,
	      char *lroot2, char *lroot3, char *nom, char *mean)
{
     char line[1025];
     long pos;
     int i;
     char strlclass[41], strltype[41], strlgen[41];
     
     if(dataf == NULL) return EOF;
     if(!global)
     {
	  if(indexf == NULL)
	  {
	       return EOF;
	  }
	  if(fread(&pos, sizeof(long), 1, indexf) == 0)
	  {
	       return EOF;
	  }
	  if(pos > oldpos)
	  {
	       for(i = oldpos + 1; i <= pos; ++i)
	       {
		    fgets(line, 1024, dataf);
	       }
	  } else
	  {
	       rewind(dataf);
	       for(i = 0; i <= pos; ++i)
	       {
		    fgets(line, 1024, dataf);
	       }
	  }
	  oldpos = pos;
     } else
     {
	  fgets(line, 1024, dataf);
     }
     if(feof(dataf))
     {
	  return EOF;
     } else
     {
	  sscanf(line, "%40s %19s", strlclass, lroot1);
	  lroot2[0] = 0;
	  lroot3[0] = 0;
	  if(strcmp(lroot1, ".") == 0)
	  {
	       lroot1[0] = 0;
	  }
	  if(strcmp(strlclass, STR_NOUN) == 0)
	  {
	       *lclass = NOUN;
	       sscanf(line, "%*s %*s %40s %40s", strltype, strlgen);
	       if(strcmp(strlgen, STR_MASC) == 0)
	       {
		    *lgen = MASC;
	       }
	       else if(strcmp(strlgen, STR_FEMI) == 0)
	       {
		    *lgen = FEMI;
	       }
	       else if(strcmp(strlgen, STR_NEUT) == 0)
	       {
		    *lgen = NEUT;
	       }
	       else
	       {
		    fprintf(stderr, "%s%s: érvénytelen fõnévi nem\n", line,
			    strlgen);
		    exit(-1);
	       }
	       if(strstr(strltype, STR_DECL1) == strltype)
	       {
		    *ltype = DECL1;
	       }
	       else if(strstr(strltype, STR_DECL2) == strltype)
	       {
		    *ltype = DECL2;
		    if(strstr(strltype, STR_DECL2_0))
		    {
			 *ltype |= DECL2_0;
		    }
		    if(strstr(strltype, STR_DECL2_ER))
		    {
			 *ltype |= DECL2_ER;
		    }
	       }
	       else if(strstr(strltype, STR_DECL3) == strltype)
	       {
		    *ltype = DECL3;
		    if(strstr(strltype, STR_DECL3_I1))
		    {
			 *ltype |= DECL3_I1;
		    }
		    if(strstr(strltype, STR_DECL3_I2))
		    {
			 *ltype |= DECL3_I2;
		    }
		    sscanf(line, "%*s %*s %*s %*s %19s", nom);
	       }
	       else if(strstr(strltype, STR_DECL4) == strltype)
	       {
		    *ltype = DECL4;
	       }
	       else if(strstr(strltype, STR_DECL5) == strltype)
	       {
		    *ltype = DECL5;
	       }
	       else
	       {
		    fprintf(stderr, "%s%s: érvénytelen declinatio\n", line,
			    strltype);
		    exit(-1);
	       }
	  }
	  else if(strcmp(strlclass, STR_ADJ) == 0)
	  {
	       *lclass = ADJ;
	       sscanf(line, "%*s %*s %40s", strltype);
	       if(strstr(strltype, STR_END3) == strltype)
	       {
		    *ltype = END3;
		    if(strstr(strltype, STR_END3_0))
		    {
			 *ltype |= END3_0;
		    }
		    if(strstr(strltype, STR_END3_ER))
		    {
			 *ltype |= END3_ER;
		    }
	       }
	       else if(strstr(strltype, STR_DECL3_END3) == strltype)
	       {
		    *ltype = DECL3_END3;
		    if(strstr(strltype, STR_DECL3_END3_ER))
		    {
			 *ltype |= DECL3_END3_ER;
		    }
	       }
	       else if(strstr(strltype, STR_DECL3_END2) == strltype)
	       {
		    *ltype = DECL3_END2;
	       }
	       else if(strstr(strltype, STR_DECL3_END1) == strltype)
	       {
		    *ltype = DECL3_END1;
		    if(strstr(strltype, STR_DECL3_NOT_I))
		    {
			 *ltype |= DECL3_NOT_I;
		    }
		    sscanf(line, "%*s %*s %*s %19s", nom);
	       }
	       else
	       {
		    fprintf(stderr, "%s%s: érvénytelen melléknévi típus\n",
			    line, strltype);
		    exit(-1);
	       }
	       if(strstr(strltype, STR_COMP_IRREG))
	       {
		    *ltype |= COMP_IRREG;
	       }
	       if(strstr(strltype, STR_SUPER_IRREG))
	       {
		    *ltype |= SUPER_IRREG;
	       }
	       if(strstr(strltype, STR_SUPER_IRREG_L))
	       {
		    *ltype |= SUPER_IRREG_L;
	       }
	       if(strstr(strltype, STR_ADV_IRREG))
	       {
		    *ltype |= ADV_IRREG;
	       }
	       if(strstr(strltype, STR_NO_COMP))
	       {
		    *ltype |= NO_COMP;
	       }
	       if(strstr(strltype, STR_NO_SUPER))
	       {
		    *ltype |= NO_SUPER;
	       }
	  }
	  else if(strcmp(strlclass, STR_VERB) == 0)
	  {
	       *lclass = VERB;
	       sscanf(line, "%*s %*s %19s %19s %s", lroot2, lroot3, strltype);
	       if(strcmp(lroot2, ".") == 0)
	       {
		    lroot2[0] = 0;
	       }
	       if(strcmp(lroot3, ".") == 0)
	       {
		    lroot3[0] = 0;
	       }
	       if(strstr(strltype, STR_CONI1) == strltype)
	       {
		    *ltype = CONI1;
		    if(strstr(strltype, STR_CONI1_IRR))
		    {
			 *ltype |= CONI1_IRR;
		    }
	       }
	       else if(strstr(strltype, STR_CONI2) == strltype)
	       {
		    *ltype = CONI2;
	       }
	       else if(strstr(strltype, STR_CONI3I) == strltype)
	       {
		    *ltype = CONI3I;
	       }
	       else if(strstr(strltype, STR_CONI3) == strltype)
	       {
		    *ltype = CONI3;
	       }
	       else if(strstr(strltype, STR_CONI3I) == strltype)
	       {
		    *ltype = CONI3I;
	       }
	       else if(strstr(strltype, STR_CONI4) == strltype)
	       {
		    *ltype = CONI4;
	       }
	       else if(strstr(strltype, STR_FERO_TYPE) == strltype)
	       {
		    *ltype = FERO_TYPE;
	       }
	       else
	       {
		    fprintf(stderr, "%s%s: érvénytelen coniugatio\n", line,
			    strltype);
		    exit(-1);
	       }
	       if(strstr(strltype, STR_DEPONENS))
	       {
		    *ltype |= DEPONENS;
	       }
	       if(strstr(strltype, STR_SEMI_DEPONENS))
	       {
		    *ltype |= SEMI_DEPONENS;
	       }
	       if(strstr(strltype, STR_SHORT_IMPTIV))
	       {
		    *ltype |= SHORT_IMPTIV;
	       }
	       if(strstr(strltype, STR_NO_SUPINUM))
	       {
		    *ltype |= NO_SUPINUM;
	       }
	       if(strstr(strltype, STR_NO_PERFECTUM))
	       {
		    *ltype |= NO_PERFECTUM;
	       }
	  }
	  else if(strcmp(strlclass, STR_POADV) == 0)
	  {
	       *lclass = POADV;
	  }
	  else if(strcmp(strlclass, STR_PRAEP) == 0)
	  {
	       *lclass = PRAEP;
	  }
	  else if(strcmp(strlclass, STR_INTIE) == 0)
	  {
	       *lclass = INTIE;
	  }
	  else if(strcmp(strlclass, STR_CET) == 0)
	  {
	       *lclass = CET;
	  }
	  else if(strcmp(strlclass, STR_POCON) == 0)
	  {
	       *lclass = POCON;
	  }
	  else if(strcmp(strlclass, STR_PRON) == 0)
	  {
	       *lclass = PRON;
	       lroot2[0] = 0;
	       lroot3[0] = 0;
	       sscanf(line, "%*s %*s %19[^# \t] %19[^# \t]", lroot2, lroot3);
	  }
	  else if(strcmp(strlclass, STR_NUMER) == 0)
	  {
	       *lclass = NUMER;
	       lroot2[0] = 0;
	       lroot3[0] = 0;
	       sscanf(line, "%*s %*s %19[^# \t] %19[^# \t]", lroot2, lroot3);
	  }
	  else
	  {
	       fprintf(stderr, "%s%s: érvénytelen szófaj\n", line,
		       strlclass);
	       exit(-1);
	  }
	  strcpy(mean, "Nincs megadva a jelentés.");
	  sscanf(line, "%*[^#]# %199[^\n]", mean);
     }
     return 0;
}

