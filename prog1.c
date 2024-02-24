#include <stdio.h>
#include "input.h"
#include <limits.h>
#include <stdlib.h>
#include "library.h"

int main(){
	slovar *slova = calloc(1,sizeof(slovar));
	int key = 0,stats = 0,temp = 0,len = 1,number = 0, napravl=0;
	do{
	printf("Введите номер операции: \n1. Ввод массива \n2. Вывод массива \n3. Сортировка массива\n");
	int op = getint(&key,0,INT_MAX);
	if (op == -1){
		if (len > 1) len -=1;
		for(int i = 0; i < len; i++){
			free( (slova+i) -> tolk);
		}	
		free(slova);
		return 0;
	}
	switch (key){
		case 1:
		printf("Введите номер способа ввода: \n1. С клавиатуры \n2. Из файла txt \n3. Из бинарного файла\n");
		op = getint(&temp,0,INT_MAX);
		if (op == -1) return 0;
		switch(temp){	
			case 1:
				stats = inputstc(&slova,&len);
				break;	
			case 2:
				stats = outfile(&slova, &len);
				break;
			case 3:
				stats = outbin(&slova, &len);
				break;
			default:
				puts("Введите число от 1 до 3 \n");
		}
		break;
		case 2:
		printf("Введите номер способа вывода: \n1. На экран \n2. В файл txt \n3. В бинарный файл\n");
		op = getint(&temp,0,INT_MAX);
		if (op == -1) return 0;
		switch(temp){
			case 1:
				stats = outstc(&slova,&len);
				break;
			case 2:
				stats = inputfile(&slova,&len);
				break;
			case 3:
				stats = inputbin(&slova,&len);
				break;
			default:
				puts("Введите число от 1 до 3 \n");
		}
		break;
		case 3:
		printf("Выберите: \n1. Выбор алгоритма сортировки\n2. Выбор поля структуры\n3. Направление сортировки \n");
		op = getint(&temp,0,INT_MAX);
		if (op == -1) return 0;
		switch(temp){
			case 1:
				printf("number = %d \n",number);
				printf("napvarl = %d \n",napravl);
				stats = sortik(slova,number,napravl,len);
				break;
			case 2:
				number = getnum();
				break;
			case 3:
				napravl = getnap();
				break;
			default:
				puts("Введите число от 1 до 3 \n");
		}
		break;
		default:
		puts("Введите число от 1 до 3 \n");
	}
	}while (stats == 0);

	if (len > 1) len -=1;
	for(int i = 0; i < len; i++){
		free( (slova+i) -> tolk);
	}	
	free(slova);
	return 0;
}
