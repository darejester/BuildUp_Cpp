#pragma once
#include "player.h"
#include <algorithm>
#include <random>

class human : public player
{
public:
	human();
	human(std::vector<domino*> a_temp_hand, std::vector<domino*> a_temp_boneyard):m_hand(a_temp_hand), m_boneyard(a_temp_boneyard) {}
	std::vector<domino*>& get_hand() { return m_hand; }
	std::vector<domino*>& get_boneyard() { return m_boneyard; }
	char get_id() { return 'B'; }
	void draw();
	bool is_hand_empty() { return m_hand.empty(); }
	void display_hand();
	void display_boneyard();
	void place(stack& a_stack);
	void fill_stack(std::vector<domino*>& a_stack);
	void player_play(stack& a_stack, player* a_bot);
	bool check_playable( std::vector<domino*>& a_hand,  std::vector<domino*>& a_stack_temp);
	void get_help(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2, player* a_bot);
	bool check_legality(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2);
	void strategy(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2) {}

	~human() { std::cout << "destroyed human" << std::endl; }
private:
	std::vector<domino*> m_hand;
	std::vector<domino*> m_boneyard;
};

human::human()
{
	//auto seed = std::random_device{};
	//auto rng = std::default_random_engine{};

	for (int l = 0; l <= 6; l++)
	{
		for (int r = l; r <= 6; r++)
		{
			m_boneyard.push_back(new domino(l, r, 'B'));
		}
		
		//m_boneyard.push_back(new domino('W'));
		
	}
	
	std::random_shuffle(std::begin(m_boneyard), std::end(m_boneyard));
	/*for (auto i : m_boneyard)
	{
		i->display_domino();
	}
	std::cout << "\n";*/
	std::cout << "human object created" << std::endl;
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
void human::draw()
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
void human::display_hand()
{
	std::cout << "PLAYER HAND:" << std::endl;
	for (auto x : m_hand)
	{
		x->display_domino();
		std::cout<< " ";
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
void human::display_boneyard()
{
	std::cout << "PLAYER BONEYARD:" << std::endl;
	std::cout << "TOP ";
	for (auto x : m_boneyard)
	{
		x->display_domino();
		std::cout << " ";
	}
	std::cout << "BOTTOM";
	std::cout << "\n \n";
}

/* *********************************************************************
Function Name: place
Purpose: place player domino onto stack
Parameters: Object of Stack class
Return Value: None
Algorithm:
			1) checks if there are any playable dominos
			2) checks if the locations picked is a legal move
			3) places domino onto stack location if legal move
Assistance Received: none
********************************************************************* */
void human::place(stack& a_stack)
{

	int loc1;
	int loc2;
	std::vector<domino*>& temp = a_stack.get_stack();
	std::vector<domino*>::iterator it;
	if (this->check_playable(m_hand, temp))
	{
		//get locations
		std::cout << "which domino do you want to place?" << std::endl;
		std::cin >> loc1;
		//input validation
		while (loc1 >= m_hand.size() || loc1 < 0)
		{
			std::cout << "There is no domino in that part of your hand. Enter again..." << std::endl;
			std::cin >> loc1;
		}
		std::cout << "where to place it?" << std::endl;
		std::cin >> loc2;
		while (loc2 >= 12 || loc2 < 0)
		{
			std::cout << "Invalid location. Enter again..." << std::endl;
			std::cin >> loc2;
		}

		//check if placement of domino is legal
		//condition 1
		if (this->check_legality(m_hand, temp, loc1, loc2))
		{
			//place
			temp[loc2] = m_hand[loc1];
			it = m_hand.begin() + loc1;
			m_hand.erase(it);
			//display_hand();
			return;
		}
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
void human::fill_stack(std::vector<domino*>& a_stack)
{
	for (int i = 6; i < 12; i++)
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
		a_bot is a player object passed by reference. This function passes a_bot to the get_help function and asks a_bot to provide a strategic move
Return Value: None
Algorithm:
			1) asks player to input an integer
			2) does action based on the input
Assistance Received: none
********************************************************************* */
void human::player_play(stack& a_stack, player* a_bot)
{
	int loc1 = 0;
	int loc2 = 0;
	int action = -1;

	//action input
	std::cout << "ACTIONS:" << std::endl;
	std::cout << "1-Place card, 2-Ask Bot for Help,...." << std::endl;
	std::cin >> action;
	while (action < 2 || action <= 0)
	{
		std::cout << "INPUT INVALID. Try again...." << std::endl;
		std::cin >> action;
	}
	//action decider
	if (action == 1)
	{
		this->place(a_stack);
	}
	else if (action == 2)
	{
		this->get_help(m_hand, a_stack.get_stack(), loc1, loc2, a_bot);
	}


	
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
bool human::check_playable(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp)
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
Function Name: get_help
Purpose: uses Bot object's stategy to figure out what locations are going to give the most strategic move
Parameters:
	a_hand
		a vector of domino object pointers that is passed by reference. This function checks a_hand for its contents
	a_stack_temp
		a vector of domino object pointers that is passed by reference. This function checks a_stack_temp  for its contents
	a_loc1
		an integer that holds the location for the player's hand. This will be modified based on the bot's strategy
	a_loc2
		an integer that holds the location for the stack. This will be modified based on the bot's strategy
	a_bot
		the bot object that will provide the player with the strategy

Return Value: None
Algorithm:
			1) call Bot's strategy function
			2) decide whether the locations that the strategy function is good enough to play
			3) set the stack at location 2 equal to hand at location 1
			4) erase location 1 from hand
Assistance Received: none
********************************************************************* */
void human::get_help(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2, player* a_bot)
{
	int ans = -1;
	std::vector<domino*>::iterator it;

	a_bot->strategy(a_hand, a_stack_temp, a_loc1, a_loc2);

	std::cout << "Do you want to play this move?" << std::endl;
	std::cout << "1= yes, 0 = no" << std::endl;
	std::cin >> ans;
	while (ans > 1 || ans < 0)
	{
		std::cout << "Input invalid. pleas try again..." << std::endl;
		std::cin >> ans;
	}
	if (ans == 1)
	{
		//place
		a_stack_temp[a_loc2] = m_hand[a_loc1];
		it = m_hand.begin() + a_loc1;
		m_hand.erase(it);
	}
	else
	{
		return;
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
bool human::check_legality(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2)
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
		std::cout << "Tile placement is illegal." << std::endl;
		std::cout << "A non-double tile may be placed on any tile as long as the total number of pips on it is greater than or equal to that of the tile on which it is placed." << std::endl;
		std::cout << "A double tile (e.g., 0-0, 1-1, 2-2) may be placed on any non-double tile, even if the non-double tile has more pips." << std::endl;
		std::cout << "A double tile may be placed on another double tile only if it has more total pips than the tile on which it is placed." << std::endl;
		return 0;
	}
}