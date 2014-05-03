#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "fssimplewindow.h"

#include "projectRuixi1.h"
#include "yspng.h"
#include "warpImage.h"
#include "makegif.h"
#include "ysglfontdata.h"



////////////////////////////////////
// define game modes
//////////////////////////////////////
#define WAIT_LEFTBUT 0
#define WAIT_POS1 1
#define WAIT_POS2 2
#define WAIT_TEMPLATE 3
#define WAIT_WARP 4
#define FINISHED 5



class Frame {
public:
    void DrawWelcome(void);
    void display(void);
    void DrawToolbox(void);
    void DrawColum(void);
    void DrawShowWindow(void);
    void DrawExit(void);
};

void Frame:: display(void) {
    glClearColor(0.9f, 0.9f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glFlush();
}

void Frame::DrawExit(void) {
    const double YS_PI=3.1415927;
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    int i;
    int cx=1280;
    int cy=15;
    for(i=0;i<200;i++) {
        double angle=(double)i*YS_PI/100.0;
        double x=(double)cx+cos(angle)*8;
        double y=(double)cy+sin(angle)*8;
        glVertex2d(x, y);
    }
    glEnd();
    
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    
    glVertex2i((1280-8/sqrt(2.)), (15-8/sqrt(2.)));
    glVertex2i((1280+8/sqrt(2.)), (15+8/sqrt(2.)));
    
    glVertex2i((1280+8/sqrt(2.)), (15-8/sqrt(2.)));
    glVertex2i((1280-8/sqrt(2.)), (15+8/sqrt(2.)));
    
    glEnd();
}

void Frame:: DrawToolbox(void) {
    glColor3ub(128, 128, 128);
    glBegin(GL_QUADS);
    
    glVertex2i(0, 0);
    glVertex2i(1300, 0);
    glVertex2i(1300, 30);
    glVertex2i(0, 30);
    
    glEnd();
}

void Frame::DrawWelcome(void) {
}

void Frame:: DrawColum(void) {
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    
    glVertex2i(200, 30);
    glVertex2i(210, 30);
    glVertex2i(210, 700);
    glVertex2i(200, 700);
    
    glVertex2i(1100, 30);
    glVertex2i(1090, 30);
    glVertex2i(1090, 700);
    glVertex2i(1100, 700);
    
    glEnd();
}

void Frame:: DrawShowWindow(void) {
    glColor3ub(128, 128, 128);
    glBegin(GL_QUADS);
    
    glVertex2i(290, 90);
    glVertex2i(1010, 90);
    glVertex2i(1010, 650);
    glVertex2i(290, 650);
    
    glEnd();
    
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    
    glVertex2i(300, 100);
    glVertex2i(1000, 100);
    glVertex2i(1000, 640);
    glVertex2i(300, 640);
    
    glEnd();
}


/* Beauty competition---Renjie Li */
/********************************************************************************/
int GrayScale(int X1,int Y1,int X2,int Y2,int wid,unsigned char dat[]) {
    unsigned int avg=0;
    
	for(int y=Y1; y<Y2; ++y) {
		for(int x=X1; x<X2; ++x) {
			unsigned char *pix=dat+(wid*y+x)*4;
			avg=(pix[0]+pix[1]+pix[2])/3;
		}
	}
    return avg/Y2/X2;
}

int Compare(int p,int q) {
    if(p>q) {
        return 1;
    }
    else {
        return 2;
    }
}


int BeautyCompetition(YsRawPngDecoder &image1,YsRawPngDecoder &image2) {//get input from user interface
    unsigned int m,n;
        
                        //calculate the grayscale of each iamge
            m=GrayScale(0,0,image1.wid,image1.hei,image1.wid,image1.rgba);


            n=GrayScale(0,0,image2.wid,image2.hei,image2.wid,image2.rgba);


    
    return Compare(m,n);                   //compare two scales and return a value
}
/********************************************************************************/

/* Main Function */






int main(void)
{
	Frame fra;
    
	int lb, mb, rb, rx, ry;//mouse variables
	int mode=0;
	int isWarp=1;  // in the warp or compete mode
	int winner=0;
	int mouseDown=0; 

	int winWid,winHei;
	
	Button Left[4];
	Button Right[4];
	Button Menu[6];

	YsRawPngDecoder image1;
	YsRawPngDecoder image2;
	makegif gif;

	TextString FaceLocation[4];
	TextString TemplateLocation[4];

	int pos1[4];
	int pos2[4];

	int image2Pos[2][4]; //the first index is the image, the second index is the position

	int faceChosen;
	int templateChosen;
	
	////////////////////////////////////////////////////////////////////
	// initialize the positions
	////////////////////////////////////////////////////////////////////

	image2Pos[0][0]=95;
	image2Pos[0][1]=12;
	image2Pos[0][2]=153;
	image2Pos[0][3]=85;

	image2Pos[1][0]=290;
	image2Pos[1][1]=25;
	image2Pos[1][2]=410;
	image2Pos[1][3]=155;
	
	

	////////////////////////////////////////////////////////////////////
	// initialize the face & template locations
	////////////////////////////////////////////////////////////////////

	FaceLocation[0].Set("face0.png");
	FaceLocation[1].Set("face1.png");
	FaceLocation[2].Set("face2.png");
	FaceLocation[3].Set("face3.png");

	TemplateLocation[0].Set("template0.png");
	TemplateLocation[1].Set("template1.png");
	TemplateLocation[2].Set("GIF1/01.png");
	TemplateLocation[3].Set("GIF2/01.png");


	///////////////////////////////////////////////////////////////////////
	// initialize the buttons
	///////////////////////////////////////////////////////////////////////

	for (int i=0; i<4; i++)
	{
		Left[i].wid=160;
		Left[i].hei=120;
		Right[i].wid=160;
		Right[i].hei=120;
	}

    Left[0].init(20, 50, "Picture 1");
    Left[1].init(20, 200, "Picture 2");
    Left[2].init(20, 350, "Picture 3");
    Left[3].init(20, 500, "Picture 4");

	Right[0].init(1120, 50, "Template 1");
    Right[1].init(1120, 200, "Template 2");
    Right[2].init(1120, 350, "Gif 1");
    Right[3].init(1120, 500, "Gif 2");
    
	for (int i=0; i<6; i++)
	{
		Menu[i].wid=80;
		Menu[i].hei=20;
	}
	
	Menu[0].init(20, 5, "Start");
    Menu[1].init(120, 5, "Compete");
    Menu[2].init(220, 5, "Rotate");
    Menu[3].init(320, 5, "Clear");
    Menu[4].init(420, 5, "Exit");
    Menu[5].init(520, 5, "Help");

	FsOpenWindow(64,16,1300,700,1);
	fra.display();

	FsGetWindowSize(winWid,winHei);

	while(1)
	{
		mouseDown=0;
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		fra.DrawToolbox();
        fra.DrawColum();
        fra.DrawShowWindow();
        fra.DrawExit();

		for (int i=0; i<4; i++)
		{
			Left[i].draw();
			Right[i].draw();
		}

		for (int i=0; i<6; i++)
		{
			Menu[i].draw();
		}


		////////////////////////////////////////////////////////////////////////
		// get button states
		////////////////////////////////////////////////////////////////////////

		if(FsGetMouseEvent(lb,mb,rb,rx,ry)==FSMOUSEEVENT_LBUTTONDOWN)
		{
			mouseDown=1;
			for (int i=0; i<4; i++)
			{
				Left[i].checkPressed(rx, ry);
				Right[i].checkPressed(rx, ry);
			}
			for (int i=0; i<6; i++)
			{
				Menu[i].checkPressed(rx, ry);
			}
		}


		if (Menu[3].state==1)
		{
			mode=WAIT_LEFTBUT;
			Menu[3].state=0;
			isWarp=1;
			Menu[1].state=0;
			winner=0;
		}
		
		if (Menu[1].state==1)
		{
			isWarp=0;
		}

		if (Menu[4].state==1)
		{
			break;
		}

		///////////////////////////////////////////////////////////////
		// switch among different state of the game
		////////////////////////////////////////////////////////////////
		
		if (isWarp==1) //in the warp mode
		{
			switch(mode)
			{
			case WAIT_LEFTBUT:
				{
					for (int i=0; i<4; i++)
					{
						if (Left[i].state==1) // if pressed
						{
						
							if(YSOK==image1.Decode(FaceLocation[i].GetPointer())) 
							{
								printf(FaceLocation[i].GetPointer());
								mode=WAIT_POS1;
								Left[i].state=0;
								faceChosen=i;
								break;
							}
						}

					}
					break;
				}
			case WAIT_POS1:
				{
					if (mouseDown==1)
					{
						if (rx-300<=image1.wid && 550-ry<=image1.hei && rx-300>0 && 550-ry>0)
						{
							pos1[0]=rx-300;
							pos1[1]=image1.hei-(550-ry);
							mouseDown=0;
							mode=WAIT_POS2;
							printf("first pos %d %d\n",pos1[0],pos1[1]);
						}
					
					}
					break;
				}
			case WAIT_POS2:
				{
					if (mouseDown==1)
					{
						if (rx-300<=image1.wid && 550-ry<=image1.hei && rx-300>0 && 550-ry>0)
						{
							pos1[2]=rx-300;
							pos1[3]=image1.hei-(550-ry);
							mouseDown=0;
							mode=WAIT_TEMPLATE;
							printf("second pos %d %d\n",pos1[2],pos1[3]);
						}
					
					}
					break;
				}
			case WAIT_TEMPLATE:
				{
				
					for (int i=0; i<2; i++)
					{
						if (Right[i].state==1) // if pressed
						{
						
							if(YSOK==image2.Decode(TemplateLocation[i].GetPointer())) 
							{
								mode=WAIT_WARP;
								Right[i].state=0;
								templateChosen=i;

								pos2[0]=image2Pos[i][0];
								pos2[1]=image2Pos[i][1];
								pos2[2]=image2Pos[i][2];
								pos2[3]=image2Pos[i][3];
							
								break;


							}
						}

					}

					if (Right[2].state==1)
					{
						if(YSOK==image2.Decode(TemplateLocation[2].GetPointer())) 
							{
								mode=WAIT_WARP;
								Right[2].state=0;
								templateChosen=2;
								//printf("GIF1\n");


								//char *image1String=FaceLocation[faceChosen].GetPointer();
								char gifString[]={"GIF1/01.png"};
								//char gifString[]={"GIF2/01.png"};

								gif.initial(gifString,image2,12,15,0,45,40); //initial the gif class 
								//gif.initial(gifString,image2,4,160,50,260,165); //initial the gif class 
								gif.setImage1(image1,FaceLocation[faceChosen].GetPointer()); // select the head picture

								gif.setImage1HeadLT(pos1[0],pos1[1]); // select the left top point of the head picture

								gif.setImage2HeadRB(pos1[2],pos1[3]); // select the right bottom point of the head picture
								gif.copyRGBA(image1,image2);

								break;

							}
						break;

					}

					if (Right[3].state==1)
					{
						if(YSOK==image2.Decode(TemplateLocation[3].GetPointer())) 
							{
								mode=WAIT_WARP;
								Right[3].state=0;
								templateChosen=3;
								//printf("GIF1\n");


								//char *image1String=FaceLocation[faceChosen].GetPointer();
								//char gifString[]={"GIF1/01.png"};
								char gifString[]={"GIF2/01.png"};

								printf(FaceLocation[faceChosen].GetPointer());

								//gif.initial(gifString,image2,12,15,0,45,40); //initial the gif class 
								gif.initial(gifString,image2,4,160,50,260,165); //initial the gif class 
								gif.setImage1(image1,FaceLocation[faceChosen].GetPointer()); // select the head picture

								gif.setImage1HeadLT(pos1[0],pos1[1]); // select the left top point of the head picture

								gif.setImage2HeadRB(pos1[2],pos1[3]); // select the right bottom point of the head picture
								gif.copyRGBA(image1,image2);

								break;

							}
						break;

					}
					
						
				
					break;
				}
			case WAIT_WARP:
				{
					if (Menu[0].state==1)
					{
						warpImage(image1, image2, pos1, pos2, 0.0);
						mode=FINISHED;
						Menu[0].state=0;
					}
					if (Menu[2].state==1)
					{
						warpImage(image1, image2, pos1, pos2,-20.0);
						mode=FINISHED;
						Menu[2].state=0;
					}
					break;
				
				}
			case FINISHED:
				{
					if (Menu[3].state==1)
					{
						mode=WAIT_LEFTBUT;
						Menu[3].state=0;
					}
					break;
				}
			}
		}
		else
		{
			switch(mode)
			{
			case WAIT_LEFTBUT:
				{
					for (int i=0; i<4; i++)
					{
						if (Left[i].state==1) // if pressed
						{
						
							if(YSOK==image1.Decode(FaceLocation[i].GetPointer())) 
							{
								printf(FaceLocation[i].GetPointer());
								mode=WAIT_TEMPLATE;
								Left[i].state=0;
								//faceChosen=i;
								break;
							}
						}

					}
					break;
				}
			case WAIT_TEMPLATE:
				{
				
					for (int i=0; i<4; i++)
					{
						if (Left[i].state==1) // if pressed
						{
						
							if(YSOK==image2.Decode(FaceLocation[i].GetPointer())) 
							{
								printf(FaceLocation[i].GetPointer());
								mode=WAIT_WARP;
								Left[i].state=0;
								//faceChosen=i;
								break;
							}
						}

					}
					
					break;
				}
			case WAIT_WARP:
				{
					
					if (Menu[0].state==1)
					{
						
						winner=BeautyCompetition(image1,image2);
						glRasterPos2d(300.0,(double)(winHei-50));
						if (winner==1)
						{
							YsGlDrawFontBitmap20x32("PICTURE 1 WINS!");
						}
						else if (winner==2)
						{
							YsGlDrawFontBitmap20x32("PICTURE 2 WINS!");
						}
						printf("\nWINNER:%d!!!\n",winner);
						mode=FINISHED;
						Menu[0].state=0;
					}
					break;
				
				}
			case FINISHED:
				{
					if (Menu[3].state==1)
					{
						mode=WAIT_LEFTBUT;
						Menu[3].state=0;
						winner=0;
					}
					break;
				}
			}
		}

		///////////////////////////////////////////////////////////////
		// actually draw
		//////////////////////////////////////////////////////////////

		if (mode==WAIT_LEFTBUT)
		{
			//do nothing 
		}
		else if (mode>WAIT_LEFTBUT && mode<=WAIT_TEMPLATE)
		{
			image1.Flip();
			FsGetWindowSize(winWid,winHei);
			glRasterPos2d(300.0,(double)(winHei-150));
			glDrawPixels(image1.wid,image1.hei,GL_RGBA,GL_UNSIGNED_BYTE,image1.rgba);
			image1.Flip();
		}
		else if (mode>WAIT_TEMPLATE && mode<=FINISHED)
		{
			if (templateChosen<2)
			{
				image2.Flip();
				FsGetWindowSize(winWid,winHei);
				glRasterPos2d(300.0,(double)(winHei-150));
				glDrawPixels(image2.wid,image2.hei,GL_RGBA,GL_UNSIGNED_BYTE,image2.rgba);
				image2.Flip();
			}
			else if(templateChosen==2 || templateChosen==3)
			{
				if (mode==FINISHED)
				{
				gif.draw();
				}
				else 
				{
					image2.Flip();
					FsGetWindowSize(winWid,winHei);
					glRasterPos2d(300.0,(double)(winHei-150));
					glDrawPixels(image2.wid,image2.hei,GL_RGBA,GL_UNSIGNED_BYTE,image2.rgba);
					image2.Flip();
				}
			}

			if (winner==1)
			{
				glRasterPos2d(300.0,(double)(winHei-50));
				YsGlDrawFontBitmap20x32("PICTURE 1 WINS!");
			}
			else if (winner==2)
			{
				glRasterPos2d(300.0,(double)(winHei-50));
				YsGlDrawFontBitmap20x32("PICTURE 2 WINS!");
			}
						
		}

		


		FsSwapBuffers();
		FsSleep(25);
	}

	return 0;
	
}