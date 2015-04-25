#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

std::map<std::string, int> monthMap;
/* Clang doesn't support C++0x style initializer yet! */

int before_the_day(int month, int day)
{
	if (month >= 3) return 1;
	if (month == 1) return -1;
	if (month == 2)
	{
		if (day <= 28) return -1;
		if (day == 29) return 0;
	}
}

int with_the_day(int month, int day, int year)
{
	if (!(year % 4 == 0 && !(year % 100 == 0 ^ year % 400 == 0))) return 0;
	if (month >= 3) return -1;
	if (month == 1) return 0;
	if (month == 2)
	{
		if (day <= 28) return 0;
		if (day == 29) return 0;
	}
	return 0;
}

// We should write a good version after passing the contest.

bool have_the_day(int year)
{
	// std::cout << std::endl << "in is " << !(year % 100 == 0 ^ year % 400 == 0) << std::endl;
	// return (year % 4 == 0 && !(year % 100 == 0 ^ year % 400 == 0));
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int lowest_four(int year)
{
	if (year % 4 == 0) return year;
	if ((year + 1) % 4 == 0) return year + 1;
	if ((year + 2) % 4 == 0) return year + 2;
	if ((year + 3) % 4 == 0) return year + 3;
	return 0;
}

int hightest_four(int year)
{
	if (year % 4 == 0) return year;
#ifdef _DEBUG
	printf("%d\n", (year - 1) % 4 == 0);
#endif
	if ((year - 1) % 4 == 0) return year - 1;
	if ((year - 2) % 4 == 0) return year - 2;
	if ((year - 3) % 4 == 0) return year - 3;
	return 0;
}

int lowest_hundred(int year)
{
	// std::printf("lowest hunred is %d\n", (year % 100 == 0) ? year : year - year % 100);
	return (year % 100 == 0) ? year : year + 100 - year % 100;
}

int highest_hundred(int year)
{
	// std::printf("highest hunred is %d\n", (year % 100 == 0) ? year : year + 100 - year % 100);
	return (year % 100 == 0) ? year : year - year % 100;
}

int lowest_4hundred(int year)
{
	return (year % 400 == 0) ? year : year + 400 - year % 400;
}

int highest_4hundred(int year)
{
	return (year % 400 == 0) ? year : year - year % 400;
}

int count_the_day_between(int start, int end)
{
	// int _raw = (end - start) / 4;
	// if (have_the_day(start) || have_the_day(end)) _raw += 1;
	// return _raw;

	// Maybe we should think more mathematically
	// solution = 4 - (100 but not 400)

	int num4 = (hightest_four(end) - lowest_four(start)) / 4 + 1;
#ifdef _DEBUG
	std::printf("%d, %d, %d\n", hightest_four(end), lowest_four(start), (hightest_four(end) - lowest_four(start)) / 4);
	std::cout << "Num 4 is: " << num4 << std::endl;
#endif
	int num100 = (highest_hundred(end) - lowest_hundred(start)) / 100 + 1;
#ifdef _DEBUG
	std::cout << "Num 100 is: " << num100 << std::endl;
#endif
	int num400 = (highest_4hundred(end) - lowest_4hundred(start)) / 400 + 1;
#ifdef _DEBUG
	std::cout << "Num 400 is: " << num400 << std::endl;
#endif
	// Doing primary school math Olympiad with the computer LOL
	return num4 - num100 + num400;
}

// class Date
// {
// private:

// public:
// 	Date();
// 	Date(std::string string);
// 	~Date();
// };

// Date::Date()
// {

// }

// Date::Date(std::string string)
// {
// 	// sscanf("string");
// }

// Date::~Date()
// {

// }

void test()
{
	std::cout << have_the_day(2000) << have_the_day(1919) << have_the_day(1900) << have_the_day(1996);
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
	monthMap["October"] = 10;
	monthMap["November"] = 11;
	monthMap["December"] = 12;


	
	int T, day, year, month;
	int day_, year_, month_;

	std::string sMonth;
	char ssMonth[10];


	std::string sMonth_;
	char ssMonth_[10];
#ifdef _DEBUG
	test();
#endif

	scanf("%d", &T);

	int result;

	for (int i = 0; i < T; ++i)
	{
		std::scanf("%s %d, %d", ssMonth, &day, &year);
		sMonth = ssMonth;
		month = monthMap[sMonth];
#ifdef _DEBUG
		std::cout << sMonth << day << " " << year << std::endl;
#endif

		std::scanf("%s %d, %d", ssMonth_, &day_, &year_);
		sMonth_ = ssMonth_;
		month_ = monthMap[sMonth_];
#ifdef _DEBUG
		std::cout << sMonth_ << day_ << " " << year_  << std::endl;
#endif
		
		result = count_the_day_between(year, year_);

#ifdef _DEBUG
		std::cout << "Case #" << i + 1 << ": " << result << std::endl;
#endif		
		// result += with_the_day(month, day, year);
#ifdef _DEBUG
		printf("%d, %d\n", with_the_day(month, day, year_), with_the_day(month_, day_, year_));
#endif
		// result += with_the_day(month_, day_, year_);
		// if (year == year_ && count_the_day_between(year, year) == 1 && with_the_day(month_, day_, year_) == -1) result += 1;
		// if (year == year_ && count_the_day_between(year, year) == 1 && with_the_day(month, day, year) == 0) result -= 1;
		if (have_the_day(year) && before_the_day(month, day) == 1) result -= 1;
		if (have_the_day(year_) && before_the_day(month_, day_) == -1) result -= 1;

		std::cout << "Case #" << i + 1 << ": " << result;
		if (i != T - 1) cout << endl;

	}


	return 0;
}

