
#include<iostream>

#include "scenary.hh"

namespace oct::verso::v1::glfw
{

Version::Version(int M, int m) : major(M),minor(m),accepted(false)
{
}







Scenary::Scenary() : version(3,3),running(false),window(NULL)
{
}
Scenary::Scenary(int M, int m) : version(M,m),running(false),window(NULL)
{
}


bool Scenary::screen(const char* title, int w, int h)
{
    width = w;
    height = h;

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	//std::cout << "Windows : " << window << "\n";

	glfwSetErrorCallback(error_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

    return true;
}
float Scenary::aspect()const
{
    return float(width)/float(height);
}
Scenary::operator GLFWwindow*()
{
    return window;
}

void Scenary::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void Scenary::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(GLFW_KEY_ESCAPE == key)
    {
        WINDOW(window,Scenary)->running = false;
    }
}
void Scenary::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

bool Scenary::is_error(std::ostream& out,const std::source_location location)
{
    GLenum error = glGetError();
    switch(error)
    {
    case GL_NO_ERROR:
        return false;

    default:
        out << location.file_name() << '('
              << location.line() << ':'
              << location.column() << ") `"
              << location.function_name() << "`: " << error << "\n";
        return true;
    }

    return false;
}

}
