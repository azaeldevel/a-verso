// Include standard headers
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
//GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


#include "glfw/scenary.hh"

namespace verso = oct::verso::v1;

int main( void )
{
    verso::glfw::Triangle triangle;
    triangle.run();
	return EXIT_SUCCESS;
}
