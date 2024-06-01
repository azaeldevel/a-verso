
#include <a-verso/0/shapes.hh>

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
class Shapes : public verso_here::gl::Scenary
{
private:
    void (Shapes::*action_draw)();

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    verso::numbers::Triangle<float> triangle;
    verso::Rectangle<float> rectangle;
    GLuint vao_triangle, vbo_triangle , vao_rectangle, vbo_rectangle;
    verso::Shader shader_triangle;
    verso::Shader shader_shape;

    void draw_triangle();
    void draw_plane();
    void draw_both();

public:
    Shapes();
    bool active();
    virtual void render();
    virtual void clean();

};


/**
*\brief Dibuja un cubo y puede rotarlo
*
**/
class Triangles : public verso_here::gl::Scenary
{
private:
    void (Triangles::*action_draw)();

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    verso::numbers::Triangle<float> triangle;
    GLuint vao_triangle, vbo_triangle;
    verso::Shader shader_triangle;

    void draw_triangle();
    void draw_running();

public:
    Triangles();
    bool active();
    virtual void render();
    virtual void clean();

};





class Develop : public verso_here::gl::Verso
{
public:
    Develop();
    virtual void render();
    virtual void clean();

public:
    Shapes shaders;
    Triangles triangles;

private:
    void handle();
    virtual bool active();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

};
