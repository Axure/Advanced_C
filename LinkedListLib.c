// FM Advanced C course notes

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define _DEBUG
#undef _DEBUG

#ifdef _DEBUG

#endif

typedef void IntToVoid(int);
typedef struct _node * pNode;
typedef struct _node {
	int value;
	struct _node * next;
} Node;

typedef struct {
	Node * head;

} List;

Node * insert_head(Node * head, int value);
void unit_test();
void print_list(Node * head);
void add_head(List * list, int value); // This function has not bypassed the unit test.
void traverse(List * list, IntToVoid _function);
pNode search(List * pList, int value);
int remove_value(List * pList, int value);
void clear(List * pList);
void add_tail(List * list, int value);
Node * insert_many(Node * head, ...);

void add_tail(List * pList, int value) {
	Node * newTail = (Node*)malloc(sizeof(Node));

	newTail->value = value;
	newTail->next = NULL;
	if (pList->head == NULL) pList->head = newTail;
	else {
		Node * _pointer = pList->head;
		while(_pointer->next != NULL) _pointer = _pointer->next;
		_pointer->next = newTail;
	}

	// Maybe we should use recursion and pass the last available node address.. This is a handsome idea!
}

void clear(List * pList) {
	Node * _aux_pointer;

	while(pList->head != NULL) {
		_aux_pointer = pList->head->next;
		free(pList->head);
		pList->head = _aux_pointer;
	}

}

int remove_value(List * pList, int value) { // This only deletes the first instance...
	pNode p, q;
	int ifSucceeded = 0;
	for (q = 0, p = pList->head; p; q = p, p = p->next) {
		printf("p value is %d\n", p->value);
		if (p->value == value)
		{

			printf("Entered!\n");
			if (q) {

				q->next = p->next;

				free(p);
			} else {
				pList->head = p->next;
				free(p);

			}

			ifSucceeded += 1;

		}
	}

	return ifSucceeded;
}

// return 0 not found
// return 1 found and deleted



pNode search(List * pList, int value) {

}

void sumInteger(int value) {
	static int sum = 0;
	sum += value;
	printf("sum is %d now.\n", sum);
}

void traverse(List * list, IntToVoid _function) {
	Node * _head = list->head;
	int i = 0;
	printf("called\n");
	while(_head != NULL) {
		++i;
		printf("i is at %d\n", i);
		_function(_head->value);
		_head = _head->next;
	}
}

void add_head(List * list, int value) { // This function has a side effect.
	list->head = insert_head(list->head, value);
}




Node * insert_head(Node * head, int value) { // Callback?
	Node * newHead = (Node*)malloc(sizeof(Node));

	newHead->value = value;
	newHead->next = head;
	// head = newHead; // This is redundant unless you pass the pointer, again, by reference...

	return newHead;
}

Node * insert_many(Node * head, ...) { // Callback? Why call back?

	va_list args_list;

	va_start(args_list, head);
	Node * newHead = head;
	int value;
	while ((value = va_arg(args_list, int)) != -1) {
		newHead = insert_head(newHead, value);
	}




	// head = newHead; // This is redundant unless you pass the pointer, again, by reference...

	return newHead;
}



int main(int argc, char const *argv[])
{
	unit_test();
	return 0;
}

void print_list(Node * head) {
#ifdef _DEBUG
	printf("\n=====Begin======\n");
#endif
	
	Node * _head = head;
	while(_head != NULL) {
		printf("%d ", _head->value);
		_head = _head->next;
	}
#ifdef _DEBUG
	printf("=====End======\n\n");
#endif
	
}

void unit_test() {
	// Assert?
	// Expect?
	// How to get that kind of things?
	int _int;
	Node * newHead = NULL;
	List newList;
	
	while(scanf("%d", &_int) && _int != -1) {
#ifdef _DEBUG
		printf("%d, %d\n", _int, (_int != -1));
#endif
		
		newHead = insert_head(newHead, _int);
	}

	newList.head = newHead; // This piece of code is suspicious


	print_list(newHead);


#ifdef _DEBUG
	traverse(&newList, sumInteger);

	add_tail(&newList, 134);
	print_list(newList.head);

	printf("Found %d instances.\n", remove_value(&newList, 1));
	print_list(newList.head);

	add_tail(&newList, 134);
	print_list(newList.head);

	clear(&newList);
	print_list(newList.head);

	add_tail(&newList, 134);
	print_list(newList.head);

	newList.head = insert_many(newList.head, 123, 123, 32, 1, 32, 4, -1);
	print_list(newList.head);
#endif



}