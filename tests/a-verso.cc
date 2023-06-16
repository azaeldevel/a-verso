
#include<SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

void init(){}
void render(){}
void update(){}
void handleEvents(){}
void clean(){}
bool g_bRunning = true;
int main()
{
init();
while(g_bRunning)
{
handleEvents();
update();
render();
}
clean();
}
