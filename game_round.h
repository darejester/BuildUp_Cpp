#pragma once
#include "player.h"

class game_round
{
public:
	game_round();
	//play round
	void round_play(player* a_human, player* a_bot, stack& a_stack, player* a_turn_order[2]);
	//pick first to play each round
	void first_pick(player* a_human,player* a_bot,player* a_turn_order[2], std::vector<domino*>& a_stack);


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

void game_round::round_play(player* a_human, player* a_bot, stack& a_stack, player* a_turn_order[2])
{
	
	//a_turn_order[0]->display_boneyard();
	// human and bot draw
	a_turn_order[0]->draw();
	a_turn_order[1]->draw();
	for (int i = 0; i < 2; i++)
	{
		while (a_turn_order[i]->check_playable(a_turn_order[i]->get_hand(),a_stack.get_stack()))
		{
			std::cout << "=============================================================================" << std::endl;
			std::cout << "TURN: " << (a_turn_order[i]->get_hand())[0]->display_color() << std::endl;
			std::cout << "=============================================================================" << std::endl;
			a_bot->display_boneyard();
			a_bot->display_hand();
			a_stack.display_stack();
			a_human->display_hand();
			a_human->display_boneyard();
			std::cout << "=============================================================================" << std::endl;
			//replace .place(a_stack) with .place(a_stack.get_stack())

			a_turn_order[i]->player_play(a_stack);

			

		}
	}
	}
	


void game_round::first_pick(player* a_human, player* a_bot, player* a_turn_order[2], std::vector<domino*>& a_stack)
{
	std::cout << "first_pick() called " << std::endl;
	// 0-5 = bot's first 6, 6-11 = human's first 6
	for (int i = 0; i < 6; i++)
	{
		if (a_stack[i]->total_pips() > a_stack[i + 6]->total_pips()) // if bot has higher total pips count
		{
			a_turn_order[0] = a_bot;
			a_turn_order[1] = a_human;
			return;
		}
		else if (a_stack[i]->total_pips() < a_stack[i + 6]->total_pips()) // if player has higher total pips count
		{
			a_turn_order[0] = a_human;
			a_turn_order[1] = a_bot;
			return;
		}
		else // if bot and player has equal total pips count
		{
			continue;
		}
	}

}