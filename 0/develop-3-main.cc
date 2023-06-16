
#include "develop-3-Game.hh"

int main(int argc, char* argv[])
{
    Game g_game;
    g_game.init("Tutorial 01",1024, 768);
    while(g_game.is_running())
    {
        g_game.handleEvents();
        g_game.update();
        g_game.rendering();
    }

    g_game.clean();
    return 0;
}
