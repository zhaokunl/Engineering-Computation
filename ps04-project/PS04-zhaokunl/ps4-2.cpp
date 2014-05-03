#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"

void DrawCannon(void)
{
    glColor3ub(0, 0, 255);
    glBegin(GL_QUADS);
    
    glVertex2i(50, 550);
    glVertex2i(60, 550);
    glVertex2i(60, 540);
    glVertex2i(50, 540);
    
    glEnd();
}

void DrawCannonLine(int a)
{
    const double YS_PI=3.1415927;
    glColor3ub(0, 0, 255);
    glBegin(GL_LINES);
    
    double x,y,length;
    length=30;
    double angle=a*YS_PI/180;
    x=55+cos(angle)*length;
    y=545-sin(angle)*length;
    glVertex2i(55, 545);
    glVertex2i(x, y);

    glEnd();
}

void RotateCannonline(int &angle, int Maxangle)
{
    angle+=1;
    if(angle>Maxangle)
    {
        angle=0;
    }
}

void DrawTarget(int y)
{
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    
    glVertex2i(750, y);
    glVertex2i(800, y);
    glVertex2i(800, y+50);
    glVertex2i(750, y+50);
    
    glEnd();
}

void DrawObstacles(int x1,int y1, int x2, int y2)
{
    glColor3ub(0, 255, 0);
    glBegin(GL_QUADS);

    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    
    glEnd();
}

void DrawObstacles2(int x1,int y1, int x2, int y2)
{
    glColor3ub(0, 255, 0);
    glBegin(GL_LINE_LOOP);
    
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    
    glEnd();
}

void MoveTarget(int &y, int scrnSizeY)
{
    y+=2.5;
    if(y>scrnSizeY)
    {
        y=0;
    }
}

void DrawCannonball(int cx, int cy)
{
    const double YS_PI=3.1415927;
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    int i;
    for(i=0;i<64;i++)
    {
        double angle=(double)i*YS_PI/32.0;
        double x=(double)cx+cos(angle)*5;
        double y=(double)cy+sin(angle)*5;
        glVertex2d(x, y);
    }
    glEnd();
}

/*void DrawPoint(int p, int q)
{
    glColor3ub(255, 0, 0);
    glBegin(GL_POINT);
    glVertex2d(p, q);
    
    glEnd();
}*/

void MoveCannonball(int &x, int &y, double &vx, double &vy, double m,double dt)
{
    double fx,fy,ax,ay;
    
    x=x+vx*dt;
    y=y+vy*dt;
    
    fx=0.0;
    fy=m*98;
    
    ax=fx/m;
    ay=fy/m;
    
    vx=vx+dt*ax;
    vy=vy+dt*ay;
    
}

/*void DrawTrajectory(int x, int y)//not working
{
    const double YS_PI=3.1415927;
    glColor3ub(255, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(mx, my);
    }
    
    glEnd();
}*/

int CheckCollision(int &cx, int &cy, int &x1, int &y1, int &x2, int &y2)
{
    int rx1=cx-x1;
    int rx2=cx-x2;
    int ry1=cy-y1;
    int ry2=cy-y2;
    if(0>=(rx1*rx2) && 0>=(ry1*ry2))
    {
        return 1;
    }
    return 0;
}

int CheckHit(int &cx, int &cy, int &y)
{
    int rx=cx-750;
    int ry=cy-y;
    if(0<=rx && 50>=rx && 0<=ry && 50>=ry)
    {
        return 1;
    }
    return 0;
}


int main (void)
{
    const double YS_PI=3.1415927;
    FsOpenWindow(16, 16, 800, 600, 1);
    
    int ObstaclesState[5];
    int x1[5], y1[5], x2[5], y2[5];
    
    int Point[10000];//trajectory
    int p[10000],q[10000];//trajectory
    
    srand((unsigned)time(NULL));
    
   // for(int i=0;i<10000;i++)
   // {
   //     Point[i]=1;
   // }//draw points
    
    for(int i=0;i<5;++i)
    {
    x1[i]=rand()%720;
    y1[i]=rand()%520;
    x2[i]=x1[i]+80+rand()%70;
    y2[i]=y1[i]+80+rand()%70;
    ObstaclesState[i]=1;
    }
    
    int terminate=0;
    int y=0;
    int x=30;
    int a=55;
    int b=545;
    
    double m=1.0;
    double dt=0.025;
    int CannonballState=0;
  
    int angle=30;
    
    double vx;
    double vy;

    int Hit=0;
    int TargetState=1;
    
  
    while(0==terminate)
 {
     FsPollDevice();
     
     angle++;
     if(angle>=90) angle=0;
     
     int key=FsInkey();
       if(FSKEY_ESC==key)
       {
          terminate=1;
       }
       else if(FSKEY_SPACE==key)
     {
         if(0==CannonballState)
       {
           CannonballState=1;

           vx=cos(angle*YS_PI/180)*400;
           vy=-sin(angle*YS_PI/180)*400;
       }
     }

     //draw screen
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

     if(0!=ObstaclesState)
		{
			for(int i=0; i<5; ++i)
			{
				if(0!=ObstaclesState[i])
                {
                    DrawObstacles(x1[i],y1[i],x2[i],y2[i]);
                if(0!=CannonballState && 0!=CheckCollision(a, b, x1[i], y1[i], x2[i], y2[i]))
                 {
                    printf("Hit An Obstacle!\n");
                    ObstaclesState[i]=0;
                    CannonballState=0;
                    Hit=1;
                    a=55;
                    b=545;
                 }
                }
                if(0!=Hit)
                {
                    DrawObstacles2(x1[i],y1[i],x2[i],y2[i]);
                }
            }
        }
     
    if(0!=TargetState)
                 {
                    if(0!=CannonballState && 0!=CheckHit(a, b, y))
                    {
                        printf("HitTarget!\n");
                        TargetState=0;
                        CannonballState=0;
                        break;
                    }
                 }
        
    DrawCannonLine(x);
    RotateCannonline(x, 90);
    DrawCannon();
    DrawTarget(y);
    MoveTarget(y, 600);

     if(0!=CannonballState)
     {
        DrawCannonball(a, b);
        MoveCannonball(a, b, vx, vy, m, dt);
         
        // for(int i=0;i<10000;i++)
        // {
        //     Point[i]=1;
        // }//draw points
         
       //  if(0!=Point)//not working
       //  {
             for(int i=0; i<10000; ++i)
             {
       //          if(0!=Point[i])
        //         {
                     p[i]=a;
                 //    printf("%d\n",a);
                     q[i]=b;
//                     DrawTrajectory(p[i], q[i]);
         ///        }
           //  }
         }
        if(a>800||b>600)
         {
             CannonballState=0;
             a=55;
             b=545;
         }
     }
    FsSwapBuffers();
    FsSleep(25);
 }
    return 0;
}
