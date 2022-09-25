#include "SWAPCHAIN.h"
#include <d3d11.h>
#include <wrl/client.h>
HRESULT SWAPCHAIN::initialiseBackBuffer()
{
    static int check = 0;
    if (check) throw "reinitialised back buffer";  // possibly redundant code
    return swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer) | ++check;  //bruh what is this singleton enforcement
}

 Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<IDXGISwapChain>> SWAPCHAIN::operator&()
{
    return &swapChain;
}

  IDXGISwapChain* SWAPCHAIN::operator->()
{
    return swapChain.operator->();
}

 IDXGISwapChain** SWAPCHAIN::GetAddressOf()
{
    return swapChain.GetAddressOf();
}



Microsoft::WRL::ComPtr<ID3D11Resource>& SWAPCHAIN::getBackBuffer()
{
    return backBuffer;
}

HRESULT SWAPCHAIN::finishDrawing()
{
   auto res = swapChain->Present(1,0);
   if (res != S_OK && res != DXGI_STATUS_OCCLUDED) throw "Failed to present"; // TODO
   return res;
}
