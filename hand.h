#pragma once
#include <vector>
#include "domino.h"
#include "tiles.h"

class hand
{
public:
	//initializes a hand with a vector from boneyard(in tiles class)
	hand(/*call draw func from tile class and recieve a vector of dominos */std::vector<domino*> x) : m_current_hand(x) { std::cout << "hand object created" << std::endl; }
	//prints out the current values inside hand
	void hand_out();

private:
	//holds the dominos for current hand
	std::vector<domino*> m_current_hand;

};

void hand::hand_out()
{
	for (auto x : m_current_hand)
	{
		std::cout << x->l_pips_out() << "-" << x->r_pips_out() << std::endl;
	}
}