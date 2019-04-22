#include "stdafx.h"
#include "SMainWnd.h"


SMainWnd::SMainWnd()
{
#ifdef __USING_RENDER_OPENGL
	m_pRenderer = new SOpenGLRenderer();
#else
	m_pRenderer = new SD3D11Renderer();
#endif
}


SMainWnd::~SMainWnd()
{
	delete m_pRenderer;
}

void SMainWnd::InitWindow()
{
	m_pRenderer->Initialize(m_hWnd);
}

void SMainWnd::Render()
{
	m_pRenderer->BeginScene();
	m_pRenderer->EndScene();
}

void SMainWnd::Release()
{
#ifdef __USING_RENDER_OPENGL
	m_pRenderer->UnInitialize();
#else
	m_pRenderer->UnInitialize();
#endif
}
