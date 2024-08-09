
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

      //Sol
      glPushMatrix();
      glTranslatef(0, 0.5, 0.0);
      glRotatef(90.0, 1.0, 0.0, 0.0);
      glutSolidSphere(1.0, 30, 30);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-2, -0.5, 0.0);
      glRotatef(270.0, 1.0, 0.0, 0.0);
      glutSolidSphere(0.1, 30, 30);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(2, 0.0, -1.0);
      glutSolidSphere(0.2, 30, 30);
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



    Solar::Solar() : Scenary(solar_display,solar_reshape)
    {
    }

    void Solar::initialize()
    {
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
      active();
    }



}
