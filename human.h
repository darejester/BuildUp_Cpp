#pragma once
#include "player.h"
#include <algorithm>
#include <random>

class human : public player
{
public:
	human();
	std::vector<domino*>& get_hand() { return m_hand; }
	std::vector<domino*>& get_boneyard() { return m_boneyard; }
	void draw();
	bool is_hand_empty() { return m_hand.empty(); }
	void display_hand();
	void display_boneyard();
	void place(stack& a_stack);
	void fill_stack(std::vector<domino*>& a_stack);
	void player_play(stack& a_stack);
	bool check_playable( std::vector<domino*>& a_hand,  std::vector<domino*>& a_stack_temp);
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
	while (this->check_playable(m_hand, temp))
	{
		//get locations
		std::cout << "which domino do you want to place?" << std::endl;
		std::cin >> loc1;
		//input validation
		while (loc1 >= m_hand.size())
		{
			std::cout << "There is no domino in that part of your hand. Enter again..." << std::endl;
			std::cin >> loc1;
		}
		std::cout << "where to place it?" << std::endl;
		std::cin >> loc2;
		while (loc2 >= 12)
		{
			std::cout << "Invalid location. Enter again..." << std::endl;
			std::cin >> loc2;
		}

		//check if placement of domino is legal
		if ((m_hand[loc1]->display_l_pips() != m_hand[loc1]->display_r_pips()) && (m_hand[loc1]->total_pips() >= temp[loc2]->total_pips())) //condition 1
		{
			//place
			temp[loc2] = m_hand[loc1];
			it = m_hand.begin() + loc1;
			m_hand.erase(it);
			//display_hand();
			break;
			
		}
		else if ((m_hand[loc1]->display_l_pips() == m_hand[loc1]->display_r_pips()) && (temp[loc2]->display_l_pips() != temp[loc2]->display_r_pips())) //condition 2
		{
			//place
			temp[loc2] = m_hand[loc1];
			it = m_hand.begin() + loc1;
			m_hand.erase(it);
			//display_hand();
			break;
		}
		else if ((m_hand[loc1]->display_l_pips() == m_hand[loc1]->display_r_pips()) && (temp[loc2]->display_l_pips() == temp[loc2]->display_r_pips()) && (m_hand[loc1]->total_pips() > temp[loc2]->total_pips())) //condition 3
		{
			//place
			temp[loc2] = m_hand[loc1];
			it = m_hand.begin() + loc1;
			m_hand.erase(it);
			//display_hand();
			break;
		}
		else
		{
			std::cout << "Tile placement is illegal." << std::endl;
			std::cout << "A non-double tile may be placed on any tile as long as the total number of pips on it is greater than or equal to that of the tile on which it is placed." << std::endl;
			std::cout << "A double tile (e.g., 0-0, 1-1, 2-2) may be placed on any non-double tile, even if the non-double tile has more pips." << std::endl;
			std::cout << "A double tile may be placed on another double tile only if it has more total pips than the tile on which it is placed." << std::endl;
			continue;
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

void human::player_play(stack& a_stack)
{
	int action = -1;
	//action input
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
		this->place(a_stack);
	}
	else /*if()*/
	{

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