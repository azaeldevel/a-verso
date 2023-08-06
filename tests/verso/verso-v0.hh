


#include <verso-gl.hh>




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
    verso_here::Camera camera;
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
    verso_here::Camera camera;
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

class Develop : public verso_here::gl::Verso
{
public:
    //Game(const std::filesystem::path&);
    virtual void render();
    virtual void clean();

public:

private:
    void handle();
    void save(const std::filesystem::path&,bool seq);
    virtual bool initialize();

private:
    P1L5 p1l5;
    Cube1 cube1;
    Triangle2 triangle2;
};
