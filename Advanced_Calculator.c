#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _DEBUG
#undef _DEBUG

#ifdef _DEBUG

#endif

typedef struct Node * pNode;
typedef struct Node
{
	void * pElement;
	pNode pPrev, pNext;
} Node;

typedef struct List * pList;
typedef struct List {
	pNode pHead, pTail;
	int elementSize;
} List;

typedef void(*PrintFunction)(void *);

void unit_test();
void init_list(pList pList, int size);
void destroy_list(pList pList);
void add_head(pList pList, void * pElement);
void add_tail(pList pList, void * pElement);
void print_list(pList pList, PrintFunction printFunction);

/* I want to combine va_list with pseudo-generics */

void print_number(void * pNumber);


typedef struct Token {
	union {
		int number;
		char operation;
	} content;
	int type;
} Token;

void print_token(void * pToken);

typedef List Stack;
typedef Stack * pStack;
void * get_top(pStack pStack);
void * stack_pop(pStack pStack);


int main(int argc, char const *argv[])
{
	
	unit_test();
	return 0;
}


void unit_test()
{
	List myList;
	pList pMyList = &myList;
	init_list(pMyList, sizeof(int));
	int i;
	i = 3;
	add_tail(pMyList, &i);
	add_tail(pMyList, &i);

	i = 4;
	add_tail(pMyList, &i);
	add_tail(pMyList, &i);
	add_tail(pMyList, &i);
	add_tail(pMyList, &i);
	print_list(pMyList, print_number);

	printf("Tail address is %ld \n", pMyList->pTail);
	printf("Tail prev address is %ld \n", pMyList->pTail->pPrev);

	printf("\nTop is: ");
	print_number(get_top(pMyList));

	stack_pop(pMyList);
	printf("Tail address is %ld \n", pMyList->pTail);
	printf("\nTop is: ");
	print_number(get_top(pMyList));
	stack_pop(pMyList);
	printf("Tail address is %ld \n", pMyList->pTail);
	printf("\nTop is: ");
	print_number(get_top(pMyList));
	stack_pop(pMyList);
	printf("Tail address is %ld \n", pMyList->pTail);
	printf("\nTop is: ");
	print_number(get_top(pMyList));
	stack_pop(pMyList);
	printf("\nTop is: ");
	print_number(get_top(pMyList));
	printf("\n");
	print_list(pMyList, print_number);

}

void init_list(pList pList, int size)
{
	pList->pHead = NULL;
	pList->pTail = NULL;
	pList->elementSize = size;
}

void add_head(pList pList, void * pElement)
{
	void * newPointer = malloc(pList->elementSize);
	memcpy(newPointer, pElement, pList->elementSize);

	pNode newNode = (pNode)malloc(sizeof(Node));
	newNode->pElement = newPointer;

	newNode->pNext = pList->pHead;
	newNode->pPrev = NULL;

	if (pList->pHead == NULL)
	{
		pList->pHead = newNode;
		pList->pTail = newNode;
	}
	else
	{
		pList->pHead->pPrev = newNode;
		pList->pHead = newNode;
	}


}

void add_tail(pList pList, void * pElement)
{
	void * newPointer = malloc(pList->elementSize);
	memcpy(newPointer, pElement, pList->elementSize);

	pNode newNode = (pNode)malloc(sizeof(Node));
	newNode->pElement = newPointer;

	newNode->pPrev = pList->pTail;
	newNode->pNext = NULL;

	if (pList->pTail == NULL)
	{
		pList->pTail = newNode;
		pList->pHead = newNode;
	}
	else
	{
		pList->pTail->pNext = newNode;

		pList->pTail = newNode;

#ifdef _DEBUG
		printf("Added tail address is %ld \n", pList->pTail);
#endif
	}


}

void print_list(pList pList, PrintFunction printFunction)
{
	pNode _pHead = pList->pHead;
	while (_pHead != NULL)
	{
#ifdef _DEBUG
		printf("address %ld \n", _pHead);
#endif
		
		printFunction(_pHead->pElement);
		_pHead = _pHead->pNext;
	}
	printf("\n");
}


void print_number(void * pNumber)
{
	printf("%d ", *(int *)pNumber);
}

void print_token(void * pToken)
{

	switch (((Token *)pToken)->type)
	{
		case 1:

			printf("%d", ((Token *)pToken)->content.number);

		default:
			printf("%d", ((Token *)pToken)->content.operation);		
			break;
	}
}

void * get_top(pStack pStack)
{
	if (pStack->pHead != NULL)
	{
		return pStack->pTail->pElement;
	}
	else
	{
		return NULL;
	}
}

void * stack_pop(pStack pStack)
{
	if (pStack->pTail != NULL)
	{

#ifdef _DEBUG
		printf("Not Null!");
#endif
		
		void * _pAux;
		_pAux = pStack->pTail->pElement;

#ifdef _DEBUG
		print_number(_pAux);
#endif
		

		if (pStack->pTail->pPrev != NULL)
		{
			pStack->pTail = pStack->pTail->pPrev;
			free(pStack->pTail->pNext);
			pStack->pTail->pNext = NULL;
		}
		else
		{

		}


		return _pAux;
	}
	return NULL;
}