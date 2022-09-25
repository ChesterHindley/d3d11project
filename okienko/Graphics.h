#pragma once
#include <d3d11.h>
#include "DEVICE.h"
#include "DEVICECONTEXT.h"
#include "SWAPCHAIN.h"
#include "Window.h"
class Graphics
{
	


public:
	Graphics(Window& window);
	DEVICE dev;
	DEVICECONTEXT devContext;
	SWAPCHAIN swapChain;




};

