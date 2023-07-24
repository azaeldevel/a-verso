#include <fstream>
#include <chrono>
#include <thread>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include "develop-Verso.hh"


const GLfloat Develop::v_triangle_1[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

const GLfloat Develop::v_triangle_2[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

bool Develop::initialize(const char* title, int width, int height)
{
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if( window == NULL )
    {
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Initialize GLEW
	if (glewInit() != GLEW_OK)
    {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


    //>>
    triangle_1.build("tests/triangle_1.vs", "tests/triangle_1.fs");
    triangle_2.build("tests/triangle_2.vs", "tests/triangle_2.fs");
    shader_3.build("tests/shader_3.vs", "tests/shader_3.fs");
    mvp_matrix = glGetUniformLocation(shader_3, "MVP");

	//>>>>>
	glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo_triangle_1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_triangle_1), v_triangle_1, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo_triangle_2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_triangle_2), v_triangle_2, GL_STATIC_DRAW);

	scenary = NULL;
	running = true;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	camera = glm::vec3(4,3,3);//posision de la camara

	// Camera matrix
	view       = glm::lookAt(
								camera, // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp        = projection * view * model;

    return true;
}

void Develop::handleEvents()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(window) != 0 )
    {
        running = false;
    }
    else if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        //std::cout << "Triangle\n";
        scenary = &Develop::scenary_triangle_1;
    }
    else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        //std::cout << "Triangle\n";
        scenary = &Develop::scenary_triangle_2;
    }
}

void Develop::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader_3.use();
    glUniformMatrix4fv(mvp_matrix, 1, GL_FALSE, &mvp[0][0]);

    //>>
    if(scenary) (this->*scenary)();


}

void Develop::rendering()
{
    handleEvents();
    update();

    glfwSwapBuffers(window);
    glfwPollEvents();

}

void Develop::clean()
{
    glDeleteBuffers(1, &vbo_triangle_1);
	glDeleteVertexArrays(1, &vao);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}


void Develop::scenary_triangle_1()
{
    //std::cout << "Dariwing triangle\n";
    //triangle_1.use();
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_1);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
void Develop::scenary_triangle_2()
{
    //std::cout << "Dariwing triangle\n";
    //triangle_2.use();
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_2);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

