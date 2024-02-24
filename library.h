#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct slovar{
	char word[20];
	char *tolk;
	int udar;
}slovar;

int inputstc(slovar **ptr, int *len);
int outstc(slovar **ptr, int *len);
int inputfile(slovar **ptr, int *len);
int outfile(slovar **ptr, int *len);
int inputbin(slovar **ptr, int *len);
int outbin(slovar **ptr, int *len);
int sortik(slovar *ptr, int number, int napravl, int len);
int getnap();
int getnum();
int wordcomp(const void *a, const void *b);
int wordcomp2(const void *a, const void *b);
int tolkcomp(const void *a, const void *b);
int tolkcomp2(const void *a, const void *b);
int udarcomp(const void *a, const void *b);
int udarcomp2(const void *a, const void *b);
void shaker(void *a, size_t len, size_t size, int(*compare)(const void *,const void *));
void doubleselectionsort(void *a, size_t len, size_t size, int(*compare)(const void *, const void*));
void myrandom(slovar **ptr, int *len);
int getn();
int getm();
int sortik2(slovar *ptr, int number, int napravl, int n, int m);

#endif
