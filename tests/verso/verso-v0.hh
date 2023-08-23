
#include <numbers/0/shapes.hh>

#include <verso-gl.hh>
#include <draw.hh>
#include <quadric.hh>



namespace numbers_here = oct::nums::v0;
namespace verso_here = oct::verso::v0;


class P1L5 : public verso_here::gl::Scenary
{//Hello Triangle - Triangulo 1
public:
    P1L5() = default;
    virtual void render();
    virtual void clean();
    virtual bool initialize();

private:
    void handle();
    void update();

    static const char *vertexShaderSource;
    static const char *fragmentShaderSource;
    verso_here::Shader shader_triangle;
    GLuint VBO, VAO;
};

class Cube1 : public verso_here::gl::Scenary
{
public:
    virtual void render();
    virtual void clean();
    virtual bool initialize();

private:
    void handle();
    void update();

    GLuint VertexArrayID,vertexbuffer,colorbuffer;
    verso_here::Shader shader_cube;
    glm::mat4 Projection,Model,MVP;
    GLuint MatrixID;
    static const GLfloat g_vertex_buffer_data[];
    static const GLfloat g_color_buffer_data[];
    verso_here::v2::Camera camera;
    float delta_time, last_frame;
    GLint last_value;
};


class Triangle2 : public verso_here::gl::Scenary
{//Hello Triangle - Triangulo 1
public:
    Triangle2();
    virtual void render();
    virtual void clean();
    virtual bool initialize();

private:
    void handle();
    void update();

    static const char *vertexShaderSource;
    static const char *fragmentShaderSource;
    verso_here::Shader shader_triangle;
    GLuint VBO, VAO;
    static float vertices[];
    verso_here::Triangle<float,3,float> triangle;
    verso_here::nums_here::axis axis;
};

class Light : public verso_here::gl::Scenary
{
private:
    verso_here::Shader shader_lighting,shader_light_cube;
    GLuint vao_cube,vao_cube_light;
    GLuint vbo_cube;
    verso_here::v2::Camera camera;
    glm::mat4 projection,view,model,mvp;
    glm::vec3 light_position;
    float delta_time, last_frame;
    float aspect;

private:
    void handleEvents();
    void update();

public:
    bool initialize();
    virtual void render();
    virtual void clean();

};

class JGCI_1 : public verso_here::gl::Scenary
{
private:


private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    bool active();
    virtual void render();
    virtual void clean();

};

class JGCI_2 : public verso_here::gl::Scenary
{
private:


private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    bool active();
    virtual void render();
    virtual void clean();

};

class JGCI_3 : public verso_here::gl::Scenary
{
private:
    GLint last_GL_DEPTH_FUNC,last_GL_DEPTH_TEST;
    GLfloat last_GL_DEPTH_CLEAR_VALUE;

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


public:
    bool active();
    virtual void render();
    virtual void clean();

};

/**
*\brief Dibuja un cubo y puede rotarlo
*
**/
class JGCI_4 : public verso_here::gl::Scenary
{
private:
    GLint last_GL_DEPTH_FUNC,last_GL_DEPTH_TEST;
    GLfloat last_GL_DEPTH_CLEAR_VALUE;
    float rotate_x,rotate_y;

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


public:
    JGCI_4();
    bool active();
    virtual void render();
    virtual void clean();

};


/**
*\brief Dibuja un cubo y puede rotarlo
*
**/
class JGCI_5 : public verso_here::gl::Scenary
{
private:
    GLint last_GL_DEPTH_FUNC,last_GL_DEPTH_TEST;
    GLfloat last_GL_DEPTH_CLEAR_VALUE;


private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    numbers_here::Triangle<float> tri1;

public:
    JGCI_5();
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
    GLint last_GL_DEPTH_FUNC,last_GL_DEPTH_TEST;
    GLfloat last_GL_DEPTH_CLEAR_VALUE;

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    numbers_here::Triangle<float> equilateral;
    numbers_here::Scalene<float> rectangular;
    numbers_here::Isosceles<float> isosceles;
    numbers_here::Pyramid<float,3,3> pyramid;
    verso_here::v1::Camera camera;

    void (Triangles::*action_draw)();
    void draw_rectangeluar();
    void draw_isosceles();
    void draw_equilateral();
    void draw_pyramid();

public:
    Triangles();
    bool active();
    virtual void render();
    virtual void clean();

};


/**
*\brief Dibuja un cubo y puede rotarlo
*
**/
class Shapes : public verso_here::gl::Scenary
{
private:
    GLint last_GL_DEPTH_FUNC,last_GL_DEPTH_TEST;
    GLfloat last_GL_DEPTH_CLEAR_VALUE;

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    numbers_here::Triangle<float> equilateral;
    numbers_here::Scalene<float> rectangular;
    numbers_here::Isosceles<float> isosceles;
    numbers_here::Pyramid<float,3,3> pyramid;
    numbers_here::Rectangle<float> rectangle;
    numbers_here::Circle<float,3,1000> circle;
    verso_here::gl::Disk<GLdouble> disk;
    verso_here::gl::Cilinder<GLdouble> cilinder;
    verso_here::v1::Camera camera;

    void (Shapes::*action_draw)();
    void draw_rectangeluar();
    void draw_isosceles();
    void draw_equilateral();
    void draw_pyramid();
    void draw_rectangle();
    void draw_circle();
    void draw_disk();
    void draw_cilinder();

public:
    Shapes();
    bool active();
    virtual void render();
    virtual void clean();

};

class Develop : public verso_here::gl::Verso
{
public:
    //Game(const std::filesystem::path&);
    virtual void render();
    virtual void clean();

public:
    JGCI_1 jgci_1;
    JGCI_2 jgci_2;
    JGCI_3 jgci_3;
    JGCI_4 jgci_4;
    JGCI_5 jgci_5;
    Triangles triangles;
    Shapes shapes;

private:
    void handle();
    void save(const std::filesystem::path&,bool seq);
    virtual bool active();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    //P1L5 p1l5;
    //Cube1 cube1;
    //Triangle2 triangle2;
};



