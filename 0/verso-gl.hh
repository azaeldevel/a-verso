
#ifndef OCTETOS_AVERSO_VERSO_GL_HH
#define OCTETOS_AVERSO_VERSO_GL_HH

#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <source_location>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#include <map>

#include <shapes.hh>
#include <Shader.hh>
#include <Camera.hh>

#include "verso.hh"
#include "Camera.hh"

#define WINDOW(W,C) reinterpret_cast<C*>(glfwGetWindowUserPointer(W))


namespace oct::verso::v0::gl
{

    template<class V> V* WND(GLFWwindow* w)
    {
        return reinterpret_cast<V*>(glfwGetWindowUserPointer(w));
    }

    class Scenary : public scenary
    {
    private:

    protected:
        GLFWwindow* window;

        static bool is_error(std::ostream&,const std::source_location location = std::source_location::current());
        static void error_callback(int error, const char* description);

    public:
        void set(GLFWwindow*);
    };

    class Default : public Scenary
    {
    public:
        virtual void render();
        virtual void clean();
        virtual bool active();
        virtual void handle();

    };

    class Verso : public Scenary
    {
    private:
        Default default_scenary;
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    protected:
        int width,height;
        Scenary* scenary;
        bool running;

        bool is_scenary()const;

    public:
        Verso();

        virtual bool create(const char* title, int width, int height);
        bool is_running();
        void change(Scenary* = NULL);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        const bool& is_runnig;
        void stop();
        void run();
        //void runnig(bool);

    };

}

#endif // OCTETOS_AVERSO_AVERSO_HH
