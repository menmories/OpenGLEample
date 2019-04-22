#include "stdafx.h"
#include "SWindowBase.h"
#include <assert.h>

SWindowBase::SWindowBase()
{
}


SWindowBase::~SWindowBase()
{
}

HWND SWindowBase::GetHWND()
{
	return m_hWnd;
}

void SWindowBase::InitWindow()
{

}

HWND SWindowBase::CreateAdjustWindow(LPCTSTR szCaption, int x, int y, int cx, int cy, HWND hParent, DWORD dwStyle, HMENU hMenu)
{
	RECT rect = { x, y, x + cx, y + cy };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	return Create(szCaption, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hParent, dwStyle, hMenu);
}

HWND SWindowBase::Create(LPCTSTR szCaption, int x, int y, int cx, int cy, HWND hParent, DWORD dwStyle, HMENU hMenu)
{
	if (!RegistWindowClass())
	{
		return NULL;
	}
	m_hWnd = ::CreateWindowEx(NULL, GetWindowClassName(), szCaption, dwStyle, x, y, cx, cy, hParent, NULL, GetModuleHandle(NULL), this);
	return m_hWnd;
}


bool SWindowBase::RegistWindowClass()
{
	WNDCLASS wc = { 0 };
	wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.lpfnWndProc = SWindowBase::__WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GetWindowClassName();
	ATOM ret = ::RegisterClass(&wc);
	assert(ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);
	return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

BOOL SWindowBase::DestroyWindow()
{
	return ::DestroyWindow(m_hWnd);
}

BOOL SWindowBase::GetClientRect(RECT * rect)
{
	return ::GetClientRect(m_hWnd, rect);
}

BOOL SWindowBase::GetWindowRect(RECT * rect)
{
	return ::GetWindowRect(m_hWnd, rect);
}

LRESULT SWindowBase::ProcessWndMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		InitWindow();
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow();
		break;
	}
	case WM_PAINT:
	{
		Render();
		break;
	}
	case WM_KEYDOWN:
	{
		if (!KeyEvents(wParam, lParam))
		{
			return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		}
		break;
	}
	case WM_DESTROY:
	{
		::PostQuitMessage(0);
		break;
	}
	case WM_QUIT:
	{
		Release();
		return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}
	default:
		return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}
	return FALSE;
}

BOOL SWindowBase::ShowWindow(int nShow)
{
	return ::ShowWindow(m_hWnd, nShow);
}

void SWindowBase::MessageLoop()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Render();
	}
}

BOOL SWindowBase::SetWindowPos(int x, int y, int cx, int cy, HWND hWndInsertAfter, UINT uFlags)
{
	return ::SetWindowPos(m_hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
}

void SWindowBase::Render()
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(m_hWnd, &ps);

	::EndPaint(m_hWnd, &ps);
}

void SWindowBase::Release()
{
}

LPCTSTR SWindowBase::GetWindowClassName() const
{
	return LPCTSTR(TEXT("SWindowBase"));
}

BOOL SWindowBase::KeyEvents(WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT SWindowBase::__WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SWindowBase* pThis = NULL;
	if (uMsg == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = static_cast<SWindowBase*>(lpcs->lpCreateParams);
		pThis->m_hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
	}
	else {
		pThis = reinterpret_cast<SWindowBase*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
	if (pThis != NULL) 
	{
		return pThis->ProcessWndMessage(uMsg, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}
