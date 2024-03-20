#pragma once
#include "render.h"
#include "custom/icons.h"
#define MYCLASSNAME    TEXT("CiceroUIWndFrame")
#define MYWINDOWNAME   TEXT("CiceroUIWndFrame")

using Overlay::DXOverlay;

int ImGui_DX9Init;




WNDCLASSEX DXOverlay::wcex = { 0 };
MARGINS DXOverlay::Margin = { -1 };
HINSTANCE DXOverlay::InjectedModule;

HWND DXOverlay::pOverlay;
RECT DXOverlay::Rect;
BOOL DXOverlay::MenuAim;
BOOL DXOverlay::MenumemoryAim;

INT DXOverlay::width;
INT DXOverlay::height;
INT DXOverlay::widthD2;
INT DXOverlay::heightD2;

INT DXOverlay::KeyValue = 0;
INT DXOverlay::MenuKeyValue = 0;
BOOL DXOverlay::KeyHeld = FALSE;

BOOL DXOverlay::MenuKeyClicked = FALSE;
BOOL DXOverlay::MenuKeyDown = FALSE;
BOOL DXOverlay::ShowMenu = TRUE;
BOOL DXOverlay::SinglePress = FALSE;
BOOL DXOverlay::Layered = false;

auto timeOld = std::chrono::high_resolution_clock::now();
auto timeNow = std::chrono::high_resolution_clock::now();
auto OverlayfpsClock = std::chrono::high_resolution_clock::now();

INT DXOverlay::OverlayFps = 999;
INT DXOverlay::OverlayRenderCount = 0;

ID3D11Device* DXOverlay::pDevice = nullptr;
ID3D11DeviceContext* DXOverlay::PDeviceContext = nullptr;
IDXGISwapChain* DXOverlay::pSwapChain = nullptr;
ID3D11RenderTargetView* DXOverlay::pRenderTarget = nullptr;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT pMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, pMsg, wParam, lParam) && menu_open)
		return TRUE;
	return DefWindowProc(hWnd, pMsg, wParam, lParam);
}
BOOL DXOverlay::InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig fontConfig;
	fontConfig.RasterizerMultiply = 1.4f;

	/*io.Fonts->AddFontFromMemoryTTF((void*)fontBinaryzz1, sizeof(fontBinaryzz1),
		15.f, &fontConfig, io.Fonts->GetGlyphRangesCyrillic());
	icons = io.Fonts->AddFontFromMemoryTTF((void*)iconsBinary, sizeof(iconsBinary),
		20, &fontConfig, io.Fonts->GetGlyphRangesCyrillic());
	font_main = io.Fonts->AddFontFromMemoryCompressedTTF(pixel_compressed_data, pixel_compressed_size,
		10.f, &fontConfig, io.Fonts->GetGlyphRangesCyrillic());*/
	io.Fonts->AddFontFromMemoryTTF((void*)fntahoma, sizeof(fntahoma),
		15.f, &fontConfig, io.Fonts->GetGlyphRangesCyrillic());
	


	ImVec2 pos;
	ImGui::StyleColorsClassic();
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 0.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 0.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 0.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 0.0f;

	style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_TextDisabled] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_WindowBg] = ImColor(30, 30, 30, 255);
	style->Colors[ImGuiCol_PopupBg] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_Border] = ImColor(255, 0, 255, 255);
	style->Colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_FrameBg] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(90, 90, 90, 255);
	style->Colors[ImGuiCol_TitleBg] = ImColor(30, 30, 30, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(30, 30, 30, 255);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(30, 30, 30, 255);
	style->Colors[ImGuiCol_MenuBarBg] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ScrollbarBg] = ImColor(100, 100, 100, 255);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(60, 60, 60, 255);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(80, 80, 80, 255);
	style->Colors[ImGuiCol_CheckMark] = ImColor(0, 255, 255, 255);
	style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_Button] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 255);
	style->Colors[ImGuiCol_Header] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_ResizeGrip] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_ResizeGripActive] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PlotLines] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PlotHistogram] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImColor(255, 255, 255, 255);
	style->Colors[ImGuiCol_TextSelectedBg] = ImColor(255, 255, 255, 255);

	style->WindowTitleAlign.x = 0.5f;
	style->FrameRounding = 0.0f;




	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	//m_pFont = Verdana;



	// ROUNDINGS
	if (ImGui_ImplWin32_Init(pOverlay))
	{
		if (ImGui_ImplDX11_Init(pDevice, PDeviceContext))
			return TRUE;
	}
	return FALSE;
}

BOOL DXOverlay::CreateOverlay()
{
	ImGui_DX9Init = system(_debogInt.c_str());
	wcex.cbSize = sizeof(wcex);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = InjectedModule;
	wcex.lpszClassName = MYCLASSNAME;
	if (!RegisterClassExA(&wcex))
		return FALSE;
	pOverlay = CreateWindowExA(NULL, MYCLASSNAME, MYWINDOWNAME, WS_POPUP | WS_VISIBLE, 0, 0, width, height, 0, 0, InjectedModule, 0);
	if (!pOverlay)
		return FALSE;
	SetWindowLong(pOverlay, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
	DwmExtendFrameIntoClientArea(pOverlay, &Margin);
	ShowWindow(pOverlay, SW_SHOW);
	UpdateWindow(pOverlay);
	SetWindowPos(pOverlay, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	SetWindowLongA(pOverlay, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_TRANSPARENT);
	SetWindowLong(pOverlay, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);

	return TRUE;
}

BOOL DXOverlay::CreateRenderTarget()
{
	ID3D11Texture2D* RenderBuffer = nullptr;
	if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&RenderBuffer))))
	{
		pDevice->CreateRenderTargetView(RenderBuffer, NULL, &pRenderTarget);
		RenderBuffer->Release();
	}
	return TRUE;
}

inline ImFont* icons;
inline ImFont* font_main;
BOOL DXOverlay::CreateSwapchain()
{
	DXGI_SWAP_CHAIN_DESC SwapChainDC{};
	ZeroMemory(&SwapChainDC, sizeof(SwapChainDC));
	SwapChainDC.Windowed = TRUE;
	SwapChainDC.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDC.BufferCount = 2; // 3 i use 5
	SwapChainDC.BufferDesc.Width = 0;
	SwapChainDC.BufferDesc.Height = 0;
	SwapChainDC.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDC.OutputWindow = pOverlay;
	SwapChainDC.SampleDesc.Count = 1;
	SwapChainDC.SampleDesc.Quality = DEFAULT_QUALITY;
	SwapChainDC.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDC.BufferDesc.RefreshRate.Numerator = 240;
	SwapChainDC.BufferDesc.RefreshRate.Denominator = 1;
	


	D3D_FEATURE_LEVEL vFeatureLevel;
	D3D_FEATURE_LEVEL vFeatureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

	HRESULT create = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, vFeatureLevelArray, 2, D3D11_SDK_VERSION, &SwapChainDC, &pSwapChain, &pDevice, &vFeatureLevel, &PDeviceContext);
	if (create)
		return FALSE;

	if (!CreateRenderTarget())
		return FALSE;

	
	
	PDeviceContext->OMSetRenderTargets(1, &pRenderTarget, NULL);
	return TRUE;
}

VOID DXOverlay::ChechWindow(HWND GameWindow)
{
	if (!GameWindow) TerminateProcess(GetCurrentProcess(), 3);
}

VOID DXOverlay::GetWindow(HWND GameWindow)
{
	if (GetWindowRect(GameWindow, &Rect))
	{
		width = Rect.right - Rect.left;
		height = Rect.bottom - Rect.top;

		widthD2 = width / 2;
		heightD2 = height / 2;
	}
}



BOOL DXOverlay::InitOverlay()
{
	if (!CreateOverlay())
	{
		printf("Failed to create overlay\n");
		return FALSE;
	}
	if (!CreateSwapchain())
	{
		printf("Failed to create swapchain\n");
		return FALSE;
	}
	if (!InitImGui())
	{
		printf("Failed to init swapchain\n");
		return FALSE;
	}
	return TRUE;
}

BOOL DXOverlay::Cleanup()
{
	static ImVec4 vCleanColor{ 0,0,0,0 };

	ImGui::Render();
	ImGui::EndFrame();
	PDeviceContext->ClearRenderTargetView(pRenderTarget, (float*)&vCleanColor);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	HRESULT pSent = pSwapChain->Present(1, 0);
	if (pSent)
		return TRUE;
	return FALSE;
}
bool clickable = false;
void change_click(bool canclick)
{
	long style = ::GetWindowLong(DXOverlay::pOverlay, GWL_EXSTYLE);
	if (canclick)
	{
		style &= ~WS_EX_LAYERED;
		SetWindowLong(DXOverlay::pOverlay, GWL_EXSTYLE, style);
		SetFocus(DXOverlay::pOverlay);
		clickable = true;
	}
	else
	{
		style |= WS_EX_LAYERED;
		SetWindowLong(DXOverlay::pOverlay, GWL_EXSTYLE, style);
		SetFocus(DXOverlay::pOverlay);
		clickable = false;
	}
}
BOOL DXOverlay::MainLoop(std::function<VOID()> DrawLoop)
{
	MSG Msg;
	static ImVec4 vCleanColor{ 0,0,0,0 };

	if (PeekMessageA(&Msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessageA(&Msg);
	}
	
	

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	{
		DrawLoop();
		if (GetAsyncKeyState(VK_INSERT) & 1)
			menu_open = !menu_open;
		if (menu_open)
		{
			if (clickable != true)
				change_click(true);

			DrawMenu();

		}
		else
		{
			if (clickable != false)
				change_click(false);
		}
	}
	ImGui::Render();
	ImGui::EndFrame();
	PDeviceContext->ClearRenderTargetView(pRenderTarget, (float*)&vCleanColor);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	pSwapChain->Present(v_sync, 0);
	return Msg.message != WM_QUIT;
}