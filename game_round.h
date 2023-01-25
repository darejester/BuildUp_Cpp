#pragma once
#include "player.h"

class game_round
{
public:
	game_round();

	void round_play( stack& a_stack, player* a_turn_order[2]);


	~game_round() { std::cout << "destroyed round" << std::endl; }

private:
	//score
	int m_player_score;
	int m_bot_score;
	

};

game_round::game_round()
{
	std::cout << "game_round object created" << std::endl;
	m_player_score = 0;
	m_bot_score = 0;
}

void game_round::round_play(stack& a_stack, player* a_turn_order[2])
{
	int action = -1;
	//a_turn_order[0]->display_boneyard();
	a_turn_order[0]->draw();
	a_turn_order[1]->draw();
	while (!a_turn_order[0]->is_hand_empty())
	{
		std::cout << "=============================================================================" << std::endl;
		a_turn_order[1]->display_boneyard();
		a_turn_order[1]->display_hand();
		a_stack.display_stack();
		a_turn_order[0]->display_hand();
		a_turn_order[0]->display_boneyard();
		std::cout << "=============================================================================" << std::endl;
		//replace .place(a_stack) with .place(a_stack.get_stack())
		std::cout << "ACTIONS:" << std::endl;
		std::cout << "1-Place card, ...." << std::endl;
		std::cin >> action;
		while (action < 1)
		{
			std::cout << "INPUT INVALID. Try again...." << std::endl;
			std::cin >> action;
		}
		//action decider
		if (action == 1)
		{
			a_turn_order[0]->place(a_stack);
		}
		else
		{

		}
		
	}
	
	
	
	
}
