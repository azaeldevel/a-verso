
#ifndef OCTETOS_AVERSO_V1_COMMON_HH
#define OCTETOS_AVERSO_V1_COMMON_HH

#if defined(OCTETOS_VERSO_GLFW)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#elif defined(OCTETOS_VERSO_GLUT)
    #include <GL/glut.h>
#else
    #error "Libreria OpenGL desconocida."
#endif // OCTETOS_VERSO_GLFW

#include <numbers/0/vector.hh>
//#include <core/3/Exception.hh>


namespace oct::verso::v1
{
    namespace core_here = oct::core::v3;
    namespace core = oct::core::v3;
    namespace nums_here = oct::nums::v0;
    namespace numbers = oct::nums::v0;

    class VAO
    {
    public:
        VAO();
        ~VAO();

        void generate(int);
        void bind();

        operator GLuint();

    private:
        GLuint id;
        int size;
    };

    class VBO
    {
    public:
        VBO();
        ~VBO();

        void generate(int);
        void bind(GLenum);

        operator GLuint();

    private:
        GLuint id;
        int size;
    };
}

#endif // OCTETOS_AVERSO_AVERSO_HH
