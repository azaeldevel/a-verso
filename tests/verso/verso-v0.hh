
#include <numbers/0/shapes.hh>

#include <a-verso/0/verso-gl.hh>
#include <a-verso/0/draw.hh>
#include <a-verso/0/quadric.hh>
#include <a-verso/0/objects.hh>
#include <a-verso/0/architect.hh>




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
    verso_here::numbers::Triangle<float> tri1;

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
    verso_here::numbers::Triangle<float> equilateral;
    verso_here::numbers::Scalene<float> rectangular;
    verso_here::numbers::Isosceles<float> isosceles;
    verso_here::numbers::Pyramid<float,3,3> pyramid;
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
    verso_here::numbers::Triangle<float> equilateral;
    verso_here::numbers::Scalene<float> rectangular;
    verso_here::numbers::Isosceles<float> isosceles;
    verso_here::numbers::Pyramid<float,3,3> pyramid;
    verso_here::numbers::Rectangle<float> rectangle;
    verso_here::numbers::Circle<float,3,1000> circle;
    verso_here::gl::Disk<GLdouble> disk;
    verso_here::gl::Cilinder<GLdouble> cilinder;
    verso_here::gl::Sphere<GLdouble> sphere;
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
    void draw_sphere();

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
class Design : public verso_here::gl::Scenary
{
private:
    GLint last_GL_DEPTH_FUNC,last_GL_DEPTH_TEST;
    GLfloat last_GL_DEPTH_CLEAR_VALUE;

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    verso_here::v1::Camera camera;
    char camera_transform;
    verso_here::gl::Plane<GLdouble> plane;
    verso_here::numbers::Triangle<float> triangle;
    verso_here::numbers::matrix<float,4,4,float> projection;
    verso_here::Shader shader_text,perspective;
    glm::mat4 Projection,View,Model,MVP;
    GLuint MatrixID;

    GLuint triangle_texture;

public:
    Design();
    bool active();
    virtual void render();
    virtual void clean();

    void (Design::*action_draw)();
    void draw_triangle();
    void draw_text();

};


/**
*\brief Dibuja un cubo y puede rotarlo
*
**/
class Shaders : public verso_here::gl::Scenary
{
private:
    GLint last_GL_DEPTH_FUNC,last_GL_DEPTH_TEST;
    GLfloat last_GL_DEPTH_CLEAR_VALUE;

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


public:
    Shaders();
    bool active();
    virtual void render();
    virtual void clean();

};


/**
*\brief LOGO : Ejemplo mde luces
*
**/
class Lighting : public verso_here::gl::Scenary
{
private:
    GLint last_GL_DEPTH_FUNC,last_GL_DEPTH_TEST;
    GLfloat last_GL_DEPTH_CLEAR_VALUE;

private:
    void update();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    verso_here::v2::Camera camera;
    verso_here::Shader lightingShader,lightCubeShader;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    glm::vec3 lightPos;
    GLuint VBO, cubeVAO,lightCubeVAO;
    static float vertices[];

public:
    Lighting();
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
    Design design;
    Lighting lighting;

private:
    void handle();
    void save(const std::filesystem::path&,bool seq);
    virtual bool active();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

};



