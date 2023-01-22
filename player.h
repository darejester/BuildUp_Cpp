#pragma once
#include "hand.h"
#include "stack.h"
#include <vector>

class player
{
public:
	player();
	void draw();
	void display_hand();
	void display_boneyard();
	void place(std::vector<domino*>& a_stack);
private:
	//hand* m_hand;
	std::vector<domino*> m_hand;
	std::vector<domino*> m_boneyard;
};

player::player()
{
	for (int i = 0; i < 22; i++)
	{
		m_boneyard.push_back(new domino);
	}
	std::cout << "player object created" << std::endl;
}

void player::draw()
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

void player::display_hand()
{
	std::cout << "HAND:" << std::endl;
	std::cout << "0   1   2   3   4   5" << std::endl;
	for (auto x : m_hand)
	{
		std::cout << x->display_l_pips() << "-" << x->display_r_pips() << " ";
	}
	std::cout << "\n";
}

void player::display_boneyard()
{
	std::cout << "BONEYARD:" << std::endl;
	std::cout << "TOP ";
	for (auto x : m_boneyard)
	{
		std::cout << x->display_l_pips() << "-" << x->display_r_pips() << " ";
	}
	std::cout << "BOTTOM" << "\n";
}

void player::place(std::vector<domino*>& a_stack)
{
	int loc1;
	int loc2;
	std::vector<domino*>::iterator it;
	//get locations
	std::cout << "which domino do you want to place?" << std::endl;
	std::cin >> loc1;
	std::cout << "where to place it?" << std::endl;
	std::cin >> loc2;

	//place
	it = m_hand.begin() + loc1;
	a_stack[loc2] = m_hand[loc1];
	m_hand.erase(it);
	display_hand();
	
}