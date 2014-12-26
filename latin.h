#include "nominal.h"
#include "verb.h"
#include "part.h"

#define NOUN  1
#define ADJ   2
#define VERB  3
#define POADV 4
#define PRAEP 5
#define POCON 6
#define INTIE 7
#define PRON  8
#define NUMER 9
#define CET   10

typedef struct
{
     char *form;
     char *meaning;
     char **det;
} lat_res;

lat_res **latsearch(const char *word);
lat_res **husearch(const char *word);
