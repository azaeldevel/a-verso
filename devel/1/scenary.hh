#ifndef OCTETOS_VERSO_V1_SCENARY_HH

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <map>
#include <string>



namespace oct::verso::v1
{

    typedef int HSCENARY;
    typedef void (*DISPLAY)();
    typedef void (*RESHAPE)(GLint, GLint);

    struct Scenary
    {
        Scenary();
        Scenary(DISPLAY,RESHAPE);

        DISPLAY display;
        RESHAPE reshape;

        /**
        *\brief Activar nueva escena
        */
        virtual void active();
    };

    extern Scenary* actual;

    struct Sun : public Scenary
    {
        GLfloat position[3];

        Sun();
    };
    struct Earth : public Scenary
    {
    };
    struct Moon : public Scenary
    {
    };

    struct Solar : public Scenary
    {
        Sun sun;
        Earth earth;
        Moon moon;
        Solar();

        void initialize();
        virtual void active();
    };

    struct ViaLactea : public Scenary
    {
        Solar solar;
    };

}

#endif // OCTETOS_VERSO_V1_SCENARY_HH

