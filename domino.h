#pragma once
#include <cstdlib>

class domino 
{
public:
	domino() : l_pips(rand() % 7), r_pips(rand() % 7) { /*std::cout << l_pips << "-" << r_pips << std::endl;*/}
	int total_pips();
	int l_pips_out() { return l_pips; }
	int r_pips_out() { return r_pips; }

	~domino() {};

private:
	int l_pips;
	int r_pips;
	
};

int domino::total_pips()
{
	return l_pips + r_pips;
}