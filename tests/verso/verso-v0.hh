
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
#include <Camera.hh>


namespace verso_here = oct::verso::v0;


class Trangle1 : public verso_here::Scenary
{
public:

};

class Trangle2 : public verso_here::Scenary
{
public:

};

class Cube1 : public verso_here::Scenary
{
public:

};

class Light : public verso_here::Scenary
{
public:

};

class Develop : public verso_here::Verso
{
public:
    //Game(const std::filesystem::path&);
    bool initialize(const char* title, int width, int height);
    virtual void render();
    virtual void clean();

public:

private:
    void handleEvents();
    void update();
    void rendering();
    void save(const std::filesystem::path&,bool seq);
    bool initialize();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
private:
    verso_here::Shader shader_lighting,shader_light_cube;
    int width,height;
    GLFWwindow* window;
    GLuint vao_cube,vao_cube_light;
    GLuint vbo_cube;
    verso_here::Camera camera;
    glm::mat4 projection,view,model,mvp;
    glm::vec3 light_position;
    float delta_time, last_frame;

    static verso_here::Cube<GLfloat,3,GLfloat> cube_1;
};
