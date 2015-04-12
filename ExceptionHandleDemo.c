#include <stdio.h>
#include <setjmp.h>

#include <stdlib.h>

#include <string.h> /* What is in string.h? */


// typedef struct _array {

// }

// int * array_at(Array *a, int index) {
// 	if (index)
// 	{
// 		/* code */
// 	}
// }

static jmp_buf exception_env;
static int exception_type;

void read() {
	int a, b;
	scanf("%d %d", &a, &b);
	if (/* condition */)
	{
		/* code */
	}
}


int main(int argc, char const *argv[])
{




	

	return 0;
}