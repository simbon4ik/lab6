#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "input.h"
#include "library.h"
#include <string.h>
#include <limits.h>
#include <readline/readline.h>
#include <time.h>
#include <math.h>

int inputstc(slovar **ptr, int *len){
	printf("len = %d \n",*len);
	*ptr = realloc(*ptr,(*len)*sizeof(slovar));
	char word[20];
	int udar = 0;
	printf("Введите слово: \n");
	scanf("%s",word);
	int i = (*len) - 1;
	strcpy( (*(ptr)+i)->word,word);
	char *tolk = readline("Введите толкование слова: \n");
	(*(ptr)+i)->tolk = tolk;
	printf("Введите номер ударной гласной в слове: \n");
	int op = getint(&udar,0,20);
	if (op == -1) return 2;
	(*(ptr)+i)->udar = udar;
	(*len) +=1;
	return 0;
}

int outstc(slovar **ptr, int *len){
	for(int i = 0; i < (*len)-1; i++){
		printf("Структура номер %d = {%s, %s, %d} \n",i+1,(*(ptr)+i)->word,(*(ptr)+i)->tolk,(*(ptr)+i)->udar);
	}
	return 0;
}

/*
int existencefile(const char *filename){
	if (FILE *f = fopen(filename,"r")){
		fclose(file);
		return 1;
	}
	return 0;
}
*/

// word - char[20]
// tolk - char* 

int inputfile(slovar **ptr, int *len){
	char *filename = readline("Введите имя файла txt \n");
	FILE *f = fopen(filename,"a");
    	for(int i = 0; i < (*len)-1; i++){
		fprintf(f, "%s\n", (*(ptr)+i)->word);
		fprintf(f, "%s\n", (*(ptr)+i)->tolk);		
		fprintf(f, "%d\n", (*(ptr)+i)->udar);
	}
	fclose(f);
	free(filename);
	return 0;
}

int outfile(slovar **ptr, int *len){
	char *filename = readline("Введите имя файла txt \n");
	FILE *f = fopen(filename,"r");
	if (f == NULL){
		printf("Файлика не существует :( \n");
		free(filename);
	       	return 2;
	}
	char s[20]; 	
	int b = 0;	
	while (!feof(f)){
		int i = *len-1;
		if (fscanf(f,"%s",s) > 0){
			*ptr = (slovar*)realloc(*ptr,(*len)*sizeof(slovar));
			printf("Первое слово, считанное из файла = %s \n",s);
			strcpy(( (*ptr)+i)->word,s);
		}
		char *s = freadline2(f);
		if (s != NULL){
			( (*ptr)+i)->tolk = freadline2(f);
			printf("Второе = %s \n",((*ptr)+i) -> tolk);
		}
		if (fscanf(f,"%d",&b) > 0){		
			( (*ptr)+i)->udar = b;
			printf("Третье = %d \n",b);
		}
		*len += 1;
		free(s);
	}
	free(filename);
	*len -=1;
	return 0;
}


int inputbin(slovar **ptr, int *len){
	char *filename = readline("Введите имя файла bin \n");
	FILE *f = fopen(filename,"ab");
	for(int i = 0; i< (*len)-1; i++){
		int lenstr = strlen( (*(ptr)+i) -> tolk);
		fwrite( (*(ptr)+i)->word, sizeof(char), 20, f);
		fwrite( &lenstr, sizeof(int), 1, f);
		fwrite( (*(ptr)+i)->tolk,sizeof(char),lenstr,f);
		fwrite( &( (*(ptr)+i)->udar), sizeof(int), 1, f);
	}
	fclose(f);
	free(filename);
	return 0;
}


int outbin(slovar **ptr, int *len){
	char *filename = readline("Введите имя файла bin \n");
	FILE *f = fopen(filename,"rb");
	if (f == NULL){
		printf("Файлика не существует :( \n");
		free(filename);
	       	return 2;
	}
	char s[20];
	int b = 0;
	while (!feof(f)){
		int i = *len-1;
		if (fread(s, sizeof(char), 20 , f) > 0){
			*ptr = realloc(*ptr,(*len)*sizeof(slovar));
			printf("Первое слово, считанное из файла = %s \n",s);
			strcpy( (*(ptr)+i)->word,s);
		}
		else{
			*len+=1;
			break;
		}
		if (fread(&b, sizeof(int), 1, f) > 0){
			((*ptr)+i) -> tolk = (char*)calloc(b+1,sizeof(char));
		}
		if (fread( ((*ptr)+i) -> tolk , sizeof(char), b, f) > 0){
			(((*ptr)+i) -> tolk)[b] = '\0';
			printf("Второе = %s \n",((*ptr)+i) -> tolk);
		}
		if (fread(&b,sizeof(int), 1, f) > 0){		
			( *(ptr)+i)->udar = b;
			printf("Третье = %d \n",b);
		}
		*len += 1;
	}
	*len -=1;
	free(filename);
	return 0;
}

int sortik(slovar *ptr, int number, int napravl, int len){
	int k = 0;
	if ((number == 0) || (napravl == 0)){
		printf("Сначала выберите поле структуры и направление сортировки  (Пункты 2 и 3) \n");
		return 0;
	}
	printf("Введите номер сортировки, которую вы хотите использовать:\n1. Shaker sort\n2. Double selection sort\n3. Qsort \n");
	int op = getint(&k,0,3);
	if (op == -1)	return 10;
	int (*fptr)(const void *a, const void* b);	
	int (*masf[])(const void *a,const void *b) = {&wordcomp2,&tolkcomp2,&udarcomp2,&wordcomp,&tolkcomp,&udarcomp};
	int ukaz = (napravl-1)*3 + (number - 1);
	switch(k){
		case 1:
			shaker(ptr,len-1,sizeof(*ptr),masf[ukaz]);
			break;
		case 2:
			doubleselectionsort(ptr,len-1,sizeof(*ptr),masf[ukaz]);
			break;
		case 3:
			qsort(ptr,len-1,sizeof(*ptr),masf[ukaz]);
			break;
		default:
			printf("Введите число от 1 до 3 \n");
	}
	return 0;
}

int getnap(){
	int k = 0;
	printf("Введите направление сортировки:\n 1. По убыванию\n 2. По возрастанию\n");
	int op = getint(&k,0,2);
	if (op == -1)	return 10;
	return k;
}

int getnum(){
	int k = 0;
	printf("Введите поле структуры, по которому вы хотите сортировать:\n 1. Слово\n 2. Толкование\n 3. Ударение\n");
	int op = getint(&k,0,3);
	if (op == -1)	return 11;
	return k;
}

int wordcomp(const void *a, const void *b){
	slovar *x = (slovar*) a;
	slovar *y = (slovar*) b;
        return strcmp(x -> word, y -> word );
}

int wordcomp2(const void *a, const void *b){
	slovar *x = (slovar*) a;
	slovar *y = (slovar*) b;
        return strcmp(y -> word, x -> word );
}

int tolkcomp(const void *a, const void *b){
	slovar *x = (slovar*) a;
	slovar *y = (slovar*) b;
	return strcmp(x -> tolk, y -> tolk);
}

int tolkcomp2(const void *a, const void *b){
	slovar *x = (slovar*) a;
	slovar *y = (slovar*) b;
	return strcmp(y -> tolk, x -> tolk);
}


int udarcomp(const void *a, const void *b){
	slovar *x = (slovar*) a;
	slovar *y = (slovar*) b;
	return ((x -> udar) - (y -> udar));
}

int udarcomp2(const void *a, const void *b){
	slovar *x = (slovar*) a;
	slovar *y = (slovar*) b;
	return ((y -> udar) - (x -> udar));
}

void swap(slovar *a, slovar *b){
	slovar temp = *a;
	*a = *b;
	*b = temp;
}


void shaker(void *a, size_t len, size_t size, int(*compare)(const void *, const void*) ){
        int niz = 0;
        int ver = len - 1;
        int last = 0;
        slovar	temp;
        while (niz < ver){
                last = -1;
                for(int i = niz; i < ver; i ++){
                        if (compare(a+i*size,a+i*size+size) > 0){
				swap(a+i*size+size,a+i*size);
                                last = i;
                        }
                }
                ver = last;
                last = len;
                for (int i = ver-1; i >= niz; i--){
                        if (compare(a+i*size, a+i*size+size) > 0){
                                temp = *(slovar*)(a+i*size+size);
                                *(slovar*)(a+i*size+size) = *(slovar*)(a+i*size);
                                *(slovar*)(a+i*size) = temp;
                                last = i;
                        }
                }
                niz = last + 1;
        }
}

void doubleselectionsort(void *a, size_t len, size_t size, int(*compare)(const void *, const void*)){
        int niz = 0;
        int ver = len-1;
	int len2 = len+1;
        while (niz < ver){
		int temp1 = ver; int temp2 = niz;
		slovar max = *(slovar*)(a+ver*size);		//Макс - посл элемент
		slovar min = *(slovar*)(a+niz*size);			//Мин - первый элемент
                for (int i = niz; i <= ver; i++){
                        if (compare(a+i*size,&max) > 0){
                                max = *(slovar*)(a+i*size);
                                temp1 = i;
                        }
                        if (compare(&min,a+i*size) > 0){
                                min = *(slovar*)(a+i*size);
                                temp2 = i;
                        }
                }
              	*(slovar*)(a+temp1*size) = *(slovar*)(a+size*ver);
		if ( strcmp( ((slovar*)(a + temp1*size)) -> word, min.word) == 0){
			temp2 = temp1;
		}
                *(slovar*)(a+size*ver) = max;
                if ((temp2 != ver) || (temp1 != niz)){
		       	*(slovar*)(a+temp2*size) = *(slovar*)(a+size*niz);
               		*(slovar*)(a+size*niz) = min;
		}
                ver -= 1;
                niz +=1;
        }
}

void myrandom(slovar **ptr, int *len){
	*ptr = (slovar*)calloc(*len,sizeof(slovar));
	for(int i = 0; i < *len; i++){
		int udar = rand();
		((*ptr)+i) -> udar = udar;
		for(int j = 0; j < 20; j++) (((*ptr)+i) -> word)[j] = rand()%26+'a';
		int slen = rand()%100;
		((*ptr)+i) -> tolk = (char*)calloc(slen+1,sizeof(char));
		for(int j = 0; j < slen; j++) (((*ptr)+i)->tolk)[j] = rand()%26 + 'a';
		(((*ptr)+i) -> tolk)[slen] = '\0';
	}	
}

int getn(){
	int k = 0;
	printf("Введите количество структур в массивах: \n");
	int op = getint(&k,0,INT_MAX);
	if (op == -1)	return 10;
	return k;
}

int getm(){
	int k = 0;
	printf("Введите количество генерируемых массивов: \n");
	int op = getint(&k,0,INT_MAX);
	if (op == -1)	return 10;
	return k;
}


int sortik2(slovar *ptr, int number, int napravl, int n, int m){
	int k = 0;
	double summa = 0;
	srand(time(NULL));		//SEED
	if ((number == 0) || (napravl == 0)){
		printf("Сначала выберите поле структуры и направление сортировки  (Пункты 2 и 3) \n");
		return 0;
	}
	printf("Введите номер сортировки, которую вы хотите использовать:\n1. Shaker sort\n2. Double selection sort\n3. Qsort \n");
	int op = getint(&k,0,3);
	if (op == -1)	return 10;
	int (*fptr)(const void *a, const void* b);	
	int (*masf[])(const void *a,const void *b) = {&wordcomp2,&tolkcomp2,&udarcomp2,&wordcomp,&tolkcomp,&udarcomp};
	int ukaz = (napravl-1)*3 + (number - 1);
	
	clock_t start = clock();
	// k = Номер сортировки
	// number = Поле сортировки
	// Направление = напрелвлеие
	for(int i = 0; i < m; i++){
		myrandom(&ptr,&n);
		printf("ДОООО \n");
		int z = n + 1;
		outstc(&ptr,&z);
		printf("После \n");
	switch(k){
		case 1:
			shaker(ptr,n,sizeof(*ptr),masf[ukaz]);
			break;
		case 2:
			doubleselectionsort(ptr,n,sizeof(*ptr),masf[ukaz]);
			break;
		case 3:
			qsort(ptr,n,sizeof(*ptr),masf[ukaz]);
			break;
		default:
			printf("Введите чиселко от 1 до 3 \n");
	}
	outstc(&ptr,&z);
	for(int j = 0; j < n; j++){
	       	free((ptr+j) -> tolk);
	}
	free(ptr);
	}
	clock_t end = clock();
	summa = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("Сортировка массива из %d структур(ы) прошла за %.20f секунд \n",n,summa/m);

	return 0;
}
