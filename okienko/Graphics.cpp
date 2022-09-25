#include "Graphics.h"

Graphics::Graphics(Window& w)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferDesc = { 0,0, {0,0}, DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,DXGI_MODE_SCALING_UNSPECIFIED };
	swapChainDesc.SampleDesc = { 1,0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = w.GetHwnd();
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;


	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		D3D11_CREATE_DEVICE_DEBUG, NULL, 0, D3D11_SDK_VERSION,
		&swapChainDesc, swapChain.GetAddressOf(), dev.GetAddressOf(),
		NULL, devContext.GetAddressOf());

	swapChain.initialiseBackBuffer();

	dev.CreateRenderTargetView(swapChain.getBackBuffer().Get());  //bruh what is this 

	devContext->OMSetRenderTargets(1, dev.getRenderTargetView().GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp {0};
	vp.Width = static_cast<FLOAT>(w.getWidth());
	vp.Height = static_cast<FLOAT>(w.getHeight());
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	devContext->RSSetViewports(1u, &vp);

	devContext.setTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);





}