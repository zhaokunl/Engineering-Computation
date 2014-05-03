#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fssimplewindow.h"

class OglPrim
{
protected:
	int nVtx,*vtx;

	// First vertex (vtx[0],vtx[1]), Second vertex (vtx[2],vtx[3]), ... , nth vertex (vtx[(n-1)*2],vtx[(n-1)*2+1])
	// vtx needs to be an array of 2*nVtx integers.

public:
	OglPrim();
	~OglPrim();
	void CleanUp(void);

	OglPrim(OglPrim &from);
	OglPrim &operator=(OglPrim &from);


	void Set(int nFrom,int from[]); // 
	// Copy incoming vertices (from[0],from[1]),(from[2],from[3]),...(from[(nFrom-1)*2],from[(nFrom-1)*2+1])
	// to its own nVtx and vtx.


	void AddVertex(int x,int y);
	// Add one vertex to the end.


	void Move(int dx,int dy);
	// Move all the vertices by (dx,dy)


	void Draw(GLenum primType);  // Eg.  prim.Draw(GL_LINE_STRIP);
	// Draw the OpenGL primitive.
};

OglPrim::OglPrim()
{
	nVtx=0;
	vtx=NULL;
}

OglPrim::~OglPrim()
{
    CleanUp();
}

void OglPrim::CleanUp(void)
{
 if(NULL!=vtx)
  {
    delete[]vtx;
    vtx=NULL;
  }
}


OglPrim::OglPrim(OglPrim &from)
{
}

OglPrim &OglPrim::operator=(OglPrim &from)
{
	return *this;
}

void OglPrim::Set(int nFrom,int from[])
{
    if(NULL!=from)
    {
        CleanUp();
        vtx=new int[nFrom+1];
        if(NULL!=vtx)
        {
            vtx=from;
            //
        }
    }
}

void OglPrim::AddVertex(int x,int y)
{
	int nVtxNew=nVtx+1;
	int *vtxNew=new int [nVtxNew*2];

	for(int i=0; i<nVtx*2; ++i)
	{
		vtxNew[i]=vtx[i];
	}
	vtxNew[nVtx*2  ]=x;
	vtxNew[nVtx*2+1]=y;

	CleanUp();
	nVtx=nVtxNew;
	vtx=vtxNew;
}

void OglPrim::Move(int dx,int dy)
{
    for(int i=1; i<nVtx+1; i++)
    {
        vtx[(i-1)*2]-=dx;
        vtx[(i-1)*2+1]-=dy;
    }
}

void OglPrim::Draw(GLenum primType)
{
	glBegin(primType);
	for(int i=0; i<nVtx; ++i)
	{
		glVertex2i(vtx[i*2],vtx[i*2+1]);
	}
	glEnd();
}



int main(void)
{
	FsOpenWindow(16,16,800,600,1);

	OglPrim a,b;

	a.AddVertex(100,100);
	a.AddVertex(200,100);
	a.AddVertex(120,170);
	a.AddVertex(150,65);
	a.AddVertex(180,170);

	b=a;
	a.Move(5,5);

	while(FSKEY_ESC!=FsInkey())
	{
		FsPollDevice();

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		glColor3ub(0,0,0);
		a.Draw(GL_LINE_LOOP);

		if(0!=FsGetKeyState(FSKEY_LEFT))
		{
			a.Move(-10,0);
		}
		if(0!=FsGetKeyState(FSKEY_RIGHT))
		{
			a.Move(10,0);
		}
		if(0!=FsGetKeyState(FSKEY_UP))
		{
			a.Move(0,-10);
		}
		if(0!=FsGetKeyState(FSKEY_DOWN))
		{
			a.Move(0,10);
		}

		glColor3ub(0,0,255);
		b.Draw(GL_LINE_LOOP);

		FsSwapBuffers();
		FsSleep(25);
	}

	return 0;
}
