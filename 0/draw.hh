
#ifndef OCTETOS_AVERSO_DRAW_HH
#define OCTETOS_AVERSO_DRAW_HH

#include <core/3/Exception.hh>
#include <numbers/0/vector.hh>


namespace oct::verso::v0
{
    namespace core_here = oct::core::v3;
    namespace numbers = oct::nums::v0;

    typedef numbers::vector<float,3> Color;

    template<numbers::number C, size_t D = 3,numbers::number V = C> constexpr void draw(const numbers::Triangle<C,D,V>& triangle)
    {
        glBegin(GL_TRIANGLES);
            // Dibujamos un triángulo
            glColor3f(1.0,0.0,0.0);
            // Color del primer vértice: rojo
            glVertex3f(triangle[0].x(),triangle[0].y(),triangle[0].z());
            // Coordenadas del primer vértice
            glColor3f(0.0,1.0,0.0);
            // Color del segundo vértice: verde
            glVertex3f(triangle[1].x(),triangle[1].y(),triangle[1].z());
            // Coordenadas del segundo vértice
            glColor3f(0.0,0.0,1.0);
            // Color del tercer vértice: azúl
            glVertex3f(triangle[2].x(),triangle[2].y(),triangle[2].z());
            // Coordenadas del tercer vértice
        glEnd();
    }

}

#endif // OCTETOS_AVERSO_SHAPES_HH
