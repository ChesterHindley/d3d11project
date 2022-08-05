#include <Windows.h>
#include "Window.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "Timer.h"
#include "DEVICE.h"
#include "DEVICECONTEXT.h"
#include "SWAPCHAIN.h"
#include "SHADER.h"

#pragma comment(lib,"D3D11.lib")


namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

int WinMain(
	 HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	 LPSTR     lpCmdLine,
	 int       nShowCmd
)
{
	const int height = 900;
	const int width = 900;


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

	DEVICE dev;
	DEVICECONTEXT devContext;
	SWAPCHAIN swapChain;
	auto check = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG,NULL,0,D3D11_SDK_VERSION,&swapChainDesc,swapChain.GetAddressOf(), dev.GetAddressOf(), NULL, devContext.GetAddressOf());
	
	swapChain.initialiseBackBuffer();
	
	dev.CreateRenderTargetView(swapChain.getBackBuffer().Get());  //bruh what is this 

	const FLOAT color[4] = { 0,0,0.5,1 }; // what is this for

	struct Vertex { float x; float y; float z; float r; float g; float b; };
	 std::vector<Vertex> vertices {
		{-0.5,-0.5,0.5,1,0,0},
		 {0,0.5,0,0,1,0},
		 {0.5,-0.5,0.5,0,0,1},
		 {0,-0.5,-0.5,1,0,1},
	};
	   std::vector<int> indices = 
	   { 
		   0,1,2,
		   0,3,1,
		   2,1,3,
		   2,3,0,
	   };

	 ID3D11Buffer* vBuffer = nullptr;
	 ID3D11Buffer* indexBuffer = nullptr;
	 dev.createVertexBuffer(vertices, vBuffer);
	 dev.createIndexBuffer(indices, indexBuffer);
	 devContext.bindIndexBuffer(indexBuffer);
	 devContext.bindVertexBuffer(vertices.data(), vBuffer);
	 devContext.setTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	 SHADER<ID3D11VertexShader> vertexShader("VertexShader.cso");
	 SHADER<ID3D11PixelShader> pixelShader("PixelShader.cso");

	 dev->CreateVertexShader(vertexShader.data(), vertexShader.getSize(), nullptr, vertexShader.GetAddressOf());
	 devContext->VSSetShader(vertexShader.getShader().Get(), nullptr, 0);

	 
	 dev->CreatePixelShader(pixelShader.data(), pixelShader.getSize(), nullptr, pixelShader.GetAddressOf());
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
	 const D3D11_INPUT_ELEMENT_DESC idc[] =  // tell vshader what is in vertex buffer ?? ???  ? ?
	 {
		 {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		 {"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	 };
		 auto res = dev->CreateInputLayout(idc, std::size(idc), vertexShader.data(), vertexShader.getSize(), &inputLayout);  //TODO
		 devContext.bindInputLayout(inputLayout); 


		 struct ConstantBuffer
		 {
			 dx::XMMATRIX transform;
		 };

		 ConstantBuffer transform = { dx::XMMatrixTranspose(dx::XMMatrixScaling(3 / 4.f,1,1)) };
		 ID3D11Buffer* cBuffer;
		 dev.createConstantBuffer(reinterpret_cast<void*>(& transform),sizeof(transform), cBuffer);
		 devContext->VSSetConstantBuffers(0, 1, &cBuffer);  

	Timer t;
	MSG msg = { };

	// main event loop
	while (1)
	{
		PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
			TranslateMessage(&msg);
			DispatchMessage(&msg); // send messsage to windows function
			if (msg.message == WM_QUIT)
				break;
			 // graphics main loop
			auto dt = t.peek();

			devContext.ChangeColor(dev.getRenderTargetView().Get(), cos(dt), 0.5f, 0.2f);
			devContext->DrawIndexed(indices.size(), 0, 0);

			D3D11_MAPPED_SUBRESOURCE mappedCBuf = {};
			devContext.mapResource(cBuffer, &mappedCBuf);
			transform = { dx::XMMatrixTranspose(dx::XMMatrixRotationRollPitchYaw(dt,0,0) * dx::XMMatrixScaling(3 / 4.f ,1,1))};
			memcpy(mappedCBuf.pData, &transform, sizeof(transform));
			devContext.unmapResource(cBuffer);
			
			swapChain.finishDrawing();

	}

	cBuffer->Release();
	vBuffer->Release();
	inputLayout->Release();
	indexBuffer->Release();




	
	 return 0;
}