#pragma once
#include <cstdlib>

class domino 
{
public:
	//initializes a domino object with random L and R pips
	domino(int a_l, int a_r,char a_color) : m_l_pips(a_l/*rand() % 7*/), m_r_pips(a_r/*rand() % 7*/),m_color(a_color) { /*std::cout << l_pips << "-" << r_pips << std::endl;*/}
	// returns the total number of pips
	int total_pips();
	// returns the m_l_pips
	int display_l_pips() { return m_l_pips; }
	// returns the m_r_pips
	int display_r_pips() { return m_r_pips; }

	char display_color() { return m_color; }

	void display_domino() { std::cout << m_color  << m_l_pips  << m_r_pips; }

	~domino() {};

private:
	int m_l_pips;
	int m_r_pips;
	char m_color;
	
};

int domino::total_pips()
{
	return m_l_pips + m_r_pips;
}