#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include "makegif.h"
#include "warpImage.h"
#include "projectRuixi1.h"

/*****************************************************************************************************
Writer: Yang Wang
Andrew ID: yangwan2
Purpose: draw a gif pic
Version: 2.0
Revise time: 11 pm, 11/23/2013
Upload time: 11 pm, 11/23/2013
******************************************************************************************************/

void makegif::initial(YsRawPngDecoder &image2, TextString &str ,int num,int hLTx, int hLTy, int hRBx, int hRBy)
{
	str.Set("GIF1/1.png");
	if(YSOK==image2.Decode(str.GetPointer()))
	{
		picWidth=image2.wid;
		picHeight=image2.hei;
	}
	else
	{
		printf("Read Error!\n");
	}
	timeCounter=0;
	pictureNum=num;
	FsGetWindowSize(winWidth,winHeight);
	startX=winWidth/2;
	startY=winHeight/2;
	picLTx=startX;
	picLTy=startY-picHeight;
	picRBx=startX+picWidth;
	picRBy=startY;
	headLTx=hLTx;
	headLTy=hLTy;
	headRBx=hRBx;
	headRBy=hRBy;
}

void makegif::setImage1(YsRawPngDecoder &image1,char image1String[])
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

void makegif::copyRGBA(YsRawPngDecoder &image1,YsRawPngDecoder &image2,TextString &str)
{
	dat=new unsigned char[48*picHeight*picWidth];
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

	for(int i=0;i<12;i++)
	{
	choose(image2,str);
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
	startX+=v;
	startY+=v;

	if(startX>=winWidth || startY>=winHeight)
	{
		startX=0;
		startY=0;
	}
}

void makegif::choose(YsRawPngDecoder &image2, TextString &str)
{
	if(timeCounter%pictureNum==0)
	{
        str.Set("GIF1/1.png");
	}
	else if(timeCounter%pictureNum==1)
	{
		str.Set("GIF1/2.png");
	}
	else if(timeCounter%pictureNum==2)
	{
		str.Set("GIF1/3.png");
	}
	else if(timeCounter%pictureNum==3)
	{
		str.Set("GIF1/4.png");
	}
	else if(timeCounter%pictureNum==4)
	{
		str.Set("GIF1/5.png");
	}
	else if(timeCounter%pictureNum==5)
	{
		str.Set("GIF1/6.png");
	}
	else if(timeCounter%pictureNum==6)
	{
		str.Set("GIF1/7.png");
	}
	else if(timeCounter%pictureNum==7)
	{
		str.Set("GIF1/8.png");
	}
	else if(timeCounter%pictureNum==8)
	{
		str.Set("GIF1/9.png");
	}
	else if(timeCounter%pictureNum==9)
	{
		str.Set("GIF1/10.png");
	}
	else if(timeCounter%pictureNum==10)
	{
		str.Set("GIF1/11.png");
	}
	else if(timeCounter%pictureNum==11)
	{
		str.Set("GIF1/12.png");
	}

	if(YSOK==image2.Decode(str.GetPointer()))
	{
	}
	else
	{
		printf("Read Error!\n");
	}
}

void makegif::draw(void)
{
	timerFired();
	straightMotion(3);
	int number=timeCounter%12;
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