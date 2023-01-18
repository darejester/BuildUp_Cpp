#pragma once
#include <vector>
#include "domino.h"
#include "tiles.h"

class hand
{
public:
	hand(/*call draw func from tile class and recieve a vector of dominos */std::vector<domino*> x) : h(x) {}
	void hand_out();

private:
	//holds the dominos for current hand
	std::vector<domino*> h;

};

void hand::hand_out()
{
	for (auto x : h)
	{
		std::cout << x->l_pips_out() << "-" << x->r_pips_out() << std::endl;
	}
}