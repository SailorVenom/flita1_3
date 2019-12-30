#include <stdio.h>
#include <stdlib.h>
#define STRINGSIZE 1024
#define MAXSIZE 5000

void printarray(char** array, int n) {
	for (int i = 0; i < n; ++i)
		printf("[%d]: %s\n", i+1, array[i]); //Выводим храмимые строки
}

void array_add(char** array, int n) {
	array[n] = malloc(STRINGSIZE*sizeof(char)); //Выделение места в памяти компа под новый элемент
	scanf("%s", array[n]); //Ввод нового элемента
}

void array_rem(char** array, int n) {
	int id; //Откуда будем удалять, то есть какой элемент множества по порядку
	printf("Which id we remove: \n");
	scanf("%d", &id); 
	id--; //Это потому что в С++ нумерация с 0 происходит, а мы считьываем номер с 1
	for (int i = id; i < n-1; i++)
		array[i] = array[i+1]; //Удаление происходит сдвигом всех элементов правее удаляемого влево на 1 позицию
	free(array[n-1]); //Удаояем последний элемент и говорим компу, что память под него больше не нужна
}

int main() {
	int n1, n2; //Размеры 1=го и 2-го множеств
	printf("Enter num of elements of array 1: ");
	scanf("%d", &n1); //Считываем размер 1-го множества
	
	char** array1 = (char**)malloc(MAXSIZE*sizeof(char*)); //Выделяем память на хранение 5000 указателей на строки (То есть память на 5000 строк)
	for (int i = 0; i < n1; ++i)
		array1[i] = malloc(STRINGSIZE*sizeof(char)); //Выделяем память на каждую из 5000 строк (В строке 1024 символа, под них и выделяем память)
	
	printf("Enter elements:\n");
	for (int i = 0; i < n1; ++i)
		scanf("%s", array1[i]); //Вводим каждую строку, %s - это значит что ожидаем получтьь строку на ввод
	
	printf("Enter size of array 2: ");
	scanf("%d", &n2);
	
	char** array2 = malloc(MAXSIZE*sizeof(char*));
	for (int i = 0; i < n2; ++i)
		array2[i] = malloc(STRINGSIZE*sizeof(char));
	
	printf("Enter elements:\n");
	for (int i = 0; i < n2; ++i)
		scanf("%s", array2[i]);
	
	int cmd = -1; //Объявляем переменную команды(?) то есть какое действие бьудем делать в проге
	while(cmd != 0) {
		printf("Enter cmd:\n1. Add to 1\n2. Add to 2\n3. Remove from 1\n4. Remove from 2\n5. Print all\n");
		scanf("%d", &cmd); //Считываем команду
		switch(cmd) {
			case 0: break;
			case 1: array_add(array1, n1); n1++;break;
			case 2: array_add(array2, n2); n2++;break;
			case 3: array_rem(array1, n1); n1--; break;
			case 4: array_rem(array2, n2); n2--;break;
			case 5: printf("Array 1:\n");printarray(array1, n1); printf("Array 2:\n");printarray(array2, n2); break;			
		}
		
	}
	return 0;
}