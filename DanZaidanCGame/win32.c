#include "windows.h"
#include "stdint.h"
#include "utils.h"
#include "math.h"
#include "platformCommon.h"

#include "render.c"
#include "game.c"
#include "collision.c"

static LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	switch(uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = 0;
		} break;
		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			renderBuffer.width = rect.right;
			renderBuffer.height = rect.bottom;
			
			if(renderBuffer.pixels) {
				VirtualFree(renderBuffer.pixels, 0, MEM_RELEASE);
			}
			renderBuffer.pixels = VirtualAlloc(0, sizeof (uint32_t) * renderBuffer.width * renderBuffer.height, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			renderBuffer.bitmapInfo.bmiHeader.biSize = sizeof (renderBuffer.bitmapInfo.bmiHeader);
			renderBuffer.bitmapInfo.bmiHeader.biWidth = renderBuffer.width;
			renderBuffer.bitmapInfo.bmiHeader.biHeight = renderBuffer.height;
			renderBuffer.bitmapInfo.bmiHeader.biPlanes = 1;
			renderBuffer.bitmapInfo.bmiHeader.biBitCount = 32;
			renderBuffer.bitmapInfo.bmiHeader.biCompression = BI_RGB;
		} break;
		default: {
			result = DefWindowProcA(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSA wc = {0};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "class name";
	RegisterClassA(&wc);
	HWND hwnd = CreateWindowExA(0, wc.lpszClassName, "Break Out", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 576, 0, 0, 0, 0);
	HDC hdc = GetDC(hwnd);
	Input input = { 0 };
	
	float lastdt = 0.0166f;
	LARGE_INTEGER lastCounter;
	LARGE_INTEGER freqCounter;
	QueryPerformanceCounter(&lastCounter);
	QueryPerformanceFrequency(&freqCounter);

	while (running) {
		for(int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = 0;
		}
		MSG msg;
		while(PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE)) {
			switch(msg.message) {
				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
				case WM_KEYDOWN:
				case WM_KEYUP: {

					uint32_t vkCode = (uint32_t) msg.wParam;
					int wasDown = ((msg.lParam & (1 << 30)) != 0);
					int isDown = ((msg.lParam & (1 << 31)) == 0);

					#define process_button(vk, b)\
					if(vkCode == vk) {\
						input.buttons[b].changed = isDown != input.buttons[b].isDown;\
						input.buttons[b].isDown = isDown;\
					}
					
					process_button(VK_LEFT, BUTTON_LEFT);
					process_button(VK_RIGHT, BUTTON_RIGHT);
					process_button(VK_UP, BUTTON_UP);
					process_button(VK_DOWN, BUTTON_DOWN);
				 } break;
				default: {
					TranslateMessage(&msg);
					DispatchMessageA(&msg);
				}
			}
		}

		POINT mouse;
		GetCursorPos(&mouse);
		ScreenToClient(hwnd, &mouse);
		input.mouse.x = mouse.x;
		input.mouse.y = renderBuffer.height-mouse.y;

		simulateGame(&input, lastdt);
		StretchDIBits(hdc, 0, 0, renderBuffer.width, renderBuffer.height, 0, 0, renderBuffer.width, renderBuffer.height, renderBuffer.pixels, &renderBuffer.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER currentCounter;
		QueryPerformanceCounter(&currentCounter);
		lastdt = (float)((currentCounter.QuadPart - lastCounter.QuadPart) / (float)freqCounter.QuadPart);
		lastCounter = currentCounter;
	}
}
