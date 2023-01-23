#pragma once
#include "hand.h"
#include "player.h"

class game_round
{
public:
	game_round();

	void round_play(player& a_player, stack& a_stack);

	~game_round() { std::cout << "destroyed round" << std::endl; }

private:
	//score
	int m_player_score;
	//int m_bot_score;

};

game_round::game_round()
{
	std::cout << "game_round object created" << std::endl;
	m_player_score = 0;
	//m_bot_score = 0;
}

void game_round::round_play(player& a_player, stack& a_stack)
{
	//a_player.display_boneyard();
	a_player.draw();
	while (!a_player.is_hand_empty())
	{
		std::cout << "=============================================================================" << std::endl;

		a_stack.display_stack();
		a_player.display_hand();
		a_player.display_boneyard();
		std::cout << "=============================================================================" << std::endl;
		a_player.place(a_stack);
	}
	
	
	
	
}
