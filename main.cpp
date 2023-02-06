#include "libraries.h"
#include "domino.h"
#include "stack.h"
#include "tournament.h"
int main()
{
    srand(time(NULL));
    tournament game;

    int answer = -1;

 
    std::cout << "WELCOME!" << std::endl;
    std::cout << "0 - start new tournament, 1 - resume saved tournament" << std::endl; 
    std::cin >> answer;
    while (answer < 0 || answer > 1)
    {
        std::cout << "Input invalid. Please try again...." << std::endl;
        std::cin >> answer;
    }

    if (answer == 0)
    {
        game.start_tournament();
    }
    else if (answer == 1)
    {
        game.resume_tournament();
    }
        
        
    

}

/*
NOTES
https://pages.ramapo.edu/~amruth/teaching/opl/projects/buildup/problem.html

- fix domino repetition(done)
- fix domino color(done)
- fix 2 player (human vs bot)(done)
- fix turn order(done)
- fix display of stacks (display domino instead of the address)(done)
- fix initial filling of stacks(done)
- remove hand (done)
- deck class to manage boneyard(?)(didnt do)(done in another way)
- fix shuffle when deciding who is playing first(done)
- double tile placement mechanic(done)
- scoring(done)
- fix bot mechanics(AI)(how it plays)(done)
- fix ask for help(done)
- winner for each hand(done)
- winner for each round(done)
- play another round(done)
- fix winner declaration(done)
- fix round and hand(done)
    - round = the whole game of 4 hands

- fix serialization(fix, resume)



*/

