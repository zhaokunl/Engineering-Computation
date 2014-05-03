#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include "fssimplewindow.h"
void PlotSinAX(double a)
{
    glColor3ub(0,0,0);
    glBegin(GL_LINE_STRIP);
    double x;
    for(x=1; x<800.0; x+=0.1)
    {
        const double y=0.1*x*sin(x)*log(x);
        glVertex2d(x*10.0,300.0-y*10.0);
    }

    glEnd();
}

    int main(void) {
        double a;
        FsOpenWindow(16,16,800,600,0);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
     //   for(a=0.1; a<1.0; a+=0.1) {
            PlotSinAX(a);
            glFlush();
            while(FSKEY_NULL==FsInkey())
            {
                FsPollDevice();
                FsSleep(10);
            }
       // }
    return 0;
}
    