#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"

void display(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glFlush();
}

void DrawLauncherLine(int a, int ax, int ay)
{
    const double YS_PI=3.1415927;
    glColor3ub(255, 0, 0);
    glBegin(GL_LINES);
    
    double x,y,length;
    length=30;
    double angle=a*YS_PI/180;
    x=ax+cos(angle)*length;
    y=ay-sin(angle)*length;
    glVertex2i(ax, ay);
    glVertex2i(x, y);
    
    glEnd();
}

void RotateLauncherline(int &angle, int Maxangle)
{
    angle+=1;
    if(angle>Maxangle)
    {
        angle=90;
    }
}

void RotateLauncherline2(int &angle, int Minangle)
{
    angle-=1;
    if(angle<Minangle)
    {
        angle=90;
    }
}

void DrawLauncher(int x)
{
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    
    glVertex2i(x, 720);
    glVertex2i(x+20, 720);
    glVertex2i(x+20, 780);
    glVertex2i(x, 780);
    
    glEnd();
}

void DrawGrass(void)
{
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    
    
    glColor3ub(0, 200, 0);
    glVertex2i(0, 750);
    glColor3ub(0, 200, 0);
    glVertex2i(1200, 750);
    glColor3ub(0, 100, 200);
    glVertex2i(1200, 800);
    glColor3ub(0, 100, 200);
    glVertex2i(0, 800);
    
    glEnd();
}


void DrawStars(int r, int x, int y)
{   //R=5
    const double PI = 3.1415927;
   
    double L1=r*cos(36*PI/180);
    double L2=r*sin(36*PI/180);
    double L3=r*cos(72*PI/180);
    double L4=r*sin(72*PI/180);
    double L5=L2*tan(72*PI/180);
    double L6=L2/cos(72*PI/180);
    double L7=L6*sin(54*PI/180);
    double L8=L6*cos(54*PI/180)+r;
   
    glBegin(GL_POLYGON);
    
    glColor3f(1.0f,1.0f,0.0f);
    
    glVertex2f(x,y);
    glVertex2f(x,y+L5+L1);    //1
    glVertex2f(x+L2,y+L1);    //2
    glVertex2f(x+L2+L6,y+L1);    //3
    glVertex2f(x+L4,y-L3);    //4
    glVertex2f(x+L7,y-L8);    //5
    glVertex2f(x,y-r);    //6
    glVertex2f(x-L7,y-L8);    //7
    glVertex2f(x-L4,y-L3);   //8
    glVertex2f(x-L2-L6,y+L1);   //9
    glVertex2f(x-L2,y+L1);   //10
    glVertex2f(x,y+L5+L1);
    
    glEnd();
    glFlush();
}


void DrawMoon(int cx,int cy )
{
    const double YS_PI=3.1415927;
    glColor3ub(255, 255, 0);
    glBegin(GL_POLYGON);
    int i;
    for(i=0;i<200;i++)
    {
        double angle=(double)i*YS_PI/100.0;
        double x=(double)cx+cos(angle)*50;
        double y=(double)cy+sin(angle)*50;
        glVertex2d(x, y);
    }
    glEnd();
}

void BlackMoon(int cx, int cy)
{
    const double YS_PI=3.1415927;
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    int i;
    for(i=0;i<200;i++)
    {
        double angle=(double)i*YS_PI/100.0;
        double x=(double)cx+cos(angle)*50;
        double y=(double)cy+sin(angle)*50;
        glVertex2d(x, y);
    }
    glEnd();
}

void MoveBlackMoon(double &cx, int &x)
{
    cx+=0.1;
    if(cx>x)
    {
        cx-=100;
    }
}

void DrawFirework(int c1, int c2, int c3, int cx, int cy)
{
    const double YS_PI=3.1415927;
    glColor3ub(c1, c2, c3);
    glBegin(GL_POLYGON);
    int i;
    for(i=0;i<200;i++)
    {
        double angle=(double)i*YS_PI/100.0;
        double x=(double)cx+cos(angle)*5;
        double y=(double)cy+sin(angle)*5;
        glVertex2d(x, y);
    }
    glEnd();
}


void MoveFirework(int &x, int &y, double vx, double vy, double m,double dt)
{
    double fx,fy,ax,ay;
    
    x=x+vx*dt;
    y=y+vy*dt;
    
    fx=0.0;
    fy=-m*98;
    
    ax=fx/m;
    ay=fy/m;
    
    vx=vx+dt*ax;
    vy=vy+dt*ay;
    
}

void DrawFire(int c1, int c2, int c3, int cx, int cy)
{
    const double YS_PI=3.1415927;
    glColor3ub(c1, c2, c3);
    glBegin(GL_POLYGON);
    int i;
    srand((unsigned)time(NULL));
    double r =rand()%5;
    
    for(i=0;i<200;i++)
    {
        double angle=(double)i*YS_PI/100.0;
        double x=(double)cx+cos(angle)*r;
        double y=(double)cy+sin(angle)*r;
        glVertex2d(x, y);
    }
    glEnd();
}

void MoveFire(int &x, int &y, double vx, double vy, double m,double dt)
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





int main (void)
{
    const double YS_PI=3.1415927;
    FsOpenWindow(16, 16, 1200, 800, 1);
    display();
    
    
    int StarsState[30];
    int r[30], x[30], y[30];
    int x0=565;
    int x1=590;
    int x2=615;
    int x3=x0+10;
    int x4=x1+10;
    int x5=x2+10;
    int x6=x3;
    int x7=x4;
    int x8=x5;
    
    int x9=x6;
    
    int angle=90;
    int angle1=90;
    int angle2=90;
    
    double rotateangle1=90;
    double rotateangle2=90;
   
    int Yfirework0=720;
    int Yfirework1=720;
    int Yfirework2=720;
    int A=720;
    
    srand((unsigned)time(NULL));
    
    for(int i=0;i<30;++i)
    {
        r[i]=rand()%5;
        x[i]=rand()%1200;
        y[i]=rand()%200;
        StarsState[i]=1;
    }
    
    int cx=50+rand()%1100;
    double a=cx-100;
    
    int m=1;
    double dt=0.025;
    double vx1;
    double vy1;
    double vx2;
    double vy2;
    
    int c0=rand()%255;
    int c1=rand()%255;
    int c2=rand()%255;
    int c3=rand()%255;
    int c4=rand()%255;
    int c5=rand()%255;
    int c6=rand()%255;
    int c7=rand()%255;
    int c8=rand()%255;
    
    int randomv0=50+rand()%80;
    int randomv1=50+rand()%80;
    int randomv2=50+rand()%80;
   
    int terminate=0;
    int FireworkState=0;

    int explosion0=0;
    int explosion1=0;
    int explosion2=0;
    int px[1000],py[1000],vx[1000],vy[1000],ax[1000],bx[1000], ccx[1000], dx[1000];

    
    while(0==terminate)
   {
        FsPollDevice();
       
        rotateangle1++;
        if(rotateangle1>=180) rotateangle1=90;
       
        rotateangle2--;
        if(rotateangle1<=0) rotateangle1=90;

       
        int key=FsInkey();
        if(FSKEY_ESC==key)
        {
            terminate=1;
        }
        else if(FSKEY_SPACE==key)
        {
            if(0==FireworkState)
            {
                FireworkState=1;
                
                vx1=cos(rotateangle1*YS_PI/180)*randomv0;
                vy1=-sin(rotateangle1*YS_PI/180)*randomv0;
               
                vx2=-vx1;
                vy2=-sin(rotateangle2*YS_PI/180)*randomv1;
            }
        }

    

    //draw screen
    
       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
       
       
       DrawMoon(cx,100);
       BlackMoon(a,100);
       MoveBlackMoon(a,cx);
       
       if(0!=StarsState)
       {
           for(int i=0; i<30; ++i)
           {
               if(0!=StarsState[i])
               {
                   DrawStars(r[i], x[i], y[i]);
               }
           }
       }
     
      
       DrawGrass();
       DrawLauncher(x0);
       DrawLauncher(x1);
       DrawLauncher(x2);
       DrawLauncherLine(angle,x3,720);
       DrawLauncherLine(angle1,x4,720);
       DrawLauncherLine(angle2,x5,720);
       RotateLauncherline(angle, 180);
       RotateLauncherline2(angle2, 0);
      
    if(0!=FireworkState)
{
         DrawFirework(c0, c1, c2, x6, Yfirework0);
         DrawFirework(c3, c4, c5, x7, Yfirework1);
         DrawFirework(c6, c7, c8, x8, Yfirework2);
         MoveFirework(x6, Yfirework0, vx1, vy1, m, dt);
         MoveFirework(x8, Yfirework2, vx2, vy2, m, dt);
         MoveFirework(x7, Yfirework1, 0, -randomv2, m, dt);
         printf("aaaaaa%d\n",Yfirework0);
         if(Yfirework0<=400)
       {
               
           if(0!=FireworkState)
           {
               
                   if(Yfirework0<=400)
                   {
                       printf("Hit!\n");

                   //    FireworkState=0;
                       
                       explosion0=1;
                       for(int j=0; j<1000; ++j)
                       {
                           px[j]=x6;
                           py[j]=Yfirework0;
                           ax[j]=x7;
                           bx[j]=Yfirework1;
                           ccx[j]=x8;
                           dx[j]=Yfirework2;
                           vx[j]=rand()%600-300;
                           vy[j]=rand()%600-300;
                       }
                       
                   //    break;
                   }
               
           }
           
           if(0!=explosion0)
           {
               for(int i=0; i<1000; ++i)
               {
                   px[i]+=vx[i];
                   py[i]+=vy[i];
                   ax[i]+=vx[i];
                   bx[i]+=vy[i];
                   ccx[i]+=vx[i];
                   dx[i]+=vy[i];
               }
           }
           
           
           
           
           if(0!=explosion0)
           {
         //      glColor3f(c0,c1,c2);
         //      glPointSize(2.0f);
         //      glBegin(GL_POINTS);
               for(int i=0; i<1000; ++i)
               {
                //   glVertex2i(px[i],py[i]);
                   DrawFire(c0, c1, c2, px[i], py[i]);
                   DrawFire(c3, c4, c5, ax[i], bx[i]);
                   DrawFire(c6, c7, c8, ccx[i], dx[i]);
                   
               }
               glEnd();
           }
           if(0!=explosion1)
           {
              glColor3f(c3,c4,c5);
              glPointSize(2.0f);
              glBegin(GL_POINTS);
               for(int i=0; i<1000; ++i)
               {
                glVertex2i(px[i],py[i]);
                //   DrawFire(c3, c4, c5, px[i], py[i]);
               }
               glEnd();
           }

    }

   }
    
    FsSwapBuffers();
    FsSleep(25);
   }
    return 0;
}
