#ifndef OCTETOS_AVERSO_ARCHITECT_HH
#define OCTETOS_AVERSO_ARCHITECT_HH

#include "objects.hh"
#include "colors.hh"

namespace oct::verso::v0::architect
{

    template<numbers::number C = float> class Architect : public gl::Humanoid<C>
    {
    private:
        typedef gl::Humanoid<C> BASE;
        gl::Sphere<C> head;
        gl::Sphere<C> mark;
    public:
        Architect() = default;
        /**
        *\brief Contructor
        *\param tall Altura del sujeto
        */
        Architect(C tall) : head(0),mark(0)
        {

        }


        void create(C tall)
        {
            BASE::pivoting(tall);
            colors::white.active();
            gl::translate(BASE::cusp);
            head.create(BASE::unit,30,30);

            gl::translate(BASE::shoulder_left);
            mark.create(0.01,10,10);

            gl::translate(BASE::shoulder_right);
            mark.create(0.01,10,10);

            gl::translate(BASE::center);

            gl::translate(BASE::pelvis);
            mark.create(BASE::unit * 1.5,10,10);

            gl::translate(BASE::knee_left);
            mark.create(0.01,10,10);

            gl::translate(BASE::ankle_left);
            mark.create(0.01,10,10);

            gl::translate(BASE::center);

            //gl::translate(BASE::knee_right);
            //mark.create(0.01,10,10);

        }


    };

}

#endif // OCTETOS_AVERSO_SHAPES_HH
