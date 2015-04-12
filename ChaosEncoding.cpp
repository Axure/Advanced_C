// thiwednesday1.cpp : 定义控制台应用程序的入口点。
//

// #include "stdafx.h"
#include <iostream>
#include <stdio.h>
using namespace std;



//int _tmain(int argc, _TCHAR* argv[])
int main()
{
	char c[][5] = { { ' ', ' ', '*' }, { ' ', '*', ' ', '*' },
	{ ' ', '*', ' ', '*' }, { ' ', ' ', '*' } };
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			/*std::cout << c[i][j];
			std::cout<<std::endl;*/
			printf("%c", c[i][j]);
		}
		printf("\n");
	}
	std::cin >> i;
	//return 0;
}