
#include <filesystem>

#include "Verso.hh"


class Game : public oct::verso::Verso
{
public:
    //Game(const std::filesystem::path&);
    virtual bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    virtual void rendering();
    virtual void clean();
    virtual void handleEvents();

private:
    SDL_Window* window;
    SDL_Renderer* render;

    SDL_Texture* m_pTexture; // the new SDL_Texture variable
    SDL_Rect m_sourceRectangle; // the first rectangle
    SDL_Rect m_destinationRectangle; // another rectangle

    const std::filesystem::path path;
};
