
#ifndef OCTETOS_AVERSO_SHAPES_HH
#define OCTETOS_AVERSO_SHAPES_HH

#include <core/3/Exception.hh>
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
    class Point
    {
    public:
        Point();
        Point(C p[D])
        {
            for(unsigned char i = 0; i < D; i++)
            {
                point[i] = p[i];
            }
        }
        Point(C x, C y);
        Point(C x, C y,C z);
        Point(C x, C y,C z, C w);
        Point(const Point& p)
        {
            point[0] = p.point[0];
            point[1] = p.point[1];
            if(D == 3) point[2] = p.point[2];
        }
        Point(std::initializer_list<C>& l)
        {
            if(l.size() > D) throw core_here::exception("La cantidad de datos indicados excede la capacidad del objetos");
            unsigned char i = 0;
            for(const C& c : l)
            {
                point[i] = c;
                i++;
            }
        }
        Point(const glm::vec<D,C,glm::packed_highp>& v)
        {
            //if(v.size() != D) throw core_here::exception("La cantidad de datos indicados es diferente de la especificada para el Objeto Point");

            for(size_t i = 0; i < D; i++)
            {
                point[i] = v[i];
            }
        }


        Point& operator = (const Point& p)
        {
            point[0] = p.point[0];
            point[1] = p.point[1];
            if(D == 3) point[2] = p.point[2];

            return *this;
        }
        bool operator == (const Point& p) const
        {
            if( point[0] != p.point[0]) return false;
            if( point[1] != p.point[1]) return false;
            if(D == 3) if( point[2] != p.point[2]) return false;

            return true;
        }
        bool operator == (C c)
        {
            if( point[0] != c) return false;
            if( point[1] != c) return false;
            if(D == 3) if( point[2] != c) return false;

            return true;
        }
        V operator * (const Point<int,D,V>& p) const
        {
            V scalar = 0;

            scalar += point[0] * p.point[0];
            scalar += point[1] * p.point[1];
            if(D == 3) scalar += point[2] * p.point[2];

            return scalar;
        }
        V operator * (const Point<float,D,V>& p) const
        {
            V scalar = 0;

            scalar += point[0] * p.point[0];
            scalar += point[1] * p.point[1];
            if(D == 3) scalar += point[2] * p.point[2];

            return scalar;
        }
        Point operator + (const Point& p) const
        {
            Point pnew;

            pnew[0] = point[0] + p.point[0];
            pnew[1] = point[1] + p.point[1];
            if(D == 3) pnew[2] = point[2] + p.point[2];

            return pnew;
        }
        Point operator - (const Point& p) const
        {
            Point pnew;

            pnew[0] = point[0] - p.point[0];
            pnew[1] = point[1] - p.point[1];
            if(D == 3) pnew[2] = point[2] - p.point[2];

            return pnew;
        }
        Point operator * (V r) const
        {
            Point pnew = *this;

            pnew[0] *= r;
            pnew[1] *= r;
            if(D == 3) pnew[2] *= r;

            return pnew;
        }


        V slope(const Point& p)const
        {
            if(3 == D) throw core_here::exception("La pendiente para 3 dimensiones esta en desarrollo.");

            V y =  p.point[1] - point[1];
            V x =  p.point[0] - point[0];

            return y/x;
        }
        void move(const Point& p)
        {
            point[0] += p.point[0];
            point[1] += p.point[1];
            if(D == 3) point[2] += p.point[2];
        }
        void move(V v)
        {
            point[0] += v;
            point[1] += v;
            if(D == 3) point[2] += v;
        }
        /*void proyect(V r)
        {
            point[0] *= r;
            point[1] *= r;
            if(D == 3) point[2] *= r;
        }*/
        V distance(const Point& p)const
        {
            V d = 0;

            d +=  pow(p.point[0] - point[0],2);
            d +=  pow(p.point[1] - point[1],2);
            if(D == 3)
            {
                d +=  pow(p.point[2] - point[2],2);
            }

            return sqrt(d);
        }
        V length()const
        {
            V d = 0;

            d +=  pow(point[0],2);
            d +=  pow(point[1],2);
            if(D == 3)
            {
                d +=  pow(point[2],2);
            }

            return sqrt(d);
        }
        bool is_plane_xy() const
        {
            if(D == 2)
            {
                return false;
            }
            else if(D == 3)
            {
                if(x() != 0 and y() != 0 and z() == 0)//plano x,y
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        Point normal() const;
        V comp(const Point& b)
        {
            return ((*this) * b) / b.length();
        }
        void unit ()
        {
            V l = length();
                point[0] /= l;
                point[1] /= l;
                if(D == 3) point[2] /= l;
        }

        /*static Point create(const Point& a, const Point<int,D,V>& b, const Point& u, V angle)
        {
            V p = a * b;
            p *= angle;
            return u * p;
        }
        static Point create(const Point& a, const Point<float,D,V>& b, const Point& u, V angle)
        {
            V p = a * b;
            p *= angle;
            return u * p;
        }
        static Point create(const Point<int,D,V>& a, const Point& b, const Point& u, V angle)
        {
            V p = a * b;
            p *= angle;
            return u * p;
        }
        static Point create(const Point<float,D,V>& a, const Point& b, const Point& u, V angle)
        {
            V p = a * b;
            p *= angle;
            return u * p;
        }*/


        inline void set(C x, C y)
        {
            point[0] = x;
            point[1] = y;
        }
        inline void set(C x, C y,C z)
        {
            if(3 > D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");

            point[0] = x;
            point[1] = y;
            point[2] = z;
        }
        inline C x() const
        {
            return point[0];
        }
        inline C y() const
        {
            return point[1];
        }
        inline C z() const
        {
            if(3 > D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");

            return point[2];
        }
        inline C& x()
        {
            return point[0];
        }
        inline C& y()
        {
            return point[1];
        }
        inline C& z()
        {
            if(3 == D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");
            return point[2];
        }

        inline C& operator [] (unsigned char i)
        {
            if(i == D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");

            return point[i];
        }
        inline const C& operator [] (unsigned char i) const
        {
            if(i == D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");

            return point[i];
        }
        inline operator C*()
        {
            return point;
        }
        inline operator const C*() const
        {
            return point;
        }



#ifdef OCTETOS_AVERSO_TTD

        void print(std::ostream& out)const
        {
            out << "(";
                out << point[0] << ",";
                out << point[1];
                if(D == 3)
                {
                    out << "," << point[2];
                }
            out << ")";
        }
        void printLn(std::ostream& out)const
        {
            out << "(";
                out << point[0] << ",";
                out << point[1];
                if(D == 3)
                {
                    out << "," << point[2];
                }
            out << ")\n";
        }

#endif // OCTETOS_AVERSO_TTD
    private:
        C point[D];
    };



    template<class C, unsigned char D,class V>
    class Shape
    {
    };


    template<class C, unsigned char D,class V>
    class Line : public Shape<C,D,V>
    {

    public:
        Line() = default;
        Line(C p[2 * D])
        {
            ps[0][0] = p[0];
            ps[0][1] = p[1];
            ps[1][0] = p[2];
            ps[1][1] = p[3];
        }
        Line(const Point<C,D,V>& p0,const Point<C,D,V>& p1)
        {
            ps[0] = p0;
            ps[1] = p1;
        }



        void resize(V leng)
        {
            if(ps[0] == 0)
            {
                ps[1].move(leng);
            }
            else if(ps[0] == ps[1])
            {
                /*V s = ps[0].slope(ps[1]);
                //std::cout << "Slope : " << s << "\n";
                if(s != 0.0)
                {

                }
                V delta = ps[0].distance(ps[1]);
                delta = delta - leng;
                ps[1].proyect(delta);*/
            }
            else
            {
                //ps[1].proyect(leng);
            }

        }

        void set(C p[2 * D])
        {
            ps[0][0] = p[0];
            ps[0][1] = p[1];
            ps[1][0] = p[2];
            ps[1][1] = p[3];
            if(D == 3)
            {
                ps[2][0] = p[4];
                ps[2][1] = p[5];
            }
        }
        void set(const Point<C,D,V>& p0, const Point<C,D,V>& p1)
        {
            ps[0] = p0;
            ps[1] = p1;
        }
        void move(const Point<C,D,V>& p)
        {
            ps[0].move(p);
            ps[1].move(p);
        }

        const Point<C,D,V>& begin() const
        {
            return ps[0];
        }
        const Point<C,D,V>& end() const
        {
            return ps[1];
        }

#ifdef OCTETOS_AVERSO_SDL
        void draw(SDL_Renderer* render) const
        {
            SDL_RenderDrawLine(render,ps[0][0],ps[0][1],ps[1][0],ps[1][1]);
        }
#endif // OCTETOS_AVERSO_SDL
#ifdef OCTETOS_AVERSO_TTD

        void print(std::ostream& out)const
        {
            out << "Vector ";
                ps[0].print(out);
                ps[1].print(out);
        }

#endif // OCTETOS_AVERSO_TTD
    protected:
        Point<C,D,V> ps[2];
    };


    template<class C, unsigned char D,class V>
    class Rectangle : public Shape<C,D,V>
    {

    };

    template<class C, unsigned char D,class V> void circle(const Point<C,D,V>& center,V radio,const Point<float,D,V>& delta,std::vector<Point<C,D,V>>&);
    //template<class C, unsigned char D,class V> void circle(const Point<C,D,V>& center,const Point<C,D,V>& last,const Point<C,D,V>& delta);
    //template<class C, unsigned char D,class V> void circle(const Point& center,const Point<C,D,V>& plane,V delta);
    template<class C, unsigned char D,class V>
    class Circle : public Shape<C,D,V>
    {

    };

    namespace dd
    {

    }


}

#endif // OCTETOS_AVERSO_SHAPES_HH
