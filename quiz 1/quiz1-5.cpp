#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"


void PhysicalCoordToScreenCoord(int &sx,int &sy,double px,double py)
{
	sx=400+(int)(px*10.0);
	sy=600-(int)(py*10.0);
}

void DrawMass(double y1)
{
glBegin(GL_QUADS);

glVertex2i(360,y1);
glVertex2i(440,y1);
glVertex2i(440,y1+80);
glVertex2i(360,y1+80);

glEnd();
}

void DrawLine(double &y)
{
    glBegin(GL_LINES);
    
    glVertex2i(400,600);
    glVertex2i(400,y);
    
    glEnd();

}

void MoveMass(double &y,double &v)
{
    double dt=0.01;
    double K=15.0;
    double L0=400.0;
    double B=1;
    double m=10.0;
    double G=-98;
    
    
    
  //  fx=0.0;
  //  fy=m*98;
    
 //   ax=fx/m;
 //   ay=fy/m;
    
 //   vx=vx+dt*ax;
 //   vy=vy+dt*ay;
    double F;

    F=K*(y-120)+m*G-B*v;
    printf("%lf\n",F);
 //   v(t+dt)=v(t)+(F/m)*dt
    v-=(F/m)*dt;
    y=y+v*dt;
    //y(t+dt)=y(t)+v*dt
}

int main()
{
    FsOpenWindow(16,16,800,600,1);
    
    double y=120;
    double v=0;
    
    int terminate=0;
    while(0==terminate)
    {
        FsPollDevice();
        
        int key=FsInkey();
        if(FSKEY_ESC==key)
        {
            terminate=1;
        }

        
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    
    DrawMass(y);
    MoveMass(y, v);
    DrawLine(y);
    
    FsSwapBuffers();
    FsSleep(25);
    }
    return 0;
}

