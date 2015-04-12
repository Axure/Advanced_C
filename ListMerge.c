#include <stdio.h>
#include <stdlib.h>

typedef struct _node * pNode;
typedef struct _node {
	int value;
	struct _node * next;
} Node;

typedef struct {
	Node * head;

} List;

Node * insert_head(Node * head, int value);
void add_head(List * pList, int value);
void add_tail(List * pList, int value);
void _print_list(Node * head);
void print_list(List * pList);
List read_list();
List merge_list(List * pList_A, List * pList_B);


int main(int argc, char const *argv[])
{
	

	List List_A = read_list();
	List List_B = read_list();
	List List_C = merge_list(&List_A, &List_B);

	print_list(&List_C);

	return 0;
}

void init_list(List * pList)
{
	pList->head = NULL;
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
}

void add_tail(List * pList, int value)
{
	Node * newTail = (Node*)malloc(sizeof(Node));

	newTail->value = value;
	newTail->next = NULL;
	if (pList->head == NULL) pList->head = newTail;
	else {
		Node * _pointer = pList->head;
		while(_pointer->next != NULL) _pointer = _pointer->next;
		_pointer->next = newTail;
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
					if (pHead_A->value < pHead_B->value)
					{
						add_tail(&newList, pHead_A->value);
						pHead_A = pHead_A->next;
					}
					else
					{
						add_tail(&newList, pHead_A->value);
						pHead_A = pHead_A->next;
						pHead_B = pHead_B->next;
					}

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