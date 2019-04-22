// OpenGLDemo2_RenderWithGLFW.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#define __USING_RENDER_OPENGL
#include "OpenGLDemo2_RenderWithGLFW.h"

#ifdef __USING_RENDER_OPENGL
#include <gl/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32.lib")

void init() {
	glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
	
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glcolor3f(0.0f, 1.0f, 0.0f);
	glRectf(-0.6f, -0.6f, 0.6f, 0.6f);
	glFlush();
	
}
#define WINDOW_CAPTION "OpenGLWindow"
#else
#include "SMainWnd.h"
#define WINDOW_CAPTION TEXT("Direct3D11Window")
#endif
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
#ifdef __USING_RENDER_OPENGL
	int argc = 0;
	char* argv = "";
	glutInit(&argc, &argv);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(700, 500);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	
	int ret = glutCreateWindow(WINDOW_CAPTION);
	glewInit();
	init();
	glutDisplayFunc(display);
	glutMainLoop();
#else
	SMainWnd* pWindow = new SMainWnd();
	pWindow->CreateAdjustWindow(WINDOW_CAPTION, 700, 500, 1024, 768);
	pWindow->ShowWindow();
	RECT clientRc = { 0 };
	pWindow->GetClientRect(&clientRc);
	int nWidth = clientRc.right - clientRc.left;
	int nHeight = clientRc.bottom - clientRc.top;
	pWindow->MessageLoop();
#endif
	return 0;
}


