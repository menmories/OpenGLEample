#pragma once
#include "SWindowBase.h"
#include "SD3D11Renderer.h"
#include "SOpenGLRenderer.h"
class SMainWnd : public SWindowBase
{
public:
	SMainWnd();
	~SMainWnd();
public:
	virtual void InitWindow();

protected:
	virtual void Render();
	virtual void Release();
protected:
#ifdef __USING_RENDER_OPENGL
	SOpenGLRenderer* m_pRenderer;
#else
	SD3D11Renderer* m_pRenderer;
#endif
};

