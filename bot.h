#pragma once
#include "player.h"
#include <algorithm>
#include <random>

class bot : public player
{
public:
	bot();
	std::vector<domino*>& get_hand() { return m_hand; }
	std::vector<domino*>& get_boneyard() { return m_boneyard; }
	void draw();
	bool is_hand_empty() { return m_hand.empty(); }
	void display_hand();
	void display_boneyard();
	void place(stack& a_stack);
	void fill_stack(std::vector<domino*>& a_stack);
	void player_play(stack& a_stack);
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

void bot::display_hand()
{
	std::cout << "BOT HAND:" << std::endl;
	for (auto x : m_hand)
	{
		x->display_domino();
		std::cout << " ";
	}
	std::cout << "\n";
	std::cout << "  0     1     2     3     4     5";
	std::cout << "\n \n";
}

void bot::display_boneyard()
{
	std::cout << "BOT BONEYARD:" << std::endl;
	std::cout << "TOP ";
	for (auto x : m_boneyard)
	{
		x->display_domino();
		std::cout << " ";
	}
	std::cout << "BOTTOM";
	std::cout << "\n \n";
}

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

	loc1 = rand() % m_hand.size();
	loc2 = rand() % 12;

	//place
	it = m_hand.begin() + loc1;
	temp[loc2] = m_hand[loc1];
	m_hand.erase(it);
	//display_hand();

}

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

void bot::player_play(stack& a_stack)
{
	std::cout << "bot playing" << std::endl;
	this->place(a_stack);
}