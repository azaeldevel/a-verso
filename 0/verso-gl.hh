
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
    class Verso;

    template<class V> V* WND(GLFWwindow* w)
    {
        return reinterpret_cast<V*>(glfwGetWindowUserPointer(w));
    }

    class Scenary : public scenary
    {
    private:

    protected:
        GLFWwindow* window;
        Verso* verso;

        static bool is_error(std::ostream&,const std::source_location location = std::source_location::current());
        static void error_callback(int error, const char* description);

    public:
        void set(GLFWwindow*);
    };


    class Verso : public Scenary
    {
    private:
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    protected:
        int width,height;
        Scenary* scenary;
        bool running;

        bool is_scenary()const;

    public:
        Verso();


        /**
        *\brief Crea una venta
        *\param title Es el texto que aparece como titulo de la ventana
        *\param width Ancho de la ventana
        *\param height Alto de la ventana
        **/
        virtual bool create(const char* title, int width, int height);

        /**
        *\brief Activa el esenrio indicado
        *\param scenary un puntero al esenario que se desea activa, si se indica NULL, no se cargara algun escerio
        **/
        void change(Scenary* scenary = NULL);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        const bool& is_runnig;
        void stop();
        void run();
        //void runnig(bool);

        float aspect()const;

    };

}

#endif // OCTETOS_AVERSO_AVERSO_HH
