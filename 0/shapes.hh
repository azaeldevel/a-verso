
#ifndef OCTETOS_AVERSO_SHAPES_HH
#define OCTETOS_AVERSO_SHAPES_HH

#include <core/3/Exception.hh>
#include <glm/glm.hpp>
#include <vector>
#include <numbers/0/vector.hh>

#include "color.hh"

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

namespace oct::verso::v0
{
    //template<class T> concept Dimension = std::is_base_of<U, T>::value;
    template<typename T> concept coordinate = std::same_as<T, int> || std::same_as<T, float>;

    enum class axis
    {
        x,
        y,
        z
    };



    void active(const Color<float,3>&);
    void active(const Color<float,4>&);


    //typedef glm::vector<float,2,glm::packed_highp> vec2;
    //typedef glm::vector<float,3,glm::packed_highp> vec3;
    template<coordinate C, unsigned char D,class V = C>
    class Point  : public nums_here::vector<C,D,V>
    {
    public:
        typedef glm::vec<D,C,glm::packed_highp> GLM;
        typedef nums_here::vector<C,D,V> BASE;

        //>>>Contructores
        Point() = default;
        constexpr Point(C p[D]) : BASE(p)
        {
        }
        constexpr Point(C x, C y) : BASE(x,y)
        {
        }
        constexpr Point(C x, C y,C z) : BASE(x,y,z)
        {
        }
        constexpr Point(C x, C y,C z, C w) : BASE(x,y,z,w)
        {
        }
        constexpr Point(const Point& p) : BASE(p)
        {
        }
        constexpr Point(const nums_here::vector<C,D,V>& p) : BASE(p)
        {
        }
        constexpr Point(const GLM& p) : BASE(reinterpret_cast<const Point&>(p))
        {
        }
        /*Point(const std::initializer_list<C>& l)
        {
            if(l.size() < L) throw core_here::exception("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > L) throw core_here::exception("La cantidad de datos execede la capacidad del objeto");

            const T* c = std::data(l);
            for(size_t i = 0; i < l.size(); i++)
            {
                data[i] = c[i];
            }
        }*/

        //>>>Operadores
        constexpr Point& operator = (const Point& p)
        {
            for(size_t i = 0; i < D; i++) BASE::data[i] = p[i];

            return *this;
        }
        constexpr Point& operator = (const GLM& p)
        {
            const Point& pnew = reinterpret_cast<const Point&>(p);

            for(size_t i = 0; i < D; i++) BASE::data[i] = pnew[i];
            return *this;
        }
        operator GLM&()
        {
            return *reinterpret_cast<GLM*>(this);
        }
        operator const GLM&() const
        {
            return *reinterpret_cast<const GLM*>(this);
        }

        //>>>getters and setters



        //>>>

        constexpr V comp(const Point& b)
        {
            V v = BASE::dot(b);
            v /= b.length();

            return v;
        }

        /*
        *\brief Componente de this en la direction de b
        */
        /*constexpr V length() const
        {
            //return glm::length(*this);
        }
        constexpr V distance(const Point& b)
        {
            return glm::distance(*this,b);
        }
        constexpr void normalize() const
        {
            V l = length();
            for(size_t i = 0; i < D; i++) BASE::data[i] /= l;
        }*/


        /**
        *\brief Transformacion de tranlacion
        */
        constexpr void transl(const Point& v)
        {
            //for(size_t i = 0; i < D; i++) vertexs[i].transl(v);
        }

        /**
        *\brief Transformacion de scalado
        */
        constexpr void scale(const C& s)
        {
            //for(size_t i = 0; i < D; i++) vertexs[i].scale(s);
        }

        /**
        *\brief Transformacion de rotacion
        *\param axis Eje de rotacion
        **/
        /*constexpr void rotate(const C& angle,axis a)
        {
            switch(a)
            {
            case axis::z:
                {
                    C x1 = BASE::x, y1 = BASE::y;
                    GLM::x = x1 * cos(angle) - y1 * sin(angle);
                    GLM::y = x1 * sin(angle) + y1 * cos(angle);
                }
                break;
            case axis::y:
                {
                    C x1 = BASE::x, z1 = BASE::z;
                    GLM::x = x1 * cos(angle) - z1 * sin(angle);
                    GLM::z = x1 * sin(angle) + z1 * cos(angle);
                }
                break;
            case axis::x:
                {
                    C y1 = GLM::y, z1 = GLM::z;
                    GLM::y = y1 * cos(angle) - z1 * sin(angle);
                    GLM::z = y1 * sin(angle) + z1 * cos(angle);
                }
                break;
            }
        }*/

#ifdef OCTETOS_AVERSO_TTD
        void print(std::ostream& out)const;
        void printLn(std::ostream& out)const;
#endif // OCTETOS_AVERSO_TTD

    };




    /*template<class C, unsigned char D,class V>
    constexpr C Point<C,D,V>::scalar(const Point<C,D,V>& v)
    {

        return 0;
    }
    Point& operator = (const Point& p)
    {

    }
    Point& operator = (const GLM& p)
    {

    }
    */



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
    public:

    };

    template<class C, unsigned char D,class V>
    class Triangle : public Shape<C,D,V>
    {
    private:
        static const size_t vetexs_count = 3;
        static const size_t vetexs_base_size = vetexs_count * D;
        typedef glm::vec<D,C,glm::packed_highp> GLM;

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

        /**
        *\brief Transformacion de rotacion
        *\param axis Eje de rotacion
        **/
        void rotate(const C& angle,nums_here::axis a)
        {
            vertexs[0].rotate(angle,a);
            vertexs[1].rotate(angle,a);
            vertexs[2].rotate(angle,a);
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
