
#ifndef OCTETOS_AVERSO_VERSO_GL_HH
#define OCTETOS_AVERSO_VERSO_GL_HH

#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
//#include <map>

#include <shapes.hh>
#include <Shader.hh>
#include <Camera.hh>

#include "Verso.hh"

namespace oct::verso::v0::gl
{
    class Scenary : public scenary
    {
    private:

    protected:
        GLFWwindow* window;

    public:
    };

    class Verso : public Scenary
    {
    private:
        int width,height;

    protected:

    public:
        virtual bool create(const char* title, int width, int height);
        virtual bool initialize() = 0;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    };

}

#endif // OCTETOS_AVERSO_AVERSO_HH
