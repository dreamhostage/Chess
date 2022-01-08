#include "stdafx.h"
#include "kNight.h"

kNight::kNight() {}

kNight::kNight(const std::string& position, bool type)
{
	this->position = position;

	white = type;

	if (white)
		figure_name = "WN";
	else
		figure_name = "BN";
}

void kNight::create_moves(const std::vector<std::vector<std::string>>& field)
{
	moves.clear();

	std::vector<std::string> positions;

	temp = position;
	temp[1] -= 2;
	--temp[0];
	positions.push_back(temp);

	temp = position;
	temp[1] -= 2;
	++temp[0];
	positions.push_back(temp);

	temp = position;
	temp[1] += 2;
	--temp[0];
	positions.push_back(temp);

	temp = position;
	temp[1] += 2;
	++temp[0];
	positions.push_back(temp);

	temp = position;
	temp[0] -= 2;
	--temp[1];
	positions.push_back(temp);

	temp = position;
	temp[0] -= 2;
	++temp[1];
	positions.push_back(temp);

	temp = position;
	temp[0] += 2;
	--temp[1];
	positions.push_back(temp);

	temp = position;
	temp[0] += 2;
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

const std::string& kNight::get_figure_name()
{
	return figure_name;
}

const std::string& kNight::get_figure_coordinats()
{
	return position;
}

const std::vector<std::string>& kNight::get_moves()
{
	return moves;
}

void kNight::set_figure_coordinats(const std::string& coord)
{
	position = coord;
}

bool kNight::get_type()
{
	if (white)
		return true;
	else
		return false;
}
