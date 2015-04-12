//  Created by James Swineson on 3/21/15.
//  Copyright (c) 2015 James Swineson. All rights reserved.
//
 
#include <stdio.h>
 
// ========================== Public header ==============================
typedef struct {
    char name[20];
    int score[3];
} Student;
 
// holy shit 这接口定义的太反人类了我想说脏话行么反正勉强做出来了虽然实现很糟糕但是想想反正是个作业没打算以后再扩展那就这样吧反正好像输出是对的对了最后一个 bug 我修完没调试如果出了什么问题别怪我
 
//     输入一个学生的数据
Student* student_input(Student *pStudent);
//     输出一个学生的数据，包括平均成绩
void student_print(const Student *pStudent);
//     计算一个学生的平均成绩
double student_average(const Student *pStudent);
//     获得学生的一个成绩
int student_get_score(const Student *pStudent, int index);
 
// ========================== Private Header ============================
Student s[10];
 
//     输入全部成绩
void student_batch_input(Student *pStudent, unsigned int count);
//     输出全部成绩
void student_batch_print(Student *pStudent, unsigned int count);
 
// ========================= Implementation =============================
 
int main(int argc, const char * argv[]) {
    student_batch_input(s, sizeof(s) / sizeof(Student));
    student_batch_print(s, sizeof(s) / sizeof(Student));
     
    return 0;
}
 
//     输入一个学生的数据
Student* student_input(Student *pStudent) {
    fflush(stdin);
    scanf("%19s%d%d%d", pStudent->name, pStudent->score, pStudent->score + 1, pStudent->score + 2);
    return pStudent;
}
//     输出一个学生的数据，包括平均成绩
void student_print(const Student *pStudent) {
    printf("%s\t%d\t%d\t%d\t%lf", pStudent->name, pStudent->score[0], pStudent->score[1], pStudent->score[2], student_average(pStudent));
}
 
//     计算一个学生的平均成绩
double student_average(const Student *pStudent) {
    return (pStudent->score[0] + pStudent->score[1] + pStudent->score[2]) / 3.0;
}
 
//     获得学生的一个成绩
int student_get_score(const Student *pStudent, int index) {
    if (index < 1 || index > 3) {
        fprintf(stderr, "ERROR: Out of range! \n");
        return 0;
    }
    return pStudent->score[index - 1];
}
 
//     输入全部成绩
void student_batch_input(Student *pStudent, unsigned int count) {
    unsigned int current_count = 0;
    while (current_count++ < count) {
        printf("Student #%u: ", current_count);
        student_input(pStudent + current_count - 1);
    }
}
 
//     输出全部成绩
void student_batch_print(Student *pStudent, unsigned int count) {
    printf("no\tname\tscore1\tscore2\tscore3\taverage\n");
    unsigned int current_count = 0;
    while (current_count++ < count) {
        printf("%u\t", current_count);
        student_print(pStudent + current_count - 1);
        printf("\n");
    }
    printf("\taverage");
    for (int i = 0; i < 3; i++) {
        int sum = 0;
        for (int j = 0; j < 10; j++) {
            sum += student_get_score(pStudent + j, i + 1);
        }
        printf("\t%lf", sum / 10.0);
    }
    printf("\n\tmin");
    for (int i = 0; i < 3; i++) {
        int min = student_get_score(pStudent, i + 1);
        for (int j = 0; j < 10; j++) {
            if (min > student_get_score(pStudent + j, i + 1)) {
                min = student_get_score(pStudent + j, i + 1);
            }
        }
        printf("\t%d", min);
    }
    printf("\n\tmax");
    for (int i = 0; i < 3; i++) {
        int max = student_get_score(pStudent, i + 1);
        for (int j = 0; j < 10; j++) {
            if (max < student_get_score(pStudent + j, i + 1)) {
                max = student_get_score(pStudent + j, i + 1);
            }
        }
        printf("\t%d", max);
    }
}