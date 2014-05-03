/**************************************************************************************

This File is created by Ruixi Deng
Component Code Version 1
Nov. 17th, 2013 21:35
***************************************************************
this file contains classes including Button, FaceButton, TemplateButton and HelpButton.
This classes can initate themselves, reset there state to none pressed, dectect whether the 
button has been pressed by a mouse and draw these buttons.

*/


#ifndef STRING
#define STRING


class TextString
{
protected:
    char *str;
    
public:
    TextString();
    TextString(const char from[]);
    TextString(const TextString &str);
    ~TextString();
    void CleanUp(void);
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

//////////////////////////////////////////////////////////////////////////////////////
//Following Code By Ruixi Deng


class Button 
//the button class, can be pressed 
{
public:
	//dimensions
	int xLeft;
	int yTop;
	int wid;
	int hei;
	//0 for not pressed, 1 for pressed
	int state;
	TextString text; //the button may have text draw on them
	
	void init(int xPos, int yPos,char str[]);
	void draw();
	void checkPressed(int rx, int ry);
	void reset();

};

class FaceButton: public Button
{
public:
	void init(int width, int height, int xPos, int yPos, char str[]);
};

class TemplateButton: public Button
{
public:
	void init(int width, int height, int xPos, int yPos, char str[]);
};


class HelpButton: public Button
{
public:
	void init(int width, int height, int xPos, int yPos, char str[]);
	void showMenu();
	void quitHelp();//quit the help window when user presses SPACE
};


#endif