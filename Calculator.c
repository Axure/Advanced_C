
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef union {
	char operation;
	int number;
} Content;

typedef struct {
	Content content;
	int type; /* 0 for empty, 1 for number, 2 for binary, 3 for unary operation) */
} Token;

typedef struct _node * pNode;
typedef struct _node {
	Token value;
	struct _node * previous, * next;
} Node;

typedef struct {
	Node * head, * tail;

} List;

typedef List TokenFlow;


int abs(int x);
int get_type(const char ch);
int cmpfunc (const void * a, const void * b);
void init_list(List * pList);
Node * insert_head(Node * head, Token value);
void add_head(List * pList, Token value);
void add_tail(List * pList, Token value);
void print_token(Token token);
void _print_list(Node * head);
void print_list(List * pList);
List read_list();
List merge_list(List * pList_A, List * pList_B);







/* Accepts a string, pops out the string and a token */


int main(int argc, char const *argv[])
{


	return 0;
}


/* How to customize the precedence and direction */



/*
	With the AST, it's a compiler
	Without it, it's an interpreter
*/


// What is the standard process of tokenization?

// Directly do it is the pratice of primary school students. It is nothing wrong though ^_^



// If the tree is binary, we can use a recursion to evaluate it...

// e.g.

// The hardest part is the priority..
/*
int evaluate(pTreeNode root);
int calculate(char symbol, int left_operand, int right_operand);

int evaluate(pTreeNode root) {
	if (root->pLeft == NULL) return root->value;
	else return calculate(root->symbol, evaluate(root->pLeft), evaluate(root->pRight));
	// How to optimize the cache used for this program? Mayebe we need to use a static cache? STL map may be used 233?
	// No.. A binary tree needs no optimization as there is no repeated visit to any node.

}

int calculate(char symbol, int left_operand, int right_operand) {

}
*/











void init_list(List * pList)
{
	pList->head = NULL;
	pList->tail = NULL;
}

Node * insert_head(Node * head, Token value)
{ /* Callback? */
	Node * newHead = (Node*)malloc(sizeof(Node));

	newHead->value = value;
	newHead->next = head;
	head->previous = newHead;
	/* head = newHead; // This is redundant unless you pass the pointer, again, by reference... */

	return newHead;
}

void add_head(List * pList, Token value)
{ /* This function has a side effect. */
	pList->head = insert_head(pList->head, value);
}

void add_tail(List * pList, Token value)
{
	Node * newTail = (Node*)malloc(sizeof(Node));

	newTail->value = value;
	newTail->previous = NULL;
	newTail->next = NULL;
	if (pList->head == NULL)
	{
		pList->head = newTail;
	}
	else
	{
		Node * _pointer = pList->head;
		while(_pointer->next != NULL) _pointer = _pointer->next;
		_pointer->next = newTail;
		newTail->previous = _pointer;
	}

	/* Maybe we should use recursion and pass the last available node address.. This is a handsome idea! */
}


void _print_list(Node * head)
{

	
	Node * _head = head;
	while(_head != NULL) {

		print_token(_head->value);


		_head = _head->next;
	}
	printf("\n");

	
}

void print_list(List * pList)
{
	_print_list(pList->head);
}

void print_token(Token token)
{
	switch (token.type)
	{
		case 0:
			break;
		case 1:
			printf("%d", token.content.number);
			break;
		case 2:
			switch (token.content.operation)
			{
				case '+':

					break;
				case '-':
					
					break;

			}
			break;
		case 3:
			break;
		default:
			break;
	}
}





List read_list()
{
	List newList;
	init_list(&newList);



	char ch;


	while((EOF != (ch = getchar()) && ch != '\n'))
	{

	}

	Token _tempToken;


}


void release_list(List * pList)
{
	Node * pNode = pList->head;
	Node * pAuxNode;
	while (pNode != NULL)
	{
		pAuxNode = pNode;
		pNode = pNode->next;
		free(pAuxNode);
	}
}
