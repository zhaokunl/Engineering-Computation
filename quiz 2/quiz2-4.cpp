#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"


class Ball{
protected:
    double m, x, y, vx, vy;
public:
    void setMass(double mm);
    void SetPosition(double xx,double yy);
    void SetVelocity(double xx,double yy);
    void Move(double dt);
    void Bounce(void);
    void Draw(void);
};

void Ball::setMass(double mm)
{
    m=mm;
}

void Ball::SetPosition(double xx, double yy)
{
    x=xx;
    y=yy;
}

void Ball::SetVelocity(double xx, double yy)
{
    vx=xx;
    vy=yy;
}

void Ball::Move(double dt)
{
    double fx,fy,ax,ay;
    
    x+=vx*dt;
    y+=vy*dt;
    
    fx=0.0;
    fy=-m*9.8;  // Gravity
    
    ax=fx/m;
    ay=fy/m;
    
    vx+=dt*ax;
    vy+=dt*ay;
}

void Ball::Bounce()
{
    if(y<1.0 && vy<0.0)
    {
        vy=-vy;
    }
    
    if((x<-39.0 && vx<0.0) || (x>39.0 && vx>0.0))
    {
        vx=-vx;
    }
}

void Ball::Draw()
{
    const double YS_PI=3.1415927;
    glBegin(GL_POLYGON);
    
    int i;
    for(i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32.0;
        x+=(cos(angle))*0.1;
        y+=(sin(angle))*0.1;
        glVertex2d(400+(x*10.0),(600-10.0*y));
    }
    
    glEnd();
}








void DrawCircle(int cx,int cy,int rad,int fill)
{
    const double YS_PI=3.1415927;

    if(0!=fill)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

    int i;
    for(i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32.0;
        double x=(double)cx+cos(angle)*(double)rad;
        double y=(double)cy+sin(angle)*(double)rad;
        glVertex2d(x,y);
    }

    glEnd();
}

void Move(double &x,double &y,double &vx,double &vy,double m,double dt)
{
    double fx,fy,ax,ay;

    x+=vx*dt;
    y+=vy*dt;

    fx=0.0;
    fy=-m*9.8;  // Gravity

    ax=fx/m;
    ay=fy/m;

    vx+=dt*ax;
    vy+=dt*ay;
}

void Bounce(double &x,double &y,double &vx,double &vy)
{
    if(y<1.0 && vy<0.0)
    {
        vy=-vy;
    }

    if((x<-39.0 && vx<0.0) || (x>39.0 && vx>0.0))
    {
        vx=-vx;
    }
}

int main(void)
{
    Ball bal;

    double m,x,y,vx,vy,dt;

    m=1.0;

    x=0.0;
    y=10.0;

    vx=10.0;
    vy=0.0;

    dt=0.02;
    
    bal.setMass(m);
    bal.SetPosition(x, y);
    bal.SetVelocity(vx, vy);
    FsOpenWindow(16,16,800,600,1);

    FsPollDevice();
    while(FSKEY_NULL==FsInkey())
    {
        FsPollDevice();

        //Move(x,y,vx,vy,m,dt);
        bal.Move(dt);
        bal.Bounce();
       // Bounce(x,y,vx,vy);

        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glColor3ub(0,0,0);
        
        
        bal.Draw();
        //DrawCircle(400+(x*10.0),600-y*10.0,10,1);
        FsSwapBuffers();

        FsSleep(20);
    }
}

