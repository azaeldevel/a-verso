
#ifndef OCTETOS_AVERSO_V0_GL_HH
#define OCTETOS_AVERSO_V0_GL_HH

#include "colors.hh"


namespace oct::verso::v0::gl
{

    void translate(const numbers::vector<float,3,float>&);
    void translate(const numbers::vector<double,3,double>&);

    void color(const Color<float,3>&);
    void color(const Color<float,4>&);
    void color(const Color<unsigned char,3>&);
    void color(const Color<unsigned char,4>&);


    void clear(const Color<unsigned char,3>&);
    void clear(const Color<unsigned char,4>&);


    GLint get_attrib(GLuint program, const char *name);
    GLint get_uniform(GLuint program, const char *name);
}

#endif // OCTETOS_AVERSO_SHAPES_HH
