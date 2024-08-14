
#ifndef OCTETOS_VERSO_V3_GLFW_EXAMPLES_H
#define OCTETOS_VERSO_V3_GLFW_EXAMPLES_H

#include "glfw/scenary.hpp"




//https://cs.lmu.edu/~ray/notes/openglexamples/
namespace oct::verso::v1::devel::glfw
{
    struct awindow : public v1::glfw::Scenary
    {
        virtual void run();
    };

}

#endif