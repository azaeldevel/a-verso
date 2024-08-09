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

    struct Scenary
    {
        HSCENARY scenary;
        void (*initialize)();
        void (*display)();
        void (*reshape)(GLint w, GLint h);

        HSCENARY insert(Scenary&);

        Scenary();
        Scenary(void (*initialize)(),void (*display)(),void (*reshape)(GLint w, GLint h));
    };

    typedef Scenary Sun;
    typedef Scenary Earth;
    typedef Scenary Moon;

    struct Solar : public Scenary
    {
        Sun sun;
        Earth earth;
        Moon moon;

        Solar();
    };

    struct ViaLactea : public Scenary
    {
        Solar solar;
    };

}

#endif // OCTETOS_VERSO_V1_SCENARY_HH

