#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>
class DEVICE
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView> renderTargetView; // shouldn't really be here maybe in swapChain
private:
	HRESULT createBuffer(D3D11_BUFFER_DESC* bdc, void* data, __out ID3D11Buffer*& buffer);
public:
	HRESULT createIndexBuffer(std::vector<int>& data,__out ID3D11Buffer*& indexBuffer);  // could write own class for indexBuffer and vertexBuffer
	HRESULT CreateRenderTargetView(ID3D11Resource* backBuffer);
	ID3D11Device* operator->();
	Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID3D11Device>> operator&();
	ID3D11Device** GetAddressOf();

	Microsoft::WRL::ComPtr< ID3D11RenderTargetView>& getRenderTargetView();

	template<class T>
	HRESULT createVertexBuffer(std::vector<T>& data, __out ID3D11Buffer*& vertexBuffer)
	{
		D3D11_BUFFER_DESC bdc = {};
		bdc.ByteWidth = (UINT)data.size()*sizeof(T);//  Size of the buffer in bytes.
		bdc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		bdc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		bdc.CPUAccessFlags = 0;
		bdc.MiscFlags = 0;
		bdc.StructureByteStride = sizeof(T);

		return createBuffer(&bdc, data.data(), vertexBuffer);
	}


	HRESULT createConstantBuffer(void* data, std::size_t size, __out ID3D11Buffer*& constantBuffer);


};

