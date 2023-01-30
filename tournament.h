#pragma once
#include "game_round.h"
#include "stack.h"
#include "player.h"
#include "human.h"
#include "bot.h"

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
	int m_scoreboard[2][4];
	// holds number of rounds
	int m_game_round_counter;
};


tournament::tournament()
{
	m_scoreboard[1][1] = { 0 };
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
	// game loop
	while (m_game_round_counter < 4/*replace with something that I can equal to the number of rounds in tournament class*/)
	{
		//incremenet round_counter
		m_game_round_counter++;
		//initialize new round
		m_round = new game_round();
		//first pick if first round
		if (m_game_round_counter == 1)
		{
			m_round->first_pick(m_human,m_bot,m_turn_order, m_stack.get_stack());
		}
		
		//play
		m_round->round_play( m_human,m_bot,m_stack, m_turn_order);
		//score

		//continue?

		m_game_round_counter++;
	}
}

int tournament::next_round()
{
	m_game_round_counter++;
	return m_game_round_counter;
}
