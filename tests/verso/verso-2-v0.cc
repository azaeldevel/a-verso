#include <fstream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <map>

#ifdef __linux__
    #ifdef LINUX_ARCH
        #define STB_IMAGE_IMPLEMENTATION
    #elif defined LINUX_DEBIAN

    #elif defined LINUX_GENTOO

    #else
        //#error "Sistema operativo desconocido."
    #endif
#elif defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #error "Sistema operativo desconocido."
#endif

#include "verso-2-v0.hh"
#include "../../0/draw.hh"
#include "../../0/gl.hh"
//#include "stb/stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H


Develop::Develop() : verso_here::gl::Verso(3,3)
{
}
void Develop::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop2::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_PRESS)
    {
        //std::cout << "Closing...\n";
        WINDOW(window,Develop)->stop();
    }
    else if(GLFW_KEY_1 == key && action == GLFW_PRESS)
    {
        std::cout << "Cambieando de escenario 1..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->shaders);
    }
    else if(GLFW_KEY_2 == key && action == GLFW_PRESS)
    {
        std::cout << "Cambieando de escenario 2..\n";
        WINDOW(window,Develop)->change(&WINDOW(window,Develop)->triangles);
    }

}
bool Develop::active()
{
    //std::cout << "bool Develop2::active()\n";
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









Shapes::Shapes()
{
}
bool Shapes::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0);

    glfwSetKeyCallback(window, Shapes::key_callback);
    verso::gl::clear(verso::colors::black);
    verso::numbers::vector<float,3> O(0);
    triangle = verso::numbers::Equilateral<float>(O,0.5f);
    rectangle.create(O,0.75f,0.75f);
    //rectangle.printLn(std::cout);
    //std::cout << "\n";
    //triangle.printLn(std::cout);
    std::filesystem::path shader_dir = "tests/verso/Shaders";
    shader_triangle.build(shader_dir/"shapes.vs",shader_dir/"shapes.fs");
    shader_shape.build(shader_dir/"shapes.vs",shader_dir/"shapes.fs");

    glGenVertexArrays(1, &vao_triangle);
    glBindVertexArray(vao_triangle);
    glGenBuffers(1, &vbo_triangle);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    //glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenVertexArrays(1, &vao_rectangle);
    glBindVertexArray(vao_rectangle);
    glGenBuffers(1, &vbo_rectangle);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_rectangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    action_draw = NULL;

    return true;
}
void Shapes::render()
{
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(action_draw)(this->*action_draw)();

    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void Shapes::clean()
{

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
    else if(GLFW_KEY_1 == key && action == GLFW_PRESS)
    {
        //std::cout << "Activando trinagulo\n";
        WINDOW(window,Develop)->shaders.action_draw = &Shapes::draw_triangle;
    }
    else if(GLFW_KEY_2 == key && action == GLFW_PRESS)
    {
        //std::cout << "Activando plano\n";
        WINDOW(window,Develop)->shaders.action_draw = &Shapes::draw_plane;
    }
}
void Shapes::draw_triangle()
{
    glEnableVertexAttribArray(0);
    // draw our first triangle
    glBindVertexArray(vao_triangle);
    shader_triangle.use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
void Shapes::draw_plane()
{
    glEnableVertexAttribArray(0);
    // draw our first triangle
    glBindVertexArray(vao_rectangle);
    shader_triangle.use();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}






Triangles::Triangles()
{
}
bool Triangles::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0);

    glfwSetKeyCallback(window, Triangles::key_callback);
    verso::gl::clear(verso::colors::black);
    verso::numbers::vector<float,3> O(0);
    triangle = verso::numbers::Equilateral<float>(O,0.5f);
    //rectangle.create(O,0.75f,0.75f);
    //rectangle.printLn(std::cout);
    //std::cout << "\n";
    triangle.printLn(std::cout);
    std::filesystem::path shader_dir = "tests/verso/Shaders";
    shader_triangle.build(shader_dir/"shapes.vs",shader_dir/"shapes.fs");

    glGenVertexArrays(1, &vao_triangle);
    glBindVertexArray(vao_triangle);
    glGenBuffers(1, &vbo_triangle);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STREAM_DRAW);
    //glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    action_draw = NULL;

    return true;
}
void Triangles::render()
{
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(action_draw)(this->*action_draw)();

    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void Triangles::clean()
{
    glPopAttrib();
}
void Triangles::update()
{
}
void Triangles::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop)->change();
    }
    else if(GLFW_KEY_1 == key && action == GLFW_PRESS)
    {
        //std::cout << "Activando trinagulo\n";
        WINDOW(window,Develop)->triangles.action_draw = &Triangles::draw_triangle;
    }
    else if(GLFW_KEY_2 == key && action == GLFW_PRESS)
    {
        //std::cout << "Activando trinagulo\n";
        WINDOW(window,Develop)->triangles.action_draw = &Triangles::draw_running;
    }
}
void Triangles::draw_triangle()
{
    glEnableVertexAttribArray(0);
    // draw our first triangle
    glBindVertexArray(vao_triangle);
    shader_triangle.use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
void Triangles::draw_running()
{
    triangle.translate(0.01);
    //triangle.printLn(std::cout);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
    // draw our first triangle
    glBindVertexArray(vao_triangle);
    shader_triangle.use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

