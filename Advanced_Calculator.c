#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _DEBUG
#undef _DEBUG

#ifdef _DEBUG

#endif

int get_precedence(const char ch);
int get_order(const char ch);
int get_type(const char ch);

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
void print_nested_list(pList, PrintFunction printFunction);

/* I want to combine va_list with pseudo-generics */

void print_number(void * pNumber);


typedef struct Token {
	union {
		int number;
		char operation;
		void * address;
	} content;
	int type;
} Token;

void print_token(void * pToken);

typedef List Stack;
typedef Stack * pStack;
void * get_top(pStack pStack);
void * stack_pop(pStack pStack);

List read_token_list();

typedef struct TreeNode * pTreeNode;
typedef struct TreeNode
{
	void * pElement;
	pTreeNode pLeft, pRight;
} TreeNode;
typedef struct Tree
{
	pTreeNode pRoot;
	int elementSize;
} Tree;
typedef Tree * pTree;


void init_tree(pTree pTree, int size);
void destroy_tree(pTreeNode pRoot);
List to_nested_list(pList pOldList);
Tree get_ast(pList pList);


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

#ifdef _DEBUG

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

#endif
	print_list(pMyList, print_number);

	List newList = read_token_list();
	print_list(&newList, print_token);

	List refinedList;
	refinedList = to_nested_list(&newList);

#ifdef _DEBUG
	printf("Succeessfully converted to nested list!\n");
#endif
	print_nested_list(&refinedList, print_token);

	destroy_list(pMyList);
	destroy_list(&newList);

}

int get_precedence(char ch)
{
	/* What is more small? */
	if (ch == '\\' || ch == '%') return 4;
	if (ch == '+' || ch == '-') return 5;
	if (ch == '*' || ch == '/') return 6;
	if (ch == '^') return 7;

	return 100;

}

int get_order(char ch)
{
	if (ch == '^') return -1;
	else return 1;
}

int get_type(const char ch)
{
	if (ch >= 48 && ch < 57) return 1;
	if (ch == '+' || ch == '-' || ch == '\\' || ch == '/' || ch == '^' || ch == '*' || ch == '%') return 2;
	if (ch == '(' || ch == ')') return 8;
	if (1) return 4; /* Defaults to complex functions */
	/* Actually I don't want non-long functions in long mode */
	/* And invalid expression checker. We have to do that */
	/* Maybe you can register your own functions in an array and we can use hash? */
	return 8;
}

void init_list(pList pList, int size)
{
	pList->pHead = NULL;
	pList->pTail = NULL;
	pList->elementSize = size;
}

void destroy_list(pList pList)
{
	pNode _pHead = pList->pHead;
	pNode _pAuxNode;
	while (_pHead != NULL)
	{
		_pAuxNode = _pHead;
		_pHead = _pHead->pNext;
		free(_pAuxNode);
	}
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

void print_nested_list(pList pOldList, PrintFunction printFunction)
{
	pNode _pHead = pOldList->pHead;

	Stack _tokenStack;
	pStack _pTokenStack = &_tokenStack;
	init_list(_pTokenStack, sizeof(Token*));

	while (_pHead != NULL)
	{
#ifdef _DEBUG
		printf("address %ld \n", _pHead);
#endif
		if (((Token*)(_pHead->pElement))->type != 16)
		{
			printFunction(_pHead->pElement);
		}
		else
		{
			printf("{#%d}", ((Token*)(_pHead->pElement))->content.number);
			add_tail(_pTokenStack, _pHead->pElement);
		}
		
		_pHead = _pHead->pNext;
	}

	Token* _pToken = (Token*)stack_pop(_pTokenStack);
	while (_pToken != NULL)
	{
		printf("#%d: ", _pToken->content.number);
		print_nested_list((pList)_pToken->content.address, printFunction);
		_pToken = (Token*)stack_pop(_pTokenStack);
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

#ifdef _DEBUG

			printf("Debugging!");
#endif

			printf("%d", ((Token *)pToken)->content.number);

		default:
			printf("%c", ((Token *)pToken)->content.operation);		
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
			free(pStack->pTail);
			pStack->pTail = NULL;
			pStack->pHead = NULL;
		}


		return _pAux;
	}
	return NULL;
}




List read_token_list()
{
	List newList;
	pList pNewList = &newList;
	init_list(pNewList, sizeof(Token));



	char ch;
	Token _tempToken;
	_tempToken.type = 0; /* Empty type? */



	while((EOF != (ch = getchar()) && ch != '\n'))
	{

		/* Things are a little bit different from the polynomial case, as you have to record all the chars. */
#ifdef _DEBUG
		printf("Got character %c!\n", ch);
#endif

		switch (get_type(ch))
		/* Be ware of the getchar() complex situation */
		{
			case 1: /* Receives a digit */
				printf("A digit! %d\n", ch - 48);
				if (_tempToken.type == 0)
				{
					_tempToken.type = 1;
					_tempToken.content.number = ch - 48;
				} else {
					if (_tempToken.type == 1)
					{
						_tempToken.content.number = 10 * _tempToken.content.number + ch - 48;
					}
				}

				break;
			case 2: /* Receives a binary */
				if (_tempToken.type == 0)
				{

				}
				if (_tempToken.type == 1)
				{
					add_tail(pNewList, &_tempToken);
					_tempToken.type = 2;
					_tempToken.content.operation = ch;
					add_tail(pNewList, &_tempToken);
					_tempToken.type = 0;
				}
				break;
				/* Other cases are invalid? */

			case 4: /* Receives an unary operation */
				if (_tempToken.type == 0)
				{
					_tempToken.type = 4;
					_tempToken.content.operation = ch;
					add_tail(pNewList, &_tempToken);
					_tempToken.type = 0;
				}
				if (_tempToken.type == 4)
				{
					
					/* We don't currently deal with this case */
				}
				break;

			case 8: /* Receives a bracket */
				if (_tempToken.type == 0)
				{

				}
				if (_tempToken.type == 1)
				{
					add_tail(pNewList, &_tempToken);
				}

				_tempToken.type = 8;
				_tempToken.content.operation = ch;
				add_tail(pNewList, &_tempToken);
				_tempToken.type = 0;
				break;

			default:
				break;

		}

	}

	return newList;
}

List to_nested_list(pList pOldList)
{
	int count = 1;

	pNode _pHead = pOldList->pHead;

	Stack scopeStack;
	pStack pScopeStack = &scopeStack;
	init_list(pScopeStack, sizeof(pList));

	List resultList;
	pList pResultList = &resultList;
	add_tail(pScopeStack, (void*)pResultList);

	pList _pNewList;
	pList _pCurrentList = pResultList;

	Token _tempToken;

	while (_pHead != NULL)
	{
		Token* pToken = (Token*)(_pHead->pElement);
		if (pToken->type == 8) {
			if (pToken->content.operation == '(')
			{
				_pNewList = (pList)malloc(sizeof(List));
				init_list(_pNewList, sizeof(pNode));
				

				_tempToken.type = -1;
				_tempToken.content.number = count;
				_tempToken.content.address = (void*)&_pNewList;
				add_tail(_pNewList, (void*)(&_tempToken));

				count += 1;
				_pCurrentList = _pNewList;
				add_tail(pScopeStack, (void*)_pNewList);
			}
			else
			{
				_pCurrentList = (pList)stack_pop(pScopeStack);
			}
		}
		else
		{
			add_tail(_pCurrentList, (void*)_pHead->pElement);
			_pHead = _pHead->pNext;
		}

	}
	return resultList;
}

void init_tree(pTree pTree, int size)
{
	pTree->pRoot = NULL;
	pTree->elementSize = size;
}

// Tree get_ast(pList pList)
// {
// 	Tree newTree;
// 	pTree pNewTree;
// 	init_tree(pNewTree, sizeof(Token));
// 	pTreeNode pRoot;
// 	pTreeNode pCurrent;
// 	pTreeNode _pAuxTreeNode;

// 	Stack newStack; /* We store the address.. OMG! */
// 	pStack pNewStack;
// 	init_list(pNewStack, sizeof(pTreeNode));
// 	/* Traverse the token list */

// 	Token _tempToken;
// 	_tempToken.content.operation = '(';
// 	_tempToken.type = 8;
// 	add_head(pList, &_tempToken);
// 	_tempToken.content.operation = ')';
// 	add_tail(pList, &_tempToken);

// 	Token _addressToken;
// 	pNode _pNode = pList->pHead;

// 	pNode _address;

// 	pNode pAuxNode;

// 	/* We need to store all the data of the scopes. Scopes are just stackes */
// 	int lastPriority = 0;
// 	int _tempPriority;
// 	char lastOperator = ' ';
// 	char currentOperator = ' ';

// 	while (_pNode != NULL)
// 	{
// 		/* We need to switch to cases here! */
// 		_tempToken = *(Token*)_pNode->pElement;
// 		switch (_tempToken.type)
// 		{






// 			case 1:
// 				_pAuxTreeNode = (pTreeNode)malloc(sizeof(TreeNode));
// 				((Token*)(_pAuxTreeNode->pElement))->type = 1;
// 				((Token*)(_pAuxTreeNode->pElement))->content.number = _tempToken.content.number;
// 				if (pCurrent == NULL) /* If it's empty currently */
// 				{
// 					pCurrent = _pAuxTreeNode;
// 					pRoot = pCurrent;
// 				}
// 				else /* If not empty */
// 				{

// 					pCurrent->pRight = _pAuxTreeNode;
// 					pCurrent = pCurrent->pRight;
// 				}
// 				break;

// 			case 2: /* If it's an operator */ /* We may have to store the previous priority... */
// 				if (pCurrent == NULL)
// 				{
// 					/* It may be a minus sign, an unary operation. We will deal with it later... */

// 				}
// 				else /* if there is something in place */
// 				{

// 					currentOperator = ((Token*)(pCurrent->pElement))->content.operation;
// 					_tempPriority = get_precedence(currentOperator);
// 					if (_tempPriority > lastPriority) /* High precedence */
// 					{

// 					}
// 					else
// 					{
// 						if (_tempPriority == lastPriority) /* Equal precedence */
// 						{
// 							if (currentOperator != lastOperator) /* Different operator */
// 							{

// 							}
// 							else /* Same operator */
// 							{
// 								if (get_order(currentOperator) == 0) /* Left associative */
// 								{

// 								}
// 								else /* Right associative */
// 								{

// 								}
// 							}
// 						}
// 						else /* Low priority */
// 						{

// 						}
// 					}


// 					pAuxNode = pCurrent;

// 					pCurrent = (Node*)malloc(sizeof(Node));
// 					pCurrent->value.type = pAuxNode->value.type;
// 					pCurrent->value.content.operation = pNode->value.content.operation;
// 					pRoot = pCurrent;
// 					pCurrent->previous = pAuxNode;
// 				}
// 				break;

// 			case 4:

// 				break;

// 			case 8: /* Declare a scope for brackets */
// 				if (pNode->value.content.operation == '(')
// 				{
// 					// pRoot = (Node *)malloc(sizeof(Node));

// 					if (pRoot == NULL)
// 					{
// 						_addressToken.content.number = -1;
// 						add_tail(pList, _addressToken);
// 					}
// 					else
// 					{
// 						_addressToken.content.number = (long)pRoot;
// 					}

// 					pRoot = NULL;
// 					pCurrent = NULL;

// 					_addressToken.content.number = -1;
// 					// _addressToken.content.number = (long)pRoot;
// 					add_tail(pList, _addressToken);
// 					/* Write here the malloc instead of in a function,
// 					To get more refined control of the program */

// 					pCurrent = pRoot;
// 					// pCurrent->value.type = 0;
// 				}
// 				else
// 				{
// 					_address = (Node *)stack_pop(pList).content.number;
// 					if (_address == (Node *)-1)
// 					{
// 						pCurrent = pRoot;
// 						/* pRoot should not change */
// 					}
// 					else
// 					{
// 						pCurrent = pRoot;
// 					}
// 					pRoot = 
// 					pCurrent = pRoot;
// 				}
// 				break;
// 			default:
// 				break;
// 		}

// 		pNode = pNode->next;
// 	}

// 	pAuxNode = pList->pHead;
// 	pList->pHead = pList->pHead->pNext;
// 	free(pAuxNode);

// 	pAuxNode = pList->pTail;
// 	pList->pTail = pList->pTail->pPrev;
// 	free(pAuxNode);

// 	return newTree;
// }