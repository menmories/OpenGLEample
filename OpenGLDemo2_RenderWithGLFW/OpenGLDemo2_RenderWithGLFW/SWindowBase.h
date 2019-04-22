
#ifndef __SCARAB_WINDOW_BASE_H__
#define __SCARAB_WINDOW_BASE_H__

class SWindowBase
{
public:
	SWindowBase();
	~SWindowBase();
public:
	HWND GetHWND();

	virtual void InitWindow();

	HWND CreateAdjustWindow(LPCTSTR szCaption, int x, int y, int cx, int cy, HWND hParent = NULL, DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, HMENU hMenu = NULL);

	HWND Create(LPCTSTR szCaption, int x, int y, int cx, int cy, HWND hParent = NULL, DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, HMENU hMenu = NULL);

	bool RegistWindowClass();

	BOOL DestroyWindow();

	BOOL GetClientRect(RECT* rect);

	BOOL GetWindowRect(RECT* rect);

	BOOL ShowWindow(int nShow = SW_SHOW);

	void MessageLoop();

	BOOL SetWindowPos(int x, int y, int cx, int cy, HWND hWndInsertAfter = HWND_NOTOPMOST, UINT uFlags = SWP_NOSIZE | SWP_SHOWWINDOW);
protected:
	virtual void Render();

	virtual void Release();

	virtual LPCTSTR GetWindowClassName()const;

	LRESULT ProcessWndMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual BOOL KeyEvents(WPARAM wParam, LPARAM lParam);
private:
	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	HWND m_hWnd;
};

#endif	//__SCARAB_WINDOW_BASE_H__