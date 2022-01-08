#include "stdafx.h"
#include "rook.h"

rook::rook() {}

rook::rook(const std::string& position, bool type)
{
	this->position = position;

	white = type;

	if (white)
		figure_name = "WR";
	else
		figure_name = "BR";

	first_move = false;
}

void rook::create_moves(const std::vector<std::vector<std::string>>& field)
{
	moves.clear();

	temp = position;

	while (--temp[1] != '0')
	{
		if (field[temp[1] - 49][temp[0] - 97] == "  ")
		{
			moves.push_back(temp);
		}
		else if (field[temp[1] - 49][temp[0] - 97][0] == 'B')
		{
			if (white)
			{
				moves.push_back(temp);
				break;
			}
			else
				break;
		}
		else if (field[temp[1] - 49][temp[0] - 97][0] == 'W')
		{
			if (!white)
			{
				moves.push_back(temp);
				break;
			}
			else
				break;
		}
	}

	temp = position;

	while (++temp[1] != '9')
	{
		if (field[temp[1] - 49][temp[0] - 97] == "  ")
		{
			moves.push_back(temp);
		}
		else if (field[temp[1] - 49][temp[0] - 97][0] == 'B')
		{
			if (white)
			{
				moves.push_back(temp);
				break;
			}
			else
				break;
		}
		else if (field[temp[1] - 49][temp[0] - 97][0] == 'W')
		{
			if (!white)
			{
				moves.push_back(temp);
				break;
			}
			else
				break;
		}
	}

	temp = position;

	while (--temp[0] >= 'a')
	{
		if (field[temp[1] - 49][temp[0] - 97] == "  ")
		{
			moves.push_back(temp);
		}
		else if (field[temp[1] - 49][temp[0] - 97][0] == 'B')
		{
			if (white)
			{
				moves.push_back(temp);
				break;
			}
			else
				break;
		}
		else if (field[temp[1] - 49][temp[0] - 97][0] == 'W')
		{
			if (!white)
			{
				moves.push_back(temp);
				break;
			}
			else
				break;
		}
	}

	temp = position;

	while (++temp[0] <= 'h')
	{
		if (field[temp[1] - 49][temp[0] - 97] == "  ")
		{
			moves.push_back(temp);
		}
		else if (field[temp[1] - 49][temp[0] - 97][0] == 'B')
		{
			if (white)
			{
				moves.push_back(temp);
				break;
			}
			else
				break;
		}
		else if (field[temp[1] - 49][temp[0] - 97][0] == 'W')
		{
			if (!white)
			{
				moves.push_back(temp);
				break;
			}
			else
				break;
		}
	}
}

const std::string& rook::get_figure_name()
{
	return figure_name;
}

const std::string& rook::get_figure_coordinats()
{
	return position;
}

const std::vector<std::string>& rook::get_moves()
{
	return moves;
}

void rook::set_figure_coordinats(const std::string& coord)
{
	position = coord;
	first_move = true;;
}

bool rook::get_type()
{
	if (white)
		return true;
	else
		return false;
}

bool rook::was_first_move(int request_type)
{
	if (request_type)
		first_move = true;
	return first_move;
}