
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
    void active(const Color<unsigned char,3>& color)
    {
        glColor3b(color[0],color[1],color[2]);
    }
    void active(const Color<unsigned char,4>& color)
    {
        glColor4b(color[0],color[1],color[2],color[3]);
    }


    void clear(const Color<unsigned char,3>& color)
    {
        glClearColor(color[0],color[1],color[2],1);
    }
    void clear(const Color<unsigned char,4>& color)
    {
        glClearColor(color[0],color[1],color[2],color[3]);
    }
}


