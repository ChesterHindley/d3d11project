#pragma once
#include <d3d11.h>
#include <wrl/client.h>
class SWAPCHAIN
{
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
private:
public:
	HRESULT initialiseBackBuffer();
	 Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<IDXGISwapChain>> operator&();
	IDXGISwapChain* operator->();
	IDXGISwapChain** GetAddressOf();
	Microsoft::WRL::ComPtr<ID3D11Resource>& getBackBuffer();

};

