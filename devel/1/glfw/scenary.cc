
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

void Triangle::run()
{

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return ;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	// Open a window and create its OpenGL context
	/*
	window = glfwCreateWindow( 1024, 768, "A develop Verso", NULL, NULL);
	if( window == NULL )
    {
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	*/
	//verso::glfw::Scenary scenary;
	screen("A develop Verso",1024, 768);
	if(not window)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	/*GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);*/
	VAO VertexArrayID;
	VertexArrayID.generate(1);
	VertexArrayID.bind();

	// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	Shader shader;
	//GLuint programID = 0;
	std::filesystem::path shader_directory("devel/1/shaders");
    if(not shader.build(shader_directory/"SimpleTransform.vertex",shader_directory/"SingleColor.fragment"))
    {
        std::cout << "Fail shaders compilation\n";
    }

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(shader, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	numbers::Triangle<float> triangle,triangle2;
	constexpr numbers::vector<float,3> O(0);
	triangle = numbers::Equilateral<float>(O,1.0f);
	/*
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	*/
	BO vertex_triangle;
	vertex_triangle.generate(1);
	vertex_triangle.bind(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_DYNAMIC_DRAW);

	triangle2 = numbers::Equilateral<float>(O,0.3f);
	BO vertex_triangle2;
	vertex_triangle2.generate(1);
	vertex_triangle2.bind(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_DYNAMIC_DRAW);

	do
    {
		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram(shader);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glEnableVertexAttribArray(0);
            triangle.translate(0.01);
            glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_DYNAMIC_DRAW);
            //triangle.printLn(std::cout);
            vertex_triangle.bind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
        glDisableVertexAttribArray(0);


		/*glEnableVertexAttribArray(1);
            triangle2.translate(0.001);
            glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_DYNAMIC_DRAW);
            //triangle.printLn(std::cout);
            vertex_triangle2.bind(GL_ARRAY_BUFFER);
            glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
        glDisableVertexAttribArray(1);*/

		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteProgram(shader);
	//glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}


}
