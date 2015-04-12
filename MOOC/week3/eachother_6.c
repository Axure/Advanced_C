//本人是个小白，写的东西或多或少存在问题，望大牛们多多见谅(*^__^*) 
#include<stdio.h>
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
//    计算每门的average
double score_average(const Student *st[], int index);
//    计算每门的min
int score_min(const Student *st[], int index); 
//    计算每门的max
int score_max(const Student *st[], int index);    
int main（）{
Student* st[10];
//输入10个学生的数据
for(int i=0;i<10;i++){
student_input(st[i]);
}
printf("no / name / score1 / score2 / score3 / average \n");
for(int i=0;i<10;i++){
printf("i ");
student_print(st[i]);
printf("\n");
}
printf("average:      %f      %f      %f   ",score_average(st[],1),
score_average(st[],2),score_average(st[],3));
printf("   min:       %d      %d       %d  ",score_min(st[],1),
score_min(st[],2),score_min(st[],3));
printf("   max:       %d      %d       %d  ",score_max(st[],1),
score_max(st[],2),score_max(st[],3));
return 0;
}
Student* student_input(Student *pStudent){
printf("请输入名字：\n");
scanf("%s",&(pStudebt->name));
printf("输入score1的成绩：\n");
scanf("%d", &(pStudent->score[1]));
printf("输入score2的成绩：\n");
scanf("%d",&(pStudent->score[2]));
printf("输入score3的成绩：\n");
scanf("%d",&(pStudent->score[3]));
}
void student_print(const Student *pStudent){
printf("%d   %d   %d ",
student_get_score(pStudent,1),
student_get_score(pStudent,2),student_get_score(pStudent,3));
printf(" %f \n",student_average(pStudent));
}
double student_average(const Student *pStudent){
double r=(pStudent->score[1]+pStudent->score[2]+pStudent->score[3])/3;
return r;
}
int student_get_score(const Student *pStudent, int index){
int s=pStudent->score[index];
return s;
}
double score_average(const Student *st[], int index){
double result=0;
int sum=0;
for(int i=0;i<10;i++){
sum+=st[i]->score[index];
}
return result=(double)sum/3;
}
int score_min(const Student *st[], int index){
int thismin=st[1]->score[index];
 for(int i=1;i<10;i++){
if(thismin>st[i]->score[index]){thismin=st[i]->score[index];}
}
return thismin;
}
int score_max(const Student *st[], int index){
int thismax=st[1]->score[index];
for(int i=1;i<10;i++){
if(thismin<st[i]->score[index]){thismax=st[i]->score[index];}
}
return thismax;
}