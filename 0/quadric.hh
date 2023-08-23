
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
        Disk(const C& inner,const C& outer,GLint slices,GLint loops)
        {
            create(inner, outer, slices, loops);
        }

        void create(const C& inner,const C& outer,GLint slices,GLint loops)
        {
            gluDisk(BASE::quadric, inner, outer, slices, loops);
        }

        void create(const C& inner,const C& outer,GLint slices,GLint loops,numbers::Degree<C> degree,numbers::Degree<C> sweep)
        {
            gluPartialDisk(BASE::quadric, inner, outer, slices, loops,degree,sweep);
        }



    };


    /**
    *\brief Crea un Cilindro OpenGL
    */
    template<numbers::number C = GLdouble>
    class Cilinder : public Quadric<C>
    {
    private:


    public:
        typedef Quadric<C> BASE;

    public:
        Cilinder() = default;
        Cilinder(const C& base, const C& top,const C& height, GLint slices,GLint stacks)
        {
            create(base, top,height, slices, stacks);
        }

        void create(const C& base, const C& top,const C& height, GLint slices,GLint stacks)
        {
            gluCylinder(BASE::quadric, base, top,height, slices, stacks);
        }




    };




    /**
    *\brief Crea un Cilindro OpenGL
    */
    template<numbers::number C = GLdouble>
    class Sphere : public Quadric<C>
    {
    private:


    public:
        typedef Quadric<C> BASE;

    public:
        Sphere() = default;
        Sphere(const C& radio, GLint slices,GLint stacks)
        {
            create(radio, slices, stacks);
        }

        void create(const C& radio, GLint slices,GLint stacks)
        {
            gluSphere(BASE::quadric, radio, slices, stacks);
        }




    };


    /**
    *\brief Crea un Cilindro OpenGL
    */
    template<numbers::number C = GLdouble>
    class Circle : public Disk<C>
    {
    private:


    public:
        typedef Disk<C> BASE;

    public:
        Circle() = default;
        Circle(const C& radius,GLint slices,GLint loops) : BASE(radius,radius,slices,loops)
        {
            create(radius, slices, loops);
        }

        void create(const C& radius,GLint slices,GLint loops)
        {
            BASE::create(radius, radius, slices, loops);
        }


    };
}

#endif // OCTETOS_AVERSO_SHAPES_HH
