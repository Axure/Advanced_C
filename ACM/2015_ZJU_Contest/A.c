#include <stdio.h>



int main(int argc, char const *argv[])
{
	int N;
	scanf("%d", &N);

	int r, i, done;

	for(r = 0; r < N; ++r){
		
		int T, A, B, _temp;
		scanf("%d", &T);
		scanf("%d %d", &A, &B);
		done = 0;
		if (A == B) {
			for(i = 2; i < T; ++i){
				scanf("%d", &_temp);
				if (done == 0 && _temp != A) {
					printf("%d\n", _temp);
					done = 1;
				}
			}
		} else {
			for(i = 2; i < T; ++i){
				scanf("%d", &_temp);
				
				if (done == 0) {
					if (_temp == A) printf("%d\n", B);
					else printf("%d\n", A);
				}

				done = 1;
				
			}
		}


	}

	return 0;
}
