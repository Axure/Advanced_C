#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mid(int a, int b);
void swap (char *x, char *y);
void permute(char *a, int i, int n);
int is_valid(char *a, int n);
int cmpfunc (const void * a, const void * b);

struct array {
	int * array;
	int size;
} array;


const int mid_matrix[10][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 2, 0, 0, 0, 4, 0, 5},
	{0, 0, 0, 0, 0, 0, 0, 0, 5, 0},
	{0, 2, 0, 0, 0 ,0, 0, 5, 0, 6},
	{0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 5, 0, 0, 0, 0, 0},
	{0, 4, 0, 5, 0, 0, 0, 0, 0, 8},
	{0, 0, 5, 0, 0, 0, 0, 0, 0, 0},
	{0, 5, 0, 6, 0, 0, 0, 8, 0, 0}
};

int cmpfunc (const void * a, const void * b)
{
   return ( *(char*)a - *(char*)b );
}

int is_valid(char *a, int n)
{

	int i;
	int hash[10];
	memset(hash, 0, sizeof(int) * 10);

	hash[*a - 48] = 1;
	hash[0] = 1;
	for(i = 1; i < n; ++i){
		hash[*(a + i - 1) - 48] = 1;
		if (hash[mid(*(a + i - 1) - 48, *(a + i) - 48)] == 0) return 0;
	}

	return 1;
}

int mid(int a, int b) {
	return mid_matrix[a][b];
}

/* Function to swap values at two pointers */
void swap (char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permute(char *a, int i, int n)
{
   int j; 
   if (i == n) {

   	if (is_valid(a, n)) {
   		for(j = 0; j < n; ++j){
	   		printf("%c ", *(a + j));
	   	}
	    printf("%c\n", *(a + n));
   	}


   
 }
   else
   {
        for (j = i; j <= n; j++)
       {
          swap((a+i), (a+j));
          permute(a, i+1, n);
          swap((a+i), (a+j)); 
       }
   }
}

void permute_2(char *a, int i, int n, int *sum)
{
   int j; 
   if (i == n) {

   	if (is_valid(a, n)) {

   		*sum += 1;
   	}


   
 }
   else
   {
        for (j = i; j <= n; j++)
       {
          swap((a+i), (a+j));
          permute_2(a, i+1, n, sum);
          swap((a+i), (a+j)); 
       }
   }
} 

int main(int argc, char const *argv[])
{
	
	int repeat, r, i;
	int n, point[10], sum;
	char key[10];
	scanf("%d", &repeat);
	for (r = 0; r < repeat; ++r) {
		scanf("%d", &n);
		for(i = 1; i <= n; ++i){
			scanf("%d", point + i);
			key[i] = point[i] + 48;
		}
		sum = 0;
		qsort(key + 1, n, sizeof(char), cmpfunc);

		// for(i = 1; i <= n; ++i){
		// 	printf("%c, ", key[i]);
		// }
		// printf("\n");

		permute_2(key + 1, 0, n - 1, &sum);
		printf("%d\n", sum);
		permute(key + 1, 0, n - 1);












	}



	return 0;
}