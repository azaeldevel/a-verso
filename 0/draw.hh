
#ifndef OCTETOS_AVERSO_DRAW_HH
#define OCTETOS_AVERSO_DRAW_HH

#include <GL/glew.h>

#include <core/3/Exception.hh>
//#include <numbers/0/vector.hh>
#include <numbers/0/shapes.hh>


namespace oct::verso::v0
{
    namespace core_here = oct::core::v3;
    namespace numbers = oct::nums::v0;

    template<numbers::number T,size_t L = 3,numbers::number V = T> class Color : public numbers::sequence<T,L>
    {
    private:
        typedef numbers::sequence<T,L> BASE;
    public:
        Color() = default;
        constexpr Color(const T& v) : BASE(v)
        {
        }
        /*constexpr vector(const T v[L]) : sequence<T,L>(v)
        {
        }*/
        constexpr Color(const Color& v) : BASE(v)
        {
        }
        constexpr Color(const std::initializer_list<T>& l) : BASE(l)
        {
        }

        constexpr bool operator == (const Color& s)
        {
            for(size_t i = 0; i < L; i++) if(BASE::data[i] != s[i]) return false;

            return true;
        }


        constexpr Color operator + (const Color& s)
        {
            Color res;
            for(size_t i = 0; i < L; i++) res[i] = BASE::data[i] + s[i];

            return res;
        }
        constexpr Color operator - (const Color& s)
        {
            Color res;
            for(size_t i = 0; i < L; i++) res[i] = BASE::data[i] - s[i];

            return res;
        }
        constexpr Color operator * (const T& s)
        {
            Color res;
            for(size_t i = 0; i < L; i++) BASE::data[i] *= s;

            return res;
        }

    };

    static const Color<float,3> red{1.0f,0.0f,0.0f};
    static const Color<float,3> green{0.0f,1.0f,0.0f};
    static const Color<float,3> blue{0.0f,0.0f,1.0f};

    void draw(const numbers::Triangle<float,3,float>& triangle);

}

#endif // OCTETOS_AVERSO_SHAPES_HH
