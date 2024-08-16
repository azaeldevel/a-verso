#ifndef OCTETOS_VERSO_V1_SCENARY_HH

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <map>
#include <string>

#include "../scenary.hh"


namespace oct::verso::v1
{

    typedef int HSCENARY;
    typedef void (*DISPLAY)();
    typedef void (*RESHAPE)(GLint, GLint);

    struct Scenary : public IScenary
    {
        Scenary();
        Scenary(DISPLAY,RESHAPE);
        constexpr Scenary(const std::initializer_list<real>& l) : IScenary(l)
        {
        }
        constexpr Scenary(const numbers::vector<real>& p) : IScenary(p)
        {
        }

        DISPLAY display;
        RESHAPE reshape;

        /**
        *\brief Activar nueva escena
        */
        virtual void active();
    };

    extern Scenary* actual;

    struct Body : public Scenary
    {
        Body() = default;
        constexpr Body(const std::initializer_list<real>& l) : Scenary(l)
        {
        }
        constexpr Body(const numbers::vector<real>& p) : Scenary(p)
        {
        }


    };

    struct Sun : public Body
    {
        Sun();
        constexpr Sun(const std::initializer_list<real>& l) : Body(l)
        {
        }
        constexpr Sun(const numbers::vector<real>& p) : Body(p)
        {
        }
    };
    struct Earth : public Body
    {
        Earth();
        constexpr Earth(const std::initializer_list<real>& l) : Body(l)
        {
        }
        constexpr Earth(const numbers::vector<real>& p) : Body(p)
        {
        }
    };
    struct Moon : public Body
    {
        Moon();
        constexpr Moon(const std::initializer_list<real>& l) : Body(l)
        {
        }
        constexpr Moon(const numbers::vector<real>& p) : Body(p)
        {
        }
    };

    struct Solar : public Scenary
    {
        Sun sun;
        Earth earth;
        Moon moon;
        static void display();
        static void reshape(GLint w, GLint h);
        constexpr Solar() : Scenary(Solar::display,Solar::reshape)
        {
        }
        constexpr Solar(const std::initializer_list<real>& l) : Scenary(l)
        {
        }
        constexpr Solar(const numbers::vector<real>& p) : Scenary(p)
        {
        }

        virtual bool initialize();
        virtual void on_active();
        virtual void run();
    };

    struct ViaLactea : public Scenary
    {
        Solar solar;

    };

}

#endif // OCTETOS_VERSO_V1_SCENARY_HH

