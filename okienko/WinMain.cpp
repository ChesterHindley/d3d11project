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
#include "Graphics.h"

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
	Graphics gfx(w);


	
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
	   gfx.dev.createVertexBuffer(vertices, vBuffer);
	   gfx.dev.createIndexBuffer(indices, indexBuffer);
	   gfx.devContext.bindIndexBuffer(indexBuffer);
	   gfx.devContext.bindVertexBuffer(vertices.data(), vBuffer); 

	   
	 // load compiled shader bytecode
	 SHADER<ID3D11VertexShader> vertexShader("VertexShader.cso");
	 SHADER<ID3D11PixelShader> pixelShader("PixelShader.cso");

	 gfx.dev->CreateVertexShader(vertexShader.data(), vertexShader.getSize(), nullptr, vertexShader.GetAddressOf());
	 gfx.devContext->VSSetShader(vertexShader.getShader().Get(), nullptr, 0);

	 
	 gfx.dev->CreatePixelShader(pixelShader.data(), pixelShader.getSize(), nullptr, pixelShader.GetAddressOf());
	 gfx.devContext->PSSetShader(pixelShader.getShader().Get(), nullptr, 0);
	 



	 ID3D11InputLayout* inputLayout; // ye thats for vertex data https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11inputlayout
	 const D3D11_INPUT_ELEMENT_DESC idc[] =  // tell vshader what is in vertex buffer ?? ???  ? ?
	 {
		 {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		 {"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0} // TODO unorm
	 };
		 gfx.dev->CreateInputLayout(idc, std::size(idc), vertexShader.data(), vertexShader.getSize(), &inputLayout);  //TODO
		 gfx.devContext.bindInputLayout(inputLayout); 


		 struct ConstantBuffer
		 {
			 dx::XMMATRIX transform;
		 };

		 ConstantBuffer transform = { dx::XMMatrixTranspose(dx::XMMatrixScaling(3 / 4.f,1,1)) };
		 ID3D11Buffer* cBuffer;
		 gfx.dev.createConstantBuffer(reinterpret_cast<void*>(& transform),sizeof(transform), cBuffer);
		 gfx.devContext->VSSetConstantBuffers(0, 1, &cBuffer);  

	Timer t;
	MSG msg = { };

	// main event loop
	float xAngle = 0;
	float yAngle = 0;
	float zAngle = 0;
	while (true)
	{
		PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
			TranslateMessage(&msg);
			DispatchMessage(&msg); // send messsage to windows function
			if (msg.message == WM_QUIT)
				break;
			 // graphics main loop
			auto dt = t.peek();

			gfx.devContext.ChangeColor(gfx.dev.getRenderTargetView().Get(), 0, 0, 0);
			gfx.devContext->DrawIndexed(indices.size(), 0, 0);

			D3D11_MAPPED_SUBRESOURCE mappedCBuf = {};
			gfx.devContext.mapResource(cBuffer, &mappedCBuf);
			transform = { dx::XMMatrixTranspose(dx::XMMatrixRotationRollPitchYaw(xAngle,yAngle,zAngle) * dx::XMMatrixScaling(3 / 8.f ,1/2.f,1/2.f) * dx::XMMatrixTranslation(0,0,0.4f))};
			if (w.kbd.isKeyPressed('S'))
				xAngle += 0.05;
			if (w.kbd.isKeyPressed('W'))
				xAngle -= 0.05;
			if (w.kbd.isKeyPressed('A'))
				yAngle += 0.05;
			if (w.kbd.isKeyPressed('D'))
				yAngle -= 0.05;
			if (w.kbd.isKeyPressed(' '))
			{
				xAngle = 0;
				yAngle = 0;
				zAngle = 0;
			}

			memcpy(mappedCBuf.pData, &transform, sizeof(transform));
			gfx.devContext.unmapResource(cBuffer);
			
			gfx.swapChain.finishDrawing();

	}

	cBuffer->Release();
	vBuffer->Release();
	inputLayout->Release();
	indexBuffer->Release();




	
	 return 0;
}