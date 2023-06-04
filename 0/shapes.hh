
#ifndef OCTETOS_AVERSO_SHAPES_HH
#define OCTETOS_AVERSO_SHAPES_HH

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
    #include <core/3/Exception.hh>
#endif // OCTETOS_AVERSO_DEBUG



namespace oct::verso::v0
{
    namespace core_here = oct::core::v3;
    //template<class T> concept Dimension = std::is_base_of<U, T>::value;

    template<class C, unsigned char D,class V>
    class Point
    {
    public:
        Point()
        {
            point[0] = 0;
            point[1] = 0;
            point[2] = 0;
        }
        Point(C p[D])
        {
            for(unsigned char i = 0; i < D; i++)
            {
                point[i] = p[i];
            }
        }
        Point(C x, C y)
        {
            point[0] = x;
            point[1] = y;
        }
        Point(C x, C y,C z)
        {
            if(3 == D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");

            point[0] = x;
            point[1] = y;
            point[2] = z;
        }
        Point(std::initializer_list<C> l)
        {
            if(l.size() > D) throw core_here::exception("La cantidad de datos indicados excede la capacidad del objetos");
            unsigned char i = 0;
            for(const C& c : l)
            {
                point[i] = c;
                i++;
            }
        }

        bool operator == (const Point& p)
        {
            if( point[0] != p.point[0]) return false;
            if( point[1] != p.point[1]) return false;
            if(D == 3) if( point[2] != p.point[2]) return false;

            return true;
        }


        V operator * (const Point& p) const
        {
            V scalar = 0;

            scalar += point[0] * p.point[0];
            scalar += point[1] * p.point[1];
            if(D == 3) scalar += point[2] * p.point[2];

            return scalar;
        }
        V slope(const Point& p)const
        {
            if(3 == D) throw core_here::exception("La pendiente para 3 dimensiones esta en desarrollo.");

            V y =  p.point[1] - point[1];
            V x =  p.point[0] - point[0];

            return y/x;
        }

        C x() const
        {
            return point[0];
        }
        C y() const
        {
            return point[1];
        }
        C z() const
        {
            if(3 == D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");

            return point[2];
        }
        C& x()
        {
            return point[0];
        }
        C& y()
        {
            return point[1];
        }
        C& z()
        {
            if(3 == D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");
            return point[2];
        }

        C& operator [] (const char i)
        {
            if(i == D) throw core_here::exception("Deve especifiecarse 3 dimensiones para usar contructor de 3 demensiones");

            return point[i];
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

#endif // OCTETOS_AVERSO_TTD
    private:
        C point[D];
    };

    template<class C, unsigned char D>
    class Shape
    {
    };

    template<class C, unsigned char D,class V>
    class Line : public Shape<C,D>
    {

    public:
        Line() //: ps[0]({0,0}), ps[1]({1,1})
        {
        }
        Line(C p[2 * D])
        {
            ps[0][0] = p[0];
            ps[0][1] = p[1];
            ps[1][0] = p[2];
            ps[1][1] = p[3];


        }
        /*void draw(SDL_Renderer* render) const
        {
            SDL_RenderDrawLine(render,ps[0],ps[1],ps[2],ps[3]);
        }*/
        void resize(V leng)
        {
            V s = ps[0].slope(ps[1]);


        }

    private:
        Point<C,D,V> ps[2];
    };

    template<class C, unsigned char D>
    class Rectangle : public Shape<C,D>
    {

    };

    template<class C, unsigned char D>
    class Circle : public Shape<C,D>
    {

    };


    namespace dd
    {

    }


}

#endif // OCTETOS_AVERSO_SHAPES_HH
