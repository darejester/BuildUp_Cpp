#pragma once
#include "hand.h"

class game_round
{
public:
	game_round(tiles* x);

	~game_round(){}

private:
	//hand holder
	hand* m_hand_ptr;
	//score
	int m_player_score;
	int m_bot_score;

};

game_round::game_round(tiles* x)
{
	std::cout << "game_round object created" << std::endl;
	m_player_score = 0;
	m_bot_score = 0;
	m_hand_ptr = new hand(x->player_draw());
}
