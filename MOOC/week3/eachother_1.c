#include <stdio.h>
#include <string.h>
 
typedef struct {
    char name[20];
    int score[3];
} Student;
  
//    输入一个学生的数据
Student* student_input(Student *pStudent);
//    输出一个学生的数据，包括平均成绩
void student_print(const Student *pStudent);
//    计算一个学生的平均成绩
double student_average(const Student *pStudent);    
//    获得学生的一个成绩
int student_get_score(const Student *pStudent, int index);
//    计算一个成绩的平均值
double score_average(const Student *pStudent, int index);
//    获得一个成绩的最小值 
int get_score_min(const Student *pStudent, int index);
//    获得一个成绩的最大值 
int get_score_max(const Student *pStudent, int index);
 
int main(int argc, char *argv[])
{
    Student student[10];
    int i;
 
    for(i = 0; i < 10; i++)
    {
        student_input(&student[i]);
    }
    printf("\n\nno\tname\tscore1\tscore2\tscore3\taverage\n");
    for(i = 0; i < 10; i++)
    {
        printf("%d\t", i + 1);
        student_print(&student[i]);
    }
    printf("  \taverage\t");
    for(i = 0; i < 3; i++)
    {
        printf("%lf\t", score_average(student, i));
    }
    printf("\n  \tmin\t");
    for(i = 0; i < 3; i++)
    {
        printf("%d\t", get_score_min(student, i));
    }
    printf("\n  \tmax\t");
    for(i = 0; i < 3; i++)
    {
        printf("%d\t", get_score_max(student, i));
    }
    printf("\n");
    return 0;
}
//    输入一个学生的数据
Student* student_input(Student *pStudent)
{
    printf(" name    score1  score2  score3:\n");
    scanf("%19s %1d %1d %1d",
        &pStudent->name, 
        &pStudent->score[0],
       &pStudent->score[1],
       &pStudent->score[2]);
    return pStudent;
}
//    输出一个学生的数据，包括平均成绩
void student_print(const Student *pStudent)
{
    printf("%s\t%d\t%d\t%d\t%lf\n",
        pStudent->name,
        pStudent->score[0],
        pStudent->score[1],
        pStudent->score[2],
        student_average(pStudent));
}
//    计算一个学生的平均成绩
double student_average(const Student *pStudent)
{
    double av = 0.0;
    int i;
    for(i = 0; i < 3; i++)
        av += student_get_score(pStudent, i);
    return av / 3;
}
//    计算一个成绩的平均值
double score_average(const Student *pStudent, int index)
{
    double av = 0.0;
    int i;
    for(i = 0; i < 10; i++)
    {
        av += student_get_score(&pStudent[i], index);
    }
    return av / 10;
}
//    获得学生的一个成绩
int student_get_score(const Student *pStudent, int index)
{
    return pStudent->score[index];
}
//    获得一个成绩的最小值 
int get_score_min(const Student *pStudent, int index)
{
    int min = 5, i;
    for(i = 0; i < 10; i++)
    {
        int score = student_get_score(&pStudent[i], index);
        if(min > score)
            min = score;
    }
    return min;
}
//    获得一个成绩的最大值 
int get_score_max(const Student *pStudent, int index)
{
    int max = 0, i;
    for(i = 0; i < 10; i++)
    {
        int score = student_get_score(&pStudent[i], index);
        if(max < score)
            max = score;
    }
    return max;
}