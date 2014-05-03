#include <stdio.h>
#include <math.h>

void SwatInt(double &a, double &b)
{
    int c;
    c=a;
    a=b;
    b=c;
}

int main(void)
{
    double x,y,x0,x1,step,sum;
    step=0.001;
    int state=0;
    int terminate=0;
    
  //  printf("Enter xmin and xmax>");
   // scanf("%lf%lf",&x0,&x1);
  //  if(x0<0||x1<0)
  //  {
  //      printf("Enter positive numbers.\n");
   // }
    while(0==terminate){
    if(state==0){
        
        printf("Enter xmin and xmax>");
        scanf("%lf%lf",&x0,&x1);
    if(x0>=0 && x1>=0)
    {
    if(x0>x1)
    {
        SwatInt(x0,x1);
    }
    sum=0.0;
    for(x=x0; x<x1; x+=step)
    {
        y=0.1*x*sin(x)*log(x);
        sum+=y*step;
    }
        printf("%lf\n",sum);
        terminate=1;
    }
    else
    {
        printf("Enter positive numbers.\n");
        state=0;
    }
    }
    }
  //  printf("%lf\n",sum);
    return 0;
}

//0.1*x*sin(x)*log(x)