#pragma once
#include <cstdlib>

class domino 
{
public:
	//initializes a domino object with random L and R pips
	domino() : m_l_pips(rand() % 7), m_r_pips(rand() % 7) { /*std::cout << l_pips << "-" << r_pips << std::endl;*/}
	// returns the total number of pips
	int total_pips();
	// returns the m_l_pips
	int l_pips_out() { return m_l_pips; }
	// returns the m_r_pips
	int r_pips_out() { return m_r_pips; }

	~domino() {};

private:
	int m_l_pips;
	int m_r_pips;
	
};

int domino::total_pips()
{
	return m_l_pips + m_r_pips;
}