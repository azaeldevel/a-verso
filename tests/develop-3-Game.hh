
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shapes.hh>
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
	GLuint MatrixID;
	glm::mat4 projection,view,model,mvp;
	verso_here::Point<int,3,float> O;
	verso_here::Point<int,3,float> U1;
	verso_here::Point<float,3,float> camera,target_camera;
	float length_camera;

private:
    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
};
