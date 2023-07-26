


#include <verso-gl.hh>




namespace verso_here = oct::verso::v0;


class Trangle1 : public verso_here::gl::Scenary
{
public:

};

class Trangle2 : public verso_here::gl::Scenary
{
public:

};

class Cube1 : public verso_here::gl::Scenary
{
public:

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
    void handleEvents();
    void update();
    void rendering();
    void save(const std::filesystem::path&,bool seq);
    virtual bool initialize();

private:

};
