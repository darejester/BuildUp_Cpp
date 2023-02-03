#pragma once
#include "game_round.h"
#include "stack.h"
#include "player.h"
#include "human.h"
#include "bot.h"
#include <numeric>

class tournament
{
public:
	//set up new game
		// create stack
		// create 1st round
		// create hands
	tournament();
	//start game
	void start_tournament();
	// get reference of m_players
	player& get_player() { return *m_human; }
	// get reference of m_stack
	stack& get_stack() { return m_stack; }
	//resume game
	void resume_tournament() { std::cout << "to be implemented" << std::endl; }
	//save game
	//next round
		// create next round
		// pass stack ptr to next round
	int next_round();

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
	std::vector<int> m_tournament_scoreboard[2];
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
	while (continue_game == 1/*replace with something that I can equal to the number of rounds in tournament class*/)
	{
		//continue_game = 0;

		//incremenet round_counter
		//m_game_round_counter++;
		//initialize new round
		m_round = new game_round();
		//first pick if first round
		if (m_game_round_counter == 0)
		{
			m_round->first_pick(m_human,m_bot,m_turn_order, m_stack.get_stack());
		}
		//std::cout << "ROUND: " << m_game_round_counter+1 << std::endl;
		
		//scoreboard
		//std::cout << "Scoreboard: " << std::endl;
		//std::cout << "B : " << m_scoreboard[0] << std::endl;
		//std::cout << "W : " << m_scoreboard[1] << std::endl;
		if (continued_tournament == 1)
		{
			std::cout << "TOURNAMENT SCOREBOARD" << std::endl;
			std::cout << "B: ";
			for (int i = 0; i < m_tournament_scoreboard[0].size(); i++)
			{
				 std::cout<< m_tournament_scoreboard[0][i] << " ";
			}
			std::cout << std::endl;
			std::cout << "W: ";
			for (int i = 0; i < m_tournament_scoreboard[1].size(); i++)
			{
				 std::cout<< m_tournament_scoreboard[1][i] << " ";
			}
			std::cout << std::endl;
		}

		//play
		m_round->round_play( m_human,m_bot,m_stack, m_turn_order);

		//display
		m_bot->display_boneyard();
		m_bot->display_hand();
		m_stack.display_stack();
		m_human->display_hand();
		m_human->display_boneyard();

		//score
		m_round->score(m_stack, m_turn_order, m_scoreboard, m_game_round_counter);

		//clear hands
 		for (auto x : m_turn_order)
		{
			x->get_hand().clear();
		}

		//continue?
		if (m_game_round_counter == 3)
		{
			//B = player, W = bot
			std::cout << "End of Round Scores: " << std::endl;
			std::cout << "B : " << m_scoreboard[0] << std::endl;
			std::cout << "W : " << m_scoreboard[1] << std::endl;
			std::cout << "Do you want to continue onto the next tournament?" << std::endl;
			std::cout << "1 = continue, 0 = exit, 2 = save" << std::endl;
			std::cin >> continue_game;
			while ((continue_game > 2) || (continue_game < 0))
			{
				std::cout << "input invalid. plase try again..." << std::endl;
				std::cin >> continue_game;
			}

			if (continue_game == 1)
			{
				//update tournament scoreboard
				if (m_turn_order[0] > m_turn_order[1])
				{
					m_tournament_scoreboard[0].push_back(1);
					m_tournament_scoreboard[1].push_back(0);
				}
				else if (m_turn_order[0] < m_turn_order[1])
				{
					m_tournament_scoreboard[1].push_back(1);
					m_tournament_scoreboard[0].push_back(0);
				}

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
			else if (continue_game == 2)
			{
				//call save function
			}
			else // display winner
			{
				if (std::accumulate(m_tournament_scoreboard[0].begin(), m_tournament_scoreboard[0].end(), 0) > std::accumulate(m_tournament_scoreboard[1].begin(), m_tournament_scoreboard[1].end(), 0))
				{
					std::cout << "WINNER: HUMAN!" << std::endl;
				}
				else if (std::accumulate(m_tournament_scoreboard[0].begin(), m_tournament_scoreboard[0].end(), 0) < std::accumulate(m_tournament_scoreboard[1].begin(), m_tournament_scoreboard[1].end(), 0))
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

int tournament::next_round()
{
	m_game_round_counter++;
	return m_game_round_counter;
}
