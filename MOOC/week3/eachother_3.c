#include<stdio.h>
 
typedef struct {
    char name[20];
    int score[3];
} Student;
  
//    输入一个学生的数据 
Student *student_input(Student *pStudent);
//    输出一个学生的数据，包括平均成绩
void student_print(const Student *pStudent);
//    计算一个学生的平均成绩
double student_average(const Student *pStudent);    
//    获得学生的一个成绩
int student_get_score(const Student *pStudent, int index);
 
int main(int argc, char const *argv[])
{
    int sum = 0,no = 0,i = 0,min,max;
    Student student[10];
    while(no<10){
        student_input(&student[no]);
        no++;
        printf("\n");
    }
    no = 0;
    printf("no\tname\tscore1\tscore2\tscore3\taverage\n");
    for(no=0;no<10;no++)
    {
        printf("%d\t",++no);
        no--;          //n减减；
        student_print(&student[no]);
        printf("%.5f\n",student_average(&student[no]));
    }
    printf("\taverage\t");
    for(i=0;i<3;i++){
        for(no=0;no<10;no++){
            sum+=student_get_score(&student[no],i);
        }
        printf("%.1f\t",sum/(no*1.0));
        sum = 0;
    }
    printf("\n\tmin\t");
    for(i=0;i<3;i++){
        for(min=5,no=0;no<10;no++){
            if(min>student_get_score(&student[no],i))
                min = student_get_score(&student[no],i);
        } 
        printf("%d\t",min);
    }
    printf("\n\tmax\t");
    for(i=0;i<3;i++){
        for(max=0,no=0;no<10;no++){
            if(max<student_get_score(&student[no],i))
                max = student_get_score(&student[no],i);
        } 
        printf("%d\t",max);
    }
     
    return 0;
}
 
 
Student* student_input(Student *pStudent)
{
    scanf("%s %d %d %d",&pStudent->name,&pStudent->score[0],&pStudent->score[1],&pStudent->score[2]);
}
void student_print(const Student *pStudent)
{
    printf("%s\t%i\t%i\t%i\t",pStudent->name,pStudent->score[0],pStudent->score[1],pStudent->score[2]);
}
double student_average(const Student *pStudent)
{
    double ave = (pStudent->score[0]+pStudent->score[1]+pStudent->score[2])/3.0;
    return ave;
}
int student_get_score(const Student *pStudent, int index)
{
    int number = pStudent->score[index];
    return number;
}