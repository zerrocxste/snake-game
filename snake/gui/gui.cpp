#include "gui.h"
#include "../defines.h"
#include "../images/images.h"

cGui gui;

HWND hwndWindow;
time_t* pTime;

struct fonts
{
	ImFont* fMain;
}font;

void cGui::ImGuiInit(HWND h, LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	ImGui::CreateContext();

	auto io = ImGui::GetIO();
	font.fMain = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.9f, NULL, io.Fonts->GetGlyphRangesCyrillic());//wtf

	ImGui_ImplWin32_Init(h);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	auto& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(5, 3);
	style.ItemSpacing = ImVec2(6, 2);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.FrameRounding = 0.0f;
	style.IndentSpacing = 6.0f;
	style.ItemInnerSpacing = ImVec2(2, 4);
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 16.0f;
	style.ScrollbarSize = 9.0f;
	style.ScrollbarRounding = 0.0f;
	style.WindowPadding = ImVec2(7, 7);
	this->colorAccent[0] = 1.f, this->colorAccent[1] = 0.f, this->colorAccent[2] = 0.f;
	hwndWindow = h;
	this->flFontSize = 13.9f;	
}

void cGui::DestroyImgui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void cGui::Reset(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

void cGui::Render(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (g_pd3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		g_pd3dDevice->EndScene();
	}

	HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		this->Reset(g_pd3dDevice, g_d3dpp);
	}
}

SIZE GetWindowSize(HWND hwnd)
{
	RECT Rect; SIZE sz;
	GetWindowRect(hwnd, &Rect);
	sz.cx = (Rect.right - Rect.left);
	sz.cy = (Rect.bottom - Rect.top);
	return sz;
}

void setColorTheme(int theme)
{
	auto& style = ImGui::GetStyle();
	if (style.Alpha > 1.f)
		style.Alpha = 1.f;
	else if (style.Alpha != 1.f)
		style.Alpha += 0.01f;
	if (theme == 0)
	{
		style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.81f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.55f, 0.55f, 0.55f, 0.30f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.55f, 0.55f, 0.55f, 0.40f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.55f, 0.55f, 0.55f, 0.45f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.41f, 0.41f, 0.41f, 0.83f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.40f, 0.20f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.57f, 0.57f, 0.57f, 0.87f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.5f, 0.5f, 0.5f, 0.5f); //ImVec4(1.00f, 0.00f, 0.00f, 0.60f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.40f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.45f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.80f); //eto
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f); //eto
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	}
	else
	{
		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(58 / 255.f, 62 / 255.f, 71 / 255.f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(20 / 255.f, 20 / 255.f, 31 / 255.f, 1.0f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(28 / 255.f, 30 / 255.f, 42 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.5f, 0.5f, 0.5f, 0.5f); //ImVec4(0.f, 0.40f, 1.f, 1.f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.f, 0.50f, 1.f, 1.f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.f, 0.30f, 1.f, 1.f);
		style.Colors[ImGuiCol_Header] = ImVec4(74 / 255.f, 87 / 255.f, 109 / 255.f, 1.0f); //multicombo, combo selected item color.
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.f, 0.40f, 1.f, 0.5f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(74 / 255.f, 87 / 255.f, 109 / 255.f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	}
}

int theme = 0;
SIZE wndSz;
bool credits_open = false, setup_game_window = true;
float speed = 0.01f;

void RainbowColor(float colors[3], float speed)
{
	static int counter = 0;

	if (colors[counter] >= 1.0f)
	{
		colors[counter] = 1.0f;
		counter += 1;

		if (counter > 2)
			counter = 0;
	}
	else
	{
		int prev = counter - 1;

		if (prev < 0)
			prev = 2;

		colors[prev] -= speed;
		colors[counter] += speed;
	}
}

namespace game
{
	namespace globals
	{
		constexpr int iFieldSize[2]{ 27, 20 };
	}	
	enum DIRECTION
	{
		NONE, DOWN, LEFT, RIGHT, UP
	};
	struct field_s
	{
		field_s() { x = y = 0; }
		field_s(int x, int y) : x(x), y(y) {};
		void set(field_s a) { x = a.x, y = a.y; }
		void set(int x1, int y1) { x = x1, x = y1; }
		bool operator==(int *a)
		{
			if (x == a[0] && y == a[1])
				return true;

			return false;
		}
		bool operator==(field_s a)
		{
			if (x == a.x && y == a.y)
				return true;

			return false;
		}
		bool operator!=(int *a)
		{
			return !operator==(a);
		}
		bool operator!=(field_s a)
		{
			return !operator==(a);
		}
		DIRECTION Direction;
		int x, y;
	};
	namespace vars
	{
		bool bStopGame;
		field_s fSnakeHead;
		std::vector<field_s>fvSnakeBody;
		int iSnakeArrayLengh;
		/*DIRECTION dSnakeDirection;*/
		int iSnakePoints;
		int iSnakeHistory;
		float flSnakeSpeed; //?
		DWORD dwGameTick;
		field_s fPoint;
		bool bUpdateSnake;
	}
	namespace drawing
	{
		void AddCircle(const ImVec2& position, float radius, const ImColor& color, int segments)
		{
			auto window = ImGui::GetCurrentWindow();

			window->DrawList->AddCircle(position, radius, ImGui::ColorConvertFloat4ToU32(color), segments, 5.f);
		}

		void AddLine(const ImVec2& from, const ImVec2& to, const ImColor& color, float thickness = 1.f)
		{
			auto window = ImGui::GetCurrentWindow();

			window->DrawList->AddLine(from, to, ImGui::ColorConvertFloat4ToU32(color), thickness);
		}

		void AddImage(const ImVec2& position, const ImVec2& size, const ImTextureID pTexture, const ImColor& color)
		{
			auto window = ImGui::GetCurrentWindow();

			ImRect bb(position, ImVec2(position.x + size.x, position.y + size.y));

			window->DrawList->AddImage(pTexture, bb.Min, bb.Max, ImVec2(0.f, 0.f), ImVec2(1.f, 1.f), ImGui::ColorConvertFloat4ToU32(color));
		}

		static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
		{
			return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
		}

		void AddImageRotated(ImVec2 center, ImVec2 size, ImTextureID tex_id, float angle)
		{
			center.x += 15.f;
			center.y += 15.f;

			auto window = ImGui::GetCurrentWindow();

			float cos_a = cosf(angle);
			float sin_a = sinf(angle);
			
			ImVec2 pos[4] =
			{
				center + ImRotate(ImVec2(-size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
				center + ImRotate(ImVec2(+size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
				center + ImRotate(ImVec2(+size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a),
				center + ImRotate(ImVec2(-size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a)
			};
			ImVec2 uvs[4] =
			{
				ImVec2(0.0f, 0.0f),
				ImVec2(1.0f, 0.0f),
				ImVec2(1.0f, 1.0f),
				ImVec2(0.0f, 1.0f)
			};

			window->DrawList->AddImageQuad(tex_id, pos[0], pos[1], pos[2], pos[3], uvs[0], uvs[1], uvs[2], uvs[3], IM_COL32_WHITE);
		}

		void AddСross(const ImVec2& position, ImColor col, const int iLineSize)
		{
			AddLine(ImVec2(position[0] - iLineSize, position[1] - iLineSize), ImVec2(position[0] + iLineSize, position[1] + iLineSize), col, 5.f);
			AddLine(ImVec2(position[0] + iLineSize, position[1] - iLineSize), ImVec2(position[0] - iLineSize, position[1] + iLineSize), col, 5.f);
		}	

		void AddRectFilled(const ImVec2& position, const ImVec2& size, const ImColor& color, float rounding = 0.f)
		{
			auto window = ImGui::GetCurrentWindow();

			window->DrawList->AddRectFilled(position, size, ImGui::ColorConvertFloat4ToU32(color), rounding);
		}

		void AddRect(const ImVec2& position, const ImVec2& size, const ImColor& color, float rounding = 0.f)
		{
			auto window = ImGui::GetCurrentWindow();

			window->DrawList->AddRect(position, size, ImGui::ColorConvertFloat4ToU32(color), rounding);
		}

		void DrawFillArea(float x, float y, float w, float h, const ImColor& color)
		{
			AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color);
		}

		void DrawBox(float x, float y, float w, float h, const ImColor& color)
		{
			AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color);
		}
	}
	namespace input
	{
		void InputControlSnake()
		{
			INIT(vars::fSnakeHead.Direction = UP)

			if (GetAsyncKeyState(VK_UP) && 
				field_s(vars::fSnakeHead.x, vars::fSnakeHead.y - 1) != vars::fvSnakeBody[1]) vars::fSnakeHead.Direction = UP;
			if (GetAsyncKeyState(VK_DOWN) && 
				field_s(vars::fSnakeHead.x, vars::fSnakeHead.y + 1) != vars::fvSnakeBody[1]) vars::fSnakeHead.Direction = DOWN;
			if (GetAsyncKeyState(VK_LEFT) && 
				field_s(vars::fSnakeHead.x - 1, vars::fSnakeHead.y) != vars::fvSnakeBody[1]) vars::fSnakeHead.Direction = LEFT;
			if (GetAsyncKeyState(VK_RIGHT) && 
				field_s(vars::fSnakeHead.x + 1, vars::fSnakeHead.y) != vars::fvSnakeBody[1]) vars::fSnakeHead.Direction = RIGHT;
		}
	}
	namespace utils
	{
		float GetRoute(DIRECTION dir)
		{
			float angle = 0.f;
			switch (dir)
			{
			case game::DOWN:
				angle = 3.125;
				break;
			case game::LEFT:
				angle = 4.6875f;
				break;
			case game::RIGHT:
				angle = 1.5625f;
				break;
			case game::UP:
				angle = 0.f;
				break;
			}
			return angle;
		}
		float getRouteForRound(DIRECTION dirUP, DIRECTION dirDOWN)
		{
			float angle = 0.f;

			if (dirUP == DIRECTION::LEFT && dirDOWN == DIRECTION::UP)
				angle = 4.6875f;

			return angle;
		}
	}
	namespace rules
	{
		void ClearGameData()
		{
			vars::fPoint.set(field_s());
			vars::fSnakeHead.set(field_s(globals::iFieldSize[0] / 2, globals::iFieldSize[1] - 2));
			vars::flSnakeSpeed = 800.f;
			vars::iSnakePoints = 0;
			vars::fSnakeHead.Direction = UP;
		}
		bool FindingExitFromPlayingZone()
		{
			if (vars::fSnakeHead.x > (globals::iFieldSize[0] - 1) || vars::fSnakeHead.x < 1
				|| vars::fSnakeHead.y > (globals::iFieldSize[1] - 1) || vars::fSnakeHead.y < 1)
			{
				return true;
			}			

			return false;
		}
		bool FindingCollisionSnakeBody()
		{
			for (int i = 0; i < vars::iSnakePoints; i++)
			{
				if (vars::fSnakeHead == vars::fvSnakeBody[i + 1])
				{
					return true;
				}
			}
			return false;
		}
		void UpdateGameTick()
		{
			if (!vars::bStopGame)
			{
				if (vars::bUpdateSnake && GetTickCount() - vars::dwGameTick > vars::flSnakeSpeed)
				{
					vars::bUpdateSnake = false;
				}
				else if (!vars::bUpdateSnake)
				{
					vars::bUpdateSnake = true;
				}
			}
		}
		void UpdateSnakeMovement()
		{
			if (!vars::bStopGame)
			{
				if (!vars::bUpdateSnake)
				{
					if (vars::fSnakeHead.Direction == UP) vars::fSnakeHead.y -= 1;
					else if (vars::fSnakeHead.Direction == DOWN) vars::fSnakeHead.y += 1;
					else if (vars::fSnakeHead.Direction == LEFT) vars::fSnakeHead.x -= 1;
					else if (vars::fSnakeHead.Direction == RIGHT) vars::fSnakeHead.x += 1;
					vars::iSnakeHistory++;
					vars::dwGameTick = GetTickCount();
				}
			}
		}
		void SnakeHistoryCollector()
		{
			if (!vars::bUpdateSnake)
			{
				std::vector<field_s>temp;
				temp = vars::fvSnakeBody;
				std::reverse(std::begin(temp), std::end(temp));
				temp.push_back(vars::fSnakeHead);
				std::reverse(std::begin(temp), std::end(temp));
				vars::fvSnakeBody = temp;
			}			
		}
		void SetPointPosition()
		{
			int null[2] = { 0, 0 };
			if (vars::fPoint == null)
			{
				srand(time(pTime));
				int xResult = rand() % (globals::iFieldSize[0] - 1) + 1;
				int yResult = rand() % (globals::iFieldSize[1] - 1) + 1;
				if (vars::iSnakePoints > 0)
				{
					for (int i = 0; i < vars::iSnakePoints; i++)
					{
						if (field_s(xResult, yResult) != vars::fvSnakeBody[i])
						{
							vars::fPoint.x = xResult;
							vars::fPoint.y = yResult;
						}
					}
				}
				else
				{
					vars::fPoint.x = xResult;
					vars::fPoint.y = yResult;
				}						
			}
		}		
	}

	void RunOverlayDrawing()
	{	   
		auto DrawSectionRectFilled = [](const ImVec2& position, const ImVec2& size, const ImColor col)
		{
			drawing::DrawFillArea(position.x, position.y, size.x, size.y, col);
			drawing::DrawBox(position.x, position.y, size.x, size.y, ImColor(0.3f, 0.3f, 0.3f));
		};

		//drawing::AddImage(ImVec2(), ImVec2(200, 200), images::pmTextureData["pd3dtxBackground"], ImColor(255, 255, 255));

		//поле
		for (int x = 1; x < globals::iFieldSize[0]; ++x)
		{		
			for (int y = 1; y < globals::iFieldSize[1]; ++y)
			{
				ImVec2 pos = { (30.f * x) - 20.f, 30.f * y };

				ImColor CellColor = { 0.f, 0.7f, 0.5f };

				if (field_s(x, y) == vars::fPoint) 
					CellColor = ImColor(0.f, 0.5f, 0.7f); //point

				DrawSectionRectFilled(pos, ImVec2(30.f, 30.f), CellColor);

				if (field_s(x, y) == vars::fSnakeHead)
				{
					DrawSectionRectFilled(pos, ImVec2(30.f, 30.f), ImColor(255, 128, 0));
				}

				for (int i = 0; i < vars::iSnakePoints; i++)
				{
					if (field_s(x, y) == vars::fvSnakeBody[i + 1])
					{
						DrawSectionRectFilled(pos, ImVec2(30.f, 30.f), ImColor(255, 166, 0));
					}
				}

				//if (field_s(x, y) == vars::fSnakeHead)
				//{
				//	drawing::AddImageRotated(pos, ImVec2(30.f, 30.f), images::pmTextureData["pd3dtxSnakeHead"],
				//		utils::GetRoute(vars::fSnakeHead.Direction)); /*0.f - 6.25f*/
				//}
				/*if (vars::iSnakePoints > 1)
				{
					for (int i = 0; i < vars::iSnakePoints; i++)
					{
						if (field_s(x, y) == vars::fvSnakeBody[i + 1])
						{
							if (vars::fvSnakeBody[i].Direction != vars::fvSnakeBody[i - 1].Direction)
								drawing::AddImageRotated(pos, ImVec2(30.f, 30.f), images::pmTextureData["pd3dtxSnakeBody"],
									utils::GetRoute(vars::fvSnakeBody[i].Direction));
							else
								drawing::AddImageRotated(pos, ImVec2(30.f, 30.f), images::pmTextureData["pd3dtxSnakeRound"],
									utils::GetRoute(vars::fvSnakeBody[vars::iSnakePoints].Direction));
						}		
					}
				}			
				if (vars::iSnakePoints > 0)
				{
					if (field_s(x, y) == vars::fvSnakeBody[vars::iSnakePoints])
					{
						DIRECTION check_for = vars::iSnakePoints == 0 ? vars::fSnakeHead.Direction : vars::fvSnakeBody[vars::iSnakePoints - 1].Direction;
						if (vars::fvSnakeBody[vars::iSnakePoints].Direction == check_for)
							drawing::AddImageRotated(pos, ImVec2(30.f, 30.f), images::pmTextureData["pd3dtxSnakeTail"],
								utils::GetRoute(vars::fvSnakeBody[vars::iSnakePoints].Direction));
						else
							drawing::AddImageRotated(pos, ImVec2(30.f, 30.f), images::pmTextureData["pd3dtxSnakeRound"],
								utils::getRouteForRound(check_for, vars::fvSnakeBody[vars::iSnakePoints].Direction));
					}
				}*/			
			}		
		}

		if (vars::fSnakeHead == vars::fPoint)
		{
			float delta = vars::flSnakeSpeed / 40.f;
			vars::flSnakeSpeed -= delta;
			vars::fPoint.set(field_s());
			vars::iSnakePoints++;
		}
	}

	void RunGame()
	{
		INIT
		(
			vars::fSnakeHead.set(field_s(globals::iFieldSize[0] / 2, globals::iFieldSize[1] - 1));
			vars::flSnakeSpeed = 800.f;
		)			

		ImGui::SetNextWindowPos(ImVec2(0.f, 20.f), ImGuiCond_Always, ImVec2(0.f, 0.f));
		ImGui::SetNextWindowSize(ImVec2(wndSz.cx - 16, wndSz.cy - 55));
		ImGuiWindowFlags WndFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus;
		ImGui::Begin("##Background", nullptr, WndFlags);
		ImGui::End();
		
		input::InputControlSnake();
		rules::UpdateGameTick();
		rules::UpdateSnakeMovement();	
		rules::SnakeHistoryCollector();
		rules::SetPointPosition();

		if (rules::FindingExitFromPlayingZone() || rules::FindingCollisionSnakeBody())
			rules::ClearGameData();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4());
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::Begin("##BackBuffer", nullptr, ImVec2(), 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings);
		ImGui::SetWindowPos(ImVec2(), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		RunOverlayDrawing(); 
		ImGui::GetCurrentWindow()->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();		
	}
}

void cGui::GuiLoop()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::PushFont(font.fMain);

	setColorTheme(theme);

	wndSz = GetWindowSize(hwndWindow);

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu(u8"Игра"))
		{
			if (ImGui::MenuItem(u8"Новая игра")) { game::rules::ClearGameData(); }
			if (ImGui::MenuItem(u8"Выход", u8"Alt+F4")) { ExitProcess(0); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"Справка"))
		{
			if (ImGui::MenuItem(u8"О программе")) { credits_open = true; }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	game::RunGame();

	if (credits_open)
	{
		ImGui::SetNextWindowPos(ImVec2((wndSz.cx - 16) / 2.f - 105.5f, (wndSz.cy - 55) / 2.f - 20), ImGuiCond_Always, ImVec2(0.f, 0.f));

		ImGuiWindowFlags ThreeWndFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

		ImGui::Begin(u8"О программе", &credits_open, ThreeWndFlags);
		ImGui::Text(u8"Змейка, 2D20");
		ImGui::Text(u8"Посвещается самой красивой девушке!");
		ImGui::Text(u8"Люблю тебя!!!");
		credits_open = ImGui::IsAnyWindowHovered();

		ImGui::End();
	}

	ImGui::PopFont();

	ImGui::EndFrame();
}