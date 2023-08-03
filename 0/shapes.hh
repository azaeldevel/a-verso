
#ifndef OCTETOS_AVERSO_SHAPES_HH
#define OCTETOS_AVERSO_SHAPES_HH

#include <core/3/Exception.hh>
#include <glm/glm.hpp>
#include <vector>
#include <numbers/0/vector.hh>

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

namespace oct::verso::v0
{
    namespace core_here = oct::core::v3;
    namespace nums_here = oct::nums::v0;
    //template<class T> concept Dimension = std::is_base_of<U, T>::value;

    template<class C, unsigned char D,class V>
    class Point  : public nums_here::vector<C,D,V>
    {
    public:
        typedef glm::vec<D,C,glm::packed_highp> glm;
        typedef nums_here::vector<C,D,V> BASE;

        //>>>Contructores
        Point() = default;
        Point(C p[D]) : BASE(p)
        {
        }
        Point(C x, C y) : BASE(x,y)
        {
        }
        /*Point(C x, C y,C z) : BASE(x,y,z)
        {
        }
        Point(C x, C y,C z, C w) : BASE(x,y,z,w)
        {
        }*/
        Point(const Point& p) : BASE(p)
        {
        }
        Point(const glm& v) : BASE((const BASE&)v)
        {
        }
        Point(const std::initializer_list<C>& l) : BASE(l)
        {
            if(l.size() < D) throw core_here::exception("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > D) throw core_here::exception("La cantidad de datos execede la capacidad del objeto");

            const C* c = std::data(l);
            for(size_t i = 0; i < D; i++)
            {
                BASE::data[i] = c[i];
            }
        }

        //>>>Operadores
        Point& operator = (const Point& p);
        Point& operator = (const glm& p);
        operator glm()
        {
            glm vec;
            vec[0] = BASE::data[0];
            vec[1] = BASE::data[1];
            return vec;
        }

        //>>>getters and setters



        //>>>
        /*
        *\brief Componente de this en la direction de b
        */
        V length() const
        {
            V v = 0;
            for(size_t i = 0; i < D; i++) v += pow(BASE::data[i],V(2));

            return sqrt(v);
        }
        V comp(const Point& b)
        {
            V v = scalar(*this,b);
            v /= b.length();

            return v;
        }
        V distance(const Point& b)
        {
            return ::glm::distance((const glm&)*this,b);
        }
        Point normalize() const
        {
            return ::glm::normalize((const glm&)*this);
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

    static const float unit_cube[36 * 3] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
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
