#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t strlen2(const char *s){
	size_t k = 0;
	while (s[k] != '\0'){
		k += 1;
	}
	return k;
}

char *strdup2(const char *s){
	int k = 0, i = 0;
	char *news = NULL;
	k = strlen2(s);
       	news = (char*)calloc(k+1,sizeof(char));
	while (s[i] != '\0'){
		news[i] = s[i];
		i += 1;
	}
	news[i] = '\0';
	return news;
}

int sovp(char s, const char *simv);

char *strtok2(char *s, const char *simv){
	int k = 0, flag = 2;
	char *ptr = NULL;
	static char *Iter;
	if (s == NULL){
		s = Iter;
		if (Iter == NULL) return NULL;
	}
	ptr = s;
	while (s[k] != '\0'){
		flag = sovp(s[k],simv);
		if (flag == 1){
			k += 1;
			ptr += 1;
		}
		else{
			break;
		}
	}
	s = ptr;
	k = 0;
	flag = 0;
	while (s[k] != '\0'){
		flag = sovp(s[k],simv);
		if (flag == 1){
			s[k] = '\0';
			break;
		}
		ptr += 1;
		k += 1;
	}
	if (flag == 0){
		Iter = NULL;
	}
	else{
		Iter = ++ptr;
	}
	return s;	
}
	
char* freadline2(FILE *f){
        int n = 0, len = 0;
        char buf[51];
        n = fscanf(f,"%50[^\n]",buf);
	char *ptr = (char*)calloc(1,sizeof(char));
        while (n > 0){
		len += strlen2(buf);
                ptr = (char*)realloc(ptr,len+1);
                strcat(ptr,buf);
                n = fscanf(f,"%50[^\n]",buf);
        }
        if (n == 0){
		fscanf(f,"%*c");
                ptr[len] = '\0';
        }
	else{
		free(ptr);
		ptr = NULL;
	}
        return ptr;
}

int sovp(char s,const char *simv){
	int len = strlen2(simv);
	for(int i = 0; i < len; i++){
		if (s == simv[i]){
			return 1;
		}
	}
	return 0;
}

void *memcpy2(void *str, const void *s, size_t ob){
	char *strchar = (char *)str;
	const char *schar = (const char*) s;
	if (schar == NULL) return str;
	if (str == NULL) return NULL;
	for(size_t i = 0; i < ob; i++){
	        if (schar[i] == '\0'){
			return str;
 		}
		strchar[i] = schar[i];
	}
	return str;
}

