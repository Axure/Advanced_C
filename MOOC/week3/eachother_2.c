#include<stdio.h>
#include<string.h>
typedef struct{
    char name[10];
    int  score[3];
}Student;
 
 
int main(){
    Student std[11]={0};
    int num[]={1,2,3,4,5,6,7,8,9,10};
    int i,j=0;
    for(i=0;i<sizeof(num)/sizeof(int);i++){
        scanf("%s %d %d %d",&std[i].name,&std[i].score[0],&std[i].score[1],&std[i].score[2]);
    }
 
    float _stdavg[10];
    for(i=0;i<sizeof(num)/sizeof(int);i++){
        _stdavg[i]=(std[i].score[0]+std[i].score[1]+std[i].score[2])/3.0;
    }
    float _scoavg[3];
    int min[3]={10,10,10},max[3]={0};
    for(i=0;i<sizeof(num)/sizeof(int);i++){
        _scoavg[0]=_scoavg[0]+std[i].score[0];
        _scoavg[1]=_scoavg[1]+std[i].score[1];
        _scoavg[2]=_scoavg[2]+std[i].score[2];
    }
    for(i=0;i<3;i++){
        _scoavg[i]=_scoavg[i]/(sizeof(num)/sizeof(int)) ;
    }
    j=0;
    for(i=0;i<(sizeof(num)/sizeof(int))&&j<3;i++){
        if(std[i].score[j]<min[j])
            min[j]=std[i].score[j];
        if(i==sizeof(num)/sizeof(int)-1){
                i=-1;j++;
        }
    }
    j=0;
    for(i=0;i<(sizeof(num)/sizeof(int))&&j<3;i++){
        if(std[i].score[j]>max[j])
            max[j]=std[i].score[j];
        if(i==sizeof(num)/sizeof(int)-1){
                i=-1;j++;
            }   
    }
     
    printf("no\tname\tscore1\tscore2\tscore3\taverage\t\n");
    for(i=0;i<sizeof(num)/sizeof(int);i++){
        if((std[i].score[0]+std[i].score[1]+std[i].score[2])%3==0)
        printf("%d\t%s\t%d\t%d\t%d\t%d\t\n",num[i],std[i].name,std[i].score[0],std[i].score[1],std[i].score[2],(int)_stdavg[i]);
        else
        printf("%d\t%s\t%d\t%d\t%d\t%f\t\n",num[i],std[i].name,std[i].score[0],std[i].score[1],std[i].score[2],_stdavg[i]);
    }
    printf("\taverage\t%.1f\t%.1f\t%.1f\t\n",_scoavg[0],_scoavg[1],_scoavg[2]);
    printf("\tmin\t%d\t%d\t%d\t\n",min[0],min[1],min[2]);
    printf("\tmax\t%d\t%d\t%d\t\n",max[0],max[1],max[2]);
}