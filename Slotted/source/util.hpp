#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define SeLoadDriverPrivilege 10ull
//external dependencies
#include <windows.h>
#include <iostream>
#include <string>
#include <atomic>
#include <mutex>
#include <TlHelp32.h>
#include <dwmapi.h>
#include <xmmintrin.h>
#include <array>
#include <vector>
#include <cstdlib>
#include <random>
#include <direct.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <d3d11.h>
#include <d3d9.h>

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "d3d11.lib")

//internal dependencies

#include "cheat/kernel/impl/include.hpp"
#include "cheat/sdk.hpp"
#include "cheat/actors/cache.h"
//#include "cheat/actors/esp.hpp"

#include "render/render.h"
#include "cheat/settings.hpp"
#include "cheat/structs.hpp"
#include "cheat/mouse.hpp"
#include "render/imgui/imgui.h"
#include "render/imgui/imgui_impl_dx11.h"
#include "render/imgui/imgui_impl_win32.h"
#include "render/custom/custom.h"
#include "render/menu/menu.hpp"

#include "cheat/actors/defs.h"
#include "render/menu/icon.h"
using namespace std;

#pragma warning(disable : 6387)
#pragma warning(disable : 4244)
#pragma warning(disable : 6262)
#pragma warning(disable : 4733)
#pragma warning(disable : 4731)
#pragma warning(disable : 4235)

#pragma intrinsic(_ReturnAddress)

inline std::uint32_t process_id;
inline std::uint64_t virtualaddy;

inline ImFont* AFont;
inline ImFont* TFont;
inline ImFont* proggy_clean_menu;

inline int screen_width = GetSystemMetrics(SM_CXSCREEN);
inline int screen_height = GetSystemMetrics(SM_CYSCREEN);
//inline 
typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;
struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};
using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;
static std::uint32_t _GetProcessId(std::string process_name) {
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return 0;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE) {
		if (process_name.compare(processentry.szExeFile) == 0)
			return processentry.th32ProcessID;
	}
	return 0;
}
bool CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size)
{
	std::ofstream file_ofstream(desired_file_path.c_str(), std::ios_base::out | std::ios_base::binary);

	if (!file_ofstream.write(address, size))
	{
		file_ofstream.close();
		return false;
	}

	file_ofstream.close();
	return true;
}
bool ReadFileToMemory(const std::string& file_path, std::vector<uint8_t>* out_buffer)
{
	std::ifstream file_ifstream(file_path, std::ios::binary);

	if (!file_ifstream)
		return false;

	out_buffer->assign((std::istreambuf_iterator<char>(file_ifstream)), std::istreambuf_iterator<char>());
	file_ifstream.close();

	return true;
}

class Color
{
public:
	RGBA liquid = { 56, 106, 248, 255 };
	RGBA red = { 255,0,0,255 };
	RGBA redlol = { 255,0,0,200 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA cyan = { 0,255,255,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 100,0,0,0 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 100,000, 000, 000 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255,0,255,200 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,200 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };
	RGBA nothing = { 0,0,0 };

	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };

	RGBA filled = { 0, 0, 0, 150 };

	RGBA Plum = { 221,160,221,160 };

	RGBA VisibleColor = { 255 / 255, 0, 0 };
	RGBA InvisibleColor = { 0, 255 / 255, 0 };
	RGBA FilledFov = { 0,0,0,160 };

	RGBA rainbow() {

		static float x = 0, y = 0;
		static float r = 0, g = 0, b = 0;

		if (y >= 0.0f && y < 255.0f) {
			r = 255.0f;
			g = 0.0f;
			b = x;
		}
		else if (y >= 255.0f && y < 510.0f) {
			r = 255.0f - x;
			g = 0.0f;
			b = 255.0f;
		}
		else if (y >= 510.0f && y < 765.0f) {
			r = 0.0f;
			g = x;
			b = 255.0f;
		}
		else if (y >= 765.0f && y < 1020.0f) {
			r = 0.0f;
			g = 255.0f;
			b = 255.0f - x;
		}
		else if (y >= 1020.0f && y < 1275.0f) {
			r = x;
			g = 255.0f;
			b = 0.0f;
		}
		else if (y >= 1275.0f && y < 1530.0f) {
			r = 255.0f;
			g = 255.0f - x;
			b = 0.0f;
		}

		float rainbow_speed = 0.25f;

		x += rainbow_speed; //increase this value to switch colors faster
		if (x >= 255.0f)
			x = 0.0f;

		y += rainbow_speed; //increase this value to switch colors faster
		if (y > 1530.0f)
			y = 0.0f;


		return RGBA{ (DWORD)r, (DWORD)g, (DWORD)b, 255 };
	}
};
inline static Color Col;
inline INT32 find_process(LPCTSTR process_name) {
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hsnap, &pt)) {
		do {
			if (!lstrcmpi(pt.szExeFile, process_name)) {
				CloseHandle(hsnap);
				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}
	CloseHandle(hsnap);


	return { NULL };
}

inline void DrawRect(int x, int y, int w, int h, int t, ImColor color)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0, t);
}

inline double GetCrossDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
inline int get_fps()
{
	using namespace std::chrono;
	static int count = 0;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	static int fps = 0;

	count++;

	if (duration_cast<milliseconds>(now - last).count() > 1000) {
		fps = count;
		count = 0;
		last = now;
	}

	return fps;
}

inline void DrawFilledRect(int x, int y, int w, int h, ImU32 color, bool round = false)
{

	if (round)
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, ImDrawCornerFlags_All, 30);
	else
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

inline void DrawCornerBox(int x, int y, int w, int h, int borderPx, ImU32 color, bool round_box)
{
	int borderWidth = (borderPx < (w / 2) && borderPx < (h / 2)) ? borderPx : ((w / 2) < (h / 2) ? (w / 2) : (h / 2));


	DrawFilledRect(x + borderWidth, y, w / 3, borderWidth, color, round_box); //top 
	DrawFilledRect(x + w - w / 3, y, w / 3, borderWidth, color, round_box); //top 
	DrawFilledRect(x, y, borderWidth, h / 3, color, round_box); //left 
	DrawFilledRect(x, y + h - h / 3, borderWidth, h / 3, color, round_box); //left 
	DrawFilledRect(x + borderWidth, y + h - borderWidth, w / 3, borderWidth, color, round_box); //bottom 
	DrawFilledRect(x + w - w / 3, y + h - borderWidth, w / 3, borderWidth, color, round_box); //bottom 
	DrawFilledRect(x + w - borderWidth, y, borderWidth, h / 3, color, round_box);//right 
	DrawFilledRect(x + w - borderWidth, y + h - h / 3, borderWidth, h / 3, color, round_box);//right 
}

inline void deformed_box(int x, int y, int w, int h, int borderPx, ImU32 color, bool rounded)
{
	int borderWidth = (borderPx < (w / 2) && borderPx < (h / 2)) ? borderPx : ((w / 2) < (h / 2) ? (w / 2) : (h / 2));
	float rounding = rounded ? 10.0f : 0.0f;

	ImVec2 p1 = ImVec2(x, y);
	ImVec2 p2 = ImVec2(x + w, y + h);

	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p1.x + rounding, p1.y));
	ImGui::GetForegroundDrawList()->PathArcTo(ImVec2(p1.x + rounding, p1.y + rounding), rounding, 180.0f, 270.0f);
	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p1.x, p1.y + h / 3));

	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p1.x, p2.y - h / 3));
	ImGui::GetForegroundDrawList()->PathArcTo(ImVec2(p1.x + rounding, p2.y - rounding), rounding, 180.0f, 90.0f);
	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p1.x + w / 3, p2.y));

	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p2.x - w / 3, p2.y));
	ImGui::GetForegroundDrawList()->PathArcTo(ImVec2(p2.x - rounding, p2.y - rounding), rounding, 0.0f, 90.0f);
	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p2.x, p2.y - h / 3));

	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p2.x, p1.y + h / 3));
	ImGui::GetForegroundDrawList()->PathArcTo(ImVec2(p2.x - rounding, p1.y + rounding), rounding, 0.0f, 270.0f);
	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p2.x - w / 3, p1.y));

	ImGui::GetForegroundDrawList()->PathLineTo(ImVec2(p1.x + rounding, p1.y));
	ImGui::GetForegroundDrawList()->PathStroke(color, false, borderWidth);
}

inline std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}
inline void draw_outlined_text(ImVec2 pos, ImColor color, std::string text)
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = ImGui::CalcTextSize(line.c_str());

		ImGui::GetBackgroundDrawList()->AddText(ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), color, line.c_str());

		y = pos.y + textSize.y * (i + 1);
		i++;
	}
}
inline void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 153.0, color->B / 51.0, color->A / 255.0)), text.c_str());
}

inline void DrawThreeDBox(const vector3& base, const vector3& head, float width, float height, float tick, ImU32 color) {
	// Calculate the corner points
	vector3 halfWidthOffset = { width / 2, 0, 0 };
	vector3 halfHeightOffset = { 0, height / 2, 0 };

	vector3 bottom1 = { base.x - halfWidthOffset.x, base.y - halfHeightOffset.y, base.z };
	vector3 bottom2 = { base.x + halfWidthOffset.x, base.y - halfHeightOffset.y, base.z };
	vector3 bottom3 = { base.x + halfWidthOffset.x, base.y + halfHeightOffset.y, base.z };
	vector3 bottom4 = { base.x - halfWidthOffset.x, base.y + halfHeightOffset.y, base.z };

	vector3 top1 = { head.x - halfWidthOffset.x, head.y - halfHeightOffset.y, head.z + 20 };
	vector3 top2 = { head.x + halfWidthOffset.x, head.y - halfHeightOffset.y, head.z + 20 };
	vector3 top3 = { head.x + halfWidthOffset.x, head.y + halfHeightOffset.y, head.z + 20 };
	vector3 top4 = { head.x - halfWidthOffset.x, head.y + halfHeightOffset.y, head.z + 20 };

	// Project the 3D world coordinates to 2D screen coordinates
	vector2 screenBottom1 = w2s(bottom1);
	vector2 screenBottom2 = w2s(bottom2);
	vector2 screenBottom3 = w2s(bottom3);
	vector2 screenBottom4 = w2s(bottom4);

	vector2 screenTop1 = w2s(top1);
	vector2 screenTop2 = w2s(top2);
	vector2 screenTop3 = w2s(top3);
	vector2 screenTop4 = w2s(top4);

	// Draw the lines
	auto draw_list = ImGui::GetForegroundDrawList();
	ImVec2 points[] = { ImVec2(screenBottom1.x, screenBottom1.y), ImVec2(screenBottom2.x, screenBottom2.y), ImVec2(screenBottom3.x, screenBottom3.y), ImVec2(screenBottom4.x, screenBottom4.y),
						ImVec2(screenTop1.x, screenTop1.y), ImVec2(screenTop2.x, screenTop2.y), ImVec2(screenTop3.x, screenTop3.y), ImVec2(screenTop4.x, screenTop4.y) };

	for (int i = 0; i < 4; i++) {
		draw_list->AddLine(points[i], points[(i + 1) % 4], color, tick);
		draw_list->AddLine(points[i + 4], points[(i + 1) % 4 + 4], color, tick);
		draw_list->AddLine(points[i], points[i + 4], color, tick);
	}
}
__forceinline std::string username(__int64 playerstate)
{

	__int64 Name = request->read<__int64>(playerstate + 0xAE8);
	if (!Name) return std::string("[BOT/AI]");
	int Length = request->read<int>(Name + 16i64);
	__int64 v6 = Length;
	if (!v6) return std::string("[BOT/AI]");
	uintptr_t Data = request->read<__int64>(Name + 8);
	if (!Data) return std::string("[BOT/AI]");
	wchar_t* NameBuffer = new wchar_t[Length];
	request->read_array((uintptr_t)Data, (uint8_t*)(NameBuffer), (Length * 2));

	char v21; // al
	int v22; // r8d
	int i; // ecx
	int v25; // eax
	_WORD* v23;

	v21 = v6 - 1;
	if (!(_DWORD)v6)
		v21 = 0;
	v22 = 0;
	v23 = (_WORD*)NameBuffer;
	for (i = (v21) & 3; ; *v23++ += i & 7)
	{
		v25 = v6 - 1;
		if (!(_DWORD)v6)
			v25 = 0;
		if (v22 >= v25)
			break;
		i += 3;
		++v22;
	}

	std::wstring Temp{ NameBuffer };
	delete[] NameBuffer;
	return std::string(Temp.begin(), Temp.end());


}
inline void K2_DrawLineXD(vector2 ScreenPositionA, vector2 ScreenPositionB, float Thickness, ImColor RenderColor) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x, ScreenPositionB.y), RenderColor, Thickness);
}
inline void K2_DrawLineXDD(vector2 ScreenPositionA, vector2 ScreenPositionB, float Thickness, ImColor RenderColor) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x + 1, ScreenPositionB.y + 1), RenderColor, Thickness);
}
inline void drawskeleton(uskeletalmeshcomponent* mesh, ImColor color, float thick) {

	vector2 ChestAtLeft = w2s(mesh->get_bone_3d(37));
	vector2 ChestAtRight = w2s(mesh->get_bone_3d(8));
	vector2 Chest = { ChestAtLeft.x + (ChestAtRight.x - ChestAtLeft.x) / 2, ChestAtLeft.y };

	vector2 Head = w2s(mesh->get_bone_3d(109));

	vector2 Neck = w2s(mesh->get_bone_3d(67));

	vector2 LeftShoulder = w2s(mesh->get_bone_3d(38));
	vector2 RightShoulder = w2s(mesh->get_bone_3d(9));

	vector2 LeftElbow = w2s(mesh->get_bone_3d(39));
	vector2 RightElbow = w2s(mesh->get_bone_3d(10));

	vector2 LeftHand = w2s(mesh->get_bone_3d(54));
	vector2 RightHand = w2s(mesh->get_bone_3d(24));

	vector2 LeftLeg = w2s(mesh->get_bone_3d(78));
	vector2 RightLeg = w2s(mesh->get_bone_3d(71));

	vector2 LeftThigh = w2s(mesh->get_bone_3d(84));
	vector2 RightThigh = w2s(mesh->get_bone_3d(77));

	vector2 LeftFoot = w2s(mesh->get_bone_3d(79));
	vector2 RightFoot = w2s(mesh->get_bone_3d(72));

	vector2 LeftFeet = w2s(mesh->get_bone_3d(82));
	vector2 RightFeet = w2s(mesh->get_bone_3d(75));


	vector2 LeftFeetFinger = w2s(mesh->get_bone_3d(83));
	vector2 RightFeetFinger = w2s(mesh->get_bone_3d(76));

	vector2 Bottom = w2s(mesh->get_bone_3d(0));
	vector2 Pelvis = w2s(mesh->get_bone_3d(2));

	vector2 centerrhand;
	vector2 rti;
	vector2 rbi;
	vector2 rbbi;

	vector2 rmt;
	vector2 rmb;
	vector2 rmbb;

	vector2 rrb;
	vector2 rrm;
	vector2 rrt;

	vector2 rpb;
	vector2 rpm;
	vector2 rpt;

	vector2 rtb;
	vector2 rtm;
	vector2 rtt;
	//left hand in lobby
	vector2 centerlhand;

	vector2 lti; //
	vector2 lbi;
	vector2 lbbi;

	vector2 lmb; //
	vector2 lmm;
	vector2 lmt;

	vector2 lrb;
	vector2 lrm;
	vector2 lrt;

	vector2 lpb;
	vector2 lpm;
	vector2 lpt;

	vector2 ltb;
	vector2 ltm;
	vector2 ltt;
	


	K2_DrawLineXD(Head, Neck, thick, color);
	K2_DrawLineXD(Neck, Chest, thick, color);
	K2_DrawLineXD(Chest, Pelvis, thick, color);
	K2_DrawLineXD(Chest, LeftShoulder, thick, color);
	K2_DrawLineXD(Chest, RightShoulder, thick, color);
	K2_DrawLineXD(LeftShoulder, LeftElbow, thick, color);
	K2_DrawLineXD(RightShoulder, RightElbow, thick, color);
	K2_DrawLineXD(LeftElbow, LeftHand, thick, color);
	K2_DrawLineXD(RightElbow, RightHand, thick, color);
	K2_DrawLineXD(Pelvis, LeftLeg, thick, color);
	K2_DrawLineXD(Pelvis, RightLeg, thick, color);
	K2_DrawLineXD(LeftLeg, LeftThigh, thick, color);
	K2_DrawLineXD(RightLeg, RightThigh, thick, color);
	K2_DrawLineXD(LeftThigh, LeftFoot, thick, color);
	K2_DrawLineXD(RightThigh, RightFoot, thick, color);
	K2_DrawLineXD(LeftFoot, LeftFeet, thick, color);
	K2_DrawLineXD(RightFoot, RightFeet, thick, color);



	


}
class CKey {
private:
	BYTE bPrevState[0x100];
public:
	CKey() {
		memset(bPrevState, 0, sizeof(bPrevState));
	}

	BOOL IsKeyPushing(BYTE vKey) {
		return GetAsyncKeyState(vKey) & 0x8000;
	}

	BOOL IsKeyPushed(BYTE vKey) {
		BOOL bReturn = FALSE;

		if (IsKeyPushing(vKey))
			bPrevState[vKey] = TRUE;
		else
		{
			if (bPrevState[vKey] == TRUE)
				bReturn = TRUE;
			bPrevState[vKey] = FALSE;
		}

		return bReturn;
	}
};
inline CKey Key;
inline void debug_ptr(uintptr_t p, const char* s) {
	if (debug)
		printf(("%s %I64u \n"), s, p);
}
inline void debug_3d(vector3 three, const char* s) {
	if (debug)
		printf(("%s %f, %f, %f \n"), s, three.x, three.y, three.z);
}
inline void debug_2d(vector2 two, const char* s) {
	if (debug)
		printf(("%s %f, %f \n"), s, two.x, two.y);
}
inline void debug_1d(double one, const char* s) {
	if (debug)
		printf(("%s %f \n"), s, one);
}
inline void print_3d(vector3 three, const char* s) {

	printf(("%s %f, %f, %f \n"), s, three.x, three.y, three.z);
}
