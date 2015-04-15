#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	} content;
	void * address;
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
	#define _DEBU
	const char * _debug = "-x";
	printf("Argument number is %d, argument 2 is %s\n", argc, argv[1]);
	if (argc >= 2 && strcmp(argv[1], _debug) == 0)
	{
		printf("Entering deubg mode!...\n");


#ifdef _DEBUG
		printf("Debug function is running!");
		printf("Debug function is not running!");
#endif
	}
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

	printf("Tail address is %p \n", pMyList->pTail);
	printf("Tail prev address is %p \n", pMyList->pTail->pPrev);

	printf("\nTop is: ");
	print_number(get_top(pMyList));

	stack_pop(pMyList);
	printf("Tail address is %p \n", pMyList->pTail);
	printf("\nTop is: ");
	print_number(get_top(pMyList));
	stack_pop(pMyList);
	printf("Tail address is %p \n", pMyList->pTail);
	printf("\nTop is: ");
	print_number(get_top(pMyList));
	stack_pop(pMyList);
	printf("Tail address is %p \n", pMyList->pTail);
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
	// #undef _DEBUG
	print_list(&refinedList, print_token);

	destroy_list(pMyList);
	destroy_list(&newList);

	Token token1, token2;
	token1.content.number = 3;
	token1.type = 1;
	memcpy(&token2, &token1, sizeof(Token));
	print_token(&token1);
	print_token(&token2);

	printf("Size of Token is %d.\n", sizeof(Token));

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
	if (ch >= 48 && ch <= 57) return 1;
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
#ifdef _DEBUG
	printf("\nadd_tail: Element size is %d.\n", pList->elementSize);
#endif
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
		printf("Added tail address is %p \n", pList->pTail);
#endif
	}


}

void print_list(pList pList, PrintFunction printFunction)
{
	pNode _pHead = pList->pHead;
	while (_pHead != NULL)
	{
#ifdef _DEBUG
		printf("address %p \n", _pHead);
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
	init_list(_pTokenStack, sizeof(Token));

	while (_pHead != NULL)
	{
#ifdef _DEBUG
		printf("print_nested_list: address %p, element type is %d\n", _pHead, ((Token*)(_pHead->pElement))->type);
#endif
		if (((Token*)(_pHead->pElement))->type != -1)
		{
#ifdef _DEBUG
			printf("print_nested_list: Encountered normal element. Element ASCII is %d.\n", ((Token*)(_pHead->pElement))->content.number);
#endif
			printFunction(_pHead->pElement);
		}
		else
		{
			printf("{#%d}", ((Token*)(_pHead->pElement))->content.number);
			add_head(_pTokenStack, _pHead->pElement);
		}
		
		_pHead = _pHead->pNext;
#ifdef _DEBUG
		printf("print_nested_list: pHead is currently at %p.\n", _pHead);
#endif
	}
	printf("\n");
	Token* _pToken = (Token*)stack_pop(_pTokenStack);
	while (_pToken != NULL)
	{
		printf("#%d: ", _pToken->content.number);
		print_nested_list((pList)_pToken->address, printFunction);
		_pToken = (Token*)stack_pop(_pTokenStack);
	}
	
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

#ifdef _DEBUG_1

			printf("\nprint_token: Debugging!\n");
#endif

			printf("%d", ((Token *)pToken)->content.number);
			break;

		case -1:
#ifdef _DEBUG
			printf("\n===\nprint_token: Address is %p.\nFormula id is %d.\n===\n", ((Token *)pToken)->address, ((Token *)pToken)->content.number);
#endif
			break;
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
		printf("Stack %p is Not Null!\n", pStack);
#endif
		
		void * _pAux;
		_pAux = pStack->pTail->pElement;

#ifdef _DEBUG
		print_number(_pAux);
		printf("\n");
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
#ifdef _DEBUG
				printf("A digit! %d\n", ch - 48);
#endif
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
				if (_tempToken.type == -8)
				{
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
				if (_tempToken.content.operation == '(')
				{
					_tempToken.type = 0;
				}
				else
				{
					_tempToken.type = -8;
				}
				
				break;

			default:
				break;

		}

	}

	/* We should check that if something is left here ! */
	if (_tempToken.type == 1)
	{
		add_tail(pNewList, &_tempToken);
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
	init_list(pResultList, sizeof(Token));
	// add_tail(pScopeStack, (void*)&pResultList);

	pList _pCurrentList = pResultList;
#ifdef _DEBUG
	printf("to_nested_list: pResultList element size is %d.\n", sizeof(Token));
	printf("to_nested_list: pCurrent element size is %d.\n", _pCurrentList->elementSize);
#endif

	pList _pNewList;

	Token _tempToken;

	while (_pHead != NULL)
	{
		Token* pToken = (Token*)(_pHead->pElement);
#ifdef _DEBUG
		printf("to_nested_list: Current token is: ");
		print_token(pToken);
		printf(", type is %d, address is %p.\n", pToken->type, _pHead);
#endif
		if (pToken->type == 8) {
#ifdef _DEBUG
			printf("pToken type is %d. pToken is %c.\n", pToken->type, pToken->content.operation);
#endif
			if (pToken->content.operation == '(')
			{
				_pNewList = (pList)malloc(sizeof(List));
#ifdef _DEBUG
				printf("to_nested_list: \n\nEntering! Current stack tops at %p\n\n", _pNewList);
				printf("Size of Node is %d.\n", sizeof(Node));
				printf("Size of Token is %d.\n", sizeof(Token));
#endif
				init_list(_pNewList, sizeof(Token));
				

				_tempToken.type = -1;
				_tempToken.content.number = count;
#ifdef _DEBUG
				printf("~~~~~\nAdded formula count is %d.\n~~~~~\n", count);
#endif
				_tempToken.address = (void*)_pNewList;
				add_tail(_pCurrentList, (void*)(&_tempToken));
#ifdef _DEBUG
				printf("to_nested_list: Address token is: ");
				print_token(&_tempToken);
				printf("\n");

				printf("Entering address is %p\n", _pCurrentList);
#endif
				count += 1;
				add_tail(pScopeStack, (void*)&_pCurrentList);
				_pCurrentList = _pNewList;
				
				
#ifdef _DEBUG
				printf("\n\nto_nested_list: ENTERING! Current stack tops at %p\n\n", _pNewList);
#endif
			}
			else
			{
#ifdef _DEBUG
				printf("Leaving!\n");
#endif
				_pCurrentList = *(pList*)stack_pop(pScopeStack);
#ifdef _DEBUG
				printf("Leaving address is %p\n", _pCurrentList);

				printf("\n\nto_nested_list: LEAVING! Current stack tops at %p\n\n", _pCurrentList);
#endif
			}
		}
		else
		{
#ifdef _DEBUG
			printf("to_nested_list: TOKEN being added is: ");
			print_token((pToken));

			
			printf("Current list is at %p.\n", _pCurrentList);
#endif
			add_tail(_pCurrentList, _pHead->pElement);
#ifdef _DEBUG
			printf(", type is %d, address is %p.\n", ((Token*)get_top(_pCurrentList))->type, get_top(_pCurrentList));
#endif
		}
		_pHead = _pHead->pNext;
		if (_pHead == NULL)
		{
#ifdef _DEBUG
			printf("NULL!\n");
#endif
		}
		else
		{
#ifdef _DEBUG
			printf("Next address is %p!\n", _pHead);
			printf("to_nested_list: Next is: ");
			print_token((Token*)_pHead->pElement);
			printf("\n");
#endif
		}

	}
#ifdef _DEBUG
	printf("Element size of result list is %d.\n", resultList.elementSize);
#endif
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