
#include "draw.hh"

namespace oct::verso::v0
{
    void draw(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1)
    {
        /*std::cout << "Line front ";
        p0.print(std::cout);
        std::cout << " to ";
        p1.printLn(std::cout);*/
        glBegin(GL_LINES);
            // Dibujamos un triángulo
            glColor3f(1.0,1.0,1.0);
            // Color del primer vértice: rojo
            glVertex3f(p0.x(),p0.y(),p0.z());
            // Color del segundo vértice: verde
            glVertex3f(p1.x(),p1.y(),p1.z());
        glEnd();
    }

    void draw(const numbers::Triangle<float,3,float>& triangle)
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
    void draw(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2)
    {
        glBegin(GL_TRIANGLES);
            // Dibujamos un triángulo
            glColor3f(1.0,0.0,0.0);
            // Color del primer vértice: rojo
            glVertex3f(p0.x(),p0.y(),p0.z());
            // Coordenadas del primer vértice
            glColor3f(0.0,1.0,0.0);
            // Color del segundo vértice: verde
            glVertex3f(p1.x(),p1.y(),p1.z());
            // Coordenadas del segundo vértice
            glColor3f(0.0,0.0,1.0);
            // Color del tercer vértice: azúl
            glVertex3f(p2.x(),p2.y(),p2.z());
            // Coordenadas del tercer vértice
        glEnd();
    }
    void draw_triangle(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2, const Color<float,3>& color)
    {
        glBegin(GL_TRIANGLES);
            // Dibujamos un triángulo
            glColor3f(color.r(),color.g(),color.b());
            // Color del primer vértice: rojo
            glVertex3f(p0.x(),p0.y(),p0.z());
            // Coordenadas del primer vértice
            glColor3f(color.r(),color.g(),color.b());
            // Color del segundo vértice: verde
            glVertex3f(p1.x(),p1.y(),p1.z());
            // Coordenadas del segundo vértice
            glColor3f(color.r(),color.g(),color.b());
            // Color del tercer vértice: azúl
            glVertex3f(p2.x(),p2.y(),p2.z());
            // Coordenadas del tercer vértice
        glEnd();
    }

}
