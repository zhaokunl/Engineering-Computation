#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"

void GetLocalTimeHourMinSec(int &hour,int &min,int &sec)
{
    struct tm *localTime;
    time_t t=time(NULL);
    localTime=localtime(&t);
    hour=localTime->tm_hour;
    min=localTime->tm_min;
    sec=localTime->tm_sec;
}

void DrawClock(int cx,int cy,int rad,int fill,int r,int r2, int hours, int minutes,int seconds, int r3, int r4, int r5)
{
    const double YS_PI=3.1415927;
    
    glColor3f(0.0, 0.0, 0.0);
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
    
    int l;
    for(l=0;l<1;l++){
        double angle=seconds*YS_PI/30+l-YS_PI/2;
        double x1=(double)cx+cos(angle)*(double)r5;
        double y1=(double)cy+sin(angle)*(double)r5;
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(cx, cy);
        glVertex2d(x1, y1);
    }
    glEnd();
}

int main()
{
    FsOpenWindow(16,16,800,600,1);

    int terminate=0;
    int hour,min,sec;
        
    while(0==terminate)
    {
    FsPollDevice();
    int key=FsInkey();

    if(FSKEY_ESC==key)
    {
        terminate=1;
    }
    
 //   printf("%d %d %d\n",hour,min,sec);
    
        
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
    GetLocalTimeHourMinSec(hour,min,sec);
    DrawClock(400, 300, 250, 0, 200, 230, hour, min, sec, 180, 220,230);
        
    
    FsSwapBuffers();
    FsSleep(25);
    }
    return 0;
}
