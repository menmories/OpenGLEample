#include "stdafx.h"
#include "SOpenGLRenderer.h"
#include <assert.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
SOpenGLRenderer::SOpenGLRenderer()
	: m_hdc(NULL)
	, m_hRC(NULL)
{
}


SOpenGLRenderer::~SOpenGLRenderer()
{
}

bool SOpenGLRenderer::Initialize(HWND hWnd)
{
	IRendererBase::Initialize(hWnd);
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	RECT rect = { 0 };
	GetClientRect(hWnd, &rect);
	m_hdc = GetDC(hWnd);
	unsigned pixelFormat;
	pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (!SetPixelFormat(m_hdc, pixelFormat, &pfd))
	{
		return false;
	}
	m_hRC = wglCreateContext(m_hdc);
	if (!wglMakeCurrent(m_hdc, m_hRC))
	{
		return false;
	}
	glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
	//glViewport(0, 0, rect.right - rect.left, rect.bottom - rect.top);
	//GLenum ret = glewInit();
	return true;
}

void SOpenGLRenderer::UnInitialize()
{
	if (m_hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}
	if (m_hdc)
	{
		ReleaseDC(m_hWnd, m_hdc);
		m_hdc = NULL;
	}
	
}

void SOpenGLRenderer::FullScreen()
{
}

void SOpenGLRenderer::BeginScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_CLEAR_VALUE);
	
}

void SOpenGLRenderer::EndScene()
{
	glFinish();
	SwapBuffers(m_hdc);
}
