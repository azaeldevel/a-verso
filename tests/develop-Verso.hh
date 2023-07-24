
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
    static const GLfloat v_triangle_1[];
    static const GLfloat v_triangle_2[];

private://OpenGl Objects

    GLFWwindow* window;
    GLuint vao;
    GLuint vbo_triangle_1,vbo_triangle_2;
    char menu_main,menu_shape,menu_triangle;

    //>>>
    verso_here::Shader triangle_1,triangle_2;

    //>>>actions
    void (Develop::*scenary)();
    void scenary_triangle_1();
    void scenary_triangle_2();
};
