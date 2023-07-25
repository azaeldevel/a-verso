
#ifndef OCTETOS_AVERSO_SHAPES_HH
#define OCTETOS_AVERSO_SHAPES_HH

#include <core/3/Exception.hh>
#include <glm/glm.hpp>
#include <vector>

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

namespace oct::verso::v0
{
    namespace core_here = oct::core::v3;
    //template<class T> concept Dimension = std::is_base_of<U, T>::value;

    template<class C, unsigned char D,class V>
    class Point  : public glm::vec<D,C,glm::packed_highp>
    {
    public:
        typedef glm::vec<D,C,glm::packed_highp> vector;

        //>>>Contructores
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
        Point(const glm::vec<D,C,glm::packed_highp>& v) : vector(v)
        {
        }
        Point(std::initializer_list<C>& l);

        //>>>Operadores
        Point& operator = (const Point& p);
        Point& operator = (const glm::vec<D,C,glm::packed_highp>& p);

        //>>>getters and setters



        //>>>
        /*
        *\brief Componente de this en la direction de b
        */
        V length() const;
        V comp(const Point& b)
        {
            V v = glm::dot((const vector&)*this,b);
            v /= b.length();

            return v;
        }
        V distance(const Point& b)
        {
            return glm::distance((const vector&)*this,b);
        }
        Point normalize() const
        {
            return glm::normalize((const vector&)*this);
        }

#ifdef OCTETOS_AVERSO_TTD
        void print(std::ostream& out)const;
        void printLn(std::ostream& out)const;
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

    template<class C, unsigned char D,class V>
    class Triangle : public Shape<C,D,V>
    {
    private:
        static const size_t vetexs_count = 3;
        static const size_t vetexs_base_size = vetexs_count * D;
    public:
        constexpr Triangle() = default;
        constexpr Triangle(std::initializer_list<C>& l)
        {
            if(l.zise() < vetexs_base_size) throw core_here::exception("Para formar un triangulo se requieren 3 * D vertices osea, untotal de 9");
            if(l.zise() > vetexs_base_size) throw core_here::exception("Para formar un triangulo se requieren 3 * D vertices osea, untotal de 9");

            const C* l_base = l.begin();
            const C* vertex_base = static_cast<C*>(vertexs);
            for(size_t i = 0; i < l.zise();i++)
            {
                vertex_base[i] = l_base[i];
            }
        }
        constexpr Triangle(const C ps[vetexs_base_size])
        {
            C* vertex_base = reinterpret_cast<C*>(&vertexs);
            for(size_t i = 0; i < vetexs_base_size;i++)
            {
                vertex_base[i] = ps[i];
            }
        }

        Point<C,D,V>& operator[] (size_t i)
        {
            if(i < vetexs_count) return vertexs[i];

            throw std::out_of_range("Indice fuera de rango, deve ser menor que " + std::to_string(vetexs_count));
        }

    private:
        Point<C,D,V> vertexs[vetexs_count];
    };

    template<class C, unsigned char D,class V>
    class Cube : public Shape<C,D,V>
    {
    private:
        static const size_t vetexs_count = 36;
        static const size_t vetexs_base_size = vetexs_count * D;
    public:
        constexpr Cube() = default;
        constexpr Cube(std::initializer_list<C>& l)
        {
            if(l.zise() < vetexs_base_size) throw core_here::exception("Para formar un triangulo se requieren 3 * D vertices osea, untotal de 9");
            if(l.zise() > vetexs_base_size) throw core_here::exception("Para formar un triangulo se requieren 3 * D vertices osea, untotal de 9");

            const C* l_base = l.begin();
            const C* vertex_base = static_cast<C*>(vertexs);
            for(size_t i = 0; i < l.zise();i++)
            {
                vertex_base[i] = l_base[i];
            }
        }
        constexpr Cube(const C ps[vetexs_base_size])
        {
            C* vertex_base = reinterpret_cast<C*>(&vertexs);
            for(size_t i = 0; i < vetexs_base_size;i++)
            {
                vertex_base[i] = ps[i];
            }
        }

        constexpr Point<C,D,V>& operator[] (size_t i)
        {
            if(i < vetexs_count) return vertexs[i];

            throw std::out_of_range("Indice fuera de rango, deve ser menor que " + std::to_string(vetexs_count));
        }

    private:
        Point<C,D,V> vertexs[vetexs_count];
    };


}

#endif // OCTETOS_AVERSO_SHAPES_HH
