/**************************************************************************************

This File is created by Ruixi Deng
Component Code Version 1
Nov. 17th, 2013 21:35
***************************************************************
this file contains classes including Button, FaceButton, TemplateButton and HelpButton.
This classes can initate themselves, reset there state to none pressed, dectect whether the 
button has been pressed by a mouse and draw these buttons.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"

#include "projectRuixi1.h"

TextString::TextString() : str(NULL)
{
}

TextString::TextString(const char from[]) : str(NULL)
{
    Set(from);
}

TextString::TextString(const TextString &from) : str(NULL)
{
    Set(from.GetPointer());
}

TextString::~TextString()
{
    CleanUp();
}

void TextString::CleanUp(void)  
{
    if(NULL!=str)
    {
        delete [] str;
        str=NULL;
    }
}

void TextString::Set(const char from[])  //
{
    if(NULL!=from)
    {
        CleanUp();
        
        const int n=strlen(from);
        str=new char [n+1];  
        if(NULL!=str)
        {
            strcpy(str,from);
        }
    }
}

void TextString::Add(const char from[])
{
    if(NULL!=from)
    {
        const int nCurrent=Strlen();  
        const int nFrom=strlen(from); 

        char *newStr=new char [nCurrent+nFrom+1];
        if(NULL!=newStr)
        {
            strcpy(newStr,GetPointer());
            strcpy(newStr+nCurrent,from); 
            if(NULL!=str)
            {
                delete [] str;    
            }
            str=newStr;
        }
    }
}

void TextString::Add(const char c)
{
    const int nCurrent=Strlen();
    
    char *newStr=new char [nCurrent+2];
    if(NULL!=newStr)
    {
        strcpy(newStr,GetPointer());
        newStr[nCurrent]=c;
        newStr[nCurrent+1]=0;
        if(NULL!=str)
        {
            delete [] str;
        }
        str=newStr;
    }
}

void TextString::BackSpace(void) 
{
    if(NULL!=str)
    {
        int n=Strlen();
        if(0<n)
        {
            str[n-1]=0;
        }
    }
}

void TextString::DeleteLastControlCode(void)
{
    int n;
    for(n=strlen(str)-1; 0<=n; n--)
    {
        if(0!=isprint(str[n])) 
        {
            break;
        }
        str[n]=0;
    }
}

const char *TextString::Fgets(FILE *fp)
{
    if(NULL!=fp)
    {
        CleanUp();
        
        
        int firstLine=1;
        const int nBuf=8;
        char buf[nBuf+1];
        
        buf[nBuf]=0;
        for(;;)
        {
            if(NULL==fgets(buf,nBuf,fp))
            {
                if(0!=firstLine)  
                {
                    return NULL;
                }
                else               
                {
                    break;
                }
            }
            else
            {
                firstLine=0;
                Add(buf);
                
                int nChar=strlen(buf);
                if(buf[nChar-1]=='\n' || buf[nChar-1]=='\a') 
                {
                    break;
                }
            }
        }
        
        DeleteLastControlCode();
        return str;
    }
    return NULL;
}

const char *TextString::GetPointer(void) const  
{
    if(NULL!=str)
    {
        return str;
    }
    else
    {
        return "";
    }
}

const int TextString::Strlen(void) const
{
    return strlen(GetPointer());
}

void TextString::Print(void) const
{
    if(NULL!=str)
    {
        printf("%s\n",str);
    }
}

const TextString &TextString::operator=(const TextString &from)
{
    Set(from.GetPointer());
    return *this;    
}


//////////////////////////////////////////////////////////////////////////////////////
//Following Code By Ruixi Deng



void Button::init(int xPos, int yPos, char str[])
{
    state=0;
	xLeft=xPos;
	yTop=yPos;
	text.Set(str);
}


void Button::draw()
{
	//if the button is pressed, draw in a different color

	int displacement=5;

	glColor3ub(0,0,0);
	glBegin(GL_QUADS);
	glVertex2i(xLeft-displacement, yTop+displacement);
	glVertex2i(xLeft-displacement, yTop+hei+displacement);
	glVertex2i(xLeft+wid-displacement, yTop+hei+displacement);
	glVertex2i(xLeft+wid-displacement, yTop+displacement);

    glEnd();
	if (state==0)
	{
		//not pressed, draw it in white
		glColor3ub(255,255,255);
	}
	else
	{
		// if the button is pressed, draw it in grey
		glColor3ub(224, 224, 224);
	}
	glBegin(GL_QUADS);
	glVertex2i(xLeft, yTop);
	glVertex2i(xLeft, yTop+hei);
	glVertex2i(xLeft+wid, yTop+hei);
	glVertex2i(xLeft+wid, yTop);
    glEnd();

	//draw whatever text should be on the button
	glColor3ub(0,0,0);
	glRasterPos2d(xLeft+5, yTop+hei-1);//screen coordinate
	YsGlDrawFontBitmap12x16(text.GetPointer());

}

void Button::checkPressed(int rx, int ry)
{
    state=0;
    
	//check if the location of the last key press is in the button
	if (state==0) //if the key has not been pressed
	{
		if (rx>xLeft && rx<xLeft+wid && ry>yTop && ry<yTop+hei)
		{
			state=1;
		}
	}
}

void Button:: reset()
	//reset the state back to 0, so the cell would not be pressed anymore
{
	state=0;
}



void FaceButton::init(int width, int height, int xPos, int yPos, char str[])
{
	wid=width;
	hei=height;
	Button::init(xPos, yPos, str);
}

void TemplateButton::init(int width, int height, int xPos, int yPos, char str[])
{
	wid=width;
	hei=height;
	Button::init(xPos, yPos, str);
}

void HelpButton::init(int width, int height, int xPos, int yPos, char str[])
{
	wid=width;
	hei=height;
	Button::init(xPos, yPos, str);
}


void HelpButton::showMenu()
//show a window with some text when the user presses the button
{
	if (state==1)//if the key has been pressed
	{
		//draw a square to show the title
		glColor3ub(160,160,160);
		glBegin(GL_QUADS);
		glVertex2i(150, 150);
		glVertex2i(150+500, 150);
		glVertex2i(150+500, 150+500);
		glVertex2i(150, 150+500);
		glEnd();

		glColor3ub(255,255,255);
		glBegin(GL_QUADS);
		glVertex2i(160, 160);
		glVertex2i(160+480, 160);
		glVertex2i(160+480, 160+480);
		glVertex2i(160, 160+480);
		glEnd();

		TextString helpText;
		helpText.Set("Choose one face from the left and one template from the right.\n\
					 Press START to see the picture.\n\
					 Or choose two faces from the left.\n\
					 Press COMPETE to have a beauty contest.\n\
					 Click your mouse on the top-left and bottom-right of the face area\n\
					 to select a face.\n\
					 Press SPACE to return quit the help menu and return to the game.\n\
					 HAVE FUN!!!");		
		glRasterPos2d(160+480+10, 160+10);//screen coordinate
		YsGlDrawFontBitmap8x12(helpText.GetPointer());
		
	}
}

void HelpButton::quitHelp()
{
	if (state==1)
	{
		if (FsInkey()==FSKEY_SPACE)
		{
			Button::reset();
		}
	}
}

/*

int main(void)
{
	// the size of the window
	int windowWid=16;
	int windowHei=16;
	int windowTop=800;
	int windowLeft=800;

	FsOpenWindow(16,16,800,600,1);

	
	int key=FSKEY_NULL;
	while(FSKEY_ESC!=key)
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		
		FsSwapBuffers();
		FsSleep(50);

	}
	return 0;

}
*/