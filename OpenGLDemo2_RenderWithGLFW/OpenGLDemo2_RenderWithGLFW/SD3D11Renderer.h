
#ifndef __SCARAB_D3D11_RENDERER_H__
#define __SCARAB_D3D11_RENDERER_H__
#include "IRendererBase.h"
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11.lib")
//#pragma comment (lib, "d3dx11.lib")
//#pragma comment (lib, "d3dx10.lib")
class SD3D11Renderer : public IRendererBase
{
public:
	SD3D11Renderer();
	~SD3D11Renderer();
public:
	virtual bool Initialize(HWND hWnd);

	virtual void UnInitialize();

	virtual void FullScreen();

	virtual void BeginScene();

	virtual void EndScene();
protected:
	ID3D11DeviceContext* m_pContext;
	IDXGISwapChain *m_pSwapChain;
	ID3D11Device* m_pDevice;
	ID3D11RenderTargetView* m_pBackBuffer;
};

#endif	//__SCARAB_D3D11_RENDERER_H__