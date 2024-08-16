
#ifndef OCTETOS_AVERSO_VERSO_GLFW_HPP
#define OCTETOS_AVERSO_VERSO_GLFW_HPP

#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <source_location>
#include "../scenary.hh"
#include "../shader.hh"
#include "../shapes.hh"


#define WINDOW(W,C) reinterpret_cast<C*>(glfwGetWindowUserPointer(W))


namespace oct::verso::v1::glfw
{
    struct Version
    {
        int major;
        int minor;
        bool accepted;

        Version() = default;
        Version(int major, int minor);
    };

    template<class V> V* WND(GLFWwindow* w)
    {
        return reinterpret_cast<V*>(glfwGetWindowUserPointer(w));
    }

    /**
    *\brief Encapsula lo correcpondiente al escenario y GLFW
    *
    */
    struct Scenary : public IScenary
    {
        Scenary();
        Scenary(int major, int minor);

        bool screen(const char* title, int width, int height);

        Version version;
        bool running;
        GLFWwindow* window;
        int width,height;

        static bool is_error(std::ostream&,const std::source_location location = std::source_location::current());
        static void error_callback(int error, const char* description);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        float aspect()const;
        operator GLFWwindow*();
    };

    struct Triangle : public Scenary
    {

        virtual void run();
    };

}

#endif // OCTETOS_AVERSO_AVERSO_HH
