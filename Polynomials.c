#include <stdio.h>
#include <stdlib.h>

typedef struct _node * pNode;
typedef struct _node {
	int value;
	struct _node * next;
} Node;

typedef struct {
	Node * head;
	Node * tail;
} List;

typedef struct {
	List exponents, coefficient;
} Polynomial;

/* We need a sort
	and a coordinated sort
	*/

Node * insert_head(Node * head, int value);
void add_head(List * pList, int value);
void add_tail(List * pList, int value);
void _print_list(Node * head);
void print_list(List * pList);
List read_list();
List merge_list(List * pList_A, List * pList_B);
void normalize(Polynomial * pPolynomial);

int main(int argc, char const *argv[])
{
	

	List List_A = read_list();
	List List_B = read_list();
	add_head(&List_B, 0);
	List List_C = merge_list(&List_A, &List_B);

	print_list(&List_C);

	return 0;
}

void init_list(List * pList)
{
	pList->head = NULL;
	pList->tail = NULL;
}

Node * insert_head(Node * head, int value)
{ /* Callback? */
	Node * newHead = (Node*)malloc(sizeof(Node));

	newHead->value = value;
	newHead->next = head;
	/* head = newHead; // This is redundant unless you pass the pointer, again, by reference... */

	return newHead;
}

void add_head(List * pList, int value)
{ /* This function has a side effect. */
	pList->head = insert_head(pList->head, value);
	if (pList->tail == NULL) pList->tail = pList->head;
}

void add_tail(List * pList, int value)
{
	Node * newTail = (Node*)malloc(sizeof(Node));

	newTail->value = value;
	newTail->next = NULL;
	if (pList->head == NULL) {
		pList->head = newTail;
		pList->tail = newTail;
	}
	else {
		pList->tail->next = newTail;
		pList->tail = newTail;
	}

	/* Maybe we should use recursion and pass the last available node address.. This is a handsome idea! */
}

void _print_list(Node * head)
{

	
	Node * _head = head;
	while(_head != NULL) {

		if (_head->next != NULL) printf("%d ", _head->value);
		else printf("%d\n", _head->value);
		_head = _head->next;
	}

	
}

void print_list(List * pList)
{
	_print_list(pList->head);
}

/* Don't forget to destruct the structs... */

List read_list()
{
	List newList;
	init_list(&newList);

	int _value;

	while((scanf("%d", &_value) && _value != -1))
	{
		add_tail(&newList, _value);
	}
	print_list(&newList);
	return newList;

}

/* we should customzie the linter... */

List merge_list(List * pList_A, List * pList_B)
{
	List newList;
	init_list(&newList);

	Node * pHead_A = pList_A->head;
	Node * pHead_B = pList_B->head;

	int state;

	while ((state = (pHead_A != NULL) + 2 * (pHead_B != NULL)) != 0)
	{
		switch (state)
		{
			case 3:
				if (pHead_A->value > pHead_B->value)
				{
					add_tail(&newList, pHead_B->value);
					pHead_B = pHead_B->next;
				}
				else
				{
					add_tail(&newList, pHead_A->value);
					pHead_A = pHead_A->next;	
				}
				break;
			case 2:
				while (pHead_B != NULL)
				{
					add_tail(&newList, pHead_B->value);
					pHead_B = pHead_B->next;
				}
				break;
			case 1:
				while (pHead_A != NULL)
				{
					add_tail(&newList, pHead_A->value);
					pHead_A = pHead_A->next;
				}
				break;
			default:
				break;
		}
	} 

	return newList;

}

void normalize(Polynomial * pPolynomial)
{
	List newExponent, newCoefficient;
	init_list(&newExponent);
	init_list(&newCoefficient);

	Node *__pointer_E;
	Node *__pointer_C;

	Node * _pointer_E = pPolynomial->exponents.head;
	Node * _pointer_C = pPolynomial->coefficient.head;

	while (_pointer_E != NULL)
	{
		if (newExponent.head == NULL)
		{
			add_head(&newExponent, _pointer_E->value);
			add_head(&newCoefficient, _pointer_C->value);
		}
		else
		{
			__pointer_E = newExponent.head;
			__pointer_C = newExponent.head;
			while (__pointer_E->value > _pointer_E->value)
			{
				__pointer_E = __pointer_E->next;
				__pointer_C = __pointer_C->next;
			}
			if (__pointer_E->value == _pointer_E->value) __pointer_C->value += _pointer_C->value;
			else
			{
				insert_head(Node *head, int value)
			}
		}

		_pointer_E = _pointer_E->next;
		_pointer_C = _pointer_C->next;
	}

	pPolynomial->exponents = newExponent;
	pPolynomial->coefficient = newCoefficient;



}