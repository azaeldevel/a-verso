
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

struct Character
{
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};
static std::map<char, Character> Characters;


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
    void RenderText(verso_here::Shader &s, std::string text, float x, float y, float scale, glm::vec3 color);

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
    void action_rotate_scene();
    void action_cube();

private://OpenGl Objects
    GLuint vao;
    GLuint vbo_triangle,vbo_triangle_2,vbo_cube;
    GLuint ebo_rectangle,vbo_rectangle,vbo_rectangle_textured,ebo_rectangle_textured,vbo_text;
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
    static const GLfloat v_cube[];
    //static GLuint v_rectangle_indexs[];

	GLuint shader_0,shader_1;//shader_2
	verso_here::Shader shader_2,shader_text;
	GLuint MatrixID;
	glm::mat4 projection,view,model,mvp;
	glm::vec3 camera_direction,camera_target,camera_up,camera_rigth;
	float camera_radius;
	bool camera_rotate;

	//glm::vec3 O;
	verso_here::Point<float,3,float> camera;
	/*std::vector<verso_here::Point<float,3,float>> camera_path;
	verso_here::Point<float,3,float> camera_path_delta;
	size_t camera_index;*/
	int step,step_trans;
	//float fps;
	std::chrono::milliseconds fps_ms;

	FT_Library ft;
	FT_Face face;
};
