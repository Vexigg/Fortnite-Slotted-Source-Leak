#include "cache.h"


void cache_players() {
	

	system("cls");
	DWORD THEUWORLD = request->read<DWORD>(virtualaddy + 0x11791DF8);
	std::cout << THEUWORLD;
	Sleep(6000);


	while (true) {

		auto global_temp = std::make_shared<global_s>();

		if (!populate_global_data(global_temp)) {
			//std::cout << "populate_global_data(global_temp)";
			continue;
		}
			

		tarray<aplayerstate*> players = global_temp->game_state->get_player_array();
		std::vector<std::shared_ptr<player_data>> players_temp;

		for (int i = 0; i < players.Length(); i++) {
			auto player_data_temp = std::make_shared<player_data>();

			if (populate_player_data(global_temp, player_data_temp, players[i]))
				players_temp.push_back(player_data_temp);
		}
		global_temp->players = players_temp;

		std::unique_lock<std::mutex> lock(global->data_mutex);
		global = global_temp;
		lock.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(7));
	}
}

bool populate_global_data(const std::shared_ptr<global_s>& global_temp) {

	global_temp->world = request->read<uworld*>(virtualaddy + 0x11791DF8);
	debug_ptr((u)global_temp->world, "world");

	global_temp->game_instance = global_temp->world->get_game_instance();
	debug_ptr((u)global_temp->game_instance, "game_instance");

	global_temp->local_player = global_temp->game_instance->get_local_player();
	debug_ptr((u)global_temp->local_player, "local_player");

	global_temp->player_controller = global_temp->local_player->get_player_controller();
	debug_ptr((u)global_temp->player_controller, "player_controller");

	global_temp->player_camera_manager = global_temp->player_controller->get_camera_manager();
	debug_ptr((u)global_temp->player_camera_manager, "player_camera_manager");

	global_temp->local_pawn = global_temp->player_controller->get_acknowledged_pawn();
	debug_ptr((u)global_temp->local_pawn, "local_pawn");

	global_temp->local_root_component = global_temp->local_pawn->get_root_component();
	debug_ptr((u)global_temp->local_root_component, "local_root_component");

	global_temp->local_player_state = global_temp->local_pawn->get_player_state();
	debug_ptr((u)global_temp->local_player_state, "local_player_state");

	global_temp->local_player_team_id = global_temp->local_player_state->get_player_id();
	debug_ptr(global_temp->local_player_team_id, "local_player_team_id");

	if ((u)global_temp->local_pawn)
		global_temp->current_weapon = global_temp->local_pawn->get_current_weapon();
	if ((u)global_temp->current_weapon)
		global_temp->weapon_name = global_temp->current_weapon->get_weapon_name();

	global_temp->game_state = global_temp->world->get_game_state();
	debug_ptr((u)global_temp->game_state, "game_state");

	return true;
}

bool populate_player_data(const std::shared_ptr<global_s>& global_temp,
	const std::shared_ptr<player_data>& player_data_temp,
	aplayerstate* player_state) {
	

	player_data_temp->player_state = player_state;
	debug_ptr((u)player_data_temp->player_state, "player_state");


	player_data_temp->player_team_id = player_data_temp->player_state->get_player_id();
	debug_ptr((u)player_data_temp->player_team_id, "player_team_id");


	player_data_temp->player = player_data_temp->player_state->get_pawn_private();
	debug_ptr((u)player_data_temp->player, "player");


	player_data_temp->root_component = player_data_temp->player->get_root_component();
	debug_ptr((u)player_data_temp->root_component, "root_component");


	player_data_temp->relative_location = player_data_temp->root_component->get_relative_location();
	debug_3d(player_data_temp->relative_location, "relative_location");

	player_data_temp->player_distance = camera_postion.location.distance(player_data_temp->relative_location) / 100;
	debug_1d(player_data_temp->player_distance, "distance");


	player_data_temp->mesh = player_data_temp->player->get_mesh();
	debug_ptr((u)player_data_temp->mesh, "mesh");

	//std::cout << "populate_player_data\n";
	return true;
}




