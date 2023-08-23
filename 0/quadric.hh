
#ifndef OCTETOS_AVERSO_QUADRIC_HH
#define OCTETOS_AVERSO_QUADRIC_HH

#include <GL/glu.h>
#include <GL/gl.h>

#include "shapes.hh"

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

namespace oct::verso::v0::gl
{

    /**
    *\brief Clase base para objetos Quadric
    */
    template<numbers::number C>
    class Quadric
    {
    private:

    protected:
        GLUquadric* quadric;

    public:
        Quadric() : quadric(gluNewQuadric())
        {
        }
        ~Quadric()
        {
            gluDeleteQuadric(quadric);
        }

        operator GLUquadric*()
        {
            return quadric;
        }
        operator const GLUquadric*() const
        {
            return quadric;
        }

    };

    /**
    *\brief Crea un Disk OpenGL
    */
    template<numbers::number C = GLdouble>
    class Disk : public Quadric<C>
    {
    private:


    public:
        typedef Quadric<C> BASE;

    public:
        Disk() = default;
        Disk(C inner, C outer,GLint slices,GLint loops)
        {
            create(inner, outer, slices, loops);
        }

        void create(C inner, C outer,GLint slices,GLint loops)
        {
            gluDisk(BASE::quadric, inner, outer, slices, loops);
        }

        void create(C inner, C outer,GLint slices,GLint loops,numbers::Degree<GLdouble> degree,numbers::Degree<GLdouble> sweep)
        {
            gluPartialDisk(BASE::quadric, inner, outer, slices, loops,degree,sweep);
        }



    };
}

#endif // OCTETOS_AVERSO_SHAPES_HH
