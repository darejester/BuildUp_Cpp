#pragma once
#include "stack.h"
#include <vector>
#include "domino.h"

class player
{
public:
	player() {};
	virtual std::vector<domino*>& get_hand() = 0;
	virtual std::vector<domino*>& get_boneyard() = 0;
	virtual void draw() = 0;
	virtual bool is_hand_empty() = 0;
	virtual void display_hand() = 0;
	virtual void display_boneyard() = 0;
	virtual void place(stack& a_stack) = 0;
	virtual void fill_stack(std::vector<domino*>& a_stack) = 0;
	virtual void player_play(stack& a_stack) = 0;
private:

};

//player::player()
//{
//	for (int i = 0; i < 28; i++)
//	{
//		m_boneyard.push_back(new domino);
//	}
//	std::cout << "player object created" << std::endl;
//}







//void player::fill_stack(std::vector<domino*>& a_stack)
//{
//	//MAKE THIS START FROM 0 TO <6 FOR BOT
//	for (int i = 6; i < 12; i++)
//	{
//		//m_hand.push_back(*m_boneyard.begin());
//		a_stack.insert(a_stack.begin() + i, *m_boneyard.begin());
//		//erase 
//		m_boneyard.erase(m_boneyard.begin());
//
//
//
//	}
//
//}