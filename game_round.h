#pragma once
#include "player.h"
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>

class game_round
{
public:
	game_round();
	//play round
	void round_play(player* a_human, player* a_bot, stack& a_stack, player* a_turn_order[2]);
	//pick first to play each round
	void first_pick(player* a_human,player* a_bot,player* a_turn_order[2], std::vector<domino*>& a_stack);
	//score
	void score(stack& a_stack,player* a_turn_order[2],int (&a_scoreboard)[2], int a_game_round_counter);


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

			a_turn_order[i]->player_play(a_stack,a_bot);

			

		}
	}
}
	


void game_round::first_pick(player* a_human, player* a_bot, player* a_turn_order[2], std::vector<domino*>& a_stack)
{
	std::cout << "first_pick() called " << std::endl;


	while (a_human->get_boneyard()[0]->total_pips() == a_bot->get_boneyard()[0]->total_pips())
	{
		std::random_shuffle(std::begin(a_human->get_boneyard()), std::end(a_human->get_boneyard()));
		std::random_shuffle(std::begin(a_bot->get_boneyard()), std::end(a_bot->get_boneyard()));
		std::cout << "shuffle" << std::endl;
	}

	if (a_human->get_boneyard()[0]->total_pips() > a_bot->get_boneyard()[0]->total_pips()) // if human has higher total pips count
	{
		a_turn_order[1] = a_bot;
		a_turn_order[0] = a_human;
		return;
	}
	else if (a_human->get_boneyard()[0]->total_pips() < a_bot->get_boneyard()[0]->total_pips()) // if bot has higher total pips count
	{
		a_turn_order[1] = a_human;
		a_turn_order[0] = a_bot;
		return;
	}

}

void game_round::score(stack& a_stack, player* a_turn_order[2], int(&a_scoreboard)[2], int a_game_round_counter)
{
	int bot_total = 0;
	int human_total = 0;

	std::vector<domino*>& stack_temp = a_stack.get_stack();
	std::vector<domino*>::iterator it;

	//std::cout << "score:" << std::endl;
	//it = stack_temp.begin();

	for (int p = 0; p < 2; p++)
	{
		for (int h = 0; h < a_turn_order[p]->get_hand().size(); h++)
		{
			if (a_turn_order[p]->get_hand()[h]->display_color() == 'B')
			{
				human_total -= a_turn_order[p]->get_hand()[h]->total_pips();
			}
			else if (a_turn_order[p]->get_hand()[h]->display_color() == 'W')
			{
				bot_total -= a_turn_order[p]->get_hand()[h]->total_pips();
			}
		}
	}
	//std::cout << "human: " << human_total << std::endl;
	//std::cout << "Bot: " << bot_total << std::endl;

	for (auto x : stack_temp)
	{
		if (x->display_color() == 'B')
		{
			human_total += x->total_pips();
		}
		else if (x->display_color() == 'W')
		{
			bot_total += x->total_pips();
		}
	}
	//std::cout << "human: " << human_total << std::endl;
	//std::cout << "Bot: " << bot_total << std::endl;

	a_scoreboard[0] += human_total;
	a_scoreboard[1] += bot_total;
	
	

}