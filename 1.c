#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct set
        {
        int n ;
    char *elements;
        };

void initSet(struct set *_set);

void inputSet(struct  set *_set);

bool checkElement(char element, struct set *_set);

void addElement(char element, struct set *_set);

void printSet(struct set _set);

void deleteElementSet(char element, struct set *_set);

void destroySet(struct set *_set);

void initTwoSets(struct set *s1, struct set *s2);


char getOneSymbol(char *delEl, const char *text);

int main() {
    printf("Hello, World!\n");
    struct set _set1,s3,s4;
    initSet(&s3);
    initSet(&s4);
    initSet(&_set1);
    initTwoSets(&s3,&s4);
    printSet(s3);
    printSet(s4);
    inputSet((&_set1));
    printSet(_set1);
    
    char delEl;
    
    delEl = getOneSymbol(&delEl, "Введите элемент для удаления: ");
    
    deleteElementSet(delEl,&_set1);
    printSet(_set1);
    destroySet(&_set1);
    destroySet(&s3);
    destroySet(&s4);
    return 0;
}

char getOneSymbol(char *delEl, const char *text)
{
    printf("%s "),text;
    while (true)
    {
        scanf("%c", delEl);
        if((*delEl) != '\n')
            break;
    }
    return (*delEl);
}


void inputSet(struct set *_set)
{
    char k = ' ';
    printf("Введите элементы множества: \n");
    while (k!= '\n')
    {
        scanf("%c",&k);
        if(k!='\n')
            addElement(k,_set);
    }
    
    
    printf("введено %d элементов\n", _set->n);


}

bool checkElement(char element, struct set *_set)
{
    for (int i = 0; i < _set->n; ++i)
    {
        if(_set->elements[i]==element)
            return false;
    }
    return true;
}

void addElement(char element, struct set *_set)
{
    if(_set->n == 0)
    {
        _set->elements = (char *)malloc(sizeof(char));
        _set->elements[0] = element;
        _set->n++;
    } else if (checkElement(element,_set))
    {
        char *tmpArr = (char *)malloc((_set->n+1)*sizeof(char));
        for (int i = 0; i < _set->n; ++i)
        {
            tmpArr[i] = _set->elements[i];
        }
        free(_set->elements);
        tmpArr[(_set->n)++]=element;
        _set->elements = tmpArr;
    }
}

void initSet(struct set *_set)
{
    _set->n = 0;
}



void printSet(struct set _set)
{
    printf("множество сожержит следующие элементы: \n");
    for (int i = 0; i < _set.n; ++i)
    {
        printf("%c ",_set.elements[i]);
    }
    printf("\n");
}

void deleteElementSet(char element, struct set *_set)
{
    if(_set->n == 0)
        return;
    if(!checkElement(element,_set))
    {
        char *tmpArr = (char *)malloc((_set->n-1)*sizeof(char));
        bool isDeleted = false;
        for (int i = 0; i < _set->n; ++i)
        {
            if(_set->elements[i]==element)
            {
                isDeleted = true;
                continue;
            }
            if(!isDeleted)
            {
                tmpArr[i] = _set->elements[i];
            } else
            {
                tmpArr[i-1] = _set->elements[i];
            }
        }
        free(_set->elements);
        if(_set->n-- != 0)
            _set->elements = tmpArr;
    }
}

void destroySet(struct set *_set)
{
    if(_set->n!=0)
        free(_set->elements);
    _set->n = 0;
}

void initTwoSets(struct set *s1, struct set *s2)
{
    printf("Введите первое множество\n");
    inputSet(s1);
    printf("Введите второе множество\n");
    inputSet(s2);
}