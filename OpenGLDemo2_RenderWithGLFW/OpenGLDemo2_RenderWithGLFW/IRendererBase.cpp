#include "stdafx.h"
#include "IRendererBase.h"
#include <assert.h>

IRendererBase::IRendererBase()
	: m_hWnd(NULL)
{
}


IRendererBase::~IRendererBase()
{
}

bool IRendererBase::Initialize(HWND hWnd)
{
	assert(IsWindow(hWnd));
	m_hWnd = hWnd;
	return true;
}
