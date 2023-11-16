
#include <cstring>
#include <string>

#include "verso-2-v0.hh"

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

    //std::cout << "running..\n";
    Develop g_game;
    //std::cout << "creating..\n";
    g_game.create("Developing / Tutorial - Learning OpenGL...",800, 600);
    //std::cout << "created..\n";
    while(g_game.is_runnig)
    {
        //std::cout << "rendering..\n";
        g_game.render();
    }

    g_game.clean();
    return 0;
}
