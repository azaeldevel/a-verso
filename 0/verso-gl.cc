
#include<chrono>
#include<thread>


#include "verso-gl.hh"

namespace oct::verso::v0::gl
{

Version::Version(int major, int minor) : accepted(false)
{
}

void Scenary::set(GLFWwindow* w)
{
    window = w;
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





void Verso::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    //std::cout << "void Verso::framebuffer_size_callback(GLFWwindow*,int,int)\n";
    glViewport(0, 0, width, height);
}
void Verso::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Verso::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key)
    {
        //std::cout << "Closing verso...\n";
        WINDOW(window,Verso)->stop();
    }
}
void Scenary::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


Verso::Verso() : version(3,3),is_runnig(running)
{
}
Verso::Verso(int M, int m) : version(M,m),is_runnig(running)
{
}
bool Verso::create(const char* title, int w, int h)
{
    _width = w;
    _height = h;

    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OCTETOS_VERSO_OPENGL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OCTETOS_VERSO_OPENGL_MINOR);
	//glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#if OCTETOS_VERSO_OPENGL_MAJOR == 3 && OCTETOS_VERSO_OPENGL_MINOR >= 0
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif
#if OCTETOS_VERSO_OPENGL_MAJOR == 3 && OCTETOS_VERSO_OPENGL_MINOR >= 2
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // To make MacOS happy; should not be needed
#endif
#if OCTETOS_VERSO_OPENGL_MAJOR == 3 && OCTETOS_VERSO_OPENGL_MINOR >= 3

#endif

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(_width, _height, title, NULL, NULL);
	if( window == NULL ) return false;

	glfwSetErrorCallback(error_callback);
	glfwSetFramebufferSizeCallback(window, Verso::framebuffer_size_callback);
	glfwSetKeyCallback(window, Verso::key_callback);

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) return false;

	// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	scenary = NULL;
    glfwSetWindowUserPointer(window,this);
	//is_error(std::cout);

    //>>>>>

    //<<<<<
    //default_scenary.active();
    this->active();
	run();
    return true;
}
void Verso::change(Scenary* s)
{
    //std::cout << "Changing..\n";
    if(scenary) scenary->clean();
    //std::cout << "Changed..\n";

    if(s)
    {
        scenary = s;
        scenary->set(window);
        scenary->active();
    }
    else
    {
        scenary = NULL;
        this->active();
    }
}
bool Verso::is_scenary()const
{
    if(scenary) return true;

    return false;
}

void Verso::stop()
{
    running = false;
}
void Verso::run()
{
    running = true;
}
float Verso::aspect()const
{
    return float(_width)/float(_height);
}


}
