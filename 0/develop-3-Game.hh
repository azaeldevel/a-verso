
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Verso.hh"

namespace verso_here = oct::verso::v0;

class Game : public verso_here::Verso
{
public:
    //Game(const std::filesystem::path&);
    virtual bool initialize(const char* title, int width, int height);
    virtual void rendering();
    virtual void clean();
    virtual void handleEvents();

private:
    GLFWwindow* window;
};
