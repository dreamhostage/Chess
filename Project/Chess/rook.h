#pragma once
#include "chessman.h"

class rook : public chessman
{
	std::string position;
	std::vector<std::string> moves;
	bool white;
	std::string figure_name;
	std::string temp;
	bool first_move;

public:

	rook();
	rook(const std::string& position, bool type);

	void create_moves(const std::vector<std::vector<std::string>>& field) override;
	const std::string& get_figure_name() override;
	const std::string& get_figure_coordinats() override;
	const std::vector<std::string>& get_moves() override;
	void set_figure_coordinats(const std::string& coord) override;
	bool get_type() override;

	bool was_first_move(int request_type = 0);
};