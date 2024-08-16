#include "glut/scenary.hh"

namespace verso = oct::verso::v1;


verso::Solar solar;

// The usual application statup code.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    solar.run();

    return EXIT_SUCCESS;
}
