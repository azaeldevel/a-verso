
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <Verso.hh>

namespace verso_here = oct::verso::v0;

class Game : public verso_here::Verso
{
public:
    //Game(const std::filesystem::path&);
    virtual bool initialize(const char* title, int width, int height);
    virtual void handleEvents();
    virtual void update();
    virtual void rendering();
    virtual void clean();

private:
    GLFWwindow* window;
    GLuint vertexbuffer;
    static const GLfloat g_vertex_buffer_data[];
	GLuint programID;

private:
    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
};
