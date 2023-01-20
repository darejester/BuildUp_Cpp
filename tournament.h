#pragma once
#include "game_round.h"
#include "tiles.h"

class tournament
{
public:
	//set up new game
		// create tiles
		// create 1st round
		// create hands
	tournament();
	//start game
	//resume game
	//save game
	//next round
		// create next round
		// pass tiles ptr to next round
	int next_round();

private:
	//round holder
	game_round* m_round_ptr;
	//tiles holder
	tiles* m_tiles_ptr;
	//score board holder(for whole tournament)
	int m_scoreboard[2][4];
	// holds number of rounds
	int m_game_round_counter;
};


tournament::tournament()
{
	m_tiles_ptr = new tiles;
	m_round_ptr = new game_round(m_tiles_ptr);
	m_scoreboard[1][1] = { 0 };
	m_game_round_counter = 1;
}

int tournament::next_round()
{
	m_game_round_counter++;
	return m_game_round_counter;
}
