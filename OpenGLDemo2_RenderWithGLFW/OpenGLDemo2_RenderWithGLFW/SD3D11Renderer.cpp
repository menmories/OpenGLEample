#include "stdafx.h"
#include "SD3D11Renderer.h"
#include <assert.h>

SD3D11Renderer::SD3D11Renderer()
	: m_pContext(NULL)
	, m_pSwapChain(NULL)
	, m_pDevice(NULL)
	, m_pBackBuffer(NULL)
{
}


SD3D11Renderer::~SD3D11Renderer()
{
}

bool SD3D11Renderer::Initialize(HWND hWnd)
{
	IRendererBase::Initialize(hWnd);
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWnd;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode
	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pContext);
	if (FAILED(result))
	{
		return false;
	}

	ID3D11Texture2D* pBackBuffer = NULL;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));
	result = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pBackBuffer);
	if (FAILED(result))
	{
		return false;
	}
	pBackBuffer->Release();
	m_pContext->OMSetRenderTargets(1, &m_pBackBuffer, NULL);

	RECT rect = { 0 };
	GetClientRect(hWnd, &rect);
	D3D11_VIEWPORT viewport = { 0 };
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = rect.right - rect.left;
	viewport.Height = rect.bottom - rect.top;
	m_pContext->RSSetViewports(1, &viewport);	
	return true;
}

void SD3D11Renderer::UnInitialize()
{
	m_pSwapChain->Release();
	m_pContext->Release();
	m_pDevice->Release();
}

void SD3D11Renderer::FullScreen()
{

}

void SD3D11Renderer::BeginScene()
{
	float clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	m_pContext->ClearRenderTargetView(m_pBackBuffer, clearColor);
}

void SD3D11Renderer::EndScene()
{
	m_pSwapChain->Present(0, 0);
}
