#include "stdafx.h"
#include "queen.h"

queen::queen() {}

queen::queen(const std::string& position, bool type)
{
	this->position = position;

	white = type;

	if (white)
		figure_name = "WQ";
	else
		figure_name = "BQ";
}

void queen::create_moves(const std::vector<std::vector<std::string>>& field)
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
	/////////////////
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

const std::string& queen::get_figure_name()
{
	return figure_name;
}

const std::string& queen::get_figure_coordinats()
{
	return position;
}

const std::vector<std::string>& queen::get_moves()
{
	return moves;
}

void queen::set_figure_coordinats(const std::string& coord)
{
	position = coord;
}

bool queen::get_type()
{
	if (white)
		return true;
	else
		return false;
}
