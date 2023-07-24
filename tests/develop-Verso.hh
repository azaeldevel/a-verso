
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

#include <shapes.hh>
#include <Verso.hh>
#include <Shader.hh>


namespace verso_here = oct::verso::v0;

class Develop : public verso_here::Verso
{
public:
    //Game(const std::filesystem::path&);
    virtual bool initialize(const char* title, int width, int height);
    virtual void handleEvents();
    virtual void update();
    virtual void rendering();
    virtual void clean();

public:

private:


private://OpenGl Objects

    GLFWwindow* window;


};
