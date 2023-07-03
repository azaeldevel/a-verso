
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
    //GLuint vertexbuffer;
    static const GLfloat v_triangle[];
    static const GLfloat v_rectangle[];
    //static GLuint v_rectangle_indexs[];

	GLuint programID;
	GLuint MatrixID;
	glm::mat4 projection,view,model,mvp;
	//glm::vec3 O;
	verso_here::Point<float,3,float> camera;
	/*std::vector<verso_here::Point<float,3,float>> camera_path;
	verso_here::Point<float,3,float> camera_path_delta;
	size_t camera_index;*/
	int step,step_trans;
	//float fps;
	std::chrono::milliseconds fps_ms;

private:
    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

    void (Game::*action_main)();
    void (Game::*action_shape)();
    void action_align();
    void action_x();
    void action_create_triangle();
    void action_create_rectangle();

private://OpenGl Objects
    GLuint vao;
    GLuint vbo_triangle;
    GLuint ebo_rectangle,vbo_rectangle;
};
