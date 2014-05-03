#ifndef MAKEGIF_H_IS_INCLUDED
#define MAKEGIF_H_IS_INCLUDED

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
	char *gifDirString;

	void initial(char gifString[],YsRawPngDecoder &image2,int num,int hLTx, int hLTy, int hRBx, int hRBy);
	void setImage1(YsRawPngDecoder &image1,const char image1String[]);
	void setImage1HeadLT(int x1,int y1);
	void setImage2HeadRB(int x2,int y2);
	void copyRGBA(YsRawPngDecoder &image1,YsRawPngDecoder &image2);
	void timerFired(void);
	void straightMotion(int v);
	void choose(YsRawPngDecoder &image2);
	void draw(void);
};

#endif
