#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int score[3];
} Student;

const int capacity = 2;
const int maxIndex = 3;

typedef Student * StudentList[capacity];
 
//    输入一个学生的数据
Student* student_input(Student *pStudent);
//    输出一个学生的数据，包括平均成绩
void student_print(const Student *pStudent);
//    计算一个学生的平均成绩
double student_average(const Student *pStudent);
//    获得学生的一个成绩
int student_get_score(const Student *pStudent, int index);
StudentList* student_list_input(StudentList *pStudentList);
void student_list_print(const StudentList *pStudentList);


Student* student_input(Student *pStudent) {
	pStudent = (Student *)malloc(sizeof(Student));
	scanf("%s", pStudent->name);
	for (int i = 0; i < maxIndex; ++i)
	{
		scanf("%d", &pStudent->score[i]);
	}
	
	return pStudent;
}

void student_print(const Student *pStudent) {

	printf("%s\t", pStudent->name);
	for (int i = 0; i < maxIndex; ++i)
	{
		printf("%d\t", pStudent->score[i]);
	}
	printf("%lf\n", student_average(pStudent));
	// Todo: 模糊判断输出位数

}


double student_average(const Student *pStudent) {


	double sum = 0;
	for (int i = 0; i < maxIndex; ++i)
	{
		sum += pStudent->score[i];
	}
	return sum / (double) maxIndex;

}


int student_get_score(const Student *pStudent, int index) {
	return pStudent->score[index];
}

StudentList* student_list_input(StudentList *pStudentList){

	pStudentList = (StudentList *)malloc(sizeof(StudentList) * capacity);

	for (int i = 0; i < capacity; ++i)
	{
		*pStudentList[i] = student_input(*pStudentList[i]);
	}

	return pStudentList;

}

void student_list_print(const StudentList *pStudentList) {
	printf("%s\t%s\t", "No", "Name");

	for (int i = 1; i <= maxIndex; ++i)
	{
		printf("%s%d\t", "Score", i);
	}
	printf("%s\n", "Average");


	for (int i = 1; i <= capacity; ++i)
	{
		printf("%d\t", i);
		student_print((*pStudentList)[i - 1]);
	}

}

int main(int argc, char const *argv[])
{
	
	StudentList * myStudentList;
	myStudentList = student_list_input(myStudentList);

	student_list_print(myStudentList);


	return 0;
}