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
	player& get_player() { return m_players; }
	stack& get_stack() { return m_stack; }
	//resume game
	//save game
	//next round
		// create next round
		// pass stack ptr to next round
	int next_round();

private:
	//stack holder
	stack m_stack;
	//player holder
	player m_players;
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
	m_game_round_counter = 1;
	m_round = NULL;
}

void tournament::start_tournament()
{
	m_round = new game_round();
	m_round->round_play(m_players,m_stack);
}

int tournament::next_round()
{
	m_game_round_counter++;
	return m_game_round_counter;
}
