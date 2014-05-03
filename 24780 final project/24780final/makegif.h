#ifndef MAKEGIF_H_IS_INCLUDED
#define MAKEGIF_H_IS_INCLUDED

/*****************************************************************************************************
Writer: Yang Wang
Andrew ID: yangwan2
Purpose: draw a gif pic.
Version: 2.0
Revise time: 11 pm, 11/23/2013
Upload time: 11 pm, 11/23/2013
******************************************************************************************************/
#include "projectRuixi1.h"

class makegif
{
public:
	int timeCounter,pictureNum;
	int startX,startY;
	int winWidth,winHeight;
	int picLTx,picLTy,picRBx,picRBy;
	int headLTx,headLTy,headRBx,headRBy;
	int picWidth,picHeight;
	int image1HeadLTx,image1HeadLTy,image1HeadRBx,image1HeadRBy;
	int headWidth,headHeight;
	unsigned char *dat;


	void initial(YsRawPngDecoder &image2, TextString &str,int num,int hLTx, int hLTy, int hRBx, int hRBy);
	void setImage1(YsRawPngDecoder &image1,char image1String[]);
	void setImage1HeadLT(int x1,int y1);
	void setImage2HeadRB(int x2,int y2);
	void copyRGBA(YsRawPngDecoder &image1,YsRawPngDecoder &image2,TextString &str);
	void timerFired(void);
	void straightMotion(int v);
	void choose(YsRawPngDecoder &image2, TextString &str);
	void draw(void);
};

#endif
