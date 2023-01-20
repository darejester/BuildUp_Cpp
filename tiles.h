#pragma once
#include "domino.h"
#include <vector>

class tiles
{
public:
	tiles();
	// returns a temp vector with the next values in m_m_player_boneyard
	std::vector<domino*> player_draw();
	// returns a temp vector with the next values in m_m_bot_boneyard
	std::vector<domino*> bot_draw();
	// prints out all dominos inside player boneyard
	void player_boneyard_out();
	// prints out all dominos inside bot boneyard
	void bot_boneyard_out();
	//update tiles
	//void update_tiles(tiles* x) { m_tiles = x; }

private:
	// holds dominos for bot boneyard
	std::vector<domino*> m_bot_boneyard;
	// holds dominos for player boneyard
	std::vector<domino*> m_player_boneyard;
	// holds the 12 (6 per player) tiles
	std::vector<domino*> m_tiles;
	

};

tiles::tiles()
{
	std::cout << "tiles object created" << std::endl;
	//fill player boneyard
	for (int i = 0; i < 22; i++)
	{
		m_player_boneyard.push_back(new domino);
	}
	//fill bot boneyard
	for (int i = 0; i < 22; i++)
	{
		m_bot_boneyard.push_back(new domino);
	}
}

std::vector<domino*> tiles::player_draw()
{
	std::vector<domino*> temp;
	for (int i = 0; i < 6; i++)
	{
		//for last iteration where dominos are less than 6
		if (m_player_boneyard.empty())
		{
			return temp;
		}
		temp.push_back(*m_player_boneyard.begin());
		//erase 
		m_player_boneyard.erase(m_player_boneyard.begin());

		

	}
	return temp;
}

std::vector<domino*> tiles::bot_draw()
{
	std::vector<domino*> temp;
	for (int i = 0; i < 6; i++)
	{
		//for last iteration where dominos are less than 6
		if (m_bot_boneyard.empty())
		{
			return temp;
		}
		temp.push_back(*m_bot_boneyard.begin());
		//erase 
		m_bot_boneyard.erase(m_bot_boneyard.begin());



	}
	return temp;
}

void tiles::player_boneyard_out()
{
	for (auto x : m_player_boneyard)
	{
		std::cout << x->l_pips_out() << "-" << x->r_pips_out() << std::endl;
	}
}

void tiles::bot_boneyard_out()
{
	for (auto x : m_bot_boneyard)
	{
		std::cout << x->l_pips_out() << "-" << x->r_pips_out() << std::endl;
	}
}