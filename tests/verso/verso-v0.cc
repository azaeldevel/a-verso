#include <fstream>
#include <chrono>
#include <thread>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include "verso-v0.hh"







bool Develop::initialize()
{

    return true;
}

void Develop::handle()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(window) != 0 )
    {
        running = false;
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

void Develop::update()
{

}

void Develop::render()
{
    handle();
    update();
    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rendering();

    glfwSwapBuffers(window);
    glfwPollEvents();

}

void Develop::rendering()
{


}

void Develop::clean()
{

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}



























bool Light::initialize()
{
    shader_lighting.build("tests/light/1.colors.vs", "tests/light/1.colors.fs");
    shader_light_cube.build("tests/light/1.light_cube.vs", "tests/light/1.light_cube.fs");

    float vertices[] = {
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
    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &vao_cube);
    glGenBuffers(1, &vbo_cube);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(vao_cube);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &vao_cube_light);
    glBindVertexArray(vao_cube_light);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    light_position = glm::vec3(1.2f, 1.0f, 2.0f);
    camera.set(glm::vec3(4,3,3),glm::vec3(0,0,0));
    aspect = 4/3;

    return true;
}
void Light::render()
{
    shader_lighting.use();
    shader_lighting.set("objectColor", 1.0f, 0.5f, 0.31f);
    shader_lighting.set("lightColor",  1.0f, 1.0f, 1.0f);

    // view/projection transformations
    projection = glm::perspective(glm::radians(camera.zoom()), aspect, 0.1f, 100.0f);
    view = camera;
    shader_lighting.set("projection", projection);
    shader_lighting.set("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    shader_lighting.set("model", model);

    // render the cube
    glBindVertexArray(vao_cube);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    shader_light_cube.use();
    shader_light_cube.set("projection", projection);
    shader_light_cube.set("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, light_position);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    shader_light_cube.set("model", model);

    glBindVertexArray(vao_cube_light);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Light::clean()
{

    // Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void Light::update()
{
    float current_frame = static_cast<float>(glfwGetTime());
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
}
void Light::handleEvents()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(window) != 0 )
    {
        running = false;
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
