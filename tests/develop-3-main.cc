
#include <cstring>
#include <string>

#include "develop-3-Game.hh"

int main(int argc, char* argv[])
{
    std::string mode;
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "--mode") == 0)
        {
            mode = argv[++i];
        }
    }


    Game g_game;
    g_game.initialize("Tutorial 02",1024, 768);
    while(g_game.is_running())
    {
        g_game.rendering();
    }

    g_game.clean();
    return 0;
}
