#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int exponent, coefficient;
	int sign;
} Monomial;

typedef struct _node * pNode;
typedef struct _node {
	Monomial value;
	struct _node * previous, * next;
} Node;

typedef struct {
	Node * head, * tail;

} List;

typedef List Polynomial;






/* We need a sort
	and a coordinated sort
	*/

int abs(int x);
int get_type(const char ch);
int cmpfunc (const void * a, const void * b);
Node * insert_head(Node * head, Monomial value);
void add_head(List * pList, Monomial value);
void add_tail(List * pList, Monomial value);
void print_monomial(Monomial monomial);
void _print_list(Node * head);
void print_list(List * pList);
List read_list();
List merge_list(List * pList_A, List * pList_B);
void normalize(Polynomial * pPolynomial);
Polynomial add(Polynomial * pPolynomial_A, Polynomial * pPolynomial_B);
Polynomial inverse(Polynomial *pPolynomial);
Polynomial minus(Polynomial * pPolynomial_A, Polynomial * pPolynomial_B);
Polynomial shift(Polynomial * pPolynomial, int position);
Polynomial multiply_by_number(Polynomial *pPolynomial, int number);
Polynomial multiply(Polynomial * pPolynomial_A, Polynomial * pPolynomial_B);

int abs(int x)
{
	return (x > 0) ? x : -x;
}

int get_type(const char ch)
{
	if (ch >= 48 && ch < 57) return 1;
	if (ch == '+' || ch =='-') return 2;
	if (ch == 'x') return 4;
	return 0;
}

int cmpfunc (const void * a, const void * b)
{
   return ( ((Monomial*)b)->exponent - ((Monomial*)a)->exponent );
}

int main(int argc, char const *argv[])
{
	

	List List_A = read_list();
	List List_B = read_list();

	List List_C = add(&List_A, &List_B);
	print_list(&List_A);
	print_list(&List_B);
	// print_list(&List_C);

	// List_C = minus(&List_A, &List_B);
	// // List_C = inverse(&List_B);
	// print_list(&List_C);

	// List_C = shift(&List_C, -5);
	// print_list(&List_C);

	// List_C = multiply_by_number(&List_C, 5);
	// print_list(&List_C);
	// printf("FUcked!\n");


	List_C = multiply(&List_A, &List_B);
	print_list(&List_C);


	return 0;
}

void init_list(List * pList)
{
	pList->head = NULL;
	pList->tail = NULL;
}

Node * insert_head(Node * head, Monomial value)
{ /* Callback? */
	Node * newHead = (Node*)malloc(sizeof(Node));

	newHead->value = value;
	newHead->next = head;
	head->previous = newHead;
	/* head = newHead; // This is redundant unless you pass the pointer, again, by reference... */

	return newHead;
}

void add_head(List * pList, Monomial value)
{ /* This function has a side effect. */
	pList->head = insert_head(pList->head, value);
}

void add_tail(List * pList, Monomial value)
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

void print_monomial(Monomial monomial)
{
	if (monomial.sign == -1) printf("-");
	if (abs(monomial.coefficient) != 1 || monomial.exponent == 0) printf("%d", monomial.coefficient);
	if (monomial.exponent != 0) printf("x");
	if (monomial.exponent != 1 && monomial.exponent != 0) printf("%d", monomial.exponent);
}

void _print_list(Node * head)
{

	
	Node * _head = head;
	while(_head != NULL) {

		if (_head == head) print_monomial(_head->value);
		else
		{
			if (_head->value.sign == 1) printf("+");
			print_monomial(_head->value);
		}


		_head = _head->next;
	}
	printf("\n");

	
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



	char ch;

	Monomial _tempMonomial;
	_tempMonomial.exponent = 0;
	_tempMonomial.coefficient = 0;
	_tempMonomial.sign = 1;
	int beforeOrAfter = 0;
/* This is exactly a test of ability! */
	while((EOF != (ch = getchar()) && ch != '\n'))
	{
		switch (get_type(ch) + 8 * beforeOrAfter)
		{
			case 1: /* before, and receive a digit */
				_tempMonomial.coefficient = 10 * _tempMonomial.coefficient + ch - 48;
				break;
			case 2: /* before, and receive a symbol */
				/* This is not gonna happen? */
				if (ch == '-') _tempMonomial.sign = -1;
				break;
			case 4: /* before, and receive an x */
				beforeOrAfter = 1; /* sets to after */
				break;
			case 9: /* after, and receive a digit */
				_tempMonomial.exponent = 10 * _tempMonomial.exponent + ch - 48;
				break;
			case 10: /* after, and receive a symbol */
				beforeOrAfter = 0; /* sets to before */
				if (_tempMonomial.exponent == 0) _tempMonomial.exponent = 1;
				add_tail(&newList, _tempMonomial);
				/* reinitialize monomial */
				_tempMonomial.exponent = 0;
				_tempMonomial.coefficient = 0;
				if (ch == '+') _tempMonomial.sign = 1;
				else _tempMonomial.sign = -1;
				break;
			case 12: /* after, and receive an x */
				/* This is unreasonable */
				break;
			default:
				break;
		}

	}
	/* if ends */
	if (beforeOrAfter == 0)
	{
		_tempMonomial.exponent = 0; /* Good for refactoring */
	}
	else
	{
		if (_tempMonomial.exponent == 0)
		{
			_tempMonomial.exponent = 1;
		}
	}
	add_tail(&newList, _tempMonomial);


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
	Monomial newMonomial;

	while ((state = (pHead_A != NULL) + 2 * (pHead_B != NULL)) != 0)
	{
		// printf("Difference is %d - %d = %d\n", (pHead_A->value).exponent, (pHead_B->value).exponent, cmpfunc(&pHead_B->value, &pHead_A->value));
		switch (state)
		{
			case 3:
				if (cmpfunc(&pHead_B->value, &pHead_A->value) < 0)
				{

					add_tail(&newList, pHead_B->value);
					pHead_B = pHead_B->next;
				}
				else
				{
					if (cmpfunc(&pHead_B->value, &pHead_A->value) > 0)
					{
						add_tail(&newList, pHead_A->value);
						pHead_A = pHead_A->next;
					}
					else /* if they are equal? */
					{
						
						newMonomial.exponent = pHead_A->value.exponent;

						newMonomial.coefficient = pHead_A->value.coefficient * pHead_A->value.sign + pHead_B->value.coefficient * pHead_B->value.sign;
						newMonomial.sign = (newMonomial.coefficient >= 0) ? 1 : -1;
						newMonomial.coefficient = abs(newMonomial.coefficient);
						if (newMonomial.coefficient != 0) add_tail(&newList, newMonomial);
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

void normalize(Polynomial * pPolynomial)
{





}

Polynomial add(Polynomial * pPolynomial_A, Polynomial * pPolynomial_B)
{
	return merge_list(pPolynomial_A, pPolynomial_B);

}
Polynomial inverse(Polynomial *pPolynomial)
{
	Polynomial inversePolynomial;
	init_list(&inversePolynomial);
	Monomial _tempMonomial;
	Node * pNode = pPolynomial->head;
	while (pNode != NULL)
	{

		_tempMonomial.exponent = pNode->value.exponent;
		_tempMonomial.coefficient = pNode->value.coefficient;
		_tempMonomial.sign = -(pNode->value.sign);
		_tempMonomial.coefficient = abs(_tempMonomial.coefficient);

		add_tail(&inversePolynomial, _tempMonomial);

		pNode = pNode->next;
	}


	return inversePolynomial;

}
Polynomial minus(Polynomial * pPolynomial_A, Polynomial * pPolynomial_B)
{
	Polynomial inverseOfB = inverse(pPolynomial_B);
	return add(pPolynomial_A, &inverseOfB);
}
Polynomial shift(Polynomial * pPolynomial, int position)
{
	Polynomial shiftedPolynomial;
	init_list(&shiftedPolynomial);
	Monomial _tempMonomial;
	Node * pNode = pPolynomial->head;
	while (pNode != NULL)
	{

		_tempMonomial.exponent = pNode->value.exponent + position;
		_tempMonomial.coefficient = pNode->value.coefficient;
		_tempMonomial.sign = pNode->value.sign;


		add_tail(&shiftedPolynomial, _tempMonomial);

		pNode = pNode->next;
	}


	return shiftedPolynomial;

}
Polynomial multiply_by_number(Polynomial *pPolynomial, int number)
{

	Polynomial product;
	init_list(&product);

	Monomial _tempMonomial;
	Node * pNode = pPolynomial->head;
	while (pNode != NULL)
	{

		_tempMonomial.exponent = pNode->value.exponent;
		_tempMonomial.coefficient = number * pNode->value.coefficient;
		_tempMonomial.sign = pNode->value.sign;
		_tempMonomial.coefficient = abs(_tempMonomial.coefficient);

		add_tail(&product, _tempMonomial);

		pNode = pNode->next;
	}

	return product;

}
Polynomial multiply(Polynomial * pPolynomial_A, Polynomial * pPolynomial_B)
{
	Polynomial product, _tempPolynomial;
	init_list(&product);

	Node * pNode = pPolynomial_B->head;
	while (pNode != NULL)
	{

		_tempPolynomial = multiply_by_number(pPolynomial_A, pNode->value.coefficient);
		_tempPolynomial = shift(&_tempPolynomial, pNode->value.exponent);


		product = add(&product, &_tempPolynomial);

		pNode = pNode->next;
	}

	return product;
}