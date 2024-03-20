#pragma once
#include "../../util.hpp"
#include <map>
#include <setjmp.h>
#include <winnt.h>
#include "../../sPOOFING.h"

ImFont* VantaFont;
ImFont* NoramlFOnt;
ImFont* font;
ImFont* ESPFont;
ImFont* MenuFont;
ImFont* tahoma;
ImFont* font1;
inline ImFont* TabsFont;
inline ImFont* VFont;
inline ImFont* proggy_clean_game;

inline static int keystatus = 0;
inline static int realkey = 0;
inline int aimkey = 2;
inline int aimkey2 = 2;
inline bool GetKey(int key)
{
	realkey = key;
	return true;
}
inline void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}


inline void DrawBox(float X, float Y, float W, float H, const ImU32& color, int thickness)
{
	MRKZZ;
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

static const char* keyNames[] =
{
	"Keybind",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

inline static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
inline void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);
	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = ("Select Key");
	else
		aimkeys = preview_value;

	if (status == 1)
	{

		aimkeys = ("Press the Key");
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

inline ImFont* LexendRegular;
inline ImFont* LexendLight;

template<class T, class U>
inline static T clamp(const T& in, const U& low, const U& high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}

inline bool ImGui::Renderingtab(const char* icon, bool selected)
{
	MRKZZ;
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(icon);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = { 35, 35 };

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

	ImGui::ItemSize(size, 0);

	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	int current_tab;

	if (hovered || held)
		ImGui::SetMouseCursor(9);

	float deltatime = 1.5f * ImGui::GetIO().DeltaTime;
	static std::map<ImGuiID, float> hover_animation;
	auto it_hover = hover_animation.find(id)
		;
	if (it_hover == hover_animation.end())
	{
		hover_animation.insert({ id, 0.f });
		it_hover = hover_animation.find(id);
	}

	it_hover->second = clamp(it_hover->second + (1.15f * ImGui::GetIO().DeltaTime * (hovered ? 1.f : -1.f)), 0.0f, 0.0f);
	it_hover->second *= ImGui::GetStyle().Alpha;

	static std::map<ImGuiID, float> filled_animation;
	auto it_filled = filled_animation.find(id);

	if (it_filled == filled_animation.end())
	{
		filled_animation.insert({ id, 0.f });
		it_filled = filled_animation.find(id);
	}

	it_filled->second = clamp(it_filled->second + (2.15f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.5f)), it_hover->second, 1.f);
	it_filled->second *= ImGui::GetStyle().Alpha;

	ImGui::GetWindowDrawList()->AddText(ImVec2(bb.Min.x + 20, bb.Min.y + 4), ImColor(64, 64, 64, int(255 * ImGui::GetStyle().Alpha)), icon);

	if (selected)
	{
		ImGui::GetWindowDrawList()->AddText(ImVec2(bb.Min.x + 20, bb.Min.y + 4), ImColor(183, 183, 183, int(255 * it_filled->second)), icon);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(bb.Min.x - 11, bb.Min.y + 8.75f), ImVec2(bb.Min.x - 7 * it_filled->second, bb.Max.y - 8.75f), ImColor(201, 135, 52, int(255 * it_filled->second)), 10.f, ImDrawCornerFlags_Right);
	}

	return pressed;
}

inline bool ImGui::Renderingsubtab(const char* icon, bool selected)
{
	MRKZZ;
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(std::string(icon + std::string(icon)).c_str());
	const ImVec2 label_size = ImGui::CalcTextSize(icon);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = { 35, 35 };

	const ImRect bb(pos, ImVec2(pos.x + 35, pos.y + 35));
	ImGui::ItemSize(size, 50);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held);

	float t = selected ? 1.0f : 0.0f;
	float deltatime = 1.5f * ImGui::GetIO().DeltaTime;
	static std::map<ImGuiID, float> hover_animation;
	auto it_hover = hover_animation.find(id);
	if (it_hover == hover_animation.end())
	{
		hover_animation.insert({ id, 0.f });
		it_hover = hover_animation.find(id);
	}
	it_hover->second = ImClamp(it_hover->second + (0.2f * ImGui::GetIO().DeltaTime * (hovered || ImGui::IsItemActive() ? 1.f : -1.f)), 0.0f, 0.15f);
	it_hover->second *= min(ImGui::GetStyle().Alpha * 1.2, 1.f);

	static std::map<ImGuiID, float> filled_animation;
	auto it_filled = filled_animation.find(id);
	if (it_filled == filled_animation.end())
	{
		filled_animation.insert({ id, 0.f });
		it_filled = filled_animation.find(id);
	}
	it_filled->second = ImClamp(it_filled->second + (2.55f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.0f)), it_hover->second, 1.f);
	it_filled->second *= min(ImGui::GetStyle().Alpha * 1.2, 1.f);

	static std::map<ImGuiID, float> fill_animation;
	auto it_fill = fill_animation.find(id);
	if (it_fill == fill_animation.end())
	{
		fill_animation.insert({ id, 0.f });
		it_fill = fill_animation.find(id);
	}
	it_fill->second = ImClamp(it_filled->second + (1.75f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.0f)), it_hover->second, 1.f);
	it_fill->second *= min(ImGui::GetStyle().Alpha * 1.2, 1.f);

	ImVec4 text = ImLerp(ImVec4{ 128 / 255.f, 128 / 255.f, 128 / 255.f, ImGui::GetStyle().Alpha }, ImVec4{ 255 / 255.f, 255 / 255.f, 255 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);
	ImVec4 text2 = ImLerp(ImVec4{ 128 / 255.f, 128 / 255.f, 128 / 255.f, ImGui::GetStyle().Alpha }, ImVec4{ 255 / 255.f, 255 / 255.f, 255 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);

	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(bb.Min.x + 12, bb.Max.y - it_fill->second * 5), ImVec2(bb.Min.x + 35, bb.Max.y - 1), ImColor(201, 135, 52, int(255 * it_filled->second)), 3, ImDrawCornerFlags_Top);

	ImGui::GetForegroundDrawList()->AddText(ImVec2(bb.Min.x, bb.Min.y + 8), ImColor(text), icon);

	return pressed;
}
BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
	char lpString[1024];
	sprintf_s(lpString, sizeof(lpString), TEXT("%d"), nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
	char lpString[1024];
	sprintf_s(lpString, sizeof(lpString), TEXT("%f"), nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}
float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
{
	char szData[32];

	GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);

	return (float)atof(szData);
}
void savecfg(LPCSTR path)
{
	WritePrivateProfileInt(("a"), TEXT("Enbale"), enabletab, path);
	WritePrivateProfileInt(("a"), TEXT("Aimbot Enbale"), aimbot, path);
	WritePrivateProfileInt(("a"), TEXT("Triggerbot Enbale"), triggerbot, path);

	WritePrivateProfileInt(("a"), TEXT("Show fov"), draw_fov, path);
	WritePrivateProfileFloat(("a"), TEXT("fov size"), fov, path);
	WritePrivateProfileFloat(("a"), TEXT("smooth size"), smoothing, path);
	WritePrivateProfileInt(("a"), TEXT("Aimbot Key"), aimkey, path);
	WritePrivateProfileInt(("a"), TEXT("Aimbot Key 2"), aimkey2, path);
	WritePrivateProfileInt(("a"), TEXT("Aimbot Bone"), target_bone, path);



	WritePrivateProfileInt(("b"), TEXT("Enable visuals"), enabletab2, path);
	WritePrivateProfileInt(("b"), TEXT("Enable 2D"), box_esp, path);
	WritePrivateProfileInt(("b"), TEXT("Enable Corner"), box_corner, path);
	WritePrivateProfileInt(("b"), TEXT("Enable Round"), box_round, path);
	WritePrivateProfileInt(("b"), TEXT("Skeleton"), skeleton, path);
	WritePrivateProfileInt(("b"), TEXT("Line"), line, path);
	WritePrivateProfileInt(("b"), TEXT("Weapon"), draw_held_weapon, path);
	WritePrivateProfileInt(("b"), TEXT("Username"), draw_username, path);
	WritePrivateProfileInt(("b"), TEXT("Platform"), draw_platform, path);
	WritePrivateProfileFloat(("b"), TEXT("Box thick"), box_thickness, path);
	WritePrivateProfileFloat(("b"), TEXT("Skel thick"), skel_thickness, path);

	WritePrivateProfileFloat(("b"), TEXT("VisibleColorR"), visible_color_float[0], path);
	WritePrivateProfileFloat(("b"), TEXT("VisibleColorG"), visible_color_float[1], path);
	WritePrivateProfileFloat(("b"), TEXT("VisibleColorB"), visible_color_float[2], path);

	WritePrivateProfileFloat(("b"), TEXT("InvisibleColorR"), invisible_color_float[0], path);
	WritePrivateProfileFloat(("b"), TEXT("InvisibleColorG"), invisible_color_float[1], path);
	WritePrivateProfileFloat(("b"), TEXT("InvisibleColorB"), invisible_color_float[2], path);
}
void loadcfg(LPCSTR path)
{
	WritePrivateProfileInt(("a"), TEXT("Enbale"), enabletab, path);
	aimbot = GetPrivateProfileIntA(("a"), TEXT("Aimbot Enbale"), aimbot, path);
	draw_fov = GetPrivateProfileIntA(("a"), TEXT("Show fov"), draw_fov, path);
	fov = GetPrivateProfileFloat(("a"), TEXT("fov size"), fov, path);
	smoothing = GetPrivateProfileFloat(("a"), TEXT("smooth size"), smoothing, path);
	aimkey = GetPrivateProfileIntA(("a"), TEXT("Aimbot Key"), aimkey, path);
	target_bone = GetPrivateProfileIntA(("a"), TEXT("Aimbot Bone"), target_bone, path);



	enabletab2 = GetPrivateProfileIntA(("b"), TEXT("Enable visuals"), enabletab2, path);
	box_esp = GetPrivateProfileIntA(("b"), TEXT("Enable 2D"), box_esp, path);
	box_corner = GetPrivateProfileIntA(("b"), TEXT("Enable Corner"), box_corner, path);
	box_round = GetPrivateProfileIntA(("b"), TEXT("Enable Round"), box_round, path);
	skeleton = GetPrivateProfileIntA(("b"), TEXT("Skeleton"), skeleton, path);
	line = GetPrivateProfileIntA(("b"), TEXT("Line"), line, path);
	draw_held_weapon = GetPrivateProfileIntA(("b"), TEXT("Weapon"), draw_held_weapon, path);
	draw_username = GetPrivateProfileIntA(("b"), TEXT("Username"), draw_username, path);
	draw_platform = GetPrivateProfileIntA(("b"), TEXT("Platform"), draw_platform, path);
	box_thickness = GetPrivateProfileFloat(("b"), TEXT("Box thick"), box_thickness, path);
	skel_thickness = GetPrivateProfileFloat(("b"), TEXT("Skel thick"), skel_thickness, path);

	visible_color_float[0] = GetPrivateProfileFloat(("b"), TEXT("VisibleColorR"), visible_color_float[0], path);
	visible_color_float[1] = GetPrivateProfileFloat(("b"), TEXT("VisibleColorG"), visible_color_float[1], path);
	visible_color_float[2] = GetPrivateProfileFloat(("b"), TEXT("VisibleColorB"), visible_color_float[2], path);

	invisible_color_float[0] = GetPrivateProfileFloat(("b"), TEXT("InvisibleColorR"), invisible_color_float[0], path);
	invisible_color_float[1] = GetPrivateProfileFloat(("b"), TEXT("InvisibleColorG"), invisible_color_float[1], path);
	invisible_color_float[2] = GetPrivateProfileFloat(("b"), TEXT("InvisibleColorB"), invisible_color_float[2], path);

}
inline int MenuTab;
inline static float switch_alpha[3], open_alpha = 0;
inline void DrawMenu() {

	RECT screen_rect;
	::GetWindowRect(::GetDesktopWindow(), &screen_rect);

	static int tabs = 0;

	static int selected = 0;
	static int sub_selected = 0;

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// COLOR STYLES BY MRKZZUDUD

	style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);                      // Text color (white)
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);              // Disabled text color (white)
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);                // Window background color (dark grey)
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.25f, 0.35f, 0.6f);                 // Title bar background color (light purple)
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.25f, 0.35f, 0.6f);           // Active title bar background color (light purple)
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.25f, 0.25f, 0.35f, 0.6f);        // Collapsed title bar background color (light purple)
	style->Colors[ImGuiCol_Border] = ImVec4(0.25f, 0.52f, 0.96f, 1.0f);                      // Border color (purple)
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);                // Border shadow color (black)
	style->Colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 0.7f);                   // Button color (dark grey)
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.2f, 0.2f, 0.6f);               // Button hover color (darker grey)
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.6f);                // Button active color (darker grey)
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.2f, 0.2f, 0.3f, 1.0f);                  // Slider grab color (dark blue)
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2f, 0.2f, 0.3f, 1.0f);            // Slider grab active color (dark blue)
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.54f);                    // Frame background color (semi-transparent dark grey)
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 0.6f);              // Frame background hover color (darker grey)
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 0.6f);               // Active title bar background color (darker grey)


	ImGui::SetNextWindowSize(io.DisplaySize);
	io.IniFilename = NULL;

	io.Fonts->AddFontFromFileTTF("C:\\font.otf", 15.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
	ESPFont = io.Fonts->AddFontFromFileTTF("C:\\font.otf", 13.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
	MenuFont = io.Fonts->AddFontFromFileTTF("C:\\verdana.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
	NoramlFOnt = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 15.0f, nullptr, io.Fonts->GetGlyphRangesDefault());

	static int maintabs = 0;
	ImGui::SetNextWindowSize(ImVec2(400.0f, 600.0f), ImGuiCond_Once);

	if (ImGui::Begin(("Negro.cc"), NULL, 34))
	{
		MRKZZ;
		if (ImGui::BeginTabBar("TabBar"))
		{
			if (ImGui::BeginTabItem("Aimbot"))
			{
				ImGui::SetWindowSize(ImVec2(450.0f, 450.0f));
				ImGui::BeginChild("Aimbot", ImVec2(0, 0), true);
				ImGui::Spacing();
				ImGui::Checkbox("Show Tab", &enabletab);
				if (enabletab)
				{
					ImGui::Spacing();
					ImGui::Checkbox("Mouse Aim", &aimbot);
					ImGui::Spacing();
					ImGui::Checkbox("Trigger Bot", &triggerbot);
					ImGui::Spacing();
					ImGui::Text("Aim Key >"); ImGui::SameLine();
					HotkeyButton(aimkey, ChangeKey, keystatus);
					
					ImGui::PushItemWidth(150);
					ImGui::Spacing();
					static const char* bonename[] =
					{
						"Head",
						"Neck",
						"Chest"
					};

					ImGui::Combo(("  Hitbox"), &target_bone, bonename, IM_ARRAYSIZE(bonename));
					ImGui::Spacing();
					ImGui::Checkbox("Draw FOV", &draw_fov);
					ImGui::Spacing();
					ImGui::Checkbox("TargetLine", &targetline);
					ImGui::Spacing();
					ImGui::PushItemWidth(70);
					ImGui::SliderInt(("  FOV Size:"), &fov, 50, 800);
					ImGui::Spacing();
					ImGui::PushItemWidth(70);
					ImGui::SliderFloat(("  Smoothing:"), &smoothing, 1, 30);
				}

				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}

		if (ImGui::BeginTabItem("Visuals"))
		{

			ImGui::BeginChild("Visuals", ImVec2(0, 0), true);
			ImGui::Spacing();
			ImGui::Checkbox("Show Tab", &enabletab2);
			if (enabletab2)
			{
				ImGui::Spacing();
				ImGui::Checkbox("Otulined ESP", &box_outline);
				ImGui::Checkbox("2D Box", &box_esp);
				ImGui::Checkbox("Corner Box", &box_corner);
				ImGui::Checkbox("Round Box", &box_round);
				ImGui::Checkbox("Skeleton", &skeleton);
				ImGui::Checkbox("Distance ", &draw_distance);
				ImGui::Checkbox("Snaplines", &line);
				ImGui::Checkbox("Username ESP ", &draw_username);
				ImGui::Checkbox("Weapon ESP ", &draw_held_weapon);
				ImGui::Checkbox("Platform ESP", &draw_platform);
			}

			ImGui::EndChild();
			ImGui::EndTabItem();
		}





		if (ImGui::BeginTabItem("Misc"))
		{
			ImGui::BeginChild("Misc", ImVec2(0, 0), true);
			ImGui::Spacing();
			ImGui::Checkbox("Show Tab", &enabletab3);
			if (enabletab3)
			{
				ImGui::Spacing();
				ImGui::PushItemWidth(70);
				ImGui::SliderFloat("Box Thickness", &box_thickness, 0.5, 15);
				ImGui::PushItemWidth(70);
				ImGui::SliderFloat("Skeleton Thickness", &skel_thickness, 0.5, 15);
				ImGui::PushItemWidth(70);
				ImGui::SliderFloat("Line Thickness", &linethickness, 0.1, 5);
				ImGui::Spacing();
				ImGui::Text("Visble Color");
				ImGui::PushItemWidth(70);
				ImGui::ColorPicker3("Visible Color", visible_color_float, ImGuiColorEditFlags_NoInputs);
				ImGui::Text("Invisible Color Color");
				ImGui::PushItemWidth(70);
				ImGui::ColorPicker3("Invisible Color", invisible_color_float, ImGuiColorEditFlags_NoInputs);
				if (ImGui::Button(("Save Config"), ImVec2(30, 30)))
				{
					savecfg((("C:\\cfgfn")));
				}
				if (ImGui::Button(("Load Config"), ImVec2(30, 30)))
				{
					loadcfg((("C:\\cfgfn")));
				}



			}

			ImGui::EndChild();
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();


	}
	ImGui::End();
}
