/*
 Name: Zhaokun LI
 Andrew ID: zhaokunl
 
 Faceshop--User Interface
 -------------------------------------------------------------------
 I am responsible to build the application framework and integrate 
 all other team members' functions:
 
 Draw buttons, including menu, picture selection button, template
 selection button, start, clear using Reese' s classes
 
 When receive a request from the user, decide which mode it is and
 which image processing function to call (warp image, gif, image 
 grading). Pass the chosen images to the function and then display 
 the returned picture on the board.
 
 11/24/2013
 11:00 PM
 version 5
 */


/*
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"

#include "projectRuixi1.h"
#include "yspng.h"
#include "warpImage.h"
#include "makegif.h"
#include "ysglfontdata.h"

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

/*
int GrayScale(int X1,int Y1,int X2,int Y2,int wid,unsigned char dat[]) {
    unsigned int avg=0;
    
	for(int y=Y1; y<Y2; ++y) {
		for(int x=X1; x<X2; ++x) {
			unsigned char *pix=dat+(wid*y+x)*4;
			avg=(pix[0]+pix[1]+pix[2])/3;
		}
	}
    return avg;
}

int Compare(int p,int q) {
    if(p>q) {
        return 1;
    }
    else {
        return 2;
    }
}


int BeautyCompetition(int position1[],int position2[],
                      int wid,unsigned char rgba) {//get input from user interface
    int x1,x2,y1,y2;
    unsigned int m,n;
    
    for(int i=0;i<2;i++) {                         //locate calculating area
        if(i==0) {
            x1=position1[0];
            y1=position1[1];
            x2=position1[2];
            y2=position1[3];
        }
        if(i==1) {
            x1=position2[0];
            y1=position2[1];
            x2=position2[2];
            y2=position2[3];
        }
        
        if(i==0) {                         //calculate the grayscale of each iamge
            m=GrayScale(x1,y1,x2,y2,wid,&rgba);;
        }
        if(i==1) {
            n=GrayScale(x1,y1,x2,y2,wid,&rgba);
        }
    }
    
    return Compare(m,n);                   //compare two scales and return a value
}
*/
/********************************************************************************/

/* Main Function */
int mainNiGeTou(void) 
{
    
	FsOpenWindow(64,16,1300,700,1);
    Frame fra;
    fra.display();
    
    Button Menu1;
    Button Menu2;
    Button Menu3;
    Button Menu4;
    Button Menu5;
    Button Menu6;
    
    Button Left1;
    Button Left2;
    Button Left3;
    Button Left4;
    
    Button Right1;
    Button Right2;
    Button Right3;
    Button Right4;
    
    HelpButton help;
    Menu1.wid=80;
    Menu1.hei=20;
    Menu1.init(20, 5, "Start");
    
    Menu2.wid=80;
    Menu2.hei=20;
    Menu2.init(120, 5, "Mode");
    
    Menu3.wid=80;
    Menu3.hei=20;
    Menu3.init(220, 5, "Save");
    
    Menu4.wid=80;
    Menu4.hei=20;
    Menu4.init(320, 5, "Clear");
    
    Menu5.wid=80;
    Menu5.hei=20;
    Menu5.init(420, 5, "Exit");
    
    Menu6.wid=80;
    Menu6.hei=20;
   // Menu6.init(80, 20, 520, 5, "Help");
    Menu6.init(520, 5, "Help");
    
    Left1.wid=160;
    Left1.hei=120;
    Left1.init(20, 50, "Picture 1");
    
    Left2.wid=160;
    Left2.hei=120;
    Left2.init(20, 200, "Picture 2");
    
    Left3.wid=160;
    Left3.hei=120;
    Left3.init(20, 350, "Picture 3");
    
    Left4.wid=160;
    Left4.hei=120;
    Left4.init(20, 500, "Picture 4");
    
    Right1.wid=160;
    Right1.hei=120;
    Right1.init(1120, 50, "Template 1");
    
    Right2.wid=160;
    Right2.hei=120;
    Right2.init(1120, 200, "Template 2");
    
    Right3.wid=160;
    Right3.hei=120;
    Right3.init(1120, 350, "Template 3");
    
    Right4.wid=160;
    Right4.hei=120;
    Right4.init(1120, 500, "Template 4"); //initialize the button positions
    
    int picturestate[4];
    for(int i=0; i<4; i++) {
        picturestate[i]=0;
	}
    
    int templatestate[4];
    for(int i=0; i<4; i++) {
        templatestate[i]=0;
	}
    
    int userchosenPositionX[2];
    int userchosenPositionY[2];
    userchosenPositionX[0]=0;
    userchosenPositionX[1]=0;
	userchosenPositionY[0]=0;
	userchosenPositionY[1]=0;
    
    int pictureRoute[4];
    int templateRoute[4];
    
    char picture1[256]="input.png";
    picture1[strlen(picture1)]='\0';
    char picture2[256]="input.png";
    picture2[strlen(picture1)]='\0';
    char picture3[256]="input.png";
    picture3[strlen(picture1)]='\0';
    char picture4[256]="input.png";
    picture4[strlen(picture1)]='\0';
    
    char template1[256]="pilot.png";
    picture1[strlen(picture1)]='\0';
    char template2[256]="input.png";
    picture2[strlen(picture1)]='\0';
    char template3[256]="input.png";
    picture3[strlen(picture1)]='\0';
    char template4[256]="input.png";
    picture4[strlen(picture1)]='\0';


	YsRawPngDecoder png1;
	YsRawPngDecoder png2;


	int warped=0;


	int position1[4];
	int position2[4];

	YsRawPngDecoder png;

	int counter=0;
    
    for(;;) 
	{
		counter++;
		FsPollDevice();
		
        
        int lb, mb, rb, rx, ry;
        int mouseEvent;
        mouseEvent=FsGetMouseEvent(lb,mb,rb,rx,ry);
        
        if(mouseEvent==FSMOUSEEVENT_LBUTTONDOWN) {
            Menu1.checkPressed(rx, ry);
            Menu2.checkPressed(rx, ry);
            Menu3.checkPressed(rx, ry);
            Menu4.checkPressed(rx, ry);
            Menu5.checkPressed(rx, ry);
            Menu6.checkPressed(rx, ry);
            
            Left1.checkPressed(rx, ry);
            Left2.checkPressed(rx, ry);
            Left3.checkPressed(rx, ry);
            Left4.checkPressed(rx, ry);
            
            Right1.checkPressed(rx, ry);
            Right2.checkPressed(rx, ry);
            Right3.checkPressed(rx, ry);
            Right4.checkPressed(rx, ry);
            
            /* Click the close mark */
            if (((rx-1280)*(rx-1280)+(ry-15)*(ry-15))<=64) {
                break;
            }
        }
        
        /* Draw Screen */
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
		
        fra.DrawToolbox();
        fra.DrawColum();
        fra.DrawShowWindow();
        fra.DrawExit();

		

        if (Menu5.state==1) {
            break;
        }
		

        /* draw menu button */
		
		
        Menu1.draw();
		
		Menu2.draw();
        Menu3.draw();
        Menu4.draw();
        Menu5.draw();
        Menu6.draw();
        Left1.draw();
        Left2.draw();
        Left3.draw();
        Left4.draw();
        Right1.draw();
        Right2.draw();
        Right3.draw();
        Right4.draw();
		
        
        /* When the buttons are pressed */
        if (Left1.state==1) 
		{
            picturestate[0]=1;
			if(YSOK==png.Decode(picture1)) 
			{
                png.Flip();
            }
            else {
                printf("Read Error!\n");
                return 0;
            }

			if(YSOK==png1.Decode(picture1)) 
			{
                //png1.Flip();
            }
			Left1.state=0;
        }
        if(picturestate[0]!=0)
        {
            //YsRawPngDecoder png;
			//YsRawPngDecoder png1;
            
			
            
            int lb0, mb0, rb0, rx0, ry0;
            int mouseEvent0;
            mouseEvent0=FsGetMouseEvent(lb0,mb0,rb0,rx0,ry0);

			

			
            /*
            for (int i=0; i<2; i++) 
			{
                if(mouseEvent0==FSMOUSEEVENT_LBUTTONDOWN) 
				{
                    userchosenPositionX[i]=rx0-300;
                    userchosenPositionY[i]=550-ry0;
                }
            }
			*/
			


			if(mouseEvent0==FSMOUSEEVENT_LBUTTONDOWN)
			{
				printf("damn it!\n\n");
				printf("%d\n",counter);
			
				if(userchosenPositionX[0]==0 && userchosenPositionY[0]==0)
				{
					userchosenPositionX[0]=rx0-300;
					userchosenPositionY[0]=550-ry0;
					printf("%d, %d\n", userchosenPositionX[0], userchosenPositionY[0]);
        
				}
				else
				{
					userchosenPositionX[1]=rx0-300;
					userchosenPositionY[1]=550-ry0;
					printf("%d, %d\n", userchosenPositionX[1], userchosenPositionY[1]);
				}
			}

			position1[0]=userchosenPositionX[0];
			position1[1]=userchosenPositionY[0];
			position1[2]=userchosenPositionX[1];
			position1[3]=userchosenPositionY[1];



            /* Call function from Yangwang, pass the two parameters
            void setImage1(YsRawPngDecoder &image1,char image1String[]);
            void setImage1HeadLT(int x1,int y1);
            void setImage2HeadRB(int x2,int y2);
             */
            

            //void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation);
            
            
            int winWid,winHei;
            
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(300.0,(double)(winHei-150));
            glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        }
        
		
        
        
        if (Left2.state==1) {
            picturestate[1]=1;
        }
        if(picturestate[1]!=0){
            //YsRawPngDecoder png;
            if(YSOK==png.Decode(picture2)) {
                printf("Read Width=%d Height=%d\n",png.wid,png.hei);
                png.Flip();
            }
            else {
                printf("Read Error!\n");
                return 0;
            }
            
			if (warped==0)
			{
				int winWid,winHei;
            
				FsGetWindowSize(winWid,winHei);
				glRasterPos2d(300.0,(double)(winHei-150));
				glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
			}
        }
        
        if (Left3.state==1) {
            picturestate[2]=1;
        }
        if(picturestate[2]==1){
            YsRawPngDecoder png;
            if(YSOK==png.Decode(picture3)) {
                printf("Read Width=%d Height=%d\n",png.wid,png.hei);
                png.Flip();
            }
            else {
                printf("Read Error!\n");
                return 0;
            }
            
            int winWid,winHei;
            
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(380.0,(double)(winHei-150));
            glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        }
        
        if (Left4.state==1) {
            picturestate[3]=1;
        }
        if(picturestate[3]==1) {
            YsRawPngDecoder png;
            if(YSOK==png.Decode(picture4)) {
                printf("Read Width=%d Height=%d\n",png.wid,png.hei);
                png.Flip();
            }
            else {
                printf("Read Error!\n");
                return 0;
            }
            
            int winWid,winHei;
            
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(300.0,(double)(winHei-150));
            glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        }
        
        
        if (Right1.state==1) {
            templatestate[0]=1;
        }
        if(templatestate[0]==1) {
            //YsRawPngDecoder png;
			
            if(YSOK==png.Decode(template1)) 
			{
                //printf("Read Width=%d Height=%d\n",png.wid,png.hei);
                png.Flip();
				Right1.state=0;
				templatestate[0]=0;
            }
		    else {
                printf("Read Error!\n");
                return 0;
            }
            
			if(YSOK==png2.Decode(template1)) {
                //printf("Read Width=%d Height=%d\n",png.wid,png.hei);
                //png2.Flip();
            }

			position2[0]=495;
			position2[1]=50;
			position2[2]=590;
			position2[3]=172;


            int winWid,winHei;
            
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(300.0,(double)(winHei-150));
            glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        }
        
        if (Right2.state==1) {
            templatestate[1]=1;
        }
        if(templatestate[1]==1) {
            YsRawPngDecoder png;
            if(YSOK==png.Decode(template2)) {
                printf("Read Width=%d Height=%d\n",png.wid,png.hei);
                png.Flip();
            }
            else {
                printf("Read Error!\n");
                return 0;
            }
            
            int winWid,winHei;
            
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(300.0,(double)(winHei-150));
            glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        }
        
        if (Right3.state==1) 
		{
            templatestate[2]=1;
        }
        if(templatestate[2]==1) 
		{
            YsRawPngDecoder png;
            if(YSOK==png.Decode(picture3)) 
			{
                printf("Read Width=%d Height=%d\n",png.wid,png.hei);
                png.Flip();
            }
            else {
                printf("Read Error!\n");
                return 0;
            }
            
            int winWid,winHei;
            
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(300.0,(double)(winHei-150));
            glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        }
        
        if (Right4.state==1) {
                templatestate[3]=1;
            }
        if(templatestate[3]==1) {
            YsRawPngDecoder png;
            if(YSOK==png.Decode(picture4)) {
                printf("Read Width=%d Height=%d\n",png.wid,png.hei);
                png.Flip();
            }
            else {
                printf("Read Error!\n");
                return 0;
            }
            
            int winWid,winHei;
            
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(300.0,(double)(winHei-150));
            glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        }

		if(FSKEY_ESC==FsInkey()) 
		{ // replace by exit
			break;
		}
		else if(FsInkey()==FSKEY_SPACE)
		{
			printf("warped!\n");
			warpImage(png1,png2,position1, position2,0.0);
			warped=1;
			png2.Flip();
		}

		
		
       

		if (warped==1)
		{
			int winWid,winHei;

			FsGetWindowSize(winWid,winHei);
            glRasterPos2d(300.0,(double)(winHei-150));
            glDrawPixels(png2.wid,png2.hei,GL_RGBA,GL_UNSIGNED_BYTE,png2.rgba);
		}

        
        
        
        
   //     Menu6.showMenu();
        //if picture pressed show the picture at the left side
        //if template pressed show the template at the right side
        //if help pressed, show the help menu
        //if save pressed, save the processed picture
        //if clear pressed, clear the pictures in the middle window
        //if exit pressed, show a confirmation window
        
   //    help.showMenu();
    /*   mode: face changing or face grading
         
         close: same with exit and ESC
         
         watermark: print words at a fixed position
         
         picture: display the picture in the middle & call corressponding
         image processing function
         template: display the template in the middle & call corresponding
         image processing function
         
         start: draw the returned processed image in the middle 
         clear: clear all staff shown in the middle board
         */
		FsSwapBuffers();
		FsSleep(25);
	}
}