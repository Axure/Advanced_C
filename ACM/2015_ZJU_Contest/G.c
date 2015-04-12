#include <stdio.h>

const long double pi = 3.1415926535897932384626433832795028841971;

long double volume(int r, int h, int d) {
	return 4 * d * d * d * pi / 3.0 + d * d * h * pi + 2 * d * h * pi * r + d * d * pi * pi * r + 2 * d * pi * r * r + h * pi * r * r;

}

long double area(int r, int h, int d) {
	return 2 * pi * pi * d * r + 4 * pi * d * d + 2 * pi * r * r + 2 * pi * h * r + 2 * pi * d * h;
}

int main(int argc, char const *argv[])
{
	int R;
	scanf("%d", &R);
	int rr;
	int r, h, d;
	for(rr = 0; rr < R; ++rr){
		scanf("%d %d %d", &r, &h, &d);
		printf("%.12LF ", volume(r, h, d));
		printf("%.12LF\n", area(r, h, d));
	}

	return 0;
}