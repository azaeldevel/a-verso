
#ifndef OCTETOS_AVERSO_OBJECTS_HH
#define OCTETOS_AVERSO_OBJECTS_HH

#include "quadric.hh"

namespace oct::verso::v0::gl
{

    /**
    *\brief Dibuja una flecha
    */
    template<numbers::number C = GLdouble>
    class Arrow
    {
    private:

    protected:
        Cilinder<C> body,head;
        C base_radius,body_size,head_size;

    public:
        Arrow() : base_radius(0.01),body_size(0.9),head_size(0.1)
        {
        }

        void create(const Color<float>& color,numbers::axis axis)
        {
            glPushMatrix();
            //glMatrixMode(GL_MODELVIEW);
            color.active();
            if(axis == numbers::axis::x)
            {
                glLoadIdentity();
                glRotatef(90,0,1,0);
                body.create(base_radius,base_radius,body_size,20,20);
                glLoadIdentity();
                glTranslatef(body_size,0,0);
                glRotatef(90,0,1,0);
                head.create(base_radius * 2,0,head_size,20,20);
            }
            else if(axis == numbers::axis::y)
            {
                glLoadIdentity();
                glRotatef(-90,1,0,0);
                body.create(base_radius,base_radius,body_size,20,20);
                glLoadIdentity();
                glTranslatef(0,body_size,0);
                glRotatef(-90,1,0,0);
                head.create(base_radius * 2,0,head_size,20,20);
            }
            else if(axis == numbers::axis::z)
            {
                glLoadIdentity();
                body.create(base_radius,base_radius,body_size,20,20);
                glLoadIdentity();
                glTranslatef(0,0,body_size);
                head.create(base_radius * 2,0,head_size,20,20);
            }
            glPopMatrix();
            //glMatrixMode(GL_MODELVIEW);
        }

    };

    /**
    *\brief Dibuja una flecha
    */
    template<numbers::number C = GLdouble>
    class Axis
    {
    private:

    protected:
        Arrow<C> arrows;
        numbers::vector<C,3> O;
        Color<float,3> O_colors;
        //Sphere<C> sphere;

    public:
        Axis() : O(0),O_colors(colors::white)
        {
        }

        void create()
        {
            arrows.create(colors::red,numbers::axis::x);
            arrows.create(colors::green,numbers::axis::y);
            arrows.create(colors::blue,numbers::axis::z);
            colors::white.active();
            //sphere.create(1,20,20);
        }

    };

    template<numbers::number N>
    class Plane
    {

    private:
        N width,high;
        //size_t units;

    public:
        Plane() : width(30),high(30)
        {
        }

        void create()
        {
            N width_media = width / N(2);
            N high_media = high / N(2);

            glBegin(GL_LINES);
                colors::coordenade.active();
                for(int i = -high_media + 1; i < high_media; i++)
                {
                    glVertex3f(-width_media,0,i);
                    glVertex3f(width_media,0,i);
                }
                for(int i = -width_media + 1; i < width_media; i++)
                {
                    glVertex3f(i,0,-width_media);
                    glVertex3f(i,0,width_media);
                }
                colors::red.active();
                glVertex3f(-0.5,0,0);
                glVertex3f(0.5,0,0);
                colors::green.active();
                glVertex3f(0,0,-0.5);
                glVertex3f(0,0,0.5);
            glEnd();
        }

    };

}

#endif // OCTETOS_AVERSO_SHAPES_HH
