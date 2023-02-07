#pragma once
#include "domino.h"
#include <vector>

class stack
{
public:
	stack();
	// returns a temp vector with the next values in m_m_player_boneyard
	//std::vector<domino*> player_draw();
	// returns a temp vector with the next values in m_m_bot_boneyard
	//std::vector<domino*> bot_draw();
	// prints out all dominos inside player boneyard
	//std::vector<domino*>& get_boneyard() { return m_player_boneyard; }
	//void player_boneyard_out();
	// prints out all dominos inside bot boneyard
	//void bot_boneyard_out();
	//update stack
	//void update_stack(stack* x) { m_stack = x; }
	
	std::vector<domino*>& get_stack() { return m_stack; }
	//int* get_test() { return test; }

	void display_stack();

	~stack() { std::cout << "destroyed stack" << std::endl; }

private:
	// holds dominos for bot boneyard
	//std::vector<domino*> m_bot_boneyard;
	// holds dominos for player boneyard
	//std::vector<domino*> m_player_boneyard;
	// holds the 12 (6 per player) stack
	std::vector<domino*> m_stack;
	//int* test;
	

};


stack::stack()
{
	std::cout << "stack object created" << std::endl;
	for (int i = 0; i < 12; i++)
	{
		m_stack.push_back(NULL);
	}
	//debug: print
	//display_stack();
}

/* *********************************************************************
Function Name: display_stack
Purpose: To display stack
Parameters: None
Return Value: None
Algorithm:
			1) loop through whole stack vector
			2) output them to console
Assistance Received: none
********************************************************************* */
void stack::display_stack()
{
	std::cout << "STACK:" << std::endl;
	std::cout << " 0   1   2   3   4   5\n";
	
	for (int i = 0; i < 12; i++)
	{
		if (i == 6)
		{
			std::cout << "\n";
		}
		/*std::cout << m_stack[i]->display_l_pips() << "-" << m_stack[i]->display_r_pips();*/
		// THIS IS WORKING. FINISH MAKING BOT FIRST TO REMOVE NULL VALUES AND THEN USE THIS
		m_stack[i]->display_domino();
		//debug: display addresses
		//std::cout << m_stack[i];
		std::cout << " ";

	}
	std::cout << "\n";
	std::cout << " 6   7   8   9   10  11\n ";
	std::cout << "\n";
}
