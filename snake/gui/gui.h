#pragma once

#include "../snake.h"

class cGui
{
private:
	int x1, y1;
	float colorAccent[3];
	float flFontSize;
	bool bResetFont;
public:
	void ImGuiInit(HWND h, LPDIRECT3DDEVICE9 g_pd3dDevice);
	void DestroyImgui();
	void Reset(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp);
	void Render(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp);
	void GuiLoop();
	void setPos(int x, int y) { x1 = x, y1 = y; }
};
extern cGui gui;