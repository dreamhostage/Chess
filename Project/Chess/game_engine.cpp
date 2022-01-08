#include "stdafx.h"
#include "game_engine.h"

game_engine::game_engine()
{
	turn = false; // white turn - false; black turn - true;
	create_figures();
}

game_engine::~game_engine()
{
	for (int i = 0; i < figures.size(); ++i)
		if(figures[i])
			delete figures[i];

	for (int i = 0; i < simulated_figures.size(); ++i)
		if(simulated_figures[i])
			delete simulated_figures[i];
}

void game_engine::game_loop()
{
	while (true)
	{
	onemore:

		system("cls");
		display();

		if (check_check())
		{
			if (check_checkmate())
			{
				std::cout << "  _______________________________________\n";
				std::cout << " |                                       |\n";
				std::cout << " |              CHECKMATE!               |\n";

				if (!turn)
					std::cout << " |           Black player WIN            |\n";
				else
					std::cout << " |           White player WIN            |\n";
				std::cout << " |_______________________________________|\n";

				clear();
				create_figures();
				system("pause");
				break;
			}
			if (!turn)
				std::cout << "              [White's turn]\n";
			else
				std::cout << "              [Black's turn]\n";
			std::cout << "  _______________________________________\n";
			std::cout << " |                                       |\n";
			std::cout << " |                CHECK!                 |\n";
			std::cout << " |_______________________________________|\n";
		}
		else
		{
			if (!turn)
				std::cout << "              [White's turn]\n";
			else
				std::cout << "              [Black's turn]\n";
		}

		std::cout << "\n      Please type your command: -> ";
		std::getline(std::cin, command);

		if (command == "move")
		{
			if (!moving())
			{
				system("cls");
				goto onemore;
			}
		}
		else if ((command == "castling"))
		{
			std::cout << "    Please type rook coordinates: -> ";
			std::getline(std::cin, command);
			if (castling(command))
			{
				std::cout << "               OK!\n";
				system("pause");
			}
			else
			{
				system("pause");
				goto onemore;
			}
		}
		else if ((command == "restart"))
		{
			clear();
			create_figures();
			return;
		}
		else if ((command == "help"))
		{
			system("cls");
			std::cout << " |                White                  |\n";
			std::cout << " |_______________________________________|\n";
			std::cout << "    a   b    c    d    e    f    g    h\n";
			std::cout << "  ---------------------------------------\n";
			std::cout << "1|        Commands description:          |1\n";
			std::cout << " |                                       |\n";
			std::cout << "2|   help      --  show help             |2\n";
			std::cout << " |                                       |\n";
			std::cout << "3|   move      --  move figure           |3\n";
			std::cout << " |                                       |\n";
			std::cout << "4|   castling  --  make castling         |4\n";
			std::cout << " |                                       |\n";
			std::cout << "5|   save      --  save game             |5\n";
			std::cout << " |                                       |\n";
			std::cout << "6|   load      --  load game             |6\n";
			std::cout << " |                                       |\n";
			std::cout << "7|   restart   --  restart game          |7\n";
			std::cout << " |                                       |\n";
			std::cout << "8|                                       |8\n";
			std::cout << "  ---------------------------------------\n";
			std::cout << "    a   b    c    d    e    f    g    h\n";
			std::cout << "  _______________________________________\n";
			std::cout << " |                Black                  |\n";
			std::cout << " |                                       |\n";
			system("pause");
			goto onemore;
		}
		else if ((command == "save"))
		{
			if (save_game())
			{
				std::cout << "                   OK!\n";
				system("pause");
				goto onemore;
			}
			else
			{
				std::cout << "                  ERROR!\n";
				system("pause");
				goto onemore;
			}
		}
		else if ((command == "load"))
		{
			if (load_game())
			{
				std::cout << "                   OK!\n";
				system("pause");
				goto onemore;
			}
			else
			{
				std::cout << "                  ERROR!\n";
				system("pause");
				goto onemore;
			}
		}
		else
			goto onemore;

		system("cls");

		if (turn)
			turn = false;
		else
			turn = true;
	}
}

bool game_engine::moving()
{
	system("cls");
	display();
	std::cout << "\nPlease select the coordinates of the figure\n";
	std::cout << "        or type reset: -> ";
	std::getline(std::cin, command);
	if (command == "reset")
	{
		system("cls");
		return false;
	}

	while (!checking_figure_selection(command))
	{
		system("cls");
		display();
		std::cout << "\n   Incorrect selection. Please select the \n        coordinates of the figure\n            or type reset: -> ";
		std::getline(std::cin, command);
		if (command == "reset")
		{
			system("cls");
			return false;
		}
	}

	selected_position = command;
	selected_figure = game_field[(int)(selected_position[1] - '0') - 1][(int)(selected_position[0] - 96) - 1];

onemore:
	system("cls");
	display();
	std::cout << "\n     Select position for moving " << selected_figure << '(' << selected_position << ")\n";
	std::cout << "            or type reset: ";
	std::getline(std::cin, command);

	if (command == "reset")
	{
		system("cls");
		return false;
	}

	if (checking_figure_move(selected_position, command))
	{
		if (!simulation_check(selected_position, command))
		{
			make_move(selected_position, command);
		}
		else
		{
			std::cout << "  _______________________________________\n";
			std::cout << " |                                       |\n";
			std::cout << " |    This way you will get CHECKMATE!   |\n";
			std::cout << " |_______________________________________|\n";
			system("pause");
			goto onemore;
		}
	}
	else
	{
		std::cout << "You can't move this figure on such position!\n";
		system("pause");
		goto onemore;
	}

	return true;
}

bool game_engine::checking_figure_selection(const std::string& coordinats)
{
	if (coordinats.size() != 2)
		return false;

	int x = 0, y = 0;

	x = coordinats[0] - 96;
	y = coordinats[1] - '0';

	if (x < 1 || x > 8 || y < 1 || y > 8)
		return false;

	if (game_field[y - 1][x - 1] == "  ")
		return false;

	if (!turn && game_field[y - 1][x - 1][0] == 'B')
		return false;

	if (turn && game_field[y - 1][x - 1][0] == 'W')
		return false;

	return true;
}

void game_engine::create_figures()
{
	std::vector<std::string> empty_line;

	for (int i = 0; i < 8; ++i)
		empty_line.push_back("  ");

	for (int i = 0; i < 8; ++i)
		game_field.push_back(empty_line);

	for (int i = 0; i < 8; ++i)
		simulated_game_field.push_back(empty_line);

	for (int i = 0; i < 8; ++i)
	{
		temp = (char)(i + 97);
		temp += (char)50;
		figures.push_back(new pawn(temp, true));

		temp = (char)(i + 97);
		temp += (char)55;
		figures.push_back(new pawn(temp, false));

		if (!i)
		{
			temp = "a1";
			figures.push_back(new rook(temp, true));
			temp = "a8";
			figures.push_back(new rook(temp, false));
		}
		else if (i == 1)
		{
			temp = "b1";
			figures.push_back(new kNight(temp, true));
			temp = "b8";
			figures.push_back(new kNight(temp, false));
		}
		else if (i == 2)
		{
			temp = "c1";
			figures.push_back(new bishop(temp, true));
			temp = "c8";
			figures.push_back(new bishop(temp, false));
		}
		else if (i == 3)
		{
			temp = "d1";
			figures.push_back(new queen(temp, true));
			temp = "d8";
			figures.push_back(new queen(temp, false));
		}
		else if (i == 4)
		{
			temp = "e1";
			figures.push_back(new king(temp, true));
			temp = "e8";
			figures.push_back(new king(temp, false));
		}
		else if (i == 5)
		{
			temp = "f1";
			figures.push_back(new bishop(temp, true));
			temp = "f8";
			figures.push_back(new bishop(temp, false));
		}
		else if (i == 6)
		{
			temp = "g1";
			figures.push_back(new kNight(temp, true));
			temp = "g8";
			figures.push_back(new kNight(temp, false));
		}
		else if (i == 7)
		{
			temp = "h1";
			figures.push_back(new rook(temp, true));
			temp = "h8";
			figures.push_back(new rook(temp, false));
		}
	}

	update_map();
	update_moves();
}

bool game_engine::checking_figure_move(const std::string& position, const std::string& moving_coordinates)
{
	for (int i = 0; i < figures.size(); ++i)
	{
		if (position == figures[i]->get_figure_coordinats())
		{
			for (int k = 0; k < figures[i]->get_moves().size(); ++k)
			{
				if (moving_coordinates == figures[i]->get_moves()[k])
					return true;
			}
		}
	}

	return false;
}

void game_engine::make_move(const std::string& position, const std::string& moving_coordinates)
{
	auto it = figures.begin();
	while (it != figures.end())
	{
		if ((*it)->get_figure_coordinats() == moving_coordinates)
		{
			delete (*it);
			figures.erase(it);
			break;
		}
		++it;
	}

	it = figures.begin();
	while (it != figures.end())
	{
		if ((*it)->get_figure_coordinats() == position)
		{
			(*it)->set_figure_coordinats(moving_coordinates);
			update_moves();
			break;
		}
		++it;
	}
}

void game_engine::display()
{
	int line = 1;

	update_map();

	if(!turn)
		std::cout << " |            >>> White <<<              |\n";
	else
		std::cout << " |                White                  |\n";
	std::cout << " |_______________________________________|\n";
	std::cout << "    a   b    c    d    e    f    g    h\n";
	for (int i = 0; i < 8; ++i)
	{
		if (!i)
			std::cout << "  ---------------------------------------\n";
		else
			std::cout << " |----|----|----|----|----|----|----|----|\n";
		for (int k = 0; k < 8; ++k)
		{
			if (!k)
				std::cout << line;
			std::cout << "| " << game_field[i][k] << ' ';
		}
		std::cout << "|" << line++ << '\n';
	}
	std::cout << "  ---------------------------------------\n";
	std::cout << "    a   b    c    d    e    f    g    h\n";
	std::cout << "  _______________________________________\n";
	if (turn)
		std::cout << " |            >>> Black <<<              |\n";
	else
		std::cout << " |                Black                  |\n";
	std::cout << " |                                       |\n";
}

void game_engine::update_moves()
{
	update_map();

	for (int i = 0; i < figures.size(); ++i)
		figures[i]->create_moves(game_field);
}

void game_engine::update_map()
{
	for (int i = 0; i < game_field.size(); ++i)
		for (int k = 0; k < game_field[i].size(); ++k)
			game_field[i][k] = "  ";

	for (int i = 0; i < figures.size(); ++i)
	{
		temp = figures[i]->get_figure_coordinats();
		game_field[temp[1] - 49][temp[0] - 97] = figures[i]->get_figure_name();
	}
}

const std::string& game_engine::check_coordinates(const std::string& coord)
{
	int x = coord[0] - 97;
	int y = coord[1] - 49;

	return game_field[y][x];
}

bool game_engine::check_check()
{
	std::string WK_pos;
	std::string BK_pos;

	for (int i = 0; i < figures.size(); ++i)
	{
		if (figures[i]->get_figure_name() == "WK")
			WK_pos = figures[i]->get_figure_coordinats();
		else if (figures[i]->get_figure_name() == "BK")
			BK_pos = figures[i]->get_figure_coordinats();
	}

	for (int i = 0; i < figures.size(); ++i)
	{
		if (figures[i]->get_type())
		{
			for (int k = 0; k < figures[i]->get_moves().size(); ++k)
				if (figures[i]->get_moves()[k] == BK_pos)
					return true;
		}
		else
		{
			for (int k = 0; k < figures[i]->get_moves().size(); ++k)
				if (figures[i]->get_moves()[k] == WK_pos)
					return true;
		}
	}

	return false;
}

bool game_engine::check_checkmate()
{
	for (int i = 0; i < figures.size(); ++i)
	{
		if (!turn)
		{
			if (figures[i]->get_type())
			{
				for (int k = 0; k < figures[i]->get_moves().size(); ++k)
					if (!simulation_check(figures[i]->get_figure_coordinats(), figures[i]->get_moves()[k]))
						return false;
			}
		}
		else
		{
			if (!figures[i]->get_type())
			{
				for (int k = 0; k < figures[i]->get_moves().size(); ++k)
					if (!simulation_check(figures[i]->get_figure_coordinats(), figures[i]->get_moves()[k]))
						return false;
			}
		}
	}

	return true;
}

bool game_engine::simulation_check(const std::string& position, const std::string& moving_coordinates)
{
	// copy figures
	std::vector<std::string> empty_line;
	for (int i = 0; i < figures.size(); ++i)
	{
		if (figures[i]->get_figure_name() == "WP")
		{
			simulated_figures.push_back(new pawn(figures[i]->get_figure_coordinats(), true));
		}
		if (figures[i]->get_figure_name() == "BP")
		{
			simulated_figures.push_back(new pawn(figures[i]->get_figure_coordinats(), false));
		}
		if (figures[i]->get_figure_name() == "WK")
		{
			simulated_figures.push_back(new king(figures[i]->get_figure_coordinats(), true));
		}
		if (figures[i]->get_figure_name() == "BK")
		{
			simulated_figures.push_back(new king(figures[i]->get_figure_coordinats(), false));
		}
		if (figures[i]->get_figure_name() == "WQ")
		{
			simulated_figures.push_back(new queen(figures[i]->get_figure_coordinats(), true));
		}
		if (figures[i]->get_figure_name() == "BQ")
		{
			simulated_figures.push_back(new queen(figures[i]->get_figure_coordinats(), false));
		}
		if (figures[i]->get_figure_name() == "WR")
		{
			simulated_figures.push_back(new rook(figures[i]->get_figure_coordinats(), true));
		}
		if (figures[i]->get_figure_name() == "BR")
		{
			simulated_figures.push_back(new rook(figures[i]->get_figure_coordinats(), false));
		}
		if (figures[i]->get_figure_name() == "WN")
		{
			simulated_figures.push_back(new kNight(figures[i]->get_figure_coordinats(), true));
		}
		if (figures[i]->get_figure_name() == "BN")
		{
			simulated_figures.push_back(new kNight(figures[i]->get_figure_coordinats(), false));
		}
		if (figures[i]->get_figure_name() == "WB")
		{
			simulated_figures.push_back(new bishop(figures[i]->get_figure_coordinats(), true));
		}
		if (figures[i]->get_figure_name() == "BB")
		{
			simulated_figures.push_back(new bishop(figures[i]->get_figure_coordinats(), false));
		}
	}

	// make move
	auto it = simulated_figures.begin();
	while (it != simulated_figures.end())
	{
		if ((*it)->get_figure_coordinats() == moving_coordinates)
		{
			delete (*it);
			simulated_figures.erase(it);
			break;
		}
		++it;
	}

	it = simulated_figures.begin();
	while (it != simulated_figures.end())
	{
		if ((*it)->get_figure_coordinats() == position)
		{
			(*it)->set_figure_coordinats(moving_coordinates);
			break;
		}
		++it;
	}

	// update map
	for (int i = 0; i < simulated_game_field.size(); ++i)
		for (int k = 0; k < simulated_game_field[i].size(); ++k)
			simulated_game_field[i][k] = "  ";

	for (int i = 0; i < simulated_figures.size(); ++i)
	{
		temp = simulated_figures[i]->get_figure_coordinats();
		simulated_game_field[temp[1] - 49][temp[0] - 97] = simulated_figures[i]->get_figure_name();
	}

	// update all moves
	for (int i = 0; i < simulated_figures.size(); ++i)
		simulated_figures[i]->create_moves(simulated_game_field);

	//make check
	std::string king_pos;

	for (int i = 0; i < simulated_figures.size(); ++i)
	{
		if (!turn)
		{
			if (simulated_figures[i]->get_figure_name() == "WK")
				king_pos = simulated_figures[i]->get_figure_coordinats();
		}
		else
		{
			if (simulated_figures[i]->get_figure_name() == "BK")
				king_pos = simulated_figures[i]->get_figure_coordinats();
		}
	}

	for (int i = 0; i < simulated_figures.size(); ++i)
	{
		if (!turn)
		{
			if (!simulated_figures[i]->get_type())
			{
				for (int k = 0; k < simulated_figures[i]->get_moves().size(); ++k)
					if (simulated_figures[i]->get_moves()[k] == king_pos)
					{
						//clear
						for (int i = 0; i < simulated_figures.size(); ++i)
							delete simulated_figures[i];
						simulated_figures.clear();
						return true;
					}
			}
		}
		else
		{
			if (simulated_figures[i]->get_type())
			{
				for (int k = 0; k < simulated_figures[i]->get_moves().size(); ++k)
					if (simulated_figures[i]->get_moves()[k] == king_pos)
					{
						//clear
						for (int i = 0; i < simulated_figures.size(); ++i)
							delete simulated_figures[i];
						simulated_figures.clear();
						return true;
					}
			}
		}
	}

	//clear
	for (int i = 0; i < simulated_figures.size(); ++i)
		if(simulated_figures[i])
			delete simulated_figures[i];
	simulated_figures.clear();

	return false;
}

void game_engine::start_game()
{
	std::string command;

	while (true)
	{
		system("cls");
		std::cout << " |                White                  |\n";
		std::cout << " |_______________________________________|\n";
		std::cout << "    a   b    c    d    e    f    g    h\n";
		std::cout << "  ---------------------------------------\n";
		std::cout << "1|    |    | M  | E  | N  | U  |    |    |1\n";
		std::cout << " |----|----|----|----|----|----|----|----|\n";
		std::cout << "2|    |    |    |    |    |    |    |    |2\n";
		std::cout << " |----|----|----|----|----|----|----|----|\n";
		std::cout << "3|  1 | -- | S  | T  | A  | R  | T  |    |3\n";
		std::cout << " |----|----|----|----|----|----|----|----|\n";
		std::cout << "4|    |    |    |    |    |    |    |    |4\n";
		std::cout << " |----|----|----|----|----|----|----|----|\n";
		std::cout << "5|  2 | -- | L  | O  | A  | D  |    |    |5\n";
		std::cout << " |----|----|----|----|----|----|----|----|\n";
		std::cout << "6|    |    |    |    |    |    |    |    |6\n";
		std::cout << " |----|----|----|----|----|----|----|----|\n";
		std::cout << "7|  3 | -- | K  | E  | Y  | S  |    |    |7\n";
		std::cout << " |----|----|----|----|----|----|----|----|\n";
		std::cout << "8|    |    |    |    |    |    |    |    |8\n";

		std::cout << "  ---------------------------------------\n";
		std::cout << "    a   b    c    d    e    f    g    h\n";
		std::cout << "  _______________________________________\n";
		std::cout << " |                Black                  |\n";
		std::cout << " |                                       |\n";
		std::cout << "        ENTER YOUR CHOICE: ->> ";
		std::getline(std::cin, command);

		if (command.size())
		{
			if (command[0] == '1')
				game_loop();
			else if (command[0] == '2')
			{
				if (load_game())
				{
					std::cout << "                   OK!\n";
					system("pause");
					game_loop();
				}
				else
				{
					std::cout << "                 ERROR!\n";
					system("pause");
				}
			}
			else if (command[0] == '3')
			{
				system("cls");
				std::cout << " |                White                  |\n";
				std::cout << " |_______________________________________|\n";
				std::cout << "    a   b    c    d    e    f    g    h\n";
				std::cout << "  ---------------------------------------\n";
				std::cout << "1|        Commands description:          |1\n";
				std::cout << " |                                       |\n";
				std::cout << "2|   help      --  show help             |2\n";
				std::cout << " |                                       |\n";
				std::cout << "3|   move      --  move figure           |3\n";
				std::cout << " |                                       |\n";
				std::cout << "4|   castling  --  make castling         |4\n";
				std::cout << " |                                       |\n";
				std::cout << "5|   save      --  save game             |5\n";
				std::cout << " |                                       |\n";
				std::cout << "6|   load      --  load game             |6\n";
				std::cout << " |                                       |\n";
				std::cout << "7|   restart   --  restart game          |7\n";
				std::cout << " |                                       |\n";
				std::cout << "8|                                       |8\n";
				std::cout << "  ---------------------------------------\n";
				std::cout << "    a   b    c    d    e    f    g    h\n";
				std::cout << "  _______________________________________\n";
				std::cout << " |                Black                  |\n";
				std::cout << " |                                       |\n";
				system("pause");
			}
		}
	}
}

bool game_engine::castling(const std::string& rook_coordinates)
{
	if (check_check())
	{
		std::cout << "You have CHECK! At first do something with this!\n";
		return false;
	}

	king* king_ptr = NULL;
	rook* rook_ptr = NULL;
	std::string rook_position;
	std::string king_position;
	std::string new_king_position;
	std::string new_rook_position;
	std::vector<std::string> positions;
	int king_distance = 2;

	if (!turn)
	{
		for (int i = 0; i < figures.size(); ++i)
		{
			if(figures[i]->get_figure_name() == "WK")
				king_ptr = dynamic_cast<king*>(figures[i]);

			if (figures[i]->get_figure_name() == "WR")
			{
				if (figures[i]->get_figure_coordinats() == rook_coordinates)
				{
					rook_ptr = dynamic_cast<rook*>(figures[i]);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < figures.size(); ++i)
		{
			if (figures[i]->get_figure_name() == "BK")
				king_ptr = dynamic_cast<king*>(figures[i]);

			if (figures[i]->get_figure_name() == "BR")
			{
				if (figures[i]->get_figure_coordinats() == rook_coordinates)
				{
					rook_ptr = dynamic_cast<rook*>(figures[i]);
				}
			}
		}
	}

	if (!rook_ptr || !king_ptr)
	{
		if(!king_ptr)
			exit(777);
		std::cout << "   Incorrect input of the rook position!\n";
		return false;
	}

	if (rook_ptr->was_first_move() || king_ptr->was_first_move())
	{
		std::cout << " Error. You have already made first move!\n";
		return false;
	}

	rook_position = rook_ptr->get_figure_coordinats();
	king_position = king_ptr->get_figure_coordinats();

	if (rook_position[0] == 'a' && king_position[0] == 'e')
	{
		while (++rook_position[0] < king_position[0])
		{
			if (check_coordinates(rook_position) != "  ")
			{
				std::cout << "There are chessmen between your rook and king!\n";
				return false;
			}
		}
		--king_position[0];
		positions.push_back(king_position);
		--king_position[0];
		positions.push_back(king_position);
		temp = king_ptr->get_figure_coordinats();
		temp[0] -= 2;
		new_king_position = temp;
		++temp[0];
		new_rook_position = temp;
	}
	else if (rook_position[0] == 'h' && king_position[0] == 'e')
	{
		positions.push_back(rook_position);
		while (--rook_position[0] > king_position[0])
		{
			positions.push_back(rook_position);
			if (check_coordinates(rook_position) != "  ")
			{
				std::cout << "There are chessmen between your rook and king!\n";
				return false;
			}
		}
		++king_position[0];
		positions.push_back(king_position);
		++king_position[0];
		positions.push_back(king_position);
		temp = king_ptr->get_figure_coordinats();
		temp[0] += 2;
		new_king_position = temp;
		--temp[0];
		new_rook_position = temp;
	}

	for (int i = 0; i < positions.size(); ++i)
	{
		if (simulation_check(king_ptr->get_figure_coordinats(), positions[i]))
		{
			std::cout << "   Error! Moving position is under attack!\n";
			return false;
		}
	}

	king_ptr->set_figure_coordinats(new_king_position);
	rook_ptr->set_figure_coordinats(new_rook_position);

	king_ptr->was_first_move(1);
	rook_ptr->was_first_move(1);

	update_moves();

	return true;
}

void game_engine::clear()
{
	turn = false;

	for (int i = 0; i < figures.size(); ++i)
		if (figures[i])
			delete figures[i];

	for (int i = 0; i < simulated_figures.size(); ++i)
		if (simulated_figures[i])
			delete simulated_figures[i];

	figures.clear();
	simulated_figures.clear();
	game_field.clear();
	simulated_game_field.clear();
}

bool game_engine::save_game()
{
	std::ofstream file("save.dat");

	char trn[2];
	if (turn)
		trn[0] = '1';
	else
		trn[0] = '0';
	trn[1] = '\0';

	if (!file.is_open())
		return false;

	char keyword[9] = "savedata";
	int size = figures.size();
	char c_size[5];
	sprintf_s(c_size, "%d", size);
	
	file.write(keyword, sizeof(keyword));

	file.write(trn, 2);

	file.write(c_size, sizeof(c_size));
	
	for (int i = 0; i < size; ++i)
	{
		if (figures[i]->get_figure_name()[1] != 'K' && figures[i]->get_figure_name()[1] != 'R')
		{
			file.write(&figures[i]->get_figure_name()[0], 3);
			file.write(&figures[i]->get_figure_coordinats()[0], 3);
		}
		else
		{
			if (figures[i]->get_figure_name()[1] == 'K')
			{
				file.write(&figures[i]->get_figure_name()[0], 3);
				file.write(&figures[i]->get_figure_coordinats()[0], 3);

				king* p = dynamic_cast<king*>(figures[i]);

				if (!p)
					return false;

				if (p->was_first_move())
				{
					trn[0] = '1';
					trn[1] = '\0';
					file.write(trn, 2);
				}
				else
				{
					trn[0] = '0';
					trn[1] = '\0';
					file.write(trn, 2);
				}
			}
			else if (figures[i]->get_figure_name()[1] == 'R')
			{
				file.write(&figures[i]->get_figure_name()[0], 3);
				file.write(&figures[i]->get_figure_coordinats()[0], 3);

				rook* p = dynamic_cast<rook*>(figures[i]);

				if (!p)
					return false;

				if (p->was_first_move())
				{
					trn[0] = '1';
					trn[1] = '\0';
					file.write(trn, 2);
				}
				else
				{
					trn[0] = '0';
					trn[1] = '\0';
					file.write(trn, 2);
				}
			}
		}
	}
	
	file.close();

	return true;
}

bool game_engine::load_game()
{
	char check[9];
	char data[4];
	char trn[2];
	char count[5];
	int n = 0;
	std::ifstream file2("save.dat");

	if (!file2.is_open())
		return false;

	file2.read(check, sizeof(check));
	file2.read(trn, 2);
	file2.read(count, sizeof(count));
	n = atoi(count);

	if (!strcmp(check, "savedata"))
	{
		clear();

		if (trn[0] == '1')
		{
			turn = true;
		}
		else
		{
			turn = false;
		}

		for (int i = 0; i < n; ++i)
		{
			file2.read(data, 3);

			if (!strcmp(data, "WP"))
			{
				file2.read(data, 3);
				figures.push_back(new pawn(data, true));
			}
			else if (!strcmp(data, "BP"))
			{
				file2.read(data, 3);
				figures.push_back(new pawn(data, false));
			}
			else if (!strcmp(data, "WN"))
			{
				file2.read(data, 3);
				figures.push_back(new kNight(data, true));
			}
			else if (!strcmp(data, "BN"))
			{
				file2.read(data, 3);
				figures.push_back(new kNight(data, false));
			}
			else if (!strcmp(data, "WB"))
			{
				file2.read(data, 3);
				figures.push_back(new bishop(data, true));
			}
			else if (!strcmp(data, "BB"))
			{
				file2.read(data, 3);
				figures.push_back(new bishop(data, false));
			}
			else if (!strcmp(data, "WQ"))
			{
				file2.read(data, 3);
				figures.push_back(new queen(data, true));
			}
			else if (!strcmp(data, "BQ"))
			{
				file2.read(data, 3);
				figures.push_back(new queen(data, false));
			}
			else if (!strcmp(data, "WK"))
			{
				file2.read(data, 3);
				figures.push_back(new king(data, true));
				file2.read(trn, 2);
				if (trn[0] == '1')
					dynamic_cast<king*>(figures.back())->was_first_move(1);
			}
			else if (!strcmp(data, "BK"))
			{
				file2.read(data, 3);
				figures.push_back(new king(data, false));
				file2.read(trn, 2);
				if (trn[0] == '1')
					dynamic_cast<king*>(figures.back())->was_first_move(1);
			}
			else if (!strcmp(data, "WR"))
			{
				file2.read(data, 3);
				figures.push_back(new rook(data, true));
				file2.read(trn, 2);
				if (trn[0] == '1')
					dynamic_cast<rook*>(figures.back())->was_first_move(1);
			}
			else if (!strcmp(data, "BR"))
			{
				file2.read(data, 3);
				figures.push_back(new rook(data, false));
				file2.read(trn, 2);
				if (trn[0] == '1')
					dynamic_cast<rook*>(figures.back())->was_first_move(1);
			}
		}

		std::vector<std::string> empty_line;

		for (int i = 0; i < 8; ++i)
			empty_line.push_back("  ");

		for (int i = 0; i < 8; ++i)
			game_field.push_back(empty_line);

		for (int i = 0; i < 8; ++i)
			simulated_game_field.push_back(empty_line);

		update_moves();

		file2.close();

		if (n == figures.size())
			return true;
		else
			return false;
	}
	else
	{
		file2.close();
		return false;
	}
}