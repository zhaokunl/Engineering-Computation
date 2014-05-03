#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include "makegif.h"
#include "warpImage.h"


/*****************************************************************************************************
Writer: Yang Wang
Andrew ID: yangwan2
Purpose: 
(1)Read a series of png pics to make a gif pic effect
(2)Define the lefttopX, lefttopY, rightbottomX, rightbottomY coordinates of the png series pic
(3)Define the lefttopX,lefttopY, rightbottomX, rightbottomY coordinates of the head change area
(4)Define the initial location of the png pic
(5)Add gif effect with a straight line motion
Version: 3.0
Revise time: 4 pm, 11/30/2013
Upload time: 4 pm, 11/30/2013
******************************************************************************************************/

void makegif::initial(char gifString[],YsRawPngDecoder &image2,int num,int hLTx, int hLTy, int hRBx, int hRBy)
{
	int number=strlen(gifString);

	gifDirString=new char[number+1];
	for(int i=0;i<number;i++)
	{
		gifDirString[i]=gifString[i];
	}
	gifDirString[number]=0;

	if(YSOK==image2.Decode(gifDirString))
	{
		picWidth=image2.wid;
		picHeight=image2.hei;
	}
	else
	{
		printf("Read Error0!\n");
	}
	timeCounter=0;
	pictureNum=num;
	FsGetWindowSize(winWidth,winHeight);
	startX=winWidth/4;
	startY=winHeight*3/4;
	picLTx=startX;
	picLTy=startY-picHeight;
	picRBx=startX+picWidth;
	picRBy=startY;
	headLTx=hLTx;
	headLTy=hLTy;
	headRBx=hRBx;
	headRBy=hRBy;
}

void makegif::setImage1(YsRawPngDecoder &image1,const char image1String[])
{
	if(YSOK==image1.Decode(image1String))
	{
		//image1.Flip();
	}
	else
	{
		printf("Read Error!\n");
	}
}

void makegif::timerFired(void)
{
	timeCounter+=1;
}

void makegif::setImage1HeadLT(int x1,int y1)
{
	image1HeadLTx=x1;
	image1HeadLTy=y1;
}

void makegif::setImage2HeadRB(int x2,int y2)
{
	image1HeadRBx=x2;
	image1HeadRBy=y2;
}

void makegif::copyRGBA(YsRawPngDecoder &image1,YsRawPngDecoder &image2)
{
	dat=new unsigned char[4*pictureNum*picHeight*picWidth];
	unsigned char *dat2;
	dat2=new unsigned char[4*image1.wid*image1.hei];

	int position1[4];
	int position2[4];
	position1[0]=image1HeadLTx;
    position1[1]=image1HeadLTy;
    position1[2]=image1HeadRBx;
    position1[3]=image1HeadRBy;

	position2[0]=headLTx;
    position2[1]=headLTy;
    position2[2]=headRBx;
    position2[3]=headRBy;

	for(int y=0; y<image1.hei; ++y)
	  {
		for(int x=0; x<image1.wid; ++x)
		{
			unsigned char *pix1=image1.rgba+(image1.wid*y+x)*4;
			dat2[(image1.wid*y+x)*4]=pix1[0];
			dat2[(image1.wid*y+x)*4+1]=pix1[1];
			dat2[(image1.wid*y+x)*4+2]=pix1[2];
			dat2[(image1.wid*y+x)*4+3]=pix1[3];
			pix1=NULL;
			delete pix1;
		}
	  }

	for(int i=0;i<pictureNum;i++)
	{
	choose(image2);
	warpImage(image1,image2,position1,position2,0.0);
	image2.Flip();
	for(int y=0; y<picHeight; ++y)
	{
		for(int x=0; x<picWidth; ++x)
		{
			unsigned char *pix=image2.rgba+(picWidth*y+x)*4;
			dat[4*picWidth*picHeight*timeCounter+(picWidth*y+x)*4]=pix[0];
			dat[4*picWidth*picHeight*timeCounter+(picWidth*y+x)*4+1]=pix[1];
			dat[4*picWidth*picHeight*timeCounter+(picWidth*y+x)*4+2]=pix[2];
			dat[4*picWidth*picHeight*timeCounter+(picWidth*y+x)*4+3]=pix[3];
		}
	}

	for(int y=0; y<image1.hei; ++y)
	  {
		for(int x=0; x<image1.wid; ++x)
		{
			unsigned char *pix3=dat2+(image1.wid*y+x)*4;
			image1.rgba[(image1.wid*y+x)*4]=pix3[0];
			image1.rgba[(image1.wid*y+x)*4+1]=pix3[1];
			image1.rgba[(image1.wid*y+x)*4+2]=pix3[2];
			image1.rgba[(image1.wid*y+x)*4+3]=pix3[3];
			pix3=NULL;
			delete pix3;
		}
	  }

	image2.Flip();
	timerFired();
	}
	delete [] dat2;
}

void makegif::straightMotion(int v)
{
	int velocity=v;
	startX-=velocity;
	startY-=velocity;
	if(startX<=0)
	{
		startX=winWidth/2;
	    startY=winHeight;
	}
	
}

void makegif::choose(YsRawPngDecoder &image2)
{
	int number=timeCounter%pictureNum+1;
	if(number<10)
	{
	    char x[2];
	    itoa(number,x,10);
	    gifDirString[6]=x[0];
	    gifDirString[5]='0';
	}
	else if(number>=10)
	{
		char x[3];
		itoa(number,x,10);
	    gifDirString[6]=x[1];
	    gifDirString[5]=x[0];
	}
	if(YSOK==image2.Decode(gifDirString))
	{
	}
	else
	{
		printf("Read Error1!\n");
	}
}

void makegif::draw(void)
{
	timerFired();
	straightMotion(0);
	int number=timeCounter%pictureNum;
	unsigned char *dat1;
	dat1=new unsigned char[4*picWidth*picHeight];
	for(int y=0; y<picHeight; ++y)
	{
		for(int x=0; x<picWidth; ++x)
		{
			unsigned char *pix=dat+(picWidth*y+x)*4+4*picWidth*picHeight*number;
			dat1[(picWidth*y+x)*4]=pix[0];
			dat1[(picWidth*y+x)*4+1]=pix[1];
			dat1[(picWidth*y+x)*4+2]=pix[2];
			dat1[(picWidth*y+x)*4+3]=pix[3];
		}
	}
	
	glRasterPos2d(double(startX),double(startY));

	glDrawPixels(picWidth,picHeight,GL_RGBA,GL_UNSIGNED_BYTE,dat1);
	delete [] dat1;
}