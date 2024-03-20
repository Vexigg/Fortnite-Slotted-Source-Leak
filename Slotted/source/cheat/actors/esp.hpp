#pragma once
#include "../../sPOOFING.h"


#pragma warning(disable : 4996)

bool isVisible(uint64_t mesh)
{
	float bing = request->read<float>(mesh + 0x350);
	float bong = request->read<float>(mesh + 0x358);
	const float tick = 0.06f;
	return bong + tick >= bing;
}

extern void preform_aimbot(double closest_distance, std::shared_ptr<player_data> closest_player);


static auto aimfunction(float x, float y) -> void
{


	float ScreenCenterX = (screen_height / 2);
	float ScreenCenterY = (screen_width / 2);
	int AimSpeed = smoothing;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}


	//SPOOF_CALL(mouse_event, MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	/*driver.write(cachedplayercontroller + 0x520, TargetX);
	driver.write(cachedplayercontroller + 0x520, TargetY);*/
	return;
}

void aimbott(DWORD_PTR entity) {

	uintptr_t cachedgworld = request->read<uintptr_t>(virtualaddy + 0x117392A8);
	uintptr_t cachedgameinstance = request->read<uintptr_t>(cachedgworld + 0x1d0);
	uintptr_t cachedlocalplayers = request->read<uintptr_t>(cachedgameinstance + 0x38);
	uintptr_t cachedlocalplayer = request->read<uintptr_t>(cachedlocalplayers);
	uintptr_t cachedplayercontroller = request->read<uintptr_t>(cachedlocalplayer + 0x30);
	vector2 screen_center = { static_cast<double>(screen_height) / 2, static_cast<double>(screen_width) / 2 };
	vector2 target{};
	vector2 bone;
	uint64_t currentactormesh = request->read<uint64_t>(entity + 0x318);

	target.x = (bone.x > screen_center.x) ? -(screen_center.x - bone.x) : bone.x - screen_center.x;
	target.x /= smoothing;
	target.x = (target.x + screen_center.x > screen_center.x * 2 || target.x + screen_center.x < 0) ? 0 : target.x;

	target.y = (bone.y > screen_center.y) ? -(screen_center.y - bone.y) : bone.y - screen_center.y;
	target.y /= smoothing;
	target.y = (target.y + screen_center.y > screen_center.y * 2 || target.y + screen_center.y < 0) ? 0 : target.y;

	vector3 Angles(-target.y / smoothing, target.x / smoothing, 0);

	vector3 original1(0, 0, 0);
	//if (aimbot->enable && (Controller::IsPressingLeftTrigger() || GetAsyncKeyState(aimkey) < 0)) {
	request->write(cachedplayercontroller + 0x520, Angles.x);
	request->write(cachedplayercontroller + 0x520 + 0x8, Angles.y);
	//}



}
inline camera_position_s get_camera_postion() {


	camera_position_s camera;

	auto location_pointer = request->read<uintptr_t>((u)global->world + 0x110);
	auto rotation_pointer = request->read<uintptr_t>((u)global->world + 0x120);

	struct FNRot
	{
		double a; //0x0000
		char pad_0008[24]; //0x0008
		double b; //0x0020
		char pad_0028[424]; //0x0028
		double c; //0x01D0
	}fnRot;

	fnRot.a = request->read<double>(rotation_pointer);
	fnRot.b = request->read<double>(rotation_pointer + 0x20);
	fnRot.c = request->read<double>(rotation_pointer + 0x1d0);

	camera.location = request->read<vector3>(location_pointer);
	camera.rotation.x = asin(fnRot.c) * (180.0 / M_PI);
	camera.rotation.y = ((atan2(fnRot.a * -1, fnRot.b) * (180.0 / M_PI)) * -1) * -1;
	camera.fov = request->read<float>((uintptr_t)(u)global->player_controller + 0x394) * 90.f;

	return camera;

}
std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
	return retStr;
}
void draw_outlined_text(int x, int y, int R, int G, int B, int A, const char* str)
{
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);

	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 18.0f, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(R / 255.0f, G / 255.0f, B / 255.0f, A / 255.0f)), utf_8_2.c_str());
}
float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}
float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}
static ImColor linecolor;
static ImColor Skelcolor;
static ImColor BoxColor;

namespace u_cached {
	class u_cache
	{
	public:

		uintptr_t
			uworld,
			game_instance,
			game_state,
			local_player,
			player_controller,
			acknowledged_pawn,
			skeletal_mesh,
			player_state,
			root_component,
			player_array;
		int
			team_index,
			player_array_size;
		vector3
			relative_location,
			velocity;
	};
} static u_cached::u_cache* ud_cache = new u_cached::u_cache();

void actor_loop() {

	ImGui::PushFont(ESPFont);

	MRKZZ;
	std::unique_lock<std::mutex> lock(global->data_mutex);

	camera_postion = get_camera_postion();

	ImDrawList* draw_list = ImGui::GetForegroundDrawList();

	ImGui::PushFont(NoramlFOnt);
	char Watermark[64];
	sprintf(Watermark, ("FPS -> %.1f\n"), ImGui::GetIO().Framerate);
	float fontSize = 18;
	float textWidth = ImGui::CalcTextSize(("")).x * (fontSize / ImGui::GetFontSize());
	ImVec2 textPosition(15, 10);
	ImColor color = ImColor(255, 255, 255);
	ImGui::PopFont();
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, textPosition, color, Watermark);
	float fovthickness = 1;
	int dynamicfov = +fov;
	ImColor Color2 = ImColor(0, 0, 0, 255);
	int thickk = fovthickness + 2;

	if (draw_fov) {
		MRKZZ;
		draw_list->AddCircle(ImVec2(screen_width / 2, screen_height / 2), fov, Color2, 200.0f, thickk);

		// Draw another circle with a white color and default thickness
		draw_list->AddCircle(ImVec2(screen_width / 2, screen_height / 2), fov, ImColor(255, 255, 255, 255), 80.0f, 1.0f);
	}

	double closest_distance = DBL_MAX;
	std::shared_ptr<player_data> closest_player = std::make_shared<player_data>();
	for (auto player : global->players) {
		vector3 head_3d = player->mesh->get_head();
		vector2 head_2d = w2s(vector3(head_3d.x, head_3d.y, head_3d.z + 19));

		vector3 base_3d = player->mesh->get_base();
		vector2 base_2d = w2s(base_3d);
		float distance = ud_cache->relative_location.distance(base_3d) / 100;
		float box_hight = abs(head_2d.y - base_2d.y);
		float box_width = box_hight * 0.30;

		if (!head_2d.valid_location())
			continue;


		if (esp) {
			MRKZZ;
			ImColor visible_color;
			if (player->mesh->visible()) {
				MRKZZ;
				visible_color = ImGui::GetColorU32({ visible_color_float[0], visible_color_float[1], visible_color_float[2],  1.0f });
			}
			else if (!player->mesh->visible()) {
				MRKZZ;
				visible_color = ImGui::GetColorU32({ invisible_color_float[0], invisible_color_float[1], invisible_color_float[2],  1.0f });
			}
			if (player->player == global->local_pawn) continue;



			if (box_esp) {
				MRKZZ;
				if (box_outline)
				{
					MRKZZ;
					ImColor Color2 = ImColor(0, 0, 0, 255);
					int thickk = box_thickness + 2;

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head_2d.x - (box_width / 2), head_2d.y), ImVec2(base_2d.x + (box_width / 2), head_2d.y), Color2, thickk);

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head_2d.x - (box_width / 2), head_2d.y), ImVec2(head_2d.x - (box_width / 2), base_2d.y), Color2, thickk); // L

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head_2d.x - (box_width / 2), base_2d.y), ImVec2(base_2d.x + (box_width / 2), base_2d.y), Color2, thickk); // T

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(base_2d.x + (box_width / 2), head_2d.y), ImVec2(base_2d.x + (box_width / 2), base_2d.y), Color2, thickk); // R
				}

				//DrawBox(head_2d.x - box_width / 2, head_2d.y, box_width, CornerHeight, visible_color, visuals->box_thickness);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head_2d.x - (box_width / 2), head_2d.y), ImVec2(base_2d.x + (box_width / 2), head_2d.y), visible_color,box_thickness);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head_2d.x - (box_width / 2), head_2d.y), ImVec2(head_2d.x - (box_width / 2), base_2d.y), visible_color,box_thickness); // L

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head_2d.x - (box_width / 2), base_2d.y), ImVec2(base_2d.x + (box_width / 2), base_2d.y), visible_color,box_thickness); // T

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(base_2d.x + (box_width / 2), head_2d.y), ImVec2(base_2d.x + (box_width / 2), base_2d.y), visible_color,box_thickness); // R


			}
			if (box_round)
			{
				MRKZZ;
				if (box_outline)
				{
					MRKZZ;
					ImColor Color2 = ImColor(0, 0, 0, 255);
					int thickk = box_thickness + 2;

					draw_list->AddRect(ImVec2(head_2d.x - box_width / 1.5, head_2d.y), ImVec2((head_2d.x - box_width / 2.5) + box_width, head_2d.y + box_hight), Color2, 10, ImDrawCornerFlags_All, thickk);
				}

				draw_list->AddRect(ImVec2(head_2d.x - box_width / 1.5, head_2d.y), ImVec2((head_2d.x - box_width / 2.5) + box_width, head_2d.y + box_hight), visible_color, 10, ImDrawCornerFlags_All, box_thickness);
			}
			if (box_corner)
			{
				MRKZZ;
				if (box_outline)
				{
					MRKZZ;
					ImColor Color2 = ImColor(0, 0, 0, 255);
					int thickk = box_thickness + 2;

					DrawCornerBox(head_2d.x - box_width / 2.5, head_2d.y, box_width, box_hight, thickk, Color2, box_round);
				}

				DrawCornerBox(head_2d.x - box_width / 2.5, head_2d.y, box_width, box_hight, box_thickness, visible_color, box_round);
			}
			if (draw_username)
			{
				MRKZZ;
				auto name = username((uintptr_t)player->player_state);
				ImVec2 textPosition(head_2d.x, head_2d.y - 13);
				draw_outlined_text(textPosition, ImColor(255, 255, 255), name.c_str());
			}
			auto CurrentWeapon = request->read<uintptr_t>((uintptr_t)player->player + 0xa20);
			if (draw_held_weapon) {
				MRKZZ;
				auto ItemData = request->read<DWORD_PTR>(CurrentWeapon + 0x4a8);
				auto DisplayName = request->read<uint64_t>(ItemData + 0x98);
				auto WeaponLength = request->read<uint32_t>(DisplayName + 0x40);
				wchar_t* WeaponName = new wchar_t[uint64_t(WeaponLength) + 1];
				request->read_array((uintptr_t)request->read<PVOID>(DisplayName + 0x38), (uint8_t*)WeaponName, WeaponLength * sizeof(wchar_t));

				BYTE tier;
				tier = request->read<BYTE>(ItemData + 0x73);
				ImColor Color;

				if (tier == 2)
				{
					Color = IM_COL32(0, 255, 0, 255);
				}
				else if ((tier == 3))
				{
					Color = IM_COL32(0, 0, 255, 255);
				}
				else if ((tier == 4))
				{
					Color = IM_COL32(128, 0, 128, 255); // p
				}
				else if ((tier == 5))
				{
					Color = IM_COL32(255, 255, 0, 255); // p
				}
				else if ((tier == 6))
				{
					Color = IM_COL32(255, 255, 0, 255); // p
				}
				else if ((tier == 0) || (tier == 1))
				{
					Color = IM_COL32(255, 255, 255, 255); // p
				}
				if (!WeaponName || !tier)
				{
					delete[] WeaponName;
					WeaponName = new wchar_t[1];
					wcscpy(WeaponName, L"");
				}

				std::string wep_str = wchar_to_char(WeaponName);
				//return wep_str;
				ImVec2 textPosition(base_2d.x, base_2d.y + 5);

				draw_outlined_text(textPosition, ImColor(255, 255, 255), wep_str.c_str());
			}

			if (draw_platform) {
				MRKZZ;
				DWORD_PTR test_platform = request->read<DWORD_PTR>((uintptr_t)player->player_state + 0x438);
				wchar_t platform[64];
				request->read_array((uintptr_t)test_platform, (uint8_t*)platform, sizeof(platform));
				std::wstring platform_wstr(platform);
				std::string platform_str(platform_wstr.begin(), platform_wstr.end());
				ImVec2 textPosition(head_2d.x, head_2d.y - 33);

				draw_outlined_text(textPosition, ImColor(255, 255, 255), platform_str.c_str());
			}

			if (line) {
				MRKZZ;
				//linecolor = ImGui::GetColorU32({ linecol[0], linecol[1], linecol[2],  1.0f });
				draw_list->AddLine(ImVec2(screen_width / 2, 0), ImVec2(head_2d.x, head_2d.y), visible_color, 2);
			}
			if (skeleton) {
				MRKZZ;
				if (box_outline)
				{
					MRKZZ;
					ImColor Color2 = ImColor(0, 0, 0, 255);
					int thickk = skel_thickness + 2;

					drawskeleton(player->mesh, Color2, thickk);
				}
				//Skelcolor = ImGui::GetColorU32({ skeletoncolor[0], skeletoncolor[1], skeletoncolor[2],  1.0f });
				drawskeleton(player->mesh, visible_color, skel_thickness);
			}
			if (draw_distance) {
				std::string distance_str = (std::string)("") + std::to_string((int)distance) + (std::string)("m");
				ImVec2 text_size = ImGui::CalcTextSize(distance_str.c_str());

				DrawString(16, base_3d.x - (text_size.x / 2), base_3d.y + 15, &Col.white, false, true, distance_str.c_str());
			}


		}

		auto dist = GetCrossDistance(head_2d.x, head_2d.y, screen_width / 2, screen_height / 2);
		if (player->mesh->visible()) {
			if (dist < fov && dist < closest_distance && player->player_distance < 10000) {
				closest_distance = dist;
				closest_player = player;
			}
		}

	}

	preform_aimbot(closest_distance, closest_player);
	lock.unlock();


}