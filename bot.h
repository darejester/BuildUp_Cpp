#pragma once
#include "player.h"
#include <algorithm>
#include <random>

class bot : public player
{
public:
	bot();
	bot(std::vector<domino*> a_temp_hand, std::vector<domino*> a_temp_boneyard) :m_hand(a_temp_hand), m_boneyard(a_temp_boneyard) {}
	std::vector<domino*>& get_hand() { return m_hand; }
	std::vector<domino*>& get_boneyard() { return m_boneyard; }
	char get_id() { return 'W'; }
	void draw();
	bool is_hand_empty() { return m_hand.empty(); }
	void display_hand();
	void display_boneyard();
	void place(stack& a_stack);
	void fill_stack(std::vector<domino*>& a_stack);
	void player_play(stack& a_stack, player* a_bot);
	bool check_playable( std::vector<domino*>& a_hand,  std::vector<domino*>& a_stack_temp);
	void strategy(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2);
	bool check_legality(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2);

	~bot() { std::cout << "destroyed bot" << std::endl; }
private:
	std::vector<domino*> m_hand;
	std::vector<domino*> m_boneyard;
};

bot::bot()
{
	//auto seed = std::random_device{};
	//auto rng = std::default_random_engine{ };

	for (int l = 0; l <= 6; l++)
	{
		for (int r = l; r <= 6; r++)
		{
			m_boneyard.push_back(new domino(l, r, 'W'));
		}
		
		//m_boneyard.push_back(new domino('B'));

	}

	std::random_shuffle(std::begin(m_boneyard), std::end(m_boneyard));
	/*for (auto i : m_boneyard)
	{
		i->display_domino();
	}
	std::cout << "\n";*/
	std::cout << "bot object created" << std::endl;
}

/* *********************************************************************
Function Name: draw
Purpose: to get dominos from boneyard
Parameters: None
Return Value: None
Algorithm:
			1) loop six times
			2) check if boneyard is empty. If not,...
			3) push domino from boneyard to hand
			4) erase domino from boneyard
Assistance Received: none
********************************************************************* */
void bot::draw()
{
	for (int i = 0; i < 6; i++)
	{
		//for last iteration where dominos are less than 6
		if (m_boneyard.empty())
		{
			break;
		}
		m_hand.push_back(*m_boneyard.begin());
		//erase 
		m_boneyard.erase(m_boneyard.begin());



	}

}

/* *********************************************************************
Function Name: display_hand
Purpose: display player's hand
Parameters: None
Return Value: None
Algorithm:
			1) loop through whole hand of player
			2) print dominos to console
Assistance Received: none
********************************************************************* */
void bot::display_hand()
{
	std::cout << "BOT HAND:" << std::endl;
	for (auto x : m_hand)
	{
		std::cout << "***";
		//x->display_domino();
		std::cout << " ";
	}
	std::cout << "\n";
	std::cout << " 0   1   2   3   4   5";
	std::cout << "\n \n";
}

/* *********************************************************************
Function Name: display_doneyard
Purpose: display player's boneyard
Parameters: None
Return Value: None
Algorithm:
			1) loop through whole boneyard of player
			2) print dominos to console
Assistance Received: none
********************************************************************* */
void bot::display_boneyard()
{
	std::cout << "BOT BONEYARD:" << std::endl;
	std::cout << "TOP ";
	for (auto x : m_boneyard)
	{
		std::cout << "***";
		//x->display_domino();
		std::cout << " ";
	}
	std::cout << "BOTTOM";
	std::cout << "\n \n";
}

/* *********************************************************************
Function Name: place
Purpose: place player domino onto stack
Parameters: a_stack, Object of Stack class
Return Value: None
Algorithm:
			1) calls strategy function to find a strategic move
			2) checks if the locations picked is a legal move
			3) places domino onto stack location if legal move
Assistance Received: none
********************************************************************* */
void bot::place(stack& a_stack)
{

	int loc1;
	int loc2;
	std::vector<domino*>& temp = a_stack.get_stack();
	std::vector<domino*>::iterator it;
	////get locations
	//std::cout << "which domino do you want to place?" << std::endl;
	//std::cin >> loc1;
	////input validation
	//while (loc1 >= m_hand.size())
	//{
	//	std::cout << "There is no domino in that part of your hand. Enter again..." << std::endl;
	//	std::cin >> loc1;
	//}
	//std::cout << "where to place it?" << std::endl;
	//std::cin >> loc2;

	//get locations
	//loc1 = rand() % m_hand.size();
	//loc2 = rand() % temp.size();
	this->strategy(m_hand, temp, loc1, loc2);

	//check if placement of domino is legal
	//condition 1
	if (this->check_legality(m_hand,temp,loc1,loc2) )
	{
		//place
		temp[loc2] = m_hand[loc1];
		it = m_hand.begin() + loc1;
		m_hand.erase(it);
		//display_hand();
		return;
	}

}

/* *********************************************************************
Function Name: fill_stack
Purpose: fills 6 stacks that the player is responsible for with the first six in boneyard
Parameters: a_stack, a vector of domino object pointers that is passed by reference. This function fills a_stack with dominos from the player's boneyard
Return Value: None
Algorithm:
			1) iterate through a section of the stack
			2) insert a domino from the boneyard to the stack for each iteration
Assistance Received: none
********************************************************************* */
void bot::fill_stack(std::vector<domino*>& a_stack)
{
	for (int i = 0; i < 6; i++)
	{
		//m_hand.push_back(*m_boneyard.begin());
		a_stack.insert(a_stack.begin() + i, *m_boneyard.begin());
		//erase 
		m_boneyard.erase(m_boneyard.begin());



	}
}

/* *********************************************************************
Function Name: player_play
Purpose: allows player to play their move
Parameters:
	a_stack
		a_stack, a vector of domino object pointers that is passed by reference. This function passes a_stack to the place function if the player picks to play
	a_bot
		a_bot is a player object passed by reference. 
Return Value: None
Algorithm:
			1) call place function
Assistance Received: none
********************************************************************* */
void bot::player_play(stack& a_stack, player* a_bot)
{
	std::cout << "bot playing" << std::endl;
	this->place(a_stack);
}

/* *********************************************************************
Function Name: check_playable
Purpose: checks player's hand and boneyard if there are any dominos that can be played based on the rules
Parameters:
	a_hand
		a vector of domino object pointers that is passed by reference. This function checks a_hand for its contents
	a_stack_temp
		a vector of domino object pointers that is passed by reference. This function checks a_stack_temp  for its contents

Return Value: boolean that represents whether there is a possible play or not
Algorithm:
			1) loop through whole stack
			2) loop through whole hand
			3) cross checks dominos in hand and stack to check if there are any possile plays based on the rules
Assistance Received: none
********************************************************************* */
bool bot::check_playable(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp)
{
	// check if there is/are any plable domino(s)
	for (auto t : a_stack_temp)
	{
		for (auto h : a_hand)
		{
			//check if placement of domino is legal
			//condition 1
			//condition 2
			//condition 3
			if ((h->display_l_pips() != h->display_r_pips()) && (h->total_pips() >= t->total_pips())) 
			{
				return 1;


			}
			else if ((h->display_l_pips() == h->display_r_pips()) && (t->display_l_pips() != t->display_r_pips())) 
			{

				return 1;
			}
			else if ((h->display_l_pips() == h->display_r_pips()) && (t->display_l_pips() == t->display_r_pips()) && (h->total_pips() > t->total_pips())) 
			{

				return 1;
			}
		}
	}
	//if no more playable domino(s)
	std::cout << "No more playable domino(s)" << std::endl;
	return 0;
}

/* *********************************************************************
Function Name: strategy
Purpose: This is the Bot's strategy to playing the game
Parameters:
	a_hand
		a vector of domino object pointers that is passed by reference. This function checks a_hand for its contents
	a_stack_temp
		a vector of domino object pointers that is passed by reference. This function checks a_stack_temp  for its contents
	a_loc1
		an integer that holds the location for the player's hand. This will be modified based on the bot's strategy
	a_loc2
		an integer that holds the location for the stack. This will be modified based on the bot's strategy

Return Value: None
Algorithm:
			1) loop through whole stack
			2) check if a move is strategic based on specific conditions
			3) display reason for move
Assistance Received: none
********************************************************************* */
void bot::strategy(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2)
{
	int h = 0;
	int s = 0;
	while (h < a_hand.size())
	{
		
		//check best strategic move
		//place higher tile on enemy tile
		while (s < a_stack_temp.size())
		{
			if ((a_stack_temp[s]->display_color() != a_hand[h]->display_color()) && (a_stack_temp[s]->total_pips() < a_hand[h]->total_pips()))
			{
				if (this->check_legality(a_hand, a_stack_temp, h, s))
				{
					std::cout << "Cover opponent's high tile with own higher tile" << std::endl;
					std::cout << h << " in hand to " << s << " of stack" << std::endl;
					a_loc1 = h;
					a_loc2 = s;
					return;
				}
			}
			s++;
		}
		s = 0;
		h++;
	}
	s = 0;
	h = 0;

	//place low-value double on high value tile of enemy
	while (h < a_hand.size())
	{
		while (s < a_stack_temp.size())
		{
			if ((a_stack_temp[s]->display_color() != a_hand[h]->display_color()) && (a_hand[h]->display_l_pips() == a_hand[h]->display_r_pips()) && (a_hand[h]->total_pips() < a_stack_temp[s]->total_pips()))
			{
				if (this->check_legality(a_hand, a_stack_temp, h, s))
				{
					std::cout << "Cover opponent's high tile with own lower double tile" << std::endl;
					std::cout << h << " in hand to " << s << " of stack" << std::endl;
					a_loc1 = h;
					a_loc2 = s;
					return;
				}
			}
			s++;
		}
		s = 0;
		h++;
	}
	s = 0;
	h = 0;

	//place playable tile on own tile
	while (h < a_hand.size())
	{
		while (s < a_stack_temp.size())
		{
			if ((a_stack_temp[s]->display_color() == a_hand[h]->display_color()))
			{
				if (this->check_legality(a_hand, a_stack_temp, h, s))
				{
					std::cout << "Cover own tile to avoid having points deducted" << std::endl;
					std::cout << h << " in hand to " << s << " of stack" << std::endl;
					a_loc1 = h;
					a_loc2 = s;
					return;

				}
			}
			s++;
		}
		s = 0;
		h++;
	}
	s = 0;
	h = 0;
	while (h < a_hand.size())
	{
		while (s < a_stack_temp.size())
		{
			if (this->check_legality(a_hand, a_stack_temp, h, s))
			{
				std::cout << "No good moves. Just do a legal move" << std::endl;
				std::cout << h << " in hand to " << s << " of stack" << std::endl;
				a_loc1 = h;
				a_loc2 = s;
				return;

			}
			s++;
		}
		s = 0;
	}
	
}

/* *********************************************************************
Function Name: check_legality
Purpose: checks player's hand and boneyard if there are any dominos that can be played legally based on the rules
Parameters:
	a_hand
		a vector of domino object pointers that is passed by reference. This function checks a_hand for its contents
	a_stack_temp
		a vector of domino object pointers that is passed by reference. This function checks a_stack_temp  for its contents
	a_loc1
		an integer that holds the location for the player's hand. This will be the location in hand.
	a_loc2
		an integer that holds the location for the stack. This will be the location in stacks

Return Value: boolean that represents whether a move is a legal play or not
Algorithm:
			1) if and else statement to check if any legality condition is met
			2) return true or false
Assistance Received: none
********************************************************************* */
bool bot::check_legality(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2)
{
	//check if placement of domino is legal
	//condition 1
	//condition 2
	//condition 3
	if ((a_hand[a_loc1]->display_l_pips() != a_hand[a_loc1]->display_r_pips()) && (a_hand[a_loc1]->total_pips() >= a_stack_temp[a_loc2]->total_pips())) 
	{
		//place
		return 1;

	}
	else if ((a_hand[a_loc1]->display_l_pips() == a_hand[a_loc1]->display_r_pips()) && (a_stack_temp[a_loc2]->display_l_pips() != a_stack_temp[a_loc2]->display_r_pips())) 
	{
		return 1;
	}
	else if ((a_hand[a_loc1]->display_l_pips() == a_hand[a_loc1]->display_r_pips()) && (a_stack_temp[a_loc2]->display_l_pips() == a_stack_temp[a_loc2]->display_r_pips()) && (a_hand[a_loc1]->total_pips() > a_stack_temp[a_loc2]->total_pips())) 
	{
		return 1;
	}
	else
	{
		/*std::cout << "Tile placement is illegal." << std::endl;
		std::cout << "A non-double tile may be placed on any tile as long as the total number of pips on it is greater than or equal to that of the tile on which it is placed." << std::endl;
		std::cout << "A double tile (e.g., 0-0, 1-1, 2-2) may be placed on any non-double tile, even if the non-double tile has more pips." << std::endl;
		std::cout << "A double tile may be placed on another double tile only if it has more total pips than the tile on which it is placed." << std::endl;*/
		return 0;
	}
}