#pragma once
#include "game_round.h"
#include "stack.h"
#include "player.h"
#include "human.h"
#include "bot.h"
#include <numeric>
#include <fstream>
#include <string>
#include <sstream>

class tournament
{
public:
	//set up new game
		// create stack
		// create 1st round
		// create hands
	tournament();
	tournament* get_tournament() { return this; }
	//start game
	void start_tournament();
	// get reference of m_players
	player& get_player() { return *m_human; }
	// get reference of m_stack
	stack& get_stack() { return m_stack; }
	//resume game
	void resume_tournament();
	void read_to_stack(std::string a_temp);
	void read_to_player(std::string a_temp1, std::string a_temp2, std::string a_temp3, std::string a_temp4);
	void read_to_score(std::string a_temp1, std::string a_temp2, std::string a_temp3, std::string a_temp4);
	void read_in_turn(std::string a_temp);
	//save game
	void save_game();
	//next round
		// create next round
		// pass stack ptr to next round
	//int next_round();
	~tournament() { std::cout << "destroyed tournament" << std::endl; delete m_human; delete m_bot; }

private:
	//stack holder
	stack m_stack;
	//player holder
	human* m_human;
	bot* m_bot;
	//turn holder
	player* m_turn_order[2];
	//round holder
	game_round* m_round;
	//score board holder(for whole tournament)
	int m_scoreboard[2];
	// holds number of rounds
	int m_game_round_counter;
	// holds tournament scoreboard
	int m_tournament_scoreboard[2];
};


tournament::tournament()
{
	m_scoreboard[1] = { 0 };	
	m_game_round_counter = 0;
	m_stack.get_stack().clear();
	m_round = NULL;
	m_bot = new bot;
	m_bot->fill_stack(m_stack.get_stack());
	m_human = new human;
	m_human->fill_stack(m_stack.get_stack());
	m_turn_order[0] = NULL;
	m_turn_order[1] = NULL;
	m_tournament_scoreboard[0] = 0;
	m_tournament_scoreboard[1] = 0;
	//m_turn_order[0] = m_human;
	//m_turn_order[1] = m_bot;
	//m_turn_order[1]->fill_stack(m_stack.get_stack());
	//m_turn_order[0]->fill_stack(m_stack.get_stack());
	
}

void tournament::start_tournament()
{
	int continue_game = 1;
	int continued_tournament = 0;
	// game loop
	while (continue_game == 1)
	{
		//continue_game = 0;

		//incremenet round_counter
		//m_game_round_counter++;
		
		//initialize new round
		m_round = new game_round();
		//first pick if first round
		if (m_human->get_boneyard().size() == 22)
		{
			m_round->first_pick(m_human,m_bot,m_turn_order, m_stack.get_stack());
		}
		//std::cout << "ROUND: " << m_game_round_counter+1 << std::endl;
		
		//scoreboard
		//std::cout << "Scoreboard: " << std::endl;
		//std::cout << "B : " << m_scoreboard[0] << std::endl;
		//std::cout << "W : " << m_scoreboard[1] << std::endl;
		std::cout << "ROUND SCOREBOARD" << std::endl;
		std::cout << "B : " << m_scoreboard[0] << std::endl;
		std::cout << "W : " << m_scoreboard[1] << std::endl;

		std::cout << "TOURNAMENT SCOREBOARD" << std::endl;
		std::cout << "B: " << m_tournament_scoreboard[0];
		std::cout << std::endl;
		std::cout << "W: " << m_tournament_scoreboard[1];
		std::cout << std::endl;

		//play
		if (m_round->round_play(m_human, m_bot, m_stack, m_turn_order, m_scoreboard))
		{
			//save game
			save_game();
			return;
		}
		else
		{
			//continue playing
		}
		

		//display
		m_bot->display_boneyard();
		m_bot->display_hand();
		m_stack.display_stack();
		m_human->display_hand();
		m_human->display_boneyard();

		//score
		m_round->score(m_stack, m_turn_order, m_scoreboard);

		

		//clear hands
 		for (auto x : m_turn_order)
		{
			x->get_hand().clear();
		}

		//continue?
		if (m_human->get_boneyard().empty())
		{
			//update tournament scoreboard
			if (m_scoreboard[0] > m_scoreboard[1])
			{
				m_tournament_scoreboard[0]++;
			}
			else if (m_scoreboard[0] < m_scoreboard[1])
			{
				m_tournament_scoreboard[1]++;
			}
			else if (m_scoreboard[0] == m_scoreboard[1])
			{
				m_tournament_scoreboard[0]++;
				m_tournament_scoreboard[1]++;
			}

			//B = player, W = bot
			std::cout << "End of Round Scores: " << std::endl;
			std::cout << "B : " << m_scoreboard[0] << std::endl;
			std::cout << "W : " << m_scoreboard[1] << std::endl;
			std::cout << "Do you want to continue onto the next tournament?" << std::endl;
			std::cout << "1 = continue, 0 = exit" << std::endl;
			std::cin >> continue_game;
			while ((continue_game > 1) || (continue_game < 0))
			{
				std::cout << "input invalid. plase try again..." << std::endl;
				std::cin >> continue_game;
			}

			if (continue_game == 1)
			{
				

				m_game_round_counter = 0;
				delete m_bot;
				m_bot = new bot;
				m_bot->fill_stack(m_stack.get_stack());
				delete m_human;
				m_human = new human;
				m_human->fill_stack(m_stack.get_stack());
				m_turn_order[0] = NULL;
				m_turn_order[1] = NULL;
				m_scoreboard[0] = 0;
				m_scoreboard[1] = 0;
				continued_tournament = 1;
				continue;
			}
			else // display winner
			{
				if ((m_tournament_scoreboard[0] > m_tournament_scoreboard[1]))
				{
					std::cout << "WINNER: HUMAN!" << std::endl;
				}
				else if (m_tournament_scoreboard[0] < m_tournament_scoreboard[1])
				{
					std::cout << "WINNER: BOT!" << std::endl;
				}
				else
				{
					std::cout << "DRAW!" << std::endl;
				}
					
			}
		}
		
		m_game_round_counter++;
	}
}

/* *********************************************************************
Function Name: resume_tournament
Purpose: responsible for reading from file and resuming a saved game
Parameters: None

Return Value: None
Algorithm:
			1) clear stack, all hands, and all boneyards
			2) read from file
			3) put each line in a vector
			4) pass each line to respective functions that handle the information
Assistance Received: none
********************************************************************* */
void tournament::resume_tournament() 
{ 
	//read from save file
	//std::cout << "to be implemented" << std::endl; 
	//clear out stack
	m_stack.get_stack().clear();
	//clear out player infos
	m_human->get_hand().clear();
	m_human->get_boneyard().clear();
	m_bot->get_hand().clear();
	m_bot->get_boneyard().clear();

	std::ifstream file("OPLsaveFile.txt");
	std::vector<std::string> hand_temp;
	std::vector<std::string> stack_temp;
	std::vector<std::string> divided_line;
	std::string line;

	
	if (!file.eof()) 
	{
		//divide line into a vector
		while (std::getline(file, line)) 
		{  
			divided_line.push_back(line);
		}
		//read in stacks
		read_to_stack(divided_line[1]);
		read_to_stack(divided_line[8]);
		//m_stack.display_stack();

		//read in player infos
		read_to_player(divided_line[2],divided_line[3],divided_line[9],divided_line[10]);

		//read in scores
		read_to_score(divided_line[4], divided_line[11],divided_line[5],divided_line[12]);

		//read in turn
		read_in_turn(divided_line[14]);


		file.close();  // Close the file when you're done

		//start tournament where it left off
		start_tournament();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
	}
}

/* *********************************************************************
Function Name: read_to_stack
Purpose: reads in stacks for each player
Parameters:
	a_temp
		holds the string passed and parses it to get the stacks for respective players

Return Value: None
Algorithm:
			1) skip the label
			2) insert each domino into stack
Assistance Received: none
********************************************************************* */
void tournament::read_to_stack(std::string a_temp) 
{
	std::istringstream iss(a_temp);
	std::string word;
	while (iss >> word)
	{
		if (word == "Stacks:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_stack.get_stack().push_back(new domino(int(word[1]) - 48, int(word[2]) - 48, word[0]));
		//idx++;
	}
	
}

/* *********************************************************************
Function Name: read_to_player
Purpose: reads in boneyards and hands for each player
Parameters:
	a_temp1
		holds the string passed and parses it to get the boneyard for bot
	a_temp2
		holds the string passed and parses it to get the hand for bot
	a_temp3
		holds the string passed and parses it to get the boneyard for human
	a_temp4
		holds the string passed and parses it to get the hand for human

Return Value: None
Algorithm:
			1) skip all the labels
			2) insert each information from the file to their respective containers
Assistance Received: none
********************************************************************* */
void tournament::read_to_player(std::string a_temp1, std::string a_temp2, std::string a_temp3, std::string a_temp4)
{
	//1 = bot boneyard, 2 = bot hand, 3 = human boneyard, 4 = human hand
	std::vector<domino*> a_temp_hand;
	std::vector<domino*> a_temp_boneyard;
	std::istringstream iss1(a_temp1);
	std::istringstream iss2(a_temp2);
	std::istringstream iss3(a_temp3);
	std::istringstream iss4(a_temp4);

	std::string word;

	//bot
	while (iss1 >> word)
	{
		if (word == "Boneyard:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_bot->get_boneyard().push_back(new domino(int(word[1]) - 48, int(word[2]) - 48, word[0]));
		//idx++;
	}
	while (iss2 >> word)
	{
		if (word == "Hand:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_bot->get_hand().push_back(new domino(int(word[1]) - 48, int(word[2]) - 48, word[0]));
		//idx++;
	}

	//human
	while (iss3 >> word)
	{
		if (word == "Boneyard:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_human->get_boneyard().push_back(new domino(int(word[1]) - 48, int(word[2]) - 48, word[0]));
		//idx++;
	}
	while (iss4 >> word)
	{
		if (word == "Hand:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_human->get_hand().push_back(new domino(int(word[1]) - 48, int(word[2]) - 48, word[0]));
		//idx++;
	}


}

/* *********************************************************************
Function Name: read_to_score
Purpose: reads in scores and rounds won for each player
Parameters:
	a_temp1
		holds the string passed and parses it to get the score for bot
	a_temp2
		holds the string passed and parses it to get the rounds won for bot
	a_temp3
		holds the string passed and parses it to get the score for human
	a_temp4
		holds the string passed and parses it to get the rounds for human

Return Value: None
Algorithm:
			1) skip all the labels
			2) insert each information from the file to their respective containers
Assistance Received: none
********************************************************************* */
void tournament::read_to_score(std::string a_temp1, std::string a_temp2, std::string a_temp3, std::string a_temp4)
{
	std::istringstream iss1(a_temp1);
	std::istringstream iss2(a_temp2);
	std::istringstream iss3(a_temp3);
	std::istringstream iss4(a_temp4);
	std::string word;
	//bot
	while (iss1 >> word)
	{
		if (word == "Score:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_scoreboard[1] = stoi(word);
		//idx++;
	}
	while (iss3 >> word)
	{
		if (word == "Rounds" || word == "Won:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_tournament_scoreboard[1] += stoi(word);
		//idx++;
	}

	//human
	while (iss2 >> word)
	{
		if (word == "Score:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_scoreboard[0] = stoi(word);
		//idx++;
	}
	while (iss4 >> word)
	{
		if (word == "Rounds" || word == "Won:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		m_tournament_scoreboard[0] += stoi(word);
		//idx++;
	}
	
}

/* *********************************************************************
Function Name: read_in_turn
Purpose: reads in whos turn it is to play 
Parameters:
	a_temp
		holds the string passed and parses it to get the next player to play

Return Value: None
Algorithm:
			1) skip the label
			2) update turn order with correct information
Assistance Received: none
********************************************************************* */
void tournament::read_in_turn(std::string a_temp)
{
	std::istringstream iss1(a_temp);
	std::string word;
	while (iss1 >> word)
	{
		if (word == "Turn:")
		{
			continue;
		}
		//std::cout << word[1] << std::endl;
		if (word == "Human")
		{
			m_turn_order[0] = m_human;
			m_turn_order[1] = m_bot;
		}
		else if (word == "Computer")
		{
			m_turn_order[0] = m_bot;
			m_turn_order[1] = m_human;
		}
		
		//idx++;
	}
}

/* *********************************************************************
Function Name: save_game
Purpose: responsible for saving the game onto a text file
Parameters:None

Return Value: None
Algorithm:
			1) Set up format for the information to go in
			2) write all information to file
Assistance Received: none
********************************************************************* */
void tournament::save_game()
{
	std::ofstream out_file;

	out_file.open("OPLsaveFile.txt");

	//bot write
	out_file << "Computer:" << std::endl;
	out_file << "   Stacks: ";
	for (int i = 0; i < 6; i++)
	{
		out_file << m_stack.get_stack()[i]->display_color()<< m_stack.get_stack()[i]->display_l_pips() << m_stack.get_stack()[i]->display_r_pips() << " ";
	}
	out_file << std::endl;
	out_file << "   Boneyard: ";
	if (!m_bot->get_boneyard().empty())
	{
		for (auto x : m_bot->get_boneyard())
		{
			out_file << x->display_color() << x->display_l_pips() << x->display_r_pips() << " ";
		}
	}
	else
	{
		out_file << "";
	}
	out_file << std::endl;
	out_file << "   Hand: ";
	if (!m_bot->get_hand().empty())
	{
		for (auto x : m_bot->get_hand())
		{
			out_file << x->display_color() << x->display_l_pips() << x->display_r_pips() << " ";
		}
	}
	else
	{
		out_file << "";
	}
	out_file << std::endl;
	out_file << "   Score: " << m_scoreboard[1];
	out_file << std::endl;
	out_file << "   Rounds Won: " << m_tournament_scoreboard[1];
	out_file << std::endl;
	out_file << std::endl;

	//human write
	out_file << "Human:" << std::endl;
	out_file << "   Stacks: ";
	for (int i = 6; i < 12; i++)
	{
		out_file << m_stack.get_stack()[i]->display_color() << m_stack.get_stack()[i]->display_l_pips() << m_stack.get_stack()[i]->display_r_pips() << " ";
	}
	out_file << std::endl;
	out_file << "   Boneyard: ";
	if (!m_human->get_boneyard().empty())
	{
		for (auto x : m_human->get_boneyard())
		{
			out_file << x->display_color() << x->display_l_pips() << x->display_r_pips() << " ";
		}
	}
	else
	{
		out_file << "";
	}
	out_file << std::endl;
	out_file << "   Hand: ";
	if (!m_human->get_hand().empty())
	{
		for (auto x : m_human->get_hand())
		{
			out_file << x->display_color() << x->display_l_pips() << x->display_r_pips() << " ";
		}
	}
	else
	{
		out_file << "";
	}
	out_file << std::endl;
	out_file << "   Score: " << m_scoreboard[0];
	out_file << std::endl;
	out_file << "   Rounds Won: " << m_tournament_scoreboard[0];
	out_file << std::endl;
	out_file << std::endl;

	out_file << "Turn: ";
	if (m_turn_order[m_round->get_turn()]->get_id() == 'B')
	{
		out_file << "Human";
	}
	else if(m_turn_order[m_round->get_turn()]->get_id() == 'W')
	{
		out_file << "Computer";
	}
	else
	{
		out_file << "";
	}


	out_file.close();
}