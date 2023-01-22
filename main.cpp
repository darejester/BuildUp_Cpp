#include "libraries.h"
#include "domino.h"
#include "hand.h"
#include "stack.h"
#include "tournament.h"
int main()
{
    srand(time(NULL));
    tournament game;
    int ctr = 0;
    // game loop
    while (ctr < 4/*replace with something that I can equal to the number of rounds in tournament class*/)
    {
        game.start_tournament();
        ctr++;
        
    }
}

