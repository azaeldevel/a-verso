
#include <cstring>
#include <string>

#include "verso-v0.hh"

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

    Develop g_game;
    g_game.initialize("Developing Verso / Lighting research...",1024, 768);
    while(g_game.is_running())
    {
        g_game.render();
    }

    g_game.clean();
    return 0;
}
