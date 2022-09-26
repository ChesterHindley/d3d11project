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
#include "Object.h"
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

	Object obj(gfx);
	
	Timer t;
	MSG msg = { };

	// main event loop
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
			gfx.devContext->DrawIndexed(obj.indicesCount, 0, 0);

			obj.update(w,gfx);
			gfx.swapChain.finishDrawing(); //present
	}

	 return 0;
}