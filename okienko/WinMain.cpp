#include <Windows.h>
#include "Window.h"
#include <d3d11.h>
#include <wrl/client.h>
#include "Timer.h"
#include "DEVICE.h"
#include "DEVICECONTEXT.h"
#include "SWAPCHAIN.h"
#include "SHADER.h"
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

	struct Vertex { float x; float y; };
	 std::vector<Vertex> vertices {
		{-0.5,-0.5},{0,0.5},{0.5,-0.5},
	};
	 std::vector<int> indices = { 0,1,2 };
	 ID3D11Buffer* vBuffer = nullptr;
	 ID3D11Buffer* indexBuffer = nullptr;
	 dev.createVertexBuffer(vertices, vBuffer);
	 //dev.createIndexBuffer(indices, indexBuffer);
	 //devContext.bindIndexBuffer(indexBuffer);
	 devContext.bindVertexBuffer(vertices.data(), vBuffer);
	 devContext.setTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	 SHADER<ID3D11VertexShader> vertexShader("VertexShader.cso");
	 SHADER<ID3D11PixelShader> pixelShader("PixelShader.cso");

	 auto res = dev->CreateVertexShader(vertexShader.data(), vertexShader.getSize(), NULL, vertexShader.GetAddressOf());
	 devContext->VSSetShader(vertexShader.getShader().Get(), nullptr, 0);

	 
	 res = dev->CreatePixelShader(pixelShader.data(), pixelShader.getSize(), nullptr, pixelShader.GetAddressOf());
	 devContext->PSSetShader(pixelShader.getShader().Get(), nullptr, 0);
	 
	 devContext->OMSetRenderTargets(1, dev.getRenderTargetView().GetAddressOf(), nullptr);
	 D3D11_VIEWPORT vp;
	 vp.Width = width;
	 vp.Height = height;
	 vp.MinDepth = 0;
	 vp.MaxDepth = 1;
	 vp.TopLeftX = 0;
	 vp.TopLeftY = 0;
	 devContext->RSSetViewports(1u, &vp);


	 ID3D11InputLayout* inputLayout;
	 const D3D11_INPUT_ELEMENT_DESC idc[] =
	 {
		 {"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
	 };
	 
		 dev->CreateInputLayout(idc, 1, vertexShader.data(), vertexShader.getSize(), &inputLayout);
		 devContext->IASetInputLayout(inputLayout);


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
	devContext.ChangeColor(dev.getRenderTargetView().Get(), cos(dt), 0.5f, 0.2f);
	devContext->Draw(vertices.size(), 0);  // not my wrapper TODO
	swapChain.finishDrawing();

	}


	vBuffer->Release();
	//indexBuffer->Release();



	
	 return 0;
}