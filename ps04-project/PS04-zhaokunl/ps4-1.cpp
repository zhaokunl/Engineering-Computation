#include <stdio.h>
#include "fssimplewindow.h"
void VisualizeArrayContents(int n,int x[],int movedIndex1,int movedIndex2)
{
    int i;
    for (i=0;i<n;i++)
    {
    glColor3ub(0, 0, 255);
    glBegin(GL_QUADS);
    glVertex2i(0, i*20);
    glVertex2i(0, (i+1)*20);
    glVertex2i((x[i])*20, (i+1)*20);
    glVertex2i((x[i])*20, i*20);
    glEnd();
    }
    
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(0, (movedIndex1)*20);
    glVertex2i(0, (movedIndex1+1)*20);
    glVertex2i((x[movedIndex1])*20, (movedIndex1+1)*20);
    glVertex2i((x[movedIndex1])*20, (movedIndex1)*20);
    glEnd();
        
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(0, (movedIndex2)*20);
    glVertex2i(0, (movedIndex2+1)*20);
    glVertex2i((x[movedIndex2])*20, (movedIndex2+1)*20);
    glVertex2i((x[movedIndex2])*20, (movedIndex2)*20);
    glEnd();
    
}

void SwapInt(int &a,int &b)
{
    int c;
    c=a;
    a=b;
    b=c;
//    (You fill this function. Also correct errors.)
}

void Show(int n,int x[],int toBeMoved1,int toBeMoved2)
{
    FsPollDevice();
    while(FSKEY_NULL==FsInkey())
       {
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        VisualizeArrayContents(n,x,toBeMoved1,toBeMoved2);
        FsSwapBuffers();
        FsPollDevice();
        FsSleep(10);
       }
}

void BubbleSort(int n,int x[])
{
    // (Modify this function so that the lines about to be swapped are drawn red)
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
           Show(n, x, i, j);
            if(x[i]>x[j])
            {
                SwapInt(x[i],x[j]);
            }
        }
    }
    Show(n,x,-1,-1); // You can leave this line as is. You’ll see the first line red in the end.
}

int main(void)
{
    int x[20]={17,10,13,14,15,6,3,2,9,8,18,7,12,11,16,4,1,20,5,19};
    FsOpenWindow(16,16,400,400,1);
    BubbleSort(20, x);
    return 0;
}