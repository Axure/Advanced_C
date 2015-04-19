#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

std::map<std::string, int> monthMap;
/* Clang doesn't support C++0x style initializer yet! */


class Date
{
private:

public:
	Date();
	Date(std::string string);
	~Date();
};

Date::Date()
{

}

Date::Date(std::string string)
{
	// sscanf("string");
}

Date::~Date()
{

}

int main(int argc, char const *argv[])
{


	monthMap["January"] = 1;
	monthMap["February"] = 2;
	monthMap["March"] = 3;
	monthMap["April"] = 4;
	monthMap["May"] = 5;
	monthMap["June"] = 6;
	monthMap["July"] = 7;
	monthMap["August"] = 8;
	monthMap["September"] = 9;
	monthMap["Octorber"] = 10;
	monthMap["November"] = 11;
	monthMap["December"] = 12;


	
	int T, day, year, month;
	std::string sMonth;
	char ssMonth[10];

	scanf("%d", &T);

	for (int i = 0; i < T; ++i)
	{
		std::scanf("%s %d, %d", ssMonth, &day, &year);
		sMonth = ssMonth;
		month = monthMap[sMonth];
		std::cout << sMonth << month;
	}


	return 0;
}