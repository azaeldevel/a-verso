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
        Architect(C tall)
        {

        }


        void create(C tall)
        {
            BASE::pivoting(tall);
            colors::white.active();
            //glColor4i(100,0,0,255);
            //glLoadIdentity();
            glTranslatef(0,BASE::cusp.y(),0);
            head.create(0.20,30,30);

            //glLoadIdentity();
            glTranslatef(0.1,-0.5,0);
            mark.create(0.1,10,10);
        }


    };

}

#endif // OCTETOS_AVERSO_SHAPES_HH
