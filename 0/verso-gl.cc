
#include<chrono>
#include<thread>


#include "verso-gl.hh"

namespace oct::verso::v0::gl
{


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
    glViewport(0, 0, width, height);
}
void Scenary::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
Verso::Verso()
{
    glfwSetErrorCallback(error_callback);
}
bool Verso::create(const char* title, int w, int h)
{
    width = w;
    height = h;


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
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#if OCTETOS_VERSO_OPENGL_MAJOR >= 3 && OCTETOS_VERSO_OPENGL_MINOR >= 0
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif
#if OCTETOS_VERSO_OPENGL_MAJOR >= 3 && OCTETOS_VERSO_OPENGL_MINOR >= 2
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // To make MacOS happy; should not be needed
#endif
#if OCTETOS_VERSO_OPENGL_MAJOR >= 3 && OCTETOS_VERSO_OPENGL_MINOR >= 3

#endif

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( width, height, title, NULL, NULL);
	if( window == NULL ) return false;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) return false;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	scenary = &default_scenary;
	//is_error(std::cout);

    //>>>>>

    //<<<<<
    default_scenary.initialize();
    this->initialize();
	running = true;
    return true;
}
void Verso::change(Scenary* s)
{
    if(s)
    {
        scenary->clean();
        scenary = s;
    }
    else
    {
        scenary = &default_scenary;
    }
    scenary->initialize();
    scenary->set(window);
}
bool Verso::is_scenary()const
{
    if(scenary == &default_scenary) return false;
    if(scenary == NULL) return false;

    return true;
}





void Default::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void Default::clean()
{

}
bool Default::initialize()
{

    return true;
}
void Default::handle()
{
    if(not window) return;


}

}
