#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int score[3];
} Student;

const int capacity = 10;
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
    Student * pStudent;
    for (int i = 0; i < capacity; ++i)
    {
        
        
        pStudent = student_input((*pStudentList)[i]);
        (*pStudentList)[i] = pStudent;
        
        
        // Why does using an extra pStudent fix the problem?
        
        
    }
    
    return pStudentList;
    
}

void student_list_print(const StudentList *pStudentList) {
    printf("%s\t%s\t", "No.", "Name");
    
    for (int i = 1; i <= maxIndex; ++i)
    {
        printf("%s%d\t", "Score", i);
    }
    printf("%s\n", "Average");
    
    double sum[maxIndex];
    memset(sum, 0, sizeof(sum));
    int min[maxIndex], max[maxIndex];
    memset(max, 0, sizeof(max));
    
    int score;
    
    for (int i = 1; i <= capacity; ++i)
    {
        if (i == 1) {
            for (int j = 0; j < maxIndex; ++j) {
                score = (*pStudentList)[i - 1]->score[j];
                min[j] = score;
                // Why would 1 appear have we not changed the min[j] = *** to the right thing?
            }
        }
        for (int j = 0; j < maxIndex; ++j) {
            score = (*pStudentList)[i - 1]->score[j];
            sum[j] += score;
            min[j] = (score > min[j]) ? min[j] : score;
            max[j] = (score < max[j]) ? max[j] : score;
        }
        
        printf("%d\t", i);
        
        student_print((*pStudentList)[i - 1]);
        
        
    }
    
    printf("\tAvg");
    for (int j = 0; j < maxIndex; ++j) {
        printf("\t%lf", sum[j] / capacity);
        
    }
    printf("\n");
    
    printf("\tMin");
    for (int j = 0; j < maxIndex; ++j) {
        printf("\t%d", min[j]);
        
    }
    printf("\n");
    
    printf("\tMax");
    for (int j = 0; j < maxIndex; ++j) {
        printf("\t%d", max[j]);
        
    }
    printf("\n");
    
}

int main(int argc, char const *argv[])
{
    
    StudentList * myStudentList;
    myStudentList = student_list_input(myStudentList);
    
    student_list_print(myStudentList);
    
    
    return 0;
}


/*

 KW 5 5 5
 TD 4 3 2
 VC 3 4 5
 LT 4 3 4
 LL 3 4 3
 IY 4 2 5
 KH 4 2 1
 GP 4 4 4
 HG 2 3 4
 JJ 5 4 3

*/