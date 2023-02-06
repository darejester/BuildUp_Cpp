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
		if (this->check_legality(m_hand, temp, loc1, loc2))//condition 1
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

bool human::check_playable(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp)
{
	// check if there is/are any plable domino(s)
	for (auto t : a_stack_temp)
	{
		for (auto h : a_hand)
		{
			//check if placement of domino is legal
			if ((h->display_l_pips() != h->display_r_pips()) && (h->total_pips() >= t->total_pips())) //condition 1
			{
				return 1;
				

			}
			else if ((h->display_l_pips() == h->display_r_pips()) && (t->display_l_pips() != t->display_r_pips())) //condition 2
			{
				
				return 1;
			}
			else if ((h->display_l_pips() == h->display_r_pips()) && (t->display_l_pips() == t->display_r_pips()) && (h->total_pips() > t->total_pips())) //condition 3
			{
				
				return 1;
			}
		}
	}
	//if no more playable domino(s)
	std::cout << "No more playable domino(s)" << std::endl;
	return 0;
}

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

bool human::check_legality(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2)
{
	//check if placement of domino is legal
	if ((a_hand[a_loc1]->display_l_pips() != a_hand[a_loc1]->display_r_pips()) && (a_hand[a_loc1]->total_pips() >= a_stack_temp[a_loc2]->total_pips())) //condition 1
	{
		//place
		return 1;

	}
	else if ((a_hand[a_loc1]->display_l_pips() == a_hand[a_loc1]->display_r_pips()) && (a_stack_temp[a_loc2]->display_l_pips() != a_stack_temp[a_loc2]->display_r_pips())) //condition 2
	{
		return 1;
	}
	else if ((a_hand[a_loc1]->display_l_pips() == a_hand[a_loc1]->display_r_pips()) && (a_stack_temp[a_loc2]->display_l_pips() == a_stack_temp[a_loc2]->display_r_pips()) && (a_hand[a_loc1]->total_pips() > a_stack_temp[a_loc2]->total_pips())) //condition 3
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