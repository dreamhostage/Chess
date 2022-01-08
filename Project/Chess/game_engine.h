#pragma once
#include "chessman.h"
#include "pawn.h"
#include "rook.h"
#include "kNight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <fstream>

class game_engine
{
	bool turn;
	std::string command;
	std::string selected_position;
	std::string selected_figure;
	std::vector<std::vector<std::string>> game_field;
	std::vector<chessman*> figures;
	std::vector<std::vector<std::string>> simulated_game_field;
	std::vector<chessman*> simulated_figures;
	std::string temp;

	void create_figures();
	bool checking_figure_selection(const std::string& coordinats);
	bool moving();
	void make_move(const std::string& position, const std::string& moving_coordinates);
	bool checking_figure_move(const std::string& position, const std::string& moving_coordinates);
	void display();
	void update_moves();
	void update_map();
	const std::string& check_coordinates(const std::string& coord);
	bool check_check();
	bool check_checkmate();
	bool simulation_check(const std::string& position, const std::string& moving_coordinates);
	void game_loop();
	bool castling(const std::string& rook_coordinates);
	bool load_game();
	bool save_game();
	void clear();

public:

	game_engine();
	~game_engine();
	void start_game();
};