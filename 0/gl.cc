
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gl.hh"

namespace oct::verso::v0::gl
{
    void translate(const numbers::vector<float,3,float>& vec)
    {
        glTranslatef(vec.x(),vec.y(),vec.z());
    }
    void translate(const numbers::vector<double,3,double>& vec)
    {
        glTranslatef(vec.x(),vec.y(),vec.z());
    }


    void color(const Color<unsigned char,3>& color)
    {
        glColor3ub(color[0],color[1],color[2]);
    }
    void color(const Color<unsigned char,4>& color)
    {
        glColor4ub(color[0],color[1],color[2],color[3]);
    }


    void clear(const Color<unsigned char,3>& color)
    {
        glClearColor(color[0],color[1],color[2],1);
    }
    void clear(const Color<unsigned char,4>& color)
    {
        glClearColor(color[0],color[1],color[2],color[3]);
    }

    GLint get_attrib(GLuint program, const char *name)
    {
        GLint attribute = glGetAttribLocation(program, name);
        if(attribute == -1)
            fprintf(stderr, "Could not bind attribute %s\n", name);
        return attribute;
    }

    GLint get_uniform(GLuint program, const char *name)
    {
        GLint uniform = glGetUniformLocation(program, name);
        if(uniform == -1)
            fprintf(stderr, "Could not bind uniform %s\n", name);
        return uniform;
    }


}


