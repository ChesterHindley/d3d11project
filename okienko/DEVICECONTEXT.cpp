#include "DEVICECONTEXT.h"
#include <d3d11.h>
#include <wrl/client.h>
void DEVICECONTEXT::ChangeColor(ID3D11RenderTargetView* pRenderTargetView, float r, float g, float b)
{

	const FLOAT color[4] = {r,g,b,1.f};
	devContext->ClearRenderTargetView(pRenderTargetView, color);
}

void DEVICECONTEXT::setTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	devContext->IASetPrimitiveTopology(topology);
}

void DEVICECONTEXT::bindIndexBuffer(ID3D11Buffer* buffer)
{
	// needs to be created with a ID3D11Device::CreateBuffer
	devContext->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
}

 Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID3D11DeviceContext>> DEVICECONTEXT::operator&()
{
	return devContext.operator&();
}

 ID3D11DeviceContext* DEVICECONTEXT::operator->()
{
	return devContext.operator->();
}

 ID3D11DeviceContext** DEVICECONTEXT::GetAddressOf()
{
	return devContext.GetAddressOf();
}

void DEVICECONTEXT::setInputLayout(ID3D11InputLayout* inputLayout)
{
	// needs to be created with device ID3D11Device::CreateInputLayout
	devContext->IASetInputLayout(inputLayout);


}
