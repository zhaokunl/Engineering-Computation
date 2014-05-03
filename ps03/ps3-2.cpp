#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h>
#include "fssimplewindow.h"

void DrawClock(int cx,int cy,int rad,int fill,int r,int r2, int hours, int minutes,int r3, int r4) {
    const double YS_PI=3.1415927;
    
    if(0!=fill) {
        glBegin(GL_POLYGON); }
    
    else{
        glBegin(GL_LINE_LOOP);
    }
    
    int i;
    for(i=0;i<60;i++){
        double angle=(double)i*YS_PI/30.0;
        double x=(double)cx+cos(angle)*(double)rad;
        double y=(double)cy+sin(angle)*(double)rad;
        glVertex2d(x, y);
        }
    glEnd();

    int j;
    for(j=0;j<12;j++){
        double angle=(double)j*YS_PI/6.0;
        double x1=(double)cx+cos(angle)*(double)r;
        double y1=(double)cy+sin(angle)*(double)r;
        double x2=(double)cx+cos(angle)*((double)r+40);
        double y2=(double)cy+sin(angle)*((double)r+40);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    }
    glEnd();
    
    
    int k;
    for(k=0;k<60;k++){
        double angle=(double)k*YS_PI/30.0;
        double x1=(double)cx+cos(angle)*(double)r2;
        double y1=(double)cy+sin(angle)*(double)r2;
        double x2=(double)cx+cos(angle)*((double)r2+10);
        double y2=(double)cy+sin(angle)*((double)r2+10);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    }
    glEnd();
    
    
    int m;
    for(m=0;m<1;m++){
        double angle=hours*YS_PI/6+m-YS_PI/2+minutes*YS_PI/360;
        double x1=(double)cx+cos(angle)*(double)r3;
        double y1=(double)cy+sin(angle)*(double)r3;
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(cx, cy);
        glVertex2d(x1, y1);
    }
    glEnd();
    
    int n;
    for(n=0;n<1;n++){
        double angle=minutes*YS_PI/30+n-YS_PI/2;
        double x1=(double)cx+cos(angle)*(double)r4;
        double y1=(double)cy+sin(angle)*(double)r4;
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(cx, cy);
        glVertex2d(x1, y1);
    }
    glEnd();
}



int main(void)
{    
    int hour,minute;
    printf("Please Enter the Hours and the Minutes with a space between them:\n");
    scanf("%d %d",&hour,&minute);
    
    FsOpenWindow(16,16,800,600,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    DrawClock(400, 300, 250, 0, 200, 230, hour, minute, 180, 220);
    glFlush();
    
    FsPollDevice();
    while(FSKEY_NULL==FsInkey())
{
    FsPollDevice();
    FsSleep(10);
}
   return 0;
}