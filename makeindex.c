#include <stdio.h>
#include <ctype.h>
#include "data.h"
#include "latin.h"
#include "nominal.h"
#include "verb.h"

int main() {
     char lroot1[50], lroot2[50], lroot3[50], nom[50];
     char mean[200];
     char fname[50];
     int lclass, ltype, lgen, i;
     long pos;
     FILE *indexf['z' - 'a' + 1];
     
     if(open_dict(0) == -1)
     {
	  perror("Open error");
	  exit(-1);
     }
     for(i = 0; i <= 'z' - 'a'; ++i)
     {
	  sprintf(fname, "lat%c.ind", i + 'a');
	  indexf[i] = fopen(fname, "w");
     }
     pos = 0;
     while(read_item(&lclass, &ltype, &lgen, lroot1, lroot2, lroot3,
		     nom, mean) != EOF)
     {
	  /* v . . . f = fero */
	  if(lroot1[0] == 0 && lclass == VERB &&
	     (ltype & CONI_INFO) == FERO_TYPE)
	  {
	       char *f1 = FERO_IMP;
	       char *f2 = FERO_PERF;
	       char *f3 = FERO_SUP;	      
	       fwrite(&pos, sizeof(long), 1, indexf[f1[0] - 'a']);
	       fwrite(&pos, sizeof(long), 1, indexf[f2[0] - 'a']);
	       fwrite(&pos, sizeof(long), 1, indexf[f3[0] - 'a']);
	  }
	  if(isupper(lroot1[0]))
	  {
	       lroot1[0] = tolower(lroot1[0]);
	  }
	  if(islower(lroot1[0]))
	  {
	       fwrite(&pos, sizeof(long), 1, indexf[lroot1[0] - 'a']);
	  }
	  if((lclass == NOUN && (ltype & DECL_INFO) == DECL3) ||
	     (lclass == ADJ && (ltype & END_INFO) == DECL3_END1))
	  {
	       if(isupper(nom[0]))
	       {
		    nom[0] = tolower(nom[0]);
	       }
	       if(nom[0] != lroot1[0] && islower(nom[0]))
	       {
		    fwrite(&pos, sizeof(long), 1, indexf[nom[0] - 'a']);
	       }
	  }
	  if(lclass == VERB)
	  {
	       if(isupper(lroot2[0]))
	       {
		    lroot2[0] = tolower(lroot2[0]);
	       }
	       if(lroot2[0] != lroot1[0] && islower(lroot2[0]))
	       {
		    fwrite(&pos, sizeof(long), 1, indexf[lroot2[0] - 'a']);
	       }
	       if(isupper(lroot3[0]))
	       {
		    lroot3[0] = tolower(lroot3[0]);
	       }
	       if(lroot3[0] != lroot2[0] && lroot3[0] != lroot1[0] &&
		  islower(lroot3[0]))
	       {
		    fwrite(&pos, sizeof(long), 1, indexf[lroot3[0] - 'a']);
	       }
	  }
	  if(lclass == PRON || lclass == NUMER)
	  {
	       if(lroot2[0])
	       {
		    if(isupper(lroot2[0]))
		    {
			 lroot2[0] = tolower(lroot2[0]);
		    }
		    if(lroot2[0] != lroot1[0] && islower(lroot2[0]))
		    {
			 fwrite(&pos, sizeof(long), 1,
				indexf[lroot2[0] - 'a']);
		    }
	       }
	       if(lroot3[0])
	       {
		    if(isupper(lroot3[0]))
		    {
			 lroot3[0] = tolower(lroot3[0]);
		    }
		    if(lroot3[0] != lroot2[0] && lroot3[0] != lroot1[0] &&
		       islower(lroot3[0]))
		    {
			 fwrite(&pos, sizeof(long), 1,
				indexf[lroot3[0] - 'a']);
		    }
	       }
	  }
	  ++pos;
     }
     for(i = 0; i <= 'z' - 'a'; ++i)
     {
	  fclose(indexf[i]);
     }     
     return 0;
}
