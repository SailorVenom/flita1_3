#include <stdio.h>
#include <stdlib.h>

#define NUMBER 5 // Количество вершин
#define ORIENTED "digraph {\n" // Строка по.dot синтаксису означает, что граф будет связанный

// Структура данных - односвязанный список
struct list
{
	int value;	// Вершина графа
	struct list *next;	// Указатель на следующую смежную вершину
};

typedef struct list* LNode;
int visited[NUMBER] = { 0 }; // Проверка посещенных вершин относительно какой-либо
int visited_vertexes = 0; // Количество обойдённых вершин

void add_bond(LNode top, LNode graph[], int l_value);	// Задание связи между вершинами
void print_matrix(LNode top); // Вывод матрицы смежности
void make_dot(LNode top, FILE *fp); // Создание dot файла для визуализации графа
void depth_first_search(int i, LNode graph[]); /* Проход графа в глубину, 
								т.е. проверка на связность одной из вершин */


int main(int argc, char const *argv[])
{
	int i;
	LNode pg;
	LNode graph[NUMBER]; // Создание массива списков

	FILE *fp = fopen("graph.dot", "w");
	fputs(ORIENTED, fp);

	// Задание начальных вершин: 1...5
	for (i = 0; i < NUMBER; ++i)
	{
		graph[i] = (LNode)malloc(1 * sizeof(struct list));
		graph[i]->value = i + 1;
		graph[i]->next = NULL;
	}

	int c;
	for (i = 0; i < NUMBER; ++i)
	{
		pg = graph[i];
		printf("Введите смежные с %d вершины:\n", i+1);
		// Вводим номер вершины по одной через enter
		// Заканичваем ввод вершин связкой "0 enter"
		while(scanf(" %d", &c) != EOF && c != 0)
		{
			if (c >= 1 && c <= NUMBER)
			{
				if (c != i+1)
				{
					add_bond(pg, graph, c);
				}
				else
				{
					printf("\nВершина не может быть соединена сама с собой\n");
					printf("Введите смежные с %d вершины:\n", i+1);
				}
			}
			else
			{
				printf("\nВсего %d вершин: от 1 до %d.\n", NUMBER, NUMBER);
				printf("Введите смежные с %d вершины:\n", i+1);
			}
		}
		printf("Связи с %d вершиной установлены. Продолжаем\n\n", i+1);
	}

	// Модуль вывода матрицы смежности
	printf("   ");
	for (i = 1; i <= NUMBER; ++i)
	{
		printf("% 2d ", i);
	}
	printf("\n");
	printf("    ______________\n");
	for (i = 0; i < NUMBER; ++i)
	{
		pg = graph[i];
		printf("%d  |", pg->value);
		print_matrix(pg);
		printf("\n");
	}
	printf("\n");

	// Модуль проверки связности
	/* В случае ориентированного необходима проверка каждой вершины, 
	так как связи односторонние*/
	for (int i = 0; i < NUMBER; ++i)
	{
		depth_first_search(graph[i]->value, graph);
		for (int i = 0; i < NUMBER; ++i)
		{
			visited[i] = 0;
		}
	}
	if (visited_vertexes == NUMBER || visited_vertexes == NUMBER * NUMBER)
	{
		printf("Граф связан\n");
	}
	else
	{
		printf("Граф несвязан\n");
	}

	// Модуль создания dot файла
	for (i = 0; i < NUMBER; ++i)
	{
		pg = graph[i];
		make_dot(pg, fp);
	}
	fprintf(fp, "}");
	fclose(fp);

	// Команда визуализации графа
	system("dot -Tx11 graph.dot");

	return 0;
}


void add_bond(LNode top, LNode graph[], int l_value)	// Добавление элемента списка
{
	LNode temp = top;
	while(temp->next)
	{
		temp = temp->next;
		if (temp->value == l_value)	// Если имеется уже такое значение, то не добавлять, чтобы избежать спика по типу 5, 5, 5 ...
		{
			return;
		}
	}
	temp->next = (LNode) malloc(sizeof(struct list));
	temp->next->value = l_value;
	temp->next->next = NULL;
}


void depth_first_search(int i, LNode graph[])
{
	LNode p;
	++visited_vertexes;
	p = graph[i-1];
	visited[i-1] = 1;
	while(p != NULL)
	{
		i = p->value;
		if (visited[i-1] == 0)
		{
			depth_first_search(i, graph);
		}
		p = p->next;
	}
}


void make_dot(LNode top, FILE *fp)
{
	LNode temp = top;

	while(temp->next)
	{
		fprintf(fp, "\t%d -> %d [label=\"%d.%d\"];\n", 
			top->value, temp->next->value, top->value, temp->next->value);
		temp = temp->next;
	}
}


void print_matrix(LNode top)
{
	int check;
	LNode temp = top; 
	for (int i = 1; i <= NUMBER; ++i)
	{
		temp = top;
		while(temp->next)
		{
			if (temp->next->value == i)
			{
				check = 1;
				break;
			}
			else
			{
				check = 0;
			}
			temp = temp->next;
		}
		if (check == 1)
		{
			printf("1  ");
		}
		else
		{
			printf("0  ");
		}
	}
}