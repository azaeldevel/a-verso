
#ifndef OCTETOS_AVERSO_DRAW_HH
#define OCTETOS_AVERSO_DRAW_HH

#include <GL/glew.h>

//#include <core/3/Exception.hh>
//#include <numbers/0/vector.hh>
#include <numbers/0/shapes.hh>
#include "colors.hh"
#include "gl.hh"

namespace oct::verso::v0
{

    void outline(const numbers::Line<float,3,float>&);

    void outline(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2);

    void outline(const numbers::Triangle<float,2,float>& triangle);
    void outline(const numbers::Triangle<float,3,float>& triangle);
    void outline_triangle(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2, const RGBA<unsigned char>& c);
    void outline_triangle(const numbers::Line<float,3,float>& base, const numbers::vector<float,3,float>& cusp, const RGBA<unsigned char>& c);

    void outline(const numbers::Triangle<float,3,float>&,const numbers::core::array<RGBA<unsigned char>,3>&);

    void outline(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1);

    template<core::index auto B> void outline(const numbers::Pyramid<float,3,B,float>& pyramid)
    {
        //std::cout << "Drawing pyramid : base " << B << "\n";
        RGBA<unsigned char> color(0);
        const auto& shape = (numbers::Shape<float,3,B + 1,float>&)pyramid;
        const auto& base = (numbers::Triangle<float,3,float>&)shape;
        const auto& cusp = shape[B];
        outline(base);
        for(size_t i = 0; i < B; i++)
        {
            color[i] = 255;
            outline_triangle(shape[i],shape[i+1],cusp,color);
            //draw_triangle(shape.from(2,i),cusp,color);
            outline(base[i],cusp);
            color[i] = 0;
        }
        outline_triangle(shape[B - 1],shape[0],cusp,color);
    }

    void outline(const numbers::Rectangle<float,3,float>&);


    template<core::index auto P>void outline(const numbers::Circle<float,3,P>& circle,const RGBA<unsigned char>& color)
    {
        glBegin(GL_LINE_LOOP);
            gl::color(color);
            for(size_t i = 1; i < circle.size(); i++)
            {
                //glVertex3f(circle[i-1].x(),circle[i-1].y(),circle[i-1].z());
                glVertex3f(circle[i].x(),circle[i].y(),circle[i].z());
            }
        glEnd();
    }


    void polygon(const numbers::Triangle<float,2,float>& triangle);
    void polygon(const numbers::Triangle<float,3,float>& triangle);
    void polygon(const numbers::Triangle<float,3,float>& triangle,GLuint);
    void polygon_triangle(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2, const RGBA<unsigned char>& c);
    void polygon_triangle(const numbers::Line<float,3,float>& base, const numbers::vector<float,3,float>& cusp, const RGBA<unsigned char>& c);

    void polygon(const numbers::Rectangle<float,3,float>&);

}

#endif // OCTETOS_AVERSO_SHAPES_HH
