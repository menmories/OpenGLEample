#pragma once
#include <GL/GL.h>
#include <GL/GLU.h>
#include "IRendererBase.h"
class SOpenGLRenderer : public IRendererBase
{
public:
	SOpenGLRenderer();
	~SOpenGLRenderer();
public:
	virtual bool Initialize(HWND hWnd);

	virtual void UnInitialize();

	virtual void FullScreen();

	virtual void BeginScene();

	virtual void EndScene();

protected:
	HDC m_hdc;
	HGLRC m_hRC;
};

