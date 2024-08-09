#include "scenary.hh"

namespace verso = oct::verso::v1;


verso::Solar solar;

// The usual application statup code.
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("A verso from GLUT");
  solar.initialize();
  solar.active();
  glutMainLoop();
}
