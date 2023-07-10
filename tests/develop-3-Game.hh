
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shapes.hh>
#include <Verso.hh>
#include <Shader.hh>

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

public:

private:
    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

    void (Game::*action_main)();
    void (Game::*action_shape)();
    void action_align();
    void action_x();
    void action_create_triangle();
    void action_create_rectangle();
    void action_create_rectangle_2();
    void action_create_triangle_2();
    void action_create_rectangle_textured();

private://OpenGl Objects
    GLuint vao;
    GLuint vbo_triangle,vbo_triangle_2;
    GLuint ebo_rectangle,vbo_rectangle,vbo_rectangle_textured,ebo_rectangle_textured;
    float timeValue,greenValue;
    int vertexColorLocation;
    GLFWwindow* window;
    //GLuint vertexbuffer;
    static const GLfloat v_triangle[];
    static const GLfloat v_triangle_2[];
    static const GLfloat v_rectangle[];
    static const GLfloat v_rectangle_ebo_2[];
    static const GLuint v_rectangle_indexs[];
    static const GLfloat v_triangle_texture[];
    static const GLfloat v_rectangle_textured[];
    //static GLuint v_rectangle_indexs[];

	GLuint shader_0,shader_1;//shader_2
	verso_here::Shader shader_2;
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
};
