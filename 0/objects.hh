
#ifndef OCTETOS_AVERSO_OBJECTS_HH
#define OCTETOS_AVERSO_OBJECTS_HH

#include "quadric.hh"
#include "gl.hh"
#include "colors.hh"

namespace oct::verso::v0::gl
{


    /**
    *\brief Cualquier ente que tenga un representacion visual
    */
    template<numbers::number C = float> class Object : public core::Entity
    {

    };

    /**
    *\brief Homanoide
    */
    template<numbers::number C = float> class Animal : public Object<C>
    {
    private:
        typedef Object<C> BASE;

    protected:
        float tall;

    public:
        Animal() = default;

        /**
        *\brief Contructor
        *\param t Altura del sujeto
        */
        Animal(float t) : tall(t)
        {
        }
    };

    /**
    *\brief Homanoide
    */
    template<numbers::number C = float> class Biped : public Animal<C>
    {
    private:
        typedef Animal<C> BASE;

    protected:

    public:
        Biped() = default;
        /**
        *\brief Contructor
        *\param tall Altura del sujeto
        */
        Biped(float tall) : BASE(tall)
        {
        }
    };

    /**
    *\brief Homanoide
    */
    template<numbers::number C = float> class Quadruped : public Object<C>
    {
    private:

    protected:
        float tall;

    public:
        Quadruped() = default;
        /**
        *\brief Contructor
        *\param tall Altura del sujeto
        */
        Quadruped(float tall);
    };

    /**
    *\brief Homanoide
    */
    template<numbers::number C = float> class Humanoid : public Biped<C>
    {
    private:
        typedef Biped<C> BASE;

    protected:
        numbers::vector<C,3> cusp,center,head,neck_top,neck_base,shoulder_left,shoulder_right,pelvis,knee_left,knee_right,ankle_left,ankle_right;
        C head_size;
        C unit;
        //numbers::vector<C,3> pivot_shoulder,pivot_pelvis;
        enum class Pivots
        {
            cusp,

        };

        void pivoting(C tall)
        {
            BASE::tall = tall;
            //
            unit = BASE::tall/9.0f;
            //C offset = 0;

            //
            cusp = 0;
            cusp.y() = BASE::tall;

            //
            head = 0;
            head.y() -= unit;

            //
            neck_base = 0;
            neck_base.y() -= 1.5 * unit;

            //
            shoulder_left = neck_base;
            shoulder_right = 0;
            shoulder_left.x() += 0.8 * unit;
            shoulder_right.x() -= 0.8 * 2 * unit;
            center = 0;
            center.x() = C(0.8) * unit;

            //
            pelvis = 0;
            pelvis.y() -= unit * C(2.5);

            //
            knee_left = 0;
            knee_left.y() -= unit * C(2);
            knee_left.x() -= unit * C(0.8);

            ankle_left = 0;
            ankle_left.y() -= unit * C(2);

            /*center = 0;
            center.x() = C(0.8) * unit;
            center.y() = C(-4) * unit;*/


            /*knee_right = 0;
            knee_right.y() -= unit * C(2);
            knee_right.x() += unit * C(0.8);*/
        }

    public:
        Humanoid() = default;
        /**
        *\brief Contructor
        *\param tall Altura del sujeto
        */
        Humanoid(float tall) : BASE(tall),head_size(0.20)
        {
        }
    };

    /**
    *\brief Manipulable en tiempo de ejecucion(clase abstracta)
    */
    template<numbers::number C = float> class Interactive : public Object<C>
    {

    };





    template<numbers::number N>
    class Plane : public Object<N>
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
                gl::color(colors::coordenade);
                for(int i = -high_media; i < high_media; i++)
                {
                    if(i == 0) continue;
                    glVertex3f(-width_media,0,i);
                    glVertex3f(width_media,0,i);
                }
                glVertex3f((int)-width_media,0,(int)width_media);
                glVertex3f((int)width_media,0,(int)width_media);
                for(int i = -width_media; i < width_media; i++)
                {
                    if(i == 0) continue;
                    glVertex3f(i,0,-width_media);
                    glVertex3f(i,0,width_media);
                }
                glVertex3f(width_media,0,-width_media);
                glVertex3f(width_media,0,width_media);
            glEnd();

            glLineWidth(2.5);
            glBegin(GL_LINES);
                gl::color(colors::red);
                glVertex3f(-width_media,0,0);
                glVertex3f(width_media,0,0);
                gl::color(colors::green);
                glVertex3f(0,0,-width_media);
                glVertex3f(0,0,width_media);
            glEnd();

            gl::color(colors::white);
            O.create(1.0f/64.0f,10,10);
        }

    };

}

#endif
