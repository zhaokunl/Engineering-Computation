#include <stdio.h>
#include "fssimplewindow.h"

int main(void)
{
	char pattern[]=
	{
		"...1........1..."
		"...11......11..."
		"...1.1....1.1..."
		"...1..1..1..1..."
		"...1..1111..1..."
		"..1..........1.."
		"..1..11..11..1.."
		"..1..........1.."
		".1..111..111..1."
		".1.1.1.11.1.1.1."
		"1..1.1.11.1.1..1"
		"1...111..111...1"
		".1............1."
		".1.....11.....1."
		"..111......111.."
		".....111111....."
	};

	FsOpenWindow(16,16,300,300,0);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    
    while(FSKEY_ESC!=FsInkey())
 	{
		int lb,mb,rb,mx,my;

        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
        
        for(int i=0; i<16; i++)
        {
            for(int j=0; j<16; j++)
            {
                if (pattern[j*16+i]=='1')
                {
                    glBegin(GL_QUADS);
                    glVertex2d(i*16   , j*16   );
                    glVertex2d(i*16+16, j*16   );
                    glVertex2d(i*16+16, j*16+16);
                    glVertex2d(i*16   , j*16+16);
                }
            }
        }
        
        glEnd();
        glFlush();
        
    
		if(FSMOUSEEVENT_MOVE==FsGetMouseEvent(lb,mb,rb,mx,my))
		{
            if(0<=mx && mx<=256 && 0<=my && my<=256)
            {
                int a,b;
                a=mx/16;
                b=my/16;
                printf("a= %d\n",a);
                if(pattern[b*16+a]=='1')
                {
                    printf("%d %d 1\n",mx, my);
                }
                else
                {
                    printf("%d %d .\n",mx, my);
                }
            }
		}
        FsPollDevice();
		FsSleep(10);
	}
	return 0;
}
