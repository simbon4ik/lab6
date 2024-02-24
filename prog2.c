#include <stdio.h>
#include "input.h"
#include <limits.h>
#include <stdlib.h>
#include "library.h"

int main(){
	slovar *slova = calloc(1,sizeof(slovar));
	int key = 0,stats = 0, len = 1,number = 0, napravl=0, n = 0, m = 0;
	do{
	printf("Выберите: \n1. Выбор алгоритма сортировки\n2. Выбор поля структуры\n3. Направление сортировки \n4. Количество элементов в генерируемых массивах \n5. Количество генерируемых массивов \n");
	int op = getint(&key,0,INT_MAX);
	if (op == -1){
		if (len > 1) len -=1;
		for(int i = 0; i < len; i++){
			free((slova+i) -> tolk);
		}	
		free(slova);
		return 0;
	}
	switch(key){
		case 1:
			printf("number = %d \n",number);
			printf("napvarl = %d \n",napravl);
			stats = sortik2(slova,number,napravl,n,m);
			break;
		case 2:
			number = getnum();
			break;
		case 3:
			napravl = getnap();
			break; 
		case 4:
			n = getn();
			break;
		case 5:
			m = getm();
			break;
		default:
			puts("Введите число от 1 до 5 \n");
	}
	}while (stats == 0);
	return 0;
}
