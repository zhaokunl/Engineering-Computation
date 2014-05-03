/*A Squash Game*/
/*
 * Name: Zhaokun LI
 * Andrew ID: zhaokunl
 */

#include <stdio.h>
#include "fssimplewindow.h"

/* Class Definition */
class Racket {
public:
    int rx, ry, rdx, rdy;
    void Initialize();
    void Draw();
};

void Racket::Draw()
{
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
    
    glVertex2i(rx-rdx,ry-rdy);
    glVertex2i(rx+rdx,ry-rdy);
    glVertex2i(rx+rdx,ry+rdy);
    glVertex2i(rx-rdx,ry+rdy);
    
    glEnd();
}

void Racket::Initialize()
{
    rx=300;
	ry=550;
	rdx=40;
	rdy=10;
}

class Ball {
public:
    int bx, by, vx, vy;
    void Initialize();
    void Draw();
    void Move();
};

void Ball::Initialize()
{
    bx=400;
	by=300;
	vx=5;
	vy=-5;
}

void Ball::Draw()
{
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
    
    glVertex2i(bx-3,by-3);
    glVertex2i(bx+3,by-3);
    glVertex2i(bx+3,by+3);
    glVertex2i(bx-3,by+3);
    
    glEnd();
}

void Ball::Move()
{
    bx+=vx;
    by+=vy;
}

class Block {
public:
    int state;
    int x0, y0, x1, y1;
    void Draw();
    int CheckCollision(int bx, int by);
};

void Block::Draw()
{
    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
    glVertex2i(x0, y0);
    glVertex2i(x1, y0);
    glVertex2i(x1, y1);
    glVertex2i(x0, y1);
    
    glEnd();
}

int Block::CheckCollision(int bx, int by) {
        if(bx>x0 && bx<x1 && by>y0 && by<y1) {
            if(state==1)
                state=0;
            return 1;
        }
    else {
        return 0;
    }
}

/* Main Function */
int main(void) {
	FsOpenWindow(64,16,800,600,1);

	Racket rac;
    Ball bal[3];
    Block blo[10];
    
    /* Initialize */
    for (int i=0; i<10; i++) {
        blo[i].x0=i*80;
        blo[i].y0=40;
        blo[i].x1=(i+1)*80;
        blo[i].y1=60;
        blo[i].state=1;
    }
    
    for (int i=0; i<3; i++) {
        bal[i].Initialize();
    }
    
	rac.Initialize();

	for(;;) {
		FsPollDevice();

		if(FSKEY_ESC==FsInkey()) {
			break;
		}
        
        /* Draw Screen */
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        /* Draw Balls and Racket */
        for (int i=0; i<3; i++) {
            bal[i].Draw();
            rac.Draw();
        }
        
        /* Move Balls */
        for (int i=0; i<3; i++) {
            bal[i].Move();
        }
        
        /* Draw Blocks */
        int finish=0;
        for (int i=0; i<10; i++) {
            
            if (blo[i].state==1) {
                blo[i].Draw();
            }
            
            if (blo[i].state==0) {
                finish++;
            }
        }
        
        /* Shoot All Blocks Down */
        if (finish==10) {
            printf("You win!\n");
            break;
        }
        
        /* Check Collision */
        for (int i=0; i<10; i++) {
            for (int j=0; j<3; j++) {
            if (blo[i].state==1) {
                    if(blo[i].CheckCollision(bal[j].bx, bal[j].by)==1)
                    {
                        bal[j].vy=-bal[j].vy;
                    }
                }
            }
        }
        
        for (int i=0; i<10; i++) {
            for (int j=0; j<3; j++) {
            blo[i].CheckCollision(bal[j].bx, bal[j].by);
            }
        }
    
        /* Miss All Balls */
        int miss=0;
        for (int j=0; j<3; j++) {
            if((bal[j].bx<0 && bal[j].vx<0) || (800<bal[j].bx && 0<bal[j].vx)) {
                bal[j].vx=-bal[j].vx;
            }
            if((bal[j].by<0 && bal[j].vy<0)) {
                bal[j].vy=-bal[j].vy;
            }
        
            if(600<bal[j].by) {
                miss++;
            }
        }
        
        if (miss==3) {
            printf("Miss!\n");
            break;
        }

        /* Get Mouse Event and Move the Racket */
		int lb,mb,rb;
		FsGetMouseEvent(lb,mb,rb,rac.rx,rac.ry);
        
        /* Ensure that the Racket is within the Screen */
		if(rac.rx<0) {
			rac.rx=0;
		}
		else if(800<rac.rx) {
			rac.rx=800;
		}
		if(rac.ry<500) {
			rac.ry=500;
		}
		else if(600<rac.ry) {
			rac.ry=600;
		}

        /* Bounce the balls when hit the boundary */
        for (int j=0; j<3; j++) {
            if(rac.rx-rac.rdx<=bal[j].bx && bal[j].bx<=rac.rx+rac.rdx &&
               rac.ry-rac.rdy<=bal[j].by && bal[j].by<=rac.ry+rac.rdy &&
               0<bal[j].vy) {
                bal[j].vy=-bal[j].vy;
            }
        }
        
		FsSwapBuffers();
		FsSleep(25);
	}
}