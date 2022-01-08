#include "stdafx.h"
#include "pawn.h"

pawn::pawn() {}

pawn::pawn(const std::string& position, bool type)
{
	this->position = position;

	first_move = true;

	white = type;

	if (white)
		figure_name = "WP";
	else
		figure_name = "BP";

	if (figure_name == "WP")
	{
		if (position[1] > '2')
			first_move = false;
	}
	else
	{
		if (position[1] < '7')
			first_move = false;
	}
}

void pawn::create_moves(const std::vector<std::vector<std::string>>& field)
{
	moves.clear();

	if (white)
	{
		if (first_move)
		{
			temp = position[0];
			temp += position[1] + 1;
			moves.push_back(temp);
			temp = position[0];
			temp += position[1] + 2;
			moves.push_back(temp);
		}
		else
		{
			temp = position[0];
			temp += position[1] + 1;
			int x = (int)(temp[1] - '0' - 1);
			int y = (int)(temp[0] - 97);
			if (x >= 0 && x < 8 && y >= 0 && y < 8)
				if (field[x][y][0] != 'W' && temp[1] > position[1])
					moves.push_back(temp);
		}
	}
	else
	{
		if (first_move)
		{
			temp = position[0];
			temp += position[1] - 1;
			moves.push_back(temp);
			temp = position[0];
			temp += position[1] - 2;
			moves.push_back(temp);
		}
		else
		{
			temp = position[0];
			temp += position[1] - 1;
			int x = (int)(temp[1] - '0' - 1);
			int y = (int)(temp[0] - 97);
			if(x >= 0 && x < 8 && y >=0 && y < 8)
				if (field[x][y][0] != 'B' && temp[1] < position[1])
					moves.push_back(temp);
		}
	}
}

const std::string& pawn::get_figure_name()
{
	return figure_name;
}

const std::string& pawn::get_figure_coordinats()
{
	return position;
}

const std::vector<std::string>& pawn::get_moves()
{
	return moves;
}

void pawn::set_figure_coordinats(const std::string& coord)
{
	position = coord;
	first_move = false;
}

bool pawn::get_type()
{
	if (white)
		return true;
	else
		return false;
}
