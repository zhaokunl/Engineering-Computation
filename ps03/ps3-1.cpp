#include<stdio.h>
//using namespace std;
int main()
{
    int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int month,day,num=0;
    printf("Please enter the month and the date with a space between them:");
    scanf("%d %d",&month,&day);
    for(int i=0;i<(month-1);i++)
        num+=a[i];
    num=num+day;
    printf("It is day#%d of this year.",num);
    return 0;
}