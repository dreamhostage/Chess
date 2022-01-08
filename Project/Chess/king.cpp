#include "stdafx.h"
#include "king.h"

king::king() {}

king::king(const std::string& position, bool type)
{
	this->position = position;

	white = type;

	if (white)
		figure_name = "WK";
	else
		figure_name = "BK";

	first_move = false;
}

void king::create_moves(const std::vector<std::vector<std::string>>& field)
{
	moves.clear();

	temp = position;

	std::vector<std::string> positions;

	--temp[1];
	positions.push_back(temp);

	temp = position;
	++temp[1];
	positions.push_back(temp);

	temp = position;
	--temp[0];
	positions.push_back(temp);

	temp = position;
	++temp[0];
	positions.push_back(temp);

	temp = position;
	--temp[0];
	--temp[1];
	positions.push_back(temp);

	temp = position;
	++temp[0];
	--temp[1];
	positions.push_back(temp);

	temp = position;
	--temp[0];
	++temp[1];
	positions.push_back(temp);

	temp = position;
	++temp[0];
	++temp[1];
	positions.push_back(temp);

	for (int i = 0; i < positions.size(); ++i)
	{
		if (white)
		{
			if (positions[i][0] >= 'a' && positions[i][0] <= 'h' && positions[i][1] >= '1' && positions[i][1] <= '8')
			{
				if (field[positions[i][1] - 49][positions[i][0] - 97][0] != 'W')
					moves.push_back(positions[i]);
			}
		}
		else
		{
			if (positions[i][0] >= 'a' && positions[i][0] <= 'h' && positions[i][1] >= '1' && positions[i][1] <= '8')
			{
				if (field[positions[i][1] - 49][positions[i][0] - 97][0] != 'B')
					moves.push_back(positions[i]);
			}
		}
	}
}

const std::string& king::get_figure_name()
{
	return figure_name;
}

const std::string& king::get_figure_coordinats()
{
	return position;
}

const std::vector<std::string>& king::get_moves()
{
	return moves;
}

void king::set_figure_coordinats(const std::string& coord)
{
	position = coord;
	first_move = true;
}

bool king::get_type()
{
	if (white)
		return true;
	else
		return false;
}

bool king::was_first_move(int request_type)
{
	if (request_type)
		first_move = true;

	return first_move;
}
