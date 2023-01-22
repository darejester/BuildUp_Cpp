#pragma once
#include <vector>
#include "domino.h"
#include "stack.h"

class hand
{
public:
	hand() {}
	//initializes a hand with a vector from boneyard(in stack class)
	hand(/*call draw func from tile class and recieve a vector of dominos */std::vector<domino*> x) : m_dominos(x) { std::cout << "hand object created" << std::endl; }
	//prints out the current values inside hand
	void display_hand();

private:
	//holds the dominos for current hand
	std::vector<domino*> m_dominos;

};

void hand::display_hand()
{
	for (auto x : m_dominos)
	{
		std::cout << x->display_l_pips() << "-" << x->display_r_pips() << std::endl;
	}
}