int open_dict(char prefix);
void close_dict();
int read_item(int *lclass, int *ltype, int *lgen, char *lroot1,
	      char *lroot2, char *lroot3, char *nom, char *mean);
