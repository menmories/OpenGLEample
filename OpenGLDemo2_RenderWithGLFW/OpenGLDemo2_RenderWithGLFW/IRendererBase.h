#ifndef __IRENDERER_BASE_H__
#define __IRENDERER_BASE_H__


class IRendererBase
{
public:
	IRendererBase();
	~IRendererBase();
public:
	virtual bool Initialize(HWND hWnd);

	virtual void UnInitialize() = 0;

	virtual void FullScreen() = 0;

	virtual void BeginScene() = 0;

	virtual void EndScene() = 0;
protected:
	HWND m_hWnd;
};

#endif	//__IRENDERER_BASE_H__