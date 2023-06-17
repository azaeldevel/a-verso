
#ifndef OCTETOS_AVERSO_SHAPES_HH
#define OCTETOS_AVERSO_SHAPES_HH

#include <core/3/Exception.hh>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG
#ifdef OCTETOS_AVERSO_SDL
    #include <SDL.h>
    #include <SDL_image.h>
#endif // OCTETOS_AVERSO_SDL

namespace oct::verso::v0
{
    namespace core_here = oct::core::v3;
    //template<class T> concept Dimension = std::is_base_of<U, T>::value;

    template<class C, unsigned char D,class V>
    class Point  : public glm::vec<D,C,glm::packed_highp>
    {
    public:
        typedef glm::vec<D,C,glm::packed_highp> vector;

        Point()
        {
        }
        Point(C p[D]);
        Point(C x, C y) : vector(x,y)
        {
        }
        Point(C x, C y,C z) : vector(x,y,z)
        {
        }
        Point(C x, C y,C z, C w) : vector(x,y,z,w)
        {
        }
        Point(const Point& p) : vector(p)
        {
        }
        Point(std::initializer_list<C>& l);
        Point(const glm::vec<D,C,glm::packed_highp>& v) : vector(v)
        {
        }

#ifdef OCTETOS_AVERSO_TTD

        void print(std::ostream& out)const
        {
            out << "(";
                out << vector::x << ",";
                out << vector::y;
                if(D == 3)
                {
                    out << "," << vector::z;
                }
            out << ")";
        }
        void printLn(std::ostream& out)const
        {
            out << "(";
                out << vector::x << ",";
                out << vector::y;
                if(D == 3)
                {
                    out << "," << vector::z;
                }
            out << ")\n";
        }

#endif // OCTETOS_AVERSO_TTD

    };



    template<class C, unsigned char D,class V>
    class Shape
    {
    };


    template<class C, unsigned char D,class V> void circle(const Point<C,D,V>& center,V radio,const Point<float,D,V>& delta,std::vector<Point<float,D,V>>& rest)
    {
#ifdef OCTETOS_AVERSO_TTD
        V lu = delta.length();
        if(abs(V(1) - lu) > 0.001) throw core_here::exception("El vector delta debe se un vector unitario");
#endif // OCTETOS_AVERSO_TTD

        if(delta.is_plane_xy())//plano x,y
        {
            V dp = delta.length();
            //primer cuadrante
            //std::cout << "primer cuadrante\n";
            rest.push_back(Point<float,D,V>(radio,0));
            while(rest.back().x() > 0)
            {
                rest.push_back(rest.back());
                rest.back().x() -= dp;
                rest.back().y() += dp;
                //rest.back().printLn(std::cout);
            }

            //segundo cuadrante
            //std::cout << "segundo cuadrante\n";
            while(rest.back().y() > 0)
            {
                rest.push_back(rest.back());
                rest.back().x() -= dp;
                rest.back().y() -= dp;
                //rest.back().printLn(std::cout);
            }

            //tercer cuadrante
            //std::cout << "tercer cuadrante\n";
            while(rest.back().x() < 0)
            {
                rest.push_back(rest.back());
                rest.back().x() += dp;
                rest.back().y() -= dp;
                //rest.back().printLn(std::cout);
            }

            //cuarto cuadrante
            //std::cout << "cuarto cuadrante\n";
            while(rest.back().y() < 0)
            {
                rest.push_back(rest.back());
                rest.back().x() += dp;
                rest.back().y() += dp;
                //rest.back().printLn(std::cout);
            }
        }
        else
        {
            core_here::exception("Plano de dibujo desconocido");
        }
    }
    //template<class C, unsigned char D,class V> void circle(const Point<C,D,V>& center,const Point<C,D,V>& last,const Point<C,D,V>& delta);
    //template<class C, unsigned char D,class V> void circle(const Point& center,const Point<C,D,V>& plane,V delta);
    template<class C, unsigned char D,class V>
    class Circle : public Shape<C,D,V>
    {

    };



}

#endif // OCTETOS_AVERSO_SHAPES_HH
