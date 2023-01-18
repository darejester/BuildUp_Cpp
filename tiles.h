#pragma once
#include "domino.h"
#include <vector>

class tiles
{
public:
	tiles();
	std::vector<domino*> draw();
	void player_boneyard_out();

private:
	std::vector<domino*> bot_boneyard;
	std::vector<domino*> bot_tiles;
	std::vector<domino*> player_boneyard;
	std::vector<domino*> player_tiles;
	

};

tiles::tiles()
{
	//fill player boneyard
	for (int i = 0; i < 22; i++)
	{
		player_boneyard.push_back(new domino);
	}
	//fill bot boneyard
	for (int i = 0; i < 22; i++)
	{
		bot_boneyard.push_back(new domino);
	}
}

std::vector<domino*> tiles::draw()
{
	std::vector<domino*> temp;
	for (int i = 0; i < 6; i++)
	{
		//for last iteration where dominos are less than 6
		if (player_boneyard.empty())
		{
			return temp;
		}
		temp.push_back(*player_boneyard.begin());
		//erase 
		player_boneyard.erase(player_boneyard.begin());

		

	}
	return temp;
}

void tiles::player_boneyard_out()
{
	for (auto x : player_boneyard)
	{
		std::cout << x->l_pips_out() << "-" << x->r_pips_out() << std::endl;
	}
}