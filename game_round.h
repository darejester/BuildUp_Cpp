#pragma once
#include "tournament.h"
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
	bool round_play(player* a_human, player* a_bot, stack& a_stack, player* a_turn_order[2], int* a_scoreboard);
	//pick first to play each round
	void first_pick(player* a_human,player* a_bot,player* a_turn_order[2], std::vector<domino*>& a_stack);
	//score
	void score(stack& a_stack,player* a_turn_order[2],int* a_scoreboard);
	//get turn
	int get_turn() { return m_turn; }
	


	~game_round() { std::cout << "destroyed round" << std::endl; }

private:
	int m_turn;
	

};

game_round::game_round()
{
	std::cout << "game_round object created" << std::endl;
	m_turn = 0;
}

/* *********************************************************************
Function Name: round_play
Purpose: manages a round where players place down all of their dominos in their hand onto the stacks 
Parameters:
	a_human
		a player object that is for the human player 
	a_bot
		a player object that is for the bot player
	a_stack
		the stack object where players place their dominos on
	a_turn_order
		an array of player object pointers to handle the turn order when playing
	a_scoreboard
		an integer array that keeps record of both players' scores

Return Value: boolean that represents whether player should continue playing or save the game
Algorithm:
			1) check if both players' hands are empty, if they are, draw
			2) players take turn placing dominos in a loop until both players dont have a domino that is playable
			3) ask player if they want to save the game or not
			4) continue the game or save the game depending on player input
Assistance Received: none
********************************************************************* */
bool game_round::round_play(player* a_human, player* a_bot, stack& a_stack, player* a_turn_order[2], int* a_scoreboard)
{
	int ans = -1;

	
	//a_turn_order[0]->display_boneyard();
	// human and bot draw
	if (a_turn_order[0]->get_hand().empty() && a_turn_order[1]->get_hand().empty())
	{
		a_turn_order[0]->draw();
		a_turn_order[1]->draw();
	}
	
	
	//until there is a playable domino in either player's hand
	while (a_turn_order[0]->check_playable(a_turn_order[0]->get_hand(),a_stack.get_stack()) || a_turn_order[1]->check_playable(a_turn_order[1]->get_hand(), a_stack.get_stack()))
	{
		

		std::cout << "=============================================================================" << std::endl;
		std::cout << "TURN: " << (a_turn_order[m_turn]->get_hand())[0]->display_color() << std::endl;
		std::cout << "=============================================================================" << std::endl;
		a_bot->display_boneyard();
		a_bot->display_hand();
		a_stack.display_stack();
		a_human->display_hand();
		a_human->display_boneyard();
		std::cout << "=============================================================================" << std::endl;
		//replace .place(a_stack) with .place(a_stack.get_stack())

		if (a_turn_order[m_turn]->check_playable(a_turn_order[m_turn]->get_hand(), a_stack.get_stack()))
		{
			a_turn_order[m_turn]->player_play(a_stack, a_bot);
		}
		

		if (m_turn == 0)
		{	
			m_turn = 1;
		}	
		else
		{	
			m_turn = 0;
		}

		std::cout << "Do you want to save game?" << std::endl;
		std::cout << "1 = yes, 0 = no" << std::endl;
		std::cin >> ans;
		while (ans > 1 || ans < 0)
		{
			std::cout << "invalid input. Please try again..." << std::endl;
			std::cin >> ans;
		}

		if (ans == 1)
		{
			//save game
			return 1;

		}

	}
	return 0;

	
}

/* *********************************************************************
Function Name: first_pick
Purpose: handles how player decide which one goes first each round
Parameters:
	a_human
		a player object that is for the human player 
	a_bot
		a player object that is for the bot player
	a_turn_order
		an array of player object pointers to handle the turn order when playing. This will be updated with the actual turn order in this function
	a_stack
		the stack object where players place their dominos on

Return Value: None
Algorithm:
			1) shuffle player boneyards everytime the first domino on each has the same total number of pips
			2) whoever has the higher number of total pips goes first
Assistance Received: none
********************************************************************* */
void game_round::first_pick(player* a_human, player* a_bot, player* a_turn_order[2], std::vector<domino*>& a_stack)
{
	std::cout << "first_pick() called " << std::endl;


	while (a_human->get_boneyard()[0]->total_pips() == a_bot->get_boneyard()[0]->total_pips())
	{
		std::random_shuffle(std::begin(a_human->get_boneyard()), std::end(a_human->get_boneyard()));
		std::random_shuffle(std::begin(a_bot->get_boneyard()), std::end(a_bot->get_boneyard()));
		std::cout << "total number pips for both players are the same, shuffle" << std::endl;
	}

	if (a_human->get_boneyard()[0]->total_pips() > a_bot->get_boneyard()[0]->total_pips()) // if human has higher total pips count
	{
		a_turn_order[1] = a_bot;
		a_turn_order[0] = a_human;
		std::cout << "the first domino in the player boneyard has a total pip number of : " << a_human->get_boneyard()[0]->total_pips() << " and the bot's first domino in their boneyard has a total of: " << a_bot->get_boneyard()[0]->total_pips() << std::endl;
		std::cout << "total number of pips for human is greater, human goes first" << std::endl;
		return;
	}
	else if (a_human->get_boneyard()[0]->total_pips() < a_bot->get_boneyard()[0]->total_pips()) // if bot has higher total pips count
	{
		a_turn_order[1] = a_human;
		a_turn_order[0] = a_bot;
		std::cout << "the first domino in the player boneyard has a total pip number of : " << a_human->get_boneyard()[0]->total_pips() << " and the bot's first domino in their boneyard has a total of: " << a_bot->get_boneyard()[0]->total_pips() << std::endl;
		std::cout << "total number of pips for human is greater, bot goes first" << std::endl;
		return;
	}

}

/* *********************************************************************
Function Name: score
Purpose: handles scoring for a round
Parameters:
	a_stack
		the stack object where players place their dominos on
	a_turn_order
		an array of player object pointers to handle the turn order when playing. 
	a_scoreboard
		an integer array that keeps record of both players' scores. This will be updated in this function

Return Value: None
Algorithm:
			1) iterate through each player's hand to subtract any unplaced dominos from their respective scores
			2) iterate through the stack to check what dominos each player placed and add them to their respective scores
			3) update scoreboard with new scores
Assistance Received: none
********************************************************************* */
void game_round::score(stack& a_stack, player* a_turn_order[2], int* a_scoreboard)
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
	

	a_scoreboard[0] += human_total;
	a_scoreboard[1] += bot_total;
	
	//std::cout << "human: " << a_scoreboard[0] << std::endl;
	//std::cout << "Bot: " << a_scoreboard[1] << std::endl;
	

}