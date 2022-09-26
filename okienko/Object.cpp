#include "Object.h"
#include "SHADER.h"
namespace wrl = Microsoft::WRL;


Object::Object(Graphics& gfx)
	: transform{ { DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(3 / 4.f,1,1)) } }
{

	struct Vertex { float x; float y; float z; float r; float g; float b; };
	std::vector<Vertex> vertices{
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

	indicesCount = indices.size();

	ID3D11Buffer* tempbuf;
	gfx.dev.createVertexBuffer(vertices, tempbuf);
	vBuffer = tempbuf;
	

	gfx.dev.createIndexBuffer(indices, tempbuf);
	iBuffer = tempbuf; // memo leak ? ???? nah don't think so

	gfx.devContext.bindIndexBuffer(iBuffer.Get());
	gfx.devContext.bindVertexBuffer(vertices.data(), vBuffer.Get());

	SHADER<ID3D11VertexShader> vertexShader("VertexShader.cso");
	SHADER<ID3D11PixelShader> pixelShader("PixelShader.cso");


	gfx.dev->CreateVertexShader(vertexShader.data(), vertexShader.getSize(), nullptr, vertexShader.GetAddressOf());
	gfx.devContext->VSSetShader(vertexShader.getShader().Get(), nullptr, 0);


	gfx.dev->CreatePixelShader(pixelShader.data(), pixelShader.getSize(), nullptr, pixelShader.GetAddressOf());
	gfx.devContext->PSSetShader(pixelShader.getShader().Get(), nullptr, 0);




	 // ye thats for vertex data https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11inputlayout
	const D3D11_INPUT_ELEMENT_DESC idc[] =  // tell vshader what is in vertex buffer ?? ???  ? ?
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0} // TODO unorm
	};
	gfx.dev->CreateInputLayout(idc, std::size(idc), vertexShader.data(), vertexShader.getSize(), &inputLayout);  //TODO
	gfx.devContext.bindInputLayout(inputLayout.Get());
	
	gfx.dev.createConstantBuffer(reinterpret_cast<void*>(&transform), sizeof(transform), tempbuf);
	cBuffer = tempbuf;

	gfx.devContext->VSSetConstantBuffers(0, 1, cBuffer.GetAddressOf());


}

void Object::update(Window& w,Graphics& gfx)
{
	D3D11_MAPPED_SUBRESOURCE mappedCBuf = {};
	gfx.devContext.mapResource(cBuffer.Get(), &mappedCBuf);
	transform = {DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationRollPitchYaw(xAngle, yAngle, zAngle) *
				DirectX::XMMatrixScaling(3 / 8.f, 1 / 2.f, 1 / 2.f) *
				DirectX::XMMatrixTranslation(0, 0, 0.4f)) };


	if (w.kbd.isKeyPressed('S'))
		xAngle += 0.05; // TO SIE NIE ZAPISUJE DO TRANSFORM
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
	gfx.devContext.unmapResource(cBuffer.Get());
}
