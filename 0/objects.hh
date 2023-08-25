
#ifndef OCTETOS_AVERSO_OBJECTS_HH
#define OCTETOS_AVERSO_OBJECTS_HH

#include "quadric.hh"

namespace oct::verso::v0::gl
{

    /**
    *\brief Cualquier ente que tenga un representacion visual
    */
    class Object : public core::Entity
    {

    };

    /**
    *\brief Homanoide
    */
    class Humanoid : public Object
    {
    private:
        void pivoting();

    protected:
        float tall;
        float pivots[6];//pivotes corporales

    public:
        Humanoid() = default;
        /**
        *\brief Contructor
        *\param tall Altura del sujeto
        */
        Humanoid(float tall);
    };

    /**
    *\brief Manipulable en tiempo de ejecucion(clase abstracta)
    */
    class Interactive : public Object
    {

    };





    template<numbers::number N>
    class Plane : public Object
    {

    private:
        N width,high;
        //size_t units;
        Sphere<GLdouble> O;


    public:
        Plane() : width(50),high(50)
        {
        }
        Plane(N size) : width(size),high(size)
        {
        }
        Plane(N w,N h) : width(w),high(h)
        {
        }

        void create()
        {
            N width_media = width / N(2);
            N high_media = high / N(2);

            glLineWidth(1);
            glBegin(GL_LINES);
                colors::coordenade.active();
                for(int i = -high_media; i < high_media; i++)
                {
                    glVertex3f(-width_media,0,i);
                    glVertex3f(width_media,0,i);
                }
                glVertex3f((int)-width_media,0,(int)width_media);
                glVertex3f((int)width_media,0,(int)width_media);
                for(int i = -width_media; i < width_media; i++)
                {
                    glVertex3f(i,0,-width_media);
                    glVertex3f(i,0,width_media);
                }
                glVertex3f(width_media,0,-width_media);
                glVertex3f(width_media,0,width_media);
            glEnd();

            glLineWidth(2.5);
            glBegin(GL_LINES);
                colors::red.active();
                glVertex3f(-0.5,0,0);
                glVertex3f(0.5,0,0);
                colors::green.active();
                glVertex3f(0,0,-0.5);
                glVertex3f(0,0,0.5);
            glEnd();

            colors::white.active();
            O.create(1.0f/16.0f,10,10);
        }

    };

}

#endif // OCTETOS_AVERSO_SHAPES_HH
