#pragma once
#include "stack.h"
#include <vector>
#include "domino.h"
#include <string>

class player
{
public:
	player() {};
	virtual std::vector<domino*>& get_hand() = 0;
	virtual std::vector<domino*>& get_boneyard() = 0;
	virtual char get_id() = 0;
	virtual void draw() = 0;
	virtual bool is_hand_empty() = 0;
	virtual void display_hand() = 0;
	virtual void display_boneyard() = 0;
	virtual void place(stack& a_stack) = 0;
	virtual void fill_stack(std::vector<domino*>& a_stack) = 0;
	virtual void player_play(stack& a_stack, player* a_bot) = 0;
	virtual void strategy(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2) = 0;
	virtual bool check_playable( std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp) = 0;
	virtual bool check_legality(std::vector<domino*>& a_hand, std::vector<domino*>& a_stack_temp, int& a_loc1, int& a_loc2) = 0;
private:

};
