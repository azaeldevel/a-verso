
#ifndef OCTETOS_AVERSO_OBJECTS_HH
#define OCTETOS_AVERSO_OBJECTS_HH

#include "quadric.hh"

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
        numbers::vector<C,3> cusp,head,neck_top,neck_base,shoulder_left,shoulder_right;
        C head_size;

        void pivoting(C tall)
        {
            BASE::tall = tall;
            //
            C unit = BASE::tall/9.0f;
            C offset = 0;

            //
            cusp.x() = 0;
            cusp.y() = BASE::tall;
            cusp.z() = 0;

            //
            head = cusp;
            head.y() -= unit/C(2.0);

            //
            neck_base = cusp;
            neck_base.y() -= 1.5 * unit;

            //



            //
            shoulder_left = neck_base;
            shoulder_right = neck_base;
            shoulder_left.x() -= 0.8 * unit;
            shoulder_right.x() -= 0.8 * unit;

            //
            //neck_base = neck_top;
            //neck_base.y() -= BASE::tall - unit;

            //
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
            O.create(1.0f/64.0f,10,10);
        }

    };

}

#endif // OCTETOS_AVERSO_SHAPES_HH
