#pragma once
#include "../../util.hpp"
#include "../sdk.hpp"
#include <mutex>

struct player_data {
	aactor* player{};
	uskeletalmeshcomponent* mesh{};
	uschenecomponent* root_component{};
	aplayerstate* player_state{};
	vector3 relative_location{};
	int player_team_id{};
	int player_distance{};

	player_data() = default;
};

struct global_s {
	uworld* world{};
	ugameinstance* game_instance{};
	ulocalplayer* local_player{};
	aplayercontroller* player_controller{};
	
	aactor* local_pawn{};
	uschenecomponent* local_root_component{};
	aplayerstate* local_player_state{};
	aplayercameramanager* player_camera_manager{};
	afortweapon* current_weapon{};
	std::string weapon_name{};
	int local_player_team_id{};

	agamestate* game_state{};
	std::vector<std::shared_ptr<player_data>> players{};
	std::mutex data_mutex;
};  inline std::shared_ptr<global_s> global = std::make_shared<global_s>();
inline int fps = 0;
void cache_players();
bool populate_global_data(const std::shared_ptr<global_s>& global_temp);
bool populate_player_data(const std::shared_ptr<global_s>& global_temp,
	const std::shared_ptr<player_data>& player_data_temp,
	aplayerstate* player_state);