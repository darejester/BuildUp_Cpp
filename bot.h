#pragma once
#include "player.h"

class bot : public player
{
public:
	bot();
	virtual void fill_stack(std::vector<domino*>& a_stack);
private:
	std::vector<domino*> m_hand;
	std::vector<domino*> m_boneyard;
};

bot::bot()
{
	for (int i = 0; i < 28; i++)
	{
		m_boneyard.push_back(new domino);
	}
	std::cout << "player object created" << std::endl;
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