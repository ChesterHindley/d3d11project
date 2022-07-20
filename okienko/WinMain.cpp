#include <Windows.h>
#include "Window.h"
#include <d3d11.h>
#include <wrl/client.h>
#include "Timer.h"
#include "DEVICE.h"
#include "DEVICECONTEXT.h"
#include "SWAPCHAIN.h"

#pragma comment(lib,"D3D11.lib")

namespace wrl = Microsoft::WRL;

int WinMain(
	 HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	 LPSTR     lpCmdLine,
	 int       nShowCmd
)
{
	const int height = 900;
	const int width = 1600;
	Window w(hInstance,height,width);
	


	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferDesc = { 0,0, {0,0}, DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,DXGI_MODE_SCALING_UNSPECIFIED };
	swapChainDesc.SampleDesc = { 1,0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = w.GetHwnd();
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	//wrl::ComPtr< ID3D11Device> dev;
	DEVICE dev;
	//wrl::ComPtr < ID3D11DeviceContext> devContext;
	DEVICECONTEXT devContext;
	//wrl::ComPtr < IDXGISwapChain> swapChain;
	SWAPCHAIN swapChain;
	
	auto check = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG,NULL,0,D3D11_SDK_VERSION,&swapChainDesc,swapChain.GetAddressOf(), dev.GetAddressOf(), NULL, devContext.GetAddressOf());
	
	swapChain.initialiseBackBuffer();
	

	dev.CreateRenderTargetView(swapChain.getBackBuffer().Get());

	const FLOAT color[4] = { 0,0,0.5,1 };

	

	Timer t;
	MSG msg = { };
	while (1)
	{
		PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
		TranslateMessage(&msg);
		DispatchMessage(&msg); // send messsage to windows function
		if (msg.message == WM_QUIT)
			break;

	
	auto dt = t.peek();
	devContext.ChangeColor(dev.getRenderTargetView().Get(), 0.5, 0.5, 0.2);
	swapChain->Present(0, 0); // TODO



	}
	//ID3D11Buffer* vertexBuffer;

	//struct Vertex { float x; float y; };
	// Vertex vertices[3] = {
	//	{-0.5,-0.5},{0,0.5},{0.5,-0.5}
	//};
	//
	//const D3D11_BUFFER_DESC vBufDesc = { sizeof(vertices),D3D11_USAGE_DEFAULT,D3D11_BIND_VERTEX_BUFFER,0,0,sizeof(Vertex) };
	//D3D11_SUBRESOURCE_DATA subData= {};
	//subData.pSysMem = vertices;
	//dev->CreateBuffer(&vBufDesc, &subData, &vertexBuffer); //done
	//const UINT stride = sizeof(Vertex);
	//const UINT offset = 0u;
	//devContext->IASetVertexBuffers(0, 1, &vertexBuffer,&stride,&offset);  //done
	//devContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  //done
	//devContext->IASetIndexBuffer() //done
	//devContext->IASetInputLayout  //done


//	backBuffer->Release();

	return 0;
}