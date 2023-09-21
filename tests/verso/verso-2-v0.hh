
#include <numbers/0/shapes.hh>

#include <a-verso/0/verso-gl.hh>
#include <a-verso/0/draw.hh>
#include <a-verso/0/quadric.hh>
#include <a-verso/0/objects.hh>
#include <a-verso/0/architect.hh>




namespace verso_here = oct::verso::v0;
namespace verso = oct::verso::v0;




/**
*\brief Dibuja un cubo y puede rotarlo
*
**/
class Shapes3 : public verso_here::gl::Scenary
{
private:
    void (Shapes3::*action_draw)();

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    verso::numbers::Triangle<float> triangle;
    verso::numbers::Rectangle<float> rectangle;
    GLuint vao, vbo_triangle, vbo_rectangle;
    verso::Shader shader_triangle;
    verso::Shader shader_shape;

    void draw_triangle();
    void draw_plane();

public:
    Shapes3();
    bool active();
    virtual void render();
    virtual void clean();

};


class Develop3 : public verso_here::gl::Verso
{
public:
    Develop3();
    virtual void render();
    virtual void clean();

public:
    Shapes3 shaders;

private:
    void handle();
    virtual bool active();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

};


