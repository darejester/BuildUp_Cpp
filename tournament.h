#pragma once
#include "game_round.h"
#include "stack.h"
#include "player.h"

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
	player& get_player() { return m_player; }
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
	player m_player;

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
	m_round = NULL;
	m_player.fill_stack(m_stack.get_stack());
}

void tournament::start_tournament()
{
	// game loop
	while (m_game_round_counter < 4/*replace with something that I can equal to the number of rounds in tournament class*/)
	{
		//initialize new round
		m_round = new game_round();
		//play
		m_round->round_play(m_player, m_stack);
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
