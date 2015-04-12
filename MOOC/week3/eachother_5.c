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
int main()
{
 int i,max1=0,max2=0,max3=0,min1=5,min2=5,min3=5;
 double ave1=0,ave2=0,ave3=0;
 Student a[10];
 for(i=0;i<10;i++)
 {
 student_input(&a[i]);
 }
 for(i=0;i<10;i++)
 {
 if(a[i].score[0]>max1)
 max1=a[i].score[0];
 if(a[i].score[0]<min1)
 min1=a[i].score[0];
 if(a[i].score[1]>max2)
 max2=a[i].score[1];
 if(a[i].score[1]<min2)
 min2=a[i].score[1];
 if(a[i].score[2]>max3)
 max3=a[i].score[2];
 if(a[i].score[2]<min3)
 min3=a[i].score[2];
 }
 for(i=0;i<10;i++)
 {
 ave1+=a[i].score[0];
 ave2+=a[i].score[1];
 ave3+=a[i].score[2];
 }
 ave1/=10;ave2/=10;ave3/=10;
 printf("no\tname\tscore1\tscore2\tscore3\taverage\n");
 for(i=0;i<10;i++)
 {
 printf("%d\t",i+1);
 student_print(&a[i]);
 }
 printf("\taverage\t%.1f\t%.1f\t%.1f\n",ave1,ave2,ave3);
 printf("\tmin\t%d\t%d\t%d\n",min1,min2,min3);
 printf("\tmax\t%d\t%d\t%d\n",max1,max2,max3);
 return 0;
}
Student* student_input(Student *pStudent)
{
 int a;
 scanf("%s",pStudent->name);
 for(a=0;a<3;a++)
 scanf("%d",&pStudent->score[a]);
 return pStudent;
 }
void student_print(const Student *pStudent)
{
 float ave1=student_average(pStudent);
 printf("%s\t%d\t%d\t%d\t%f\n",pStudent->name,pStudent->score[0],pStudent->score[1],pStudent->score[2],ave1);
 return;
 }
double student_average(const Student *pStudent)
{
 double ave;
 ave=(double)(student_get_score(pStudent,0)+(double)student_get_score(pStudent,1)+(double)student_get_score(pStudent,2))/3;
 return ave;
}
int student_get_score(const Student *pStudent, int index)
{
 return pStudent->score[index];
}