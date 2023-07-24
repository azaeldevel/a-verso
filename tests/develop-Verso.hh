
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


namespace verso_here = oct::verso::v0;

class Develop : public verso_here::Verso
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
    void save(const std::filesystem::path&,bool seq);
private://OpenGl Objects
    static const GLfloat v_triangle_1[];
    static const GLfloat v_triangle_2[];
    static const GLfloat v_cube_1[];
    static const GLfloat v_cube_1_colors[];

    int width,height;
    int* buffer;

    GLFWwindow* window;
    GLuint vao;
    GLuint vbo_triangle_1,vbo_triangle_2,vbo_cube_1,vbo_cube_1_colors;
    GLuint mvp_matrix;

    //>>>
    verso_here::Shader *shader_default,shader_red,shader_green;

    //>>>actions
    void (Develop::*scenary)();
    void scenary_triangle_1();
    void scenary_triangle_2();
    void scenary_cube_1();

    //camera
    glm::mat4 projection,view,model,mvp;
	glm::vec3 camera_position,camera_direction,camera_target,camera_up,camera_rigth,camera_front;
	const float camera_speed = 0.05f;

	enum Menu
	{
        none,
        make_escenary,
        activated_escenary,
            camera_focused,
                camera_translation,
                camera_rotation,

	};
	Menu menu;
};
