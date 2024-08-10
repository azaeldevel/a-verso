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

#include "shader.hh"
#include "shapes.hh"
#include "glfw/scenary.hh"

namespace verso = oct::verso::v1;

int main( void )
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
	verso::Scenary scenary;
	scenary.screen("A develop Verso",1024, 768);
	if(not scenary.window)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(scenary);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(scenary, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	/*GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);*/
	verso::VAO VertexArrayID;
	VertexArrayID.generate(1);
	VertexArrayID.bind();

	// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	verso::Shader shader;
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

	verso::numbers::Triangle<float> g_vertex_buffer_data;
	constexpr verso::numbers::vector<float,3> O(0);
	g_vertex_buffer_data = verso::numbers::Equilateral<float>(O,1.0f);
	/*
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	*/
	verso::BO vertexbuffer;
	vertexbuffer.generate(1);
	vertexbuffer.bind(GL_ARRAY_BUFFER);

	verso::numbers::Plane<float,3,4> plane{
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };
    //plane.print(std::cout);
	verso::BO VBO;
	VBO.generate(1);
	VBO.bind(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_DYNAMIC_DRAW);
	verso::BO bo_plane;
	bo_plane.generate(1);
	bo_plane.bind(GL_ELEMENT_ARRAY_BUFFER);
	unsigned int plane_indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(plane_indices), plane_indices,GL_STATIC_DRAW);

	do
    {
		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram(shader);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
        glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );
		glEnableVertexAttribArray(0);
            g_vertex_buffer_data.translate(0.01);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
            //triangle.printLn(std::cout);
            vertexbuffer.bind(GL_ARRAY_BUFFER);
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
        glDisableVertexAttribArray(0);

        glEnableVertexAttribArray(2);
            bo_plane.bind(GL_ELEMENT_ARRAY_BUFFER);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(scenary);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(scenary, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(scenary) == 0 );

	// Cleanup VBO and shader
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteProgram(shader);
	//glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}