#include <stdio.h>
#include <stdlib.h>
int getfloat(float *k,float a,float b);
int getint(int *cnt,int a,int b);

int getint(int *cnt,int a,int b){
                int op = 0;
                do {
                        op = scanf("%d", cnt);
			if (op == EOF){
				return EOF;
                        }
                        if ((op == 0) || (a>(*cnt)) || ((*cnt) > b)){
				printf("Повторите ввод \n");
				op = 0;
                        	scanf("%*[^\n]");
                        }
           		if (op == 1){
                        	return 1;
                        }
                }while (op == 0);
	return op;
}

int getfloat(float *k,float a,float b){
                int op = 0;
                do {
                        op = scanf("%f", k);
			if (op == EOF){
                        	return EOF;
                        	}
                        if ((op == 0) || (a>(*k)) || ((*k)>b)){
				printf("Повторите ввод \n");
				op = 0;
                        	scanf("%*[^\n]");
                        	}
                        if (op == 1){
                        	return 1;
                        	}
                }while (op == 0);
	return op;
}
