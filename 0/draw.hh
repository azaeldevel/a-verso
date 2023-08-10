
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


    void draw(const numbers::Triangle<float,2,float>& triangle);
    void draw(const numbers::Triangle<float,3,float>& triangle);
    void draw(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1);
    template<size_t B> void draw(const numbers::Pyramid<float,B,3,float>& pyramid)
    {
        std::cout << "Drawing pyramid : base " << B << "\n";
        const auto& shape = (numbers::Shape<float,3,B + 1,float>&)pyramid;
        const auto& base = (numbers::Triangle<float,3,float>&)shape;
        const auto& cusp = shape[B];
        pyramid.printLn(std::cout);
        base.printLn(std::cout);
        cusp.printLn(std::cout);
        draw(base);
        for(size_t i = 0; i < B; i++)
        {
            draw(base[i],cusp);
        }
    }

}

#endif // OCTETOS_AVERSO_SHAPES_HH
