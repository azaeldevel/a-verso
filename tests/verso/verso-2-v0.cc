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
#include <a-verso/0/draw.hh>
#include <a-verso/0/gl.hh>
#include "stb/stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H








Develop3::Develop3() : verso_here::gl::Verso(3,3)
{
}
void Develop3::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "void Develop2::key_callback(GLFWwindow*,int, int,int,int)()\n";
    if(GLFW_KEY_ESCAPE == key && action == GLFW_PRESS)
    {
        //std::cout << "Closing...\n";
        WINDOW(window,Develop3)->stop();
    }
    else if(GLFW_KEY_1 == key && action == GLFW_PRESS)
    {
        //std::cout << "Cambieando de escenario..\n";
        WINDOW(window,Develop3)->change(&WINDOW(window,Develop3)->shaders);
    }

}
bool Develop3::active()
{
    //std::cout << "bool Develop2::active()\n";
    glfwSetKeyCallback(window, Develop3::key_callback);

    return true;
}
void Develop3::render()
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
void Develop3::clean()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}









Shapes3::Shapes3()
{
}
bool Shapes3::active()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0);

    glfwSetKeyCallback(window, Shapes3::key_callback);
    verso::gl::clear(verso::colors::black);
    verso::numbers::vector<float,3> O(0);
    triangle = verso::numbers::Scalene<float>(O,1.5,1.5);
    rectangle.create(O,0.75,0.5);
    //rectangle.printLn(std::cout);
    std::filesystem::path shader_dir = "tests/verso/Shaders";
    shader_triangle.build(shader_dir/"shapes.vs",shader_dir/"shapes.fs");
    shader_shape.build(shader_dir/"shapes.vs",shader_dir/"shapes.fs");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo_triangle);
    glGenBuffers(1, &vbo_rectangle);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_rectangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    action_draw = NULL;

    return true;
}
void Shapes3::render()
{
    // Color de fondo: negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(action_draw)(this->*action_draw)();

    // Forzamos el dibujado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void Shapes3::clean()
{

    glPopAttrib();
}
void Shapes3::update()
{
}
void Shapes3::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(GLFW_KEY_ESCAPE == key && action == GLFW_RELEASE)
    {
        //std::cout << "Closing JGCI_4...\n";
        WINDOW(window,Develop3)->change();
    }
    else if(GLFW_KEY_1 == key && action == GLFW_PRESS)
    {
        //std::cout << "Activando trinagulo\n";
        WINDOW(window,Develop3)->shaders.action_draw = &Shapes3::draw_triangle;
    }
    else if(GLFW_KEY_2 == key && action == GLFW_PRESS)
    {
        //std::cout << "Activando plano\n";
        WINDOW(window,Develop3)->shaders.action_draw = &Shapes3::draw_plane;
    }
}
void Shapes3::draw_triangle()
{
    glEnableVertexAttribArray(0);
    // draw our first triangle
    shader_triangle.use();
    glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
void Shapes3::draw_plane()
{
    glEnableVertexAttribArray(0);
    // draw our first triangle
    shader_triangle.use();
    glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 1, 3);
    glDisableVertexAttribArray(0);
}


