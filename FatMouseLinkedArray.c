#define BLOCK_SIZE 5

#include <stdlib.h>
#include <stdio.h>

typedef struct _array{
	int *array;
	int size;
	struct _array* next;
} Array;


Array array_create();
void array_free(Array *a);
int array_size(const Array *a);
int* array_at(Array *a, int index);
void array_inflate(Array *a);

Array array_create() {
	Array a;
	a.array = (int*)malloc(sizeof(int)*BLOCK_SIZE);
	a.size = BLOCK_SIZE;
	a.next = 0;
	return a;
}

void array_free(Array *a) {
	free(a->array);
	a->size = 0;
	if ( a->next ) {
		array_free(a->next);
		free(a->next);
	}
}

int array_size(const Array *a) {
	if ( !a->next )
		return a->size;
	else
		return a->size+array_size(a->next);
}

int* array_at(Array *a, int index) {
	if ( index < a->size ) {
		return &(a->array[index]);
	} else {
		if (!a->next) array_inflate(a);
		return array_at(a->next, index - a->size);
		
	}
}

void array_inflate(Array *a) {
	/*
// find the last block
	while ((++a) != 0) {}
// allocate a new block
	Array b;
	b.array = (int*)malloc(sizeof(int)*BLOCK_SIZE);
	b.size = BLOCK_SIZE;
	b.next = 0;
// link!
	a.next = b;
	*/
	printf("%d\n", a);

	if (!a->next)
	{
		// allocate a new block
		Array * b;
		b->array = (int*)malloc(sizeof(int)*BLOCK_SIZE);
		b->size = BLOCK_SIZE;
		b->next = 0;
		// link!
		a->next = b;
	} else {
		// find the last block
		array_inflate(a->next);
	}

}


int main(int argc, char const *argv[])
{
	Array myArray = array_create();

	printf("%lu\n", sizeof(myArray));

	array_inflate(&myArray);

	return 0;
}

