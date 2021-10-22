#include "helpers.h"
#include "defines.h"
#include "gui/gui.h"
#include "wndproc.h"
#include "images/images.h"
#include "resource.h"

#include "snake.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	helpers::window::RegMyWindowClass(hInstance, WindowName, IDI_ICON1);

	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	int x = screen_rect.right / 2 - (WindowSizeX / 2.f);
	int y = screen_rect.bottom / 2 - (WindowSizeY / 2.f);

	HWND hWnd = CreateWindow
	(
		WindowName, _T(WindowName), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX /*| WS_SIZEBOX | WS_MAXIMIZEBOX*/,
		x, y, WindowSizeX + 16, WindowSizeY + 20, NULL, NULL, hInstance, NULL
	);

	if (!hWnd)
		return 2;

	helpers::d3d::init(hWnd, hInstance);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	helpers::console::attach("debug");

	gui.ImGuiInit(hWnd, g_pd3dDevice);

	images::Initialization(g_pd3dDevice);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		//auto& io = ImGui::GetIO();
		//pos_mouse_t.x = io.MousePos.x;
		//pos_mouse_t.y = io.MousePos.y;

		gui.GuiLoop();

		gui.Render(g_pd3dDevice, g_d3dpp);
	}

	gui.DestroyImgui();

	helpers::console::detach();

	helpers::d3d::destoy();

	DestroyWindow(hWnd);
	UnregisterClass(WindowName, hInstance);

	return 0;
}