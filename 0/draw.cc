
#include "draw.hh"

namespace oct::verso::v0
{
    void outline(const numbers::Line<float,3,float>& line)
    {
        /*std::cout << "Line front ";
        p0.print(std::cout);
        std::cout << " to ";
        p1.printLn(std::cout);*/
        glBegin(GL_LINE_LOOP);
            // Dibujamos un triángulo
            //glColor3f(1.0,1.0,1.0);
            // Color del primer vértice: rojo
            glVertex3f(line[0].x(),line[0].y(),line[0].z());
            // Color del segundo vértice: verde
            glVertex3f(line[1].x(),line[1].y(),line[1].z());
        glEnd();
    }
    void outline(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1)
    {
        glBegin(GL_LINE_LOOP);
            // Dibujamos un triángulo
            //glColor3f(1.0,1.0,1.0);
            // Color del primer vértice: rojo
            glVertex3f(p0.x(),p0.y(),p0.z());
            // Color del segundo vértice: verde
            glVertex3f(p1.x(),p1.y(),p1.z());
        glEnd();
    }

    void outline(const numbers::Triangle<float,3,float>& triangle)
    {
        glBegin(GL_LINE_LOOP);
            // Dibujamos un triángulo
            //glColor3f(1.0,0.0,0.0);
            // Color del primer vértice: rojo
            glVertex3f(triangle[0].x(),triangle[0].y(),triangle[0].z());
            // Coordenadas del primer vértice
            //glColor3f(0.0,1.0,0.0);
            // Color del segundo vértice: verde
            glVertex3f(triangle[1].x(),triangle[1].y(),triangle[1].z());
            // Coordenadas del segundo vértice
            //glColor3f(0.0,0.0,1.0);
            // Color del tercer vértice: azúl
            glVertex3f(triangle[2].x(),triangle[2].y(),triangle[2].z());
            // Coordenadas del tercer vértice
        glEnd();
    }
    void outline(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2)
    {
        glBegin(GL_LINE_LOOP);
            // Dibujamos un triángulo
            //glColor3f(1.0,0.0,0.0);
            // Color del primer vértice: rojo
            glVertex3f(p0.x(),p0.y(),p0.z());
            // Coordenadas del primer vértice
            //glColor3f(0.0,1.0,0.0);
            // Color del segundo vértice: verde
            glVertex3f(p1.x(),p1.y(),p1.z());
            // Coordenadas del segundo vértice
            //glColor3f(0.0,0.0,1.0);
            // Color del tercer vértice: azúl
            glVertex3f(p2.x(),p2.y(),p2.z());
            // Coordenadas del tercer vértice
        glEnd();
    }
    void outline_triangle(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2, const Color<float,3>& color)
    {
        glBegin(GL_LINE_LOOP);
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
    void outline_triangle(const numbers::Line<float,3,float>& base, const numbers::vector<float,3,float>& cusp, const Color<float,3>& color)
    {
        glBegin(GL_LINE_LOOP);
            // Dibujamos un triángulo
            glColor3f(color.r(),color.g(),color.b());
            // Color del primer vértice: rojo
            glVertex3f(base[0].x(),base[0].y(),base[0].z());
            // Coordenadas del primer vértice
            glColor3f(color.r(),color.g(),color.b());
            // Color del segundo vértice: verde
            glVertex3f(base[1].x(),base[1].y(),base[1].z());
            // Coordenadas del segundo vértice
            glColor3f(color.r(),color.g(),color.b());
            // Color del tercer vértice: azúl
            glVertex3f(cusp.x(),cusp.y(),cusp.z());
            // Coordenadas del tercer vértice
        glEnd();
    }

    void outline(const numbers::Triangle<float,3,float>& triangle,const numbers::sequence<Color<float,3>,3>& colors)
    {
        glBegin(GL_LINE_LOOP);
            // Dibujamos un triángulo
            glColor3f(colors[0].r(),colors[0].g(),colors[0].b());
            // Color del primer vértice: rojo
            glVertex3f(triangle[0].x(),triangle[0].y(),triangle[0].z());
            // Coordenadas del primer vértice
            glColor3f(colors[1].r(),colors[1].g(),colors[1].b());
            // Color del segundo vértice: verde
            glVertex3f(triangle[1].x(),triangle[1].y(),triangle[1].z());
            // Coordenadas del segundo vértice
            glColor3f(colors[2].r(),colors[2].g(),colors[2].b());
            // Color del tercer vértice: azúl
            glVertex3f(triangle[2].x(),triangle[2].y(),triangle[2].z());
            // Coordenadas del tercer vértice
        glEnd();
    }




    void outline(const numbers::Rectangle<float,3,float>& rect)
    {
        glBegin(GL_LINE_LOOP);
            // Dibujamos un triángulo
            //glColor3f(1.0,0.0,0.0);
            // Color del primer vértice: rojo
            glVertex3f(rect[0].x(),rect[0].y(),rect[0].z());
            // Coordenadas del primer vértice
            //glColor3f(0.0,1.0,0.0);
            // Color del segundo vértice: verde
            glVertex3f(rect[1].x(),rect[1].y(),rect[1].z());
            // Coordenadas del segundo vértice
            //glColor3f(0.0,0.0,1.0);
            // Color del tercer vértice: azúl
            glVertex3f(rect[2].x(),rect[2].y(),rect[2].z());
            // Coordenadas del tercer vértice
            //glColor3f(0.0,0.0,0.0);
            // Color del tercer vértice: azúl
            glVertex3f(rect[3].x(),rect[3].y(),rect[3].z());
        glEnd();
    }










    void polygon(const numbers::Triangle<float,3,float>& triangle)
    {
        glBegin(GL_TRIANGLES);
            // Dibujamos un triángulo
            //glColor3f(1.0,0.0,0.0);
            // Color del primer vértice: rojo
            glVertex3f(triangle[0].x(),triangle[0].y(),triangle[0].z());
            // Coordenadas del primer vértice
            //glColor3f(0.0,1.0,0.0);
            // Color del segundo vértice: verde
            glVertex3f(triangle[1].x(),triangle[1].y(),triangle[1].z());
            // Coordenadas del segundo vértice
            //glColor3f(0.0,0.0,1.0);
            // Color del tercer vértice: azúl
            glVertex3f(triangle[2].x(),triangle[2].y(),triangle[2].z());
            // Coordenadas del tercer vértice
        glEnd();
    }
    void polygon(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2)
    {
        glBegin(GL_TRIANGLES);
            // Dibujamos un triángulo
            //glColor3f(1.0,0.0,0.0);
            // Color del primer vértice: rojo
            glVertex3f(p0.x(),p0.y(),p0.z());
            // Coordenadas del primer vértice
            //glColor3f(0.0,1.0,0.0);
            // Color del segundo vértice: verde
            glVertex3f(p1.x(),p1.y(),p1.z());
            // Coordenadas del segundo vértice
            //glColor3f(0.0,0.0,1.0);
            // Color del tercer vértice: azúl
            glVertex3f(p2.x(),p2.y(),p2.z());
            // Coordenadas del tercer vértice
        glEnd();
    }
    void polygon_triangle(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2, const Color<float,3>& color)
    {
        glBegin(GL_TRIANGLES);
            // Dibujamos un triángulo
            //glColor3f(color.r(),color.g(),color.b());
            // Color del primer vértice: rojo
            glVertex3f(p0.x(),p0.y(),p0.z());
            // Coordenadas del primer vértice
            //glColor3f(color.r(),color.g(),color.b());
            // Color del segundo vértice: verde
            glVertex3f(p1.x(),p1.y(),p1.z());
            // Coordenadas del segundo vértice
            //glColor3f(color.r(),color.g(),color.b());
            // Color del tercer vértice: azúl
            glVertex3f(p2.x(),p2.y(),p2.z());
            // Coordenadas del tercer vértice
        glEnd();
    }
    void polygon_triangle(const numbers::Line<float,3,float>& base, const numbers::vector<float,3,float>& cusp, const Color<float,3>& color)
    {
        glBegin(GL_TRIANGLES);
            // Dibujamos un triángulo
            //glColor3f(color.r(),color.g(),color.b());
            // Color del primer vértice: rojo
            glVertex3f(base[0].x(),base[0].y(),base[0].z());
            // Coordenadas del primer vértice
            //glColor3f(color.r(),color.g(),color.b());
            // Color del segundo vértice: verde
            glVertex3f(base[1].x(),base[1].y(),base[1].z());
            // Coordenadas del segundo vértice
            //glColor3f(color.r(),color.g(),color.b());
            // Color del tercer vértice: azúl
            glVertex3f(cusp.x(),cusp.y(),cusp.z());
            // Coordenadas del tercer vértice
        glEnd();
    }

    void polygon(const numbers::Rectangle<float,3,float>& rect)
    {
        glBegin(GL_QUADS);
            // Dibujamos un triángulo
            //glColor3f(1.0,0.0,0.0);
            // Color del primer vértice: rojo
            glVertex3f(rect[0].x(),rect[0].y(),rect[0].z());
            // Coordenadas del primer vértice
            //glColor3f(0.0,1.0,0.0);
            // Color del segundo vértice: verde
            glVertex3f(rect[1].x(),rect[1].y(),rect[1].z());
            // Coordenadas del segundo vértice
            //glColor3f(0.0,0.0,1.0);
            // Color del tercer vértice: azúl
            glVertex3f(rect[2].x(),rect[2].y(),rect[2].z());
            // Coordenadas del tercer vértice
            //glColor3f(0.0,0.0,0.0);
            // Color del tercer vértice: azúl
            glVertex3f(rect[3].x(),rect[3].y(),rect[3].z());
        glEnd();
    }
}
