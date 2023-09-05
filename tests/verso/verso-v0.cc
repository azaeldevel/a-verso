#include <fstream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <map>


#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include "verso-v0.hh"
#include <a-verso/0/draw.hh>
#include <a-verso/0/gl.hh>
#include "stb/stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H




void Develop::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_PRESS)
    {
        //std::cout << "Closing...\n";
        WINDOW(window,Develop)->stop();
    }
    else if(GLFW_KEY_1 == key && action == GLFW_PRESS)
    {
        //std::cout << "Cambieando de escenario..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->jgci_1);
    }
    else if(GLFW_KEY_2 == key && action == GLFW_PRESS)
    {
        //std::cout << "Cambieando de escenario..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->jgci_2);
    }
    else if(GLFW_KEY_3 == key && action == GLFW_PRESS)
    {
        //std::cout << "\nCambieando de escenario..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->jgci_3);
        //std::cout << "Cambiado el escenario..\n";
    }
    else if(GLFW_KEY_4 == key && action == GLFW_PRESS)
    {
        //std::cout << "Cambieando de escenario..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->jgci_4);
    }
    else if(GLFW_KEY_5 == key && action == GLFW_PRESS)
    {
        //std::cout << "Cambieando de escenario..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->jgci_5);
    }
    else if(GLFW_KEY_6 == key && action == GLFW_PRESS)
    {
        //std::cout << "Cambieando de escenario..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->shapes);
    }
    else if(GLFW_KEY_7 == key && action == GLFW_PRESS)
    {
        //std::cout << "Cambieando de escenario..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->design);
    }
    else if(GLFW_KEY_8 == key && action == GLFW_PRESS)
    {
        //std::cout << "Cambieando de escenario..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->lighting);
    }

}


bool Develop::active()
{
    //std::cout << "bool Develop::active()\n";
    glfwSetKeyCallback(window, Develop::key_callback);

    return true;
}



void Develop::render()
{
    if(scenary)
    {
        scenary->render();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }


    glfwSwapBuffers(window);
    glfwPollEvents();

}
void Develop::clean()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}



const char *P1L5::vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *P1L5::fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


bool P1L5::initialize()
{
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    is_error(std::cout);
    shader_triangle.build(std::string(vertexShaderSource),std::string(fragmentShaderSource));
    is_error(std::cout);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    is_error(std::cout);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    is_error(std::cout);

    return true;
}
void P1L5::render()
{
    handle();
    update();

    glClear(GL_COLOR_BUFFER_BIT);
    shader_triangle.use();

    // 1rst attribute buffer : vertices
    //glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    glDrawArrays(GL_TRIANGLES, 0, 3);

    //glDisableVertexAttribArray(0);
}
void P1L5::clean()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    shader_triangle.clean();
}

void P1L5::update()
{

}
void P1L5::handle()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(window) != 0 )
    {
        //running = false;
    }
    /*else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        camera.walking_front(delta_time);
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        camera.walking_back(delta_time);
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        camera.walking_right(delta_time);
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        camera.walking_left(delta_time);
    }
    else
    {

    }*/


}












const GLfloat Cube1::g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

const GLfloat Cube1::g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};


bool Cube1::initialize()
{
    glGetIntegerv(GL_DEPTH_FUNC,&last_value);

	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	//Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	shader_cube.build(std::filesystem::path("tests/verso/LOGO/shaders/TransformVertexShader.vertexshader"), std::filesystem::path("tests/verso/LOGO/shaders/ColorFragmentShader.fragmentshader" ));

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(shader_cube, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	/*
	View       = glm::lookAt(
								glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
    */
    camera.lookAt(verso_here::Point<float,3>(4,3,-3),verso_here::Point<float,3>(0,0,0));
	// Model matrix : an identity matrix (model will be at the origin)
	Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP        = Projection * (glm::mat4&)camera * Model; // Remember, matrix multiplication is the other way around

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices


	// One color for each vertex. They were generated randomly.


	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    return true;
}
void Cube1::render()
{
    handle();
    update();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Use our shader
    shader_cube.use();


        MVP        = Projection * (glm::mat4&)camera * Model;

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

}
void Cube1::clean()
{
    //std::cout << "cleaning..\n";
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(last_value);
    glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	shader_cube.clean();
}

void Cube1::update()
{
    float current_frame = static_cast<float>(glfwGetTime());
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
}
void Cube1::handle()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(window) != 0 )
    {
        //running = false;
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        camera.walking_front(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        camera.walking_back(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        camera.walking_right(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        camera.walking_left(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {

    }
    else
    {

    }


}









const char *Triangle2::vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *Triangle2::fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.4f, 0.5f, 1.0f);\n"
    "}\n\0";

float Triangle2::vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };
//verso_here::Triangle<float,3,float> Triangle2::triangle(vertices);
Triangle2::Triangle2() : triangle(vertices)
{
}
bool Triangle2::initialize()
{
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    shader_triangle.build(std::string(vertexShaderSource),std::string(fragmentShaderSource));

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), reinterpret_cast<float*>(&triangle), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    axis = verso_here::nums_here::axis::x;

    return true;
}
void Triangle2::render()
{
    handle();
    update();
    glClear(GL_COLOR_BUFFER_BIT);
    shader_triangle.use();

    // 1rst attribute buffer : vertices
    //glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    glDrawArrays(GL_TRIANGLES, 0, 3);

    //glDisableVertexAttribArray(0);
}
void Triangle2::clean()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader_triangle.clean();
}

void Triangle2::update()
{
    triangle.rotate(0.0174533,axis);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), reinterpret_cast<float*>(&triangle), GL_STATIC_DRAW);
}
void Triangle2::handle()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(window) != 0 )
    {
        //running = false;
    }
    else if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        axis = verso_here::nums_here::axis::x;
    }
    else if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        axis = verso_here::nums_here::axis::y;
    }
    else if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        axis = verso_here::nums_here::axis::z;
    }


}




















bool JGCI_1::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glfwSetKeyCallback(window, JGCI_1::key_callback);

    return true;
}
void JGCI_1::render()
{
    //glClearColor(0.0,0.0,0.0,0.0);
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT);
    // Boramos la pantalla
    glMatrixMode(GL_PROJECTION);
    // Modo proyección
    glLoadIdentity();
    // Cargamos la matriz identidad
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    // Proyección ortográfica, dentro del cubo señalado
    glMatrixMode(GL_MODELVIEW);
    // Modo de modelado
    glBegin(GL_TRIANGLES);
        // Dibujamos un triángulo
        glColor3f(1.0,0.0,0.0);
        // Color del primer vértice: rojo
        glVertex3f(0.0,0.8,0.0);
        // Coordenadas del primer vértice
        glColor3f(0.0,1.0,0.0);
        // Color del segundo vértice: verde
        glVertex3f(-0.6,-0.2,0.0);
        // Coordenadas del segundo vértice
        glColor3f(0.0,0.0,1.0);
        // Color del tercer vértice: azúl
        glVertex3f(0.6,-0.2,0.0);
        // Coordenadas del tercer vértice
    glEnd();
    // Terminamos de dibujar
    glFlush();
    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void JGCI_1::clean()
{
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void JGCI_1::update()
{

}

void JGCI_1::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key)
    {
        //std::cout << "Closing...\n";
        WINDOW(window,Develop)->change();
    }
}


bool JGCI_2::active()
{
    glfwSetKeyCallback(window, JGCI_2::key_callback);
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    return true;
}
void JGCI_2::render()
{
    //glClearColor(0.0,0.0,0.0,0.0);
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT);
    // Boramos la pantalla
    glMatrixMode(GL_PROJECTION);
    // Modo proyección
    glLoadIdentity();
    // Cargamos la matriz identidad
    gluPerspective(0.0,1.0,1.0,100.0);//glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    // Proyección ortográfica, dentro del cubo señalado
    glMatrixMode(GL_MODELVIEW);
    // Modo de modelado
    glBegin(GL_QUADS);
        // Dibujamos un cuadrado
        glColor3f(0.0,1.0,1.0);
        // Color para el cuadrado
        glVertex3f(-0.5,0.5,-0.5);
        // Coordenadas del primer vértice (superior-izquierda)
        glVertex3f(-0.5,-0.5,0.5);
        // Coordenadas del segundo vértice (inferior-izquierda)
        glVertex3f(0.5,-0.5,0.5);
        // Coordenadas del primer vértice (inferior-derecha)
        glVertex3f(0.5,0.5,-0.5);
        // Coordenadas del primer vértice (superior-derecha)
    glEnd();
    // Terminamos de dibujar
    glFlush();
    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void JGCI_2::clean()
{
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void JGCI_2::update()
{

}

void JGCI_2::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key)
    {
        //std::cout << "Closing...\n";
        WINDOW(window,Develop)->change();
    }
}


bool JGCI_3::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glGetIntegerv(GL_DEPTH_FUNC,&last_GL_DEPTH_FUNC);
    //glGetIntegerv(GL_DEPTH_TEST,&last_GL_DEPTH_TEST);
    //glGetFloatv(GL_DEPTH_CLEAR_VALUE,&last_GL_DEPTH_CLEAR_VALUE);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glfwSetKeyCallback(window, JGCI_3::key_callback);

    return true;
}
void JGCI_3::render()
{
    //glClearColor(0.0,0.0,0.0,0.0);
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Boramos la pantalla
    glMatrixMode(GL_PROJECTION);
    // Modo proyección
    glLoadIdentity();
    // Cargamos la matriz identidad
    gluPerspective(0.0,1.0,1.0,100.0);//glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    // Proyección ortográfica, dentro del cubo señalado
    glMatrixMode(GL_MODELVIEW);
    // Modo de modelado
    glBegin(GL_QUADS);
        // Dibujamos un cuadrado
        glColor3f(0.0,1.0,1.0);
        // Color para el cuadrado
        glVertex3f(-0.5,0.5,-0.5);
        // Coordenadas del primer vértice (superior-izquierda)
        glVertex3f(-0.5,-0.5,0.5);
        // Coordenadas del segundo vértice (inferior-izquierda)
        glVertex3f(0.5,-0.5,0.5);
        // Coordenadas del primer vértice (inferior-derecha)
        glVertex3f(0.5,0.5,-0.5);
        // Coordenadas del primer vértice (superior-derecha)
    glEnd();
    glBegin(GL_TRIANGLES);
        // Dibujamos un triángulo
        glColor3f(1.0,0.0,0.0);
        // Color del primer vértice: rojo
        glVertex3f(0.0,0.8,0.0);
        // Coordenadas del primer vértice
        glColor3f(0.0,1.0,0.0);
        // Color del segundo vértice: verde
        glVertex3f(-0.6,-0.2,0.0);
        // Coordenadas del segundo vértice
        glColor3f(0.0,0.0,1.0);
        // Color del tercer vértice: azúl
        glVertex3f(0.6,-0.2,0.0);
        // Coordenadas del tercer vértice
    glEnd();
    // Terminamos de dibujar
    glFlush();
    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void JGCI_3::clean()
{
    std::cout << "cleaning Cuadro y triangulo ..\n";
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    //glEnable(last_GL_DEPTH_TEST);
    //glDepthFunc(last_GL_DEPTH_FUNC);
    //glClearDepth(last_GL_DEPTH_CLEAR_VALUE);
    glPopAttrib();
}

void JGCI_3::update()
{

}

void JGCI_3::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key)
    {
        //std::cout << "Closing...\n";
        WINDOW(window,Develop)->change();
    }
}







JGCI_4::JGCI_4() : rotate_x(0),rotate_y(0)
{

}
bool JGCI_4::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glGetIntegerv(GL_DEPTH_FUNC,&last_GL_DEPTH_FUNC);
    //glGetIntegerv(GL_DEPTH_TEST,&last_GL_DEPTH_TEST);
    //glGetFloatv(GL_DEPTH_CLEAR_VALUE,&last_GL_DEPTH_CLEAR_VALUE);

    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0);

    glTranslatef(0,0,-16.0);
    glfwSetKeyCallback(window, JGCI_4::key_callback);

    return true;
}
void JGCI_4::render()
{
    //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();

  // Other Transformations
  // glTranslatef( 0.1, 0.0, 0.0 );      // Not included
  // glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included

  // Rotate when user changes rotate_x and rotate_y
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );

  // Other Transformations
  // glScalef( 2.0, 2.0, 0.0 );          // Not included

  //Multi-colored side - FRONT
  glBegin(GL_POLYGON);

  glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
  glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
  glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
  glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple

  glEnd();

  // White side - BACK
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  0.5, -0.5, 0.5 );
  glVertex3f(  0.5,  0.5, 0.5 );
  glVertex3f( -0.5,  0.5, 0.5 );
  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();

  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( 0.5, -0.5, -0.5 );
  glVertex3f( 0.5,  0.5, -0.5 );
  glVertex3f( 0.5,  0.5,  0.5 );
  glVertex3f( 0.5, -0.5,  0.5 );
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  0.5,  0.5,  0.5 );
  glVertex3f(  0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  0.5, -0.5, -0.5 );
  glVertex3f(  0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();

    glFlush();

    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void JGCI_4::clean()
{
    //std::cout << "cleaning..\n";
    //std::cout << "cleaning Cubo..\n";
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glDisable(GL_DEPTH_TEST);
    //glEnable(last_GL_DEPTH_TEST);
    //glDepthFunc(last_GL_DEPTH_FUNC);
    //glClearDepth(last_GL_DEPTH_CLEAR_VALUE);
}

void JGCI_4::update()
{
    glPopAttrib();
}


void JGCI_4::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop)->change();
    }
    else if(GLFW_KEY_UP == key && action == GLFW_PRESS)
    {
        //std::cout << "rotate_x : " << rotate_x << "\n";
        WINDOW(window,Develop)->jgci_4.rotate_x += 5;
    }
    else if(GLFW_KEY_DOWN == key && action == GLFW_PRESS)
    {
        WINDOW(window,Develop)->jgci_4.rotate_x -= 5;
    }
    else if(GLFW_KEY_RIGHT == key && action == GLFW_PRESS)
    {
        WINDOW(window,Develop)->jgci_4.rotate_y += 5;
    }
    else if(GLFW_KEY_LEFT == key && action == GLFW_PRESS)
    {
        WINDOW(window,Develop)->jgci_4.rotate_y -= 5;
    }
}







JGCI_5::JGCI_5() : tri1(verso_here::numbers::vector<float>(0,0,0), 1.0)
{

}
bool JGCI_5::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glGetIntegerv(GL_DEPTH_FUNC,&last_GL_DEPTH_FUNC);
    //glGetIntegerv(GL_DEPTH_TEST,&last_GL_DEPTH_TEST);
    //glGetFloatv(GL_DEPTH_CLEAR_VALUE,&last_GL_DEPTH_CLEAR_VALUE);

    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0);


    glfwSetKeyCallback(window, JGCI_5::key_callback);

    return true;
}
void JGCI_5::render()
{

    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Boramos la pantalla
    glMatrixMode(GL_PROJECTION);

    glRotated(0.001,1.0,0.0,1.0);
    // Modo proyección
    glLoadIdentity();
    // Cargamos la matriz identidad
    gluPerspective(0.0,1.0,1.0,100.0);//glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    // Proyección ortográfica, dentro del cubo señalado
    glMatrixMode(GL_MODELVIEW);
    // Modo de modelado
    verso_here::outline(tri1);
    // Terminamos de dibujar
    glFlush();
    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void JGCI_5::clean()
{
    //std::cout << "cleaning..\n";
    //std::cout << "cleaning Cubo..\n";
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glDisable(GL_DEPTH_TEST);
    //glEnable(last_GL_DEPTH_TEST);
    //glDepthFunc(last_GL_DEPTH_FUNC);
    //glClearDepth(last_GL_DEPTH_CLEAR_VALUE);
    glPopAttrib();
}

void JGCI_5::update()
{

}


void JGCI_5::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop)->change();
    }
}










Triangles::Triangles() : equilateral(verso_here::numbers::vector<float>(0,0,0), 1.0),rectangular(verso_here::numbers::vector<float>(0,0,0), 1.0,1.0),isosceles(verso_here::numbers::vector<float>(0,0,0), 1.0,1.0),pyramid(rectangular,verso_here::numbers::vector<float>(0,0,1.0)),action_draw(&Triangles::draw_rectangeluar)
{
}
bool Triangles::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glGetIntegerv(GL_DEPTH_FUNC,&last_GL_DEPTH_FUNC);
    //glGetIntegerv(GL_DEPTH_TEST,&last_GL_DEPTH_TEST);
    //glGetFloatv(GL_DEPTH_CLEAR_VALUE,&last_GL_DEPTH_CLEAR_VALUE);

    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0);

    glfwSetKeyCallback(window, Triangles::key_callback);
    //camera.lookAt(verso_here::Point<float,3>(3,0,0),verso_here::Point<float,3>(0,0,0));

    // Boramos la pantalla
    //glMatrixMode(GL_PROJECTION);
    //glRotated(0.001,1.0,0.0,1.0);
    //glLoadIdentity();

    //gluPerspective(0.0,1.0,1.0,100.0);//glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    //glMatrixMode(GL_MODELVIEW);
    //glTranslatef(0.1,0,0);
    //glRotatef(10,1,0,0);
    //gluLookAt(3,3,3,0,0,0,0,1,0);
    //camera.lookAt();

    verso_here::gl::clear(verso_here::colors::white);
    verso_here::gl::color(verso_here::colors::black);

    return true;
}
void Triangles::render()
{
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glRotatef(1,1,0,0);

    // Modo de modelado
    (this->*action_draw)();
    // Terminamos de dibujar
    glFlush();

    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void Triangles::clean()
{
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glDisable(GL_DEPTH_TEST);
    //glEnable(last_GL_DEPTH_TEST);
    //glDepthFunc(last_GL_DEPTH_FUNC);
    //glClearDepth(last_GL_DEPTH_CLEAR_VALUE);
    glPopAttrib();
}
void Triangles::update()
{

}


void Triangles::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop)->change();
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->triangles.camera.walking_front(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->triangles.camera.walking_back(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->triangles.camera.walking_right(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->triangles.camera.walking_left(1.5);
    }
    else if(GLFW_KEY_R == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Escaleno\n";
        WINDOW(window,Develop)->triangles.action_draw = &Triangles::draw_rectangeluar;
    }
    else if(GLFW_KEY_E == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Equlatero\n";
        WINDOW(window,Develop)->triangles.action_draw = &Triangles::draw_equilateral;
    }
    else if(GLFW_KEY_I == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->triangles.action_draw = &Triangles::draw_isosceles;
    }
    else if(GLFW_KEY_P == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->triangles.action_draw = &Triangles::draw_pyramid;
    }
}

void Triangles::draw_rectangeluar()
{
    verso_here::outline(rectangular);
}
void Triangles::draw_isosceles()
{
    verso_here::outline(isosceles);
}
void Triangles::draw_equilateral()
{
    verso_here::outline(equilateral);
}
void Triangles::draw_pyramid()
{
    verso_here::outline(pyramid);
}










Shapes::Shapes() : equilateral(verso_here::numbers::vector<float>(0,0,0), 1.0),rectangular(verso_here::numbers::vector<float>(0,0,0), 1.0,1.0),isosceles(verso_here::numbers::vector<float>(0,0,0), 1.0,1.0),pyramid(rectangular,verso_here::numbers::vector<float>(0,0,1.0)),action_draw(&Shapes::draw_rectangeluar)
{
}
bool Shapes::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glGetIntegerv(GL_DEPTH_FUNC,&last_GL_DEPTH_FUNC);
    //glGetIntegerv(GL_DEPTH_TEST,&last_GL_DEPTH_TEST);
    //glGetFloatv(GL_DEPTH_CLEAR_VALUE,&last_GL_DEPTH_CLEAR_VALUE);

    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0);

    glfwSetKeyCallback(window, Shapes::key_callback);
    //camera.lo(verso_here::Point<float,3>(3,0,0),verso_here::Point<float,3>(0,0,0));

    // Boramos la pantalla
    glMatrixMode(GL_PROJECTION);
    glRotated(0.001,1.0,0.0,1.0);
    glLoadIdentity();

    gluPerspective(0.0,1.0,1.0,100.0);//glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    //glTranslatef(0.1,0,0);
    //glRotatef(10,1,0,0);
    //gluLookAt(3,3,3,0,0,0,0,1,0);
    //camera.lookAt();

    verso_here::numbers::vector<float> vecO(0,0,0);
    rectangle.create(vecO, 1.0);
    circle.create(vecO, 1.0);

    return true;
}
void Shapes::render()
{
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glRotatef(1,1,0,0);

    // Modo de modelado
    (this->*action_draw)();
    // Terminamos de dibujar

    glFlush();

    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void Shapes::clean()
{
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glDisable(GL_DEPTH_TEST);
    //glEnable(last_GL_DEPTH_TEST);
    //glDepthFunc(last_GL_DEPTH_FUNC);
    //glClearDepth(last_GL_DEPTH_CLEAR_VALUE);
    glPopAttrib();
}
void Shapes::update()
{
}


void Shapes::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop)->change();
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->shapes.camera.walking_front(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->shapes.camera.walking_back(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->shapes.camera.walking_right(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->shapes.camera.walking_left(1.5);
    }
    else if(GLFW_KEY_R == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Escaleno\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_rectangeluar;
    }
    else if(GLFW_KEY_E == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Equlatero\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_equilateral;
    }
    else if(GLFW_KEY_I == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_isosceles;
    }
    else if(GLFW_KEY_P == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_pyramid;
    }
    else if(GLFW_KEY_S == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_rectangle;
    }
    else if(GLFW_KEY_C == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_circle;
    }
    else if(GLFW_KEY_D == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_disk;
    }
    else if(GLFW_KEY_T == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_cilinder;
    }
    else if(GLFW_KEY_H == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->shapes.action_draw = &Shapes::draw_sphere;
    }
}

void Shapes::draw_rectangeluar()
{
    verso_here::core::array<verso_here::RGBA<unsigned char>,3> colors_list;
    colors_list[0] = verso_here::colors::red;
    colors_list[1] = verso_here::colors::green;
    colors_list[2] = verso_here::colors::blue;
    //glColor3f(1.0,1.0,1.0);
    verso_here::outline(rectangular,colors_list);
}
void Shapes::draw_isosceles()
{
    verso_here::outline(isosceles);
}
void Shapes::draw_equilateral()
{
    verso_here::outline(equilateral);
}
void Shapes::draw_pyramid()
{
    verso_here::outline(pyramid);
}
void Shapes::draw_rectangle()
{
    verso_here::outline(rectangle);
}
void Shapes::draw_circle()
{
    verso_here::outline(circle,verso_here::colors::red);
}
void Shapes::draw_disk()
{
    disk.create(0.2,1,20,10,0,270);
}
void Shapes::draw_cilinder()
{
    cilinder.create(0.2,0.2,0.8,100,100);
}
void Shapes::draw_sphere()
{
    sphere.create(0.2,100,100);
}








struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

GLint attribute_coord;
GLint uniform_tex;
GLint uniform_color;
GLuint vbo;
FT_Face face;
FT_Library ft;
const char *fontfilename;


/**
 * Render text using the currently loaded font and currently set font size.
 * Rendering starts at coordinates (x, y), z is always 0.
 * The pixel coordinates that the FreeType2 library uses are scaled by (sx, sy).
 */
void render_text(const char *text, float x, float y, float sx, float sy) {
	const char *p;
	FT_GlyphSlot g = face->glyph;

	/* Create a texture that will be used to hold one "glyph" */
	GLuint tex;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(uniform_tex, 0);

	/* We require 1 byte alignment when uploading texture data */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* Clamping to edges is important to prevent artifacts when scaling */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/* Linear filtering usually looks best for text */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Set up the VBO for our vertex data */
	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

	/* Loop through all characters */
	for (p = text; *p; p++) {
		/* Try to load and render the character */
		if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;

		/* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

		/* Calculate the vertex and texture coordinates */
		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		point box[4] = {
			{x2, -y2, 0, 0},
			{x2 + w, -y2, 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};

		/* Draw the character on the screen */
		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		/* Advance the cursor to the start of the next character */
		x += (g->advance.x >> 6) * sx;
		y += (g->advance.y >> 6) * sy;
	}

	glDisableVertexAttribArray(attribute_coord);
	glDeleteTextures(1, &tex);
}



Design::Design() : camera_transform('T')
{
}
bool Design::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glGetIntegerv(GL_DEPTH_FUNC,&last_GL_DEPTH_FUNC);
    //glGetIntegerv(GL_DEPTH_TEST,&last_GL_DEPTH_TEST);
    //glGetFloatv(GL_DEPTH_CLEAR_VALUE,&last_GL_DEPTH_CLEAR_VALUE);
    action_draw = NULL;

    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0);
    glClearColor(0, 0, 0, 1);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window, Design::key_callback);
    camera.lookAt(verso_here::numbers::vector<float,3>(0,1,1),verso_here::numbers::vector<float,3>(0,0,0));
    triangle = verso_here::numbers::Scalene<float>(verso_here::numbers::vector<float,3>(0,0,0),1,1.5);
    //projection = camera.projection();

    glGenTextures(1, &triangle_texture);
    glBindTexture(GL_TEXTURE_2D, triangle_texture);
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("tests/verso/resources/textures/brickwall.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //
    /* Initialize the FreeType2 library */
	if (FT_Init_FreeType(&ft)) {
		fprintf(stderr, "Could not init freetype library\n");
		return 0;
	}

	/* Load a font */
	fontfilename = "tests/verso/resources/fonts/Antonio-Regular.ttf";
	if (FT_New_Face(ft, fontfilename, 0, &face)) {
		fprintf(stderr, "Could not open font %s\n", fontfilename);
		return 0;
	}

    //shader_text.build(std::filesystem::path("tests/verso/resources/shaders/mpv.vs"),std::filesystem::path("tests/verso/resources/shaders/mpv.fs"));
    perspective.build(std::filesystem::path("tests/verso/resources/shaders/perspective.vs"),std::filesystem::path("tests/verso/resources/shaders/perspective.fs"));
    shader_text.build(std::filesystem::path("tests/verso/resources/shaders/text.vs"),std::filesystem::path("tests/verso/resources/shaders/text.fs"));

    attribute_coord = verso_here::gl::get_attrib(shader_text, "coord");
	uniform_tex = verso_here::gl::get_uniform(shader_text, "tex");
	uniform_color = verso_here::gl::get_uniform(shader_text, "color");

	if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
		return 0;

	// Create the vertex buffer object
	glGenBuffers(1, &vbo);


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	View       = glm::lookAt(
								glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	//MVP        = Projection * View * Model;

	MatrixID = glGetUniformLocation(shader_text, "MVP");

    return true;
}
void Design::render()
{
    MVP        = Projection * View * Model;
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glLoadIdentity();
    //gluLookAt(0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    camera.lookAt();
    //glMatrixMode (GL_PROJECTION);
    //glLoadIdentity ();
    //glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    camera.perspective(90,WINDOW(window,Develop)->aspect(),0.5,30);
    //camera.orthogonal(0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 20.0f);
    glMatrixMode (GL_MODELVIEW);

    plane.create();

    if(action_draw)(this->*action_draw)();

    glFlush();
    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void Design::clean()
{
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glDisable(GL_DEPTH_TEST);
    //glEnable(last_GL_DEPTH_TEST);
    //glDepthFunc(last_GL_DEPTH_FUNC);
    //glClearDepth(last_GL_DEPTH_CLEAR_VALUE);
    glPopAttrib();
}
void Design::update()
{

}


void Design::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop)->change();
    }
    else if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->design.camera_transform = 'T';
    }
    else if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        WINDOW(window,Develop)->design.camera_transform = 'R';
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if(WINDOW(window,Develop)->design.camera_transform == 'T') WINDOW(window,Develop)->design.camera.walking_front(1.5);
        else if(WINDOW(window,Develop)->design.camera_transform == 'R') WINDOW(window,Develop)->design.camera.walking_front(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if(WINDOW(window,Develop)->design.camera_transform == 'T') WINDOW(window,Develop)->design.camera.walking_back(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if(WINDOW(window,Develop)->design.camera_transform == 'T') WINDOW(window,Develop)->design.camera.walking_right(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if(WINDOW(window,Develop)->design.camera_transform == 'T') WINDOW(window,Develop)->design.camera.walking_left(1.5);
    }
    else if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        if(WINDOW(window,Develop)->design.camera_transform == 'T') WINDOW(window,Develop)->design.camera.walking_up(1.5);
    }
    else if(GLFW_KEY_3 == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->design.action_draw = &Design::draw_triangle;
    }
    else if(GLFW_KEY_1 == key && action == GLFW_RELEASE)
    {
        //std::cout << "Cambiado tirnago : Isoceles\n";
        WINDOW(window,Develop)->design.action_draw = &Design::draw_text;
    }


}

 void Design::draw_triangle()
 {
    verso_here::polygon(triangle,triangle_texture);
 }
 void Design::draw_text()
 {
	shader_text.use();
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	//verso_here::polygon(triangle,triangle_texture);
 }







Shaders::Shaders()
{
}
bool Shaders::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glfwSetKeyCallback(window, Shaders::key_callback);


    return true;
}
void Shaders::clean()
{

    glPopAttrib();
}
void Shaders::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop)->change();
    }

}
void Shaders::update()
{
}
void Shaders::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}







float Lighting::vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
Lighting::Lighting() : lightPos(1.2f, 1.0f, 2.0f)
{
}
bool Lighting::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glfwSetKeyCallback(window, Lighting::key_callback);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    lightingShader.build(std::filesystem::path("tests/verso/resources/shaders/lighting/colors.fs"), std::filesystem::path("tests/verso/resources/shaders/lighting/colors.fs"));
    lightCubeShader.build(std::filesystem::path("tests/verso/resources/shaders/lighting/light_cube.vs"), std::filesystem::path("tests/verso/resources/shaders/lighting/light_cube.fs"));

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    //verso_here::gl::color(verso_here::colors::white);
    //verso_here::gl::clear(verso_here::colors::red);
    //camera.lookAt(verso_here::numbers::vector<float,3>(0,1,3),verso_here::numbers::vector<float,3>(0,0,0));

    return true;
}
void Lighting::clean()
{

    glPopAttrib();
}
void Lighting::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop)->change();
    }

}
void Lighting::update()
{
}
void Lighting::render()
{
    // per-frame time logic
    // --------------------
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // render
        // ------
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);

        // view/projection transformations
        glm::mat4 projection = verso_here::v2::perspective(glm::radians(45.0f), WINDOW(window,Develop)->aspect(), 0.1f, 100.0f);
        glm::mat4 view = verso_here::v2::lookAt(glm::vec3(0,0,4),glm::vec3(0,0,0),glm::vec3(0,1,0));
        lightingShader.set("projection", projection);
        lightingShader.set("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.set("model", model);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.set("projection", projection);
        lightCubeShader.set("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.set("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
