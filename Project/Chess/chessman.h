#pragma once
#include <iostream>
#include <vector>
#include <string>

class chessman
{

public:

	virtual const std::string& get_figure_name() = 0;
	virtual const std::string& get_figure_coordinats() = 0;
	virtual void set_figure_coordinats(const std::string& coord) = 0;
	virtual const std::vector<std::string>& get_moves() = 0;
	virtual void create_moves(const std::vector<std::vector<std::string>>& field) = 0;
	virtual bool get_type() = 0;

	chessman() {}
	virtual ~chessman() {}
};
