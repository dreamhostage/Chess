#include "stdafx.h"
#include "bishop.h"

bishop::bishop() {}

bishop::bishop(const std::string& position, bool type)
{
	this->position = position;

	white = type;

	if (white)
		figure_name = "WB";
	else
		figure_name = "BB";
}

void bishop::create_moves(const std::vector<std::vector<std::string>>& field)
{
	moves.clear();

	temp = position;
	--temp[0];
	--temp[1];
	while (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8')
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
		--temp[0];
		--temp[1];
	}

	temp = position;
	++temp[0];
	--temp[1];
	while (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8')
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
		++temp[0];
		--temp[1];
	}

	temp = position;
	--temp[0];
	++temp[1];
	while (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8')
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
		--temp[0];
		++temp[1];
	}

	temp = position;
	++temp[0];
	++temp[1];
	while (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8')
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
		++temp[0];
		++temp[1];
	}
}

const std::string& bishop::get_figure_name()
{
	return figure_name;
}

const std::string& bishop::get_figure_coordinats()
{
	return position;
}

const std::vector<std::string>& bishop::get_moves()
{
	return moves;
}

void bishop::set_figure_coordinats(const std::string& coord)
{
	position = coord;
}

bool bishop::get_type()
{
	if (white)
		return true;
	else
		return false;
}
