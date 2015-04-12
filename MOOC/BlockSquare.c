#include <stdio.h>
#include <Block.h>

typedef int (*IntToInt)(int);

IntToInt square(IntToInt f) {
	IntToInt g;
	g = (IntToInt)(^ (int x) {return f(x) * f(x);});
	return g;
}

int f(int x) {
	return x;
}

int main(int argc, char const *argv[])
{
	printf("%d\n", (square(f))(3));

	return 0;
}