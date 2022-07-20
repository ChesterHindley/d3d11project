#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>
class DEVICE
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView> renderTargetView;
private:
	HRESULT createBuffer(D3D11_BUFFER_DESC* bdc, void* data, __out ID3D11Buffer* buffer);
public:
	HRESULT createIndexBuffer(std::vector<int>* data,__out ID3D11Buffer* indexBuffer);  // could write own class for indexBuffer and vertexBuffer
	HRESULT createVertexBuffer(std::vector<double>* data, __out ID3D11Buffer* vertexBuffer); 
	HRESULT CreateRenderTargetView(ID3D11Resource* backBuffer);
	ID3D11Device* operator->();
	Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID3D11Device>> operator&();
	ID3D11Device** GetAddressOf();

	Microsoft::WRL::ComPtr< ID3D11RenderTargetView>& getRenderTargetView();
};

