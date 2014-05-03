#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "fssimplewindow.h"
#include "yspng.h"

class TextString
{
protected:
    char *str;
public:
    TextString();
    TextString(const char from[]);
    TextString(const TextString &str);
    ~TextString();
    void CleanUp();
    void Set(const char from[]);
    void Add(const char from[]);
    void Add(const char c);
    void BackSpace(void);
    const char *Fgets(FILE *fp);
    void DeleteLastControlCode(void);
    const char *GetPointer(void) const;
    const int Strlen(void) const;
    void Print(void) const;
    const TextString &operator=(const TextString &from);
};


void InvertColor(int wid,int hei,unsigned char dat[])
{
	for(int y=0; y<hei; ++y)
	{
		for(int x=0; x<wid; ++x)
		{
			unsigned char *pix=dat+(wid*y+x)*4;
			unsigned int a=255-pix[0];
            unsigned int b=255-pix[1];
            unsigned int c=255-pix[2];
    
			pix[0]=a;
			pix[1]=b;
			pix[2]=c;
		}
	}
}

int main(void)
{
    printf("Enter File Name\n");
    
    char keyy[256];
    fgets(keyy, 256 , stdin);
    keyy[strlen(keyy)-1]='\0';
    
    YsRawPngDecoder png;
    if(YSOK==png.Decode(keyy))
    {
        printf("Read Width=%d Height=%d\n",png.wid,png.hei);
        png.Flip();
    }
    else
    {
        printf("Read Error!\n");
        return 0;
    }
    
    FsOpenWindow(16,16,png.wid+10,png.hei+10,1);
    
    int key=FSKEY_NULL;
    while(FSKEY_ESC!=key)
    {
        FsPollDevice();
        key=FsInkey();
       
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        int winWid,winHei;
       
        FsGetWindowSize(winWid,winHei);
        glRasterPos2d(0.0,(double)(winHei-11));
        glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        
        if(FSKEY_I==key)
        {
            InvertColor(png.wid,png.hei,png.rgba);
        }
        
        int lb, mb, rb, mx, my;
        if(FSMOUSEEVENT_MOVE==FsGetMouseEvent(lb,mb,rb,mx,my))
		{
            if(0<=mx && mx<=png.wid && 0<=my && my<=png.hei)
            {
                printf("mx=%d; my=%d r=%u g=%u b=%u\n",
                       mx, (png.hei-my),
                       png.rgba[0+(png.wid*(png.hei-my)+mx)*4],
                       png.rgba[1+(png.wid*(png.hei-my)+mx)*4],
                       png.rgba[2+(png.wid*(png.hei-my)+mx)*4]);
            }
		}
        FsSwapBuffers();
        FsSleep(50);
    }
    return 0;
}