#pragma once
void preform_aimbot(double closest_distance, std::shared_ptr<player_data> closest_player) {
	if (closest_distance != DBL_MAX && aimbot && (u)global->local_pawn) {
		if (Key.IsKeyPushing(aimkey)) {
			vector2 target_loc{};
			if (target_bone == 0) {
				target_loc = w2s(closest_player->mesh->get_head());
			}
			else if (target_bone == 1) {
				target_loc = w2s(closest_player->mesh->get_bone_3d(66));
			}
			else if (target_bone == 2) {
				vector2 chest_left = w2s(closest_player->mesh->get_bone_3d(37));
				vector2 chest_right = w2s(closest_player->mesh->get_bone_3d(8));
				target_loc = { chest_left.x + (chest_right.x - chest_left.x) / 2, chest_left.y };
			}
			if (targetline) {
				if (box_outline)
				{
					ImColor Color2 = ImColor(0, 0, 0, 255);
					int thickk = linethickness + 2;

					ImGui::GetForegroundDrawList()->AddLine(ImVec2(screen_width / 2, screen_height / 2), ImVec2(target_loc.x, target_loc.y), Color2, thickk);
				}
				ImGui::GetForegroundDrawList()->AddLine(ImVec2(screen_width / 2, screen_height / 2), ImVec2(target_loc.x, target_loc.y), ImColor(255,0,255), linethickness);
			}

			Sleep(aimdelay);
			move_mouse(target_loc);

			if (triggerbot && closest_distance < 50 && closest_player->player_distance < 15) {
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
	}
}
