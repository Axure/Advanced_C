#include <stdio.h>




int main(int argc, char const *argv[])
{
	int repeat, r;
	int A1, H1, A2, H2;
	scanf("%d", &repeat);
	for(r = 0; r < repeat; ++r){
		scanf("%d %d %d %d", &A1, &H1, &A2, &H2);
		if (A1 <= 0) {
			printf("Invalid\n");
		} else {
			H1 -= A2;
			H2 -= A1;
			if (H1 <= 0) printf("Discard ");
			else printf("%d %d ", A1, H1);
			if (H2 <= 0) printf("Discard\n");
			else printf("%d %d\n", A2, H2);

		}
	}

	return 0;
}