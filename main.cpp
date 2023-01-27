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
    std::cout << "0 - start new tournament" << std::endl;
    std::cin >> answer;

    if (answer == 0)
    {
        game.start_tournament();
    }
    else if (answer == 1)
    {
        game.resume_tournament();
    }
    else if (answer == 2)
    {
        //save tournament?
    }
        
        
    

}

/*
NOTES
- fix domino repetition
- fix domino color(done)
- fix serialization(fix, resume)
- fix 2 player (human vs bot)(done)
- fix turn order
- fix display of stacks (display domino instead of the address)(done)
- fix initial filling of stacks(done)
- remove hand (done)
- deck class to manage boneyard and no repetition of a domino

*/

