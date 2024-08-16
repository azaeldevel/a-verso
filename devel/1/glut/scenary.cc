
#include "scenary.hh"

namespace oct::verso::v1
{
    Scenary* actual;

    Scenary::Scenary() : display(NULL),reshape(NULL)
    {
    }
    Scenary::Scenary(DISPLAY d,RESHAPE r) : display(d),reshape(r)
    {
    }

    void Scenary::active()
    {
        actual = this;
    }





    void solar_display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        // Rotate the scene so we can see the tops of the shapes.
        glRotatef(-20.0, 1.0, 0.0, 0.0);

        Solar& solar = *static_cast<Solar*>(actual);

        //Sol
        glPushMatrix();
        glTranslatef(solar.sun.position[0], solar.sun.position[1], solar.sun.position[2]);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glutSolidSphere(1.0, 60, 30);
        glPopMatrix();

        //Earth
        glPushMatrix();
        glTranslatef(solar.earth.position[0], solar.earth.position[1], solar.earth.position[2]);
        glRotatef(270.0, 1.0, 0.0, 0.0);
        glutSolidSphere(0.3, 60, 30);
        glPopMatrix();

        //Moon
        glPushMatrix();
        glTranslatef(solar.moon.position[0], solar.moon.position[1], solar.moon.position[2]);
        glutSolidSphere(0.1, 60, 30);
        glPopMatrix();

        glPopMatrix();
        glFlush();
    }

    void solar_reshape(GLint w, GLint h)
    {
      glViewport(0, 0, w, h);
      glMatrixMode(GL_PROJECTION);
      GLfloat aspect = GLfloat(w) / GLfloat(h);
      glLoadIdentity();
      if (w <= h) {
        // width is smaller, so stretch out the height
        glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
      } else {
        // height is smaller, so stretch out the width
        glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
      }
    }



    Sun::Sun() : position{0, 0.5, 0.0}
    {
    }

    Earth::Earth() : position{-2, -0.5, 0.0}
    {
    }

    Moon::Moon() : position{-2.5, 0.0, -1.0}
    {
    }






    Solar::Solar() : Scenary(solar_display,solar_reshape)
    {
    }

    void Solar::initialize()
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
        GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
        GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };

      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
      glMaterialfv(GL_FRONT, GL_SPECULAR, white);
      glMaterialf(GL_FRONT, GL_SHININESS, 30);

      glLightfv(GL_LIGHT0, GL_AMBIENT, black);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
      glLightfv(GL_LIGHT0, GL_SPECULAR, white);
      glLightfv(GL_LIGHT0, GL_POSITION, direction);

      glEnable(GL_LIGHTING);                // so the renderer considers light
      glEnable(GL_LIGHT0);                  // turn LIGHT0 on
      glEnable(GL_DEPTH_TEST);              // so the renderer considers depth
    }

    void Solar::on_active()
    {
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        actual = this;
    }
    void Solar::run()
    {
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowPosition(80, 80);
        glutInitWindowSize(800, 600);
        glutCreateWindow("A verso from GLUT");
        initialize();
        on_active();
        glutMainLoop();
    }


}
