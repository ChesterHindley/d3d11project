#pragma once
#include "Graphics.h"
#include <wrl/client.h>
#include <DirectXMath.h>
#include "window.h"
class Object
{
private:
	struct ConstantBuffer { DirectX::XMMATRIX transform; };

	Microsoft::WRL::ComPtr<ID3D11Buffer> vBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> iBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> cBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	ConstantBuffer transform;


public:
	int indicesCount;
	float xAngle = 0;
	float yAngle = 0;
	float zAngle = 0;
	Object(Graphics& gfx);
	void update(Window& w,Graphics& gfx);



};

