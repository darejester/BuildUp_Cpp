#include "libraries.h"
#include "domino.h"
#include "hand.h"
#include "tiles.h"

//test

int main()
{
    std::cout << "Hello World!\n";
    tiles* t = new tiles;
    int temp = 0;
    while (1)
    {
        std::cout << "boneyard" << std::endl;
        t->player_boneyard_out();
        
        hand* h = new hand(t->draw());
        std::cout << "hand" << std::endl;
        h->hand_out();

        std::cin >> temp;

        
        
        
    }
}

