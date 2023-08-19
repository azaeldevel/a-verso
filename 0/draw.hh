
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

    template<numbers::number T = float, size_t L = 3> class Color : public numbers::sequence<T,L>
    {
    private:
        typedef numbers::sequence<T,L> BASE;
    public:
        Color() = default;
        constexpr Color(const T& v) : BASE(v)
        {
        }
        /*
        constexpr vector(const T v[L]) : sequence<T,L>(v)
        {
        }
        */
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


        constexpr T& r()
        {
            return BASE::data[0];
        }
        constexpr const T& r() const
        {
            return BASE::data[0];
        }
        constexpr T& g()
        {
            return BASE::data[1];
        }
        constexpr const T& g() const
        {
            return BASE::data[1];
        }
        constexpr T& b()
        {
            return BASE::data[2];
        }
        constexpr const T& b() const
        {
            return BASE::data[2];
        }


    };

    namespace colors
    {
        static const Color<float,3> red{1.0f,0.0f,0.0f};
        static const Color<float,3> green{0.0f,1.0f,0.0f};
        static const Color<float,3> blue{0.0f,0.0f,1.0f};
    }

    void outline(const numbers::Line<float,3,float>&);

    void outline(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2);

    void outline(const numbers::Triangle<float,2,float>& triangle);
    void outline(const numbers::Triangle<float,3,float>& triangle);
    void outline_triangle(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1, const numbers::vector<float,3,float>& p2, const Color<float,3>& c);
    void outline_triangle(const numbers::Line<float,3,float>& base, const numbers::vector<float,3,float>& cusp, const Color<float,3>& c);

    void outline(const numbers::vector<float,3,float>& p0, const numbers::vector<float,3,float>& p1);

    template<size_t B> void outline(const numbers::Pyramid<float,3,B,float>& pyramid)
    {
        //std::cout << "Drawing pyramid : base " << B << "\n";
        Color<float,3> color(0);
        const auto& shape = (numbers::Shape<float,3,B + 1,float>&)pyramid;
        const auto& base = (numbers::Triangle<float,3,float>&)shape;
        const auto& cusp = shape[B];
        outline(base);
        for(size_t i = 0; i < B; i++)
        {
            color[i] = 1.0f;
            outline_triangle(shape[i],shape[i+1],cusp,color);
            //draw_triangle(shape.from(2,i),cusp,color);
            outline(base[i],cusp);
            color[i] = 0.0f;
        }
        outline_triangle(shape[B - 1],shape[0],cusp,color);
    }

    void outline(const numbers::Rectangle<float,3,float>&);


    template<size_t P>void outline(const numbers::Circle<float,3,P>& circle,const Color<float,3>& color)
    {
        glBegin(GL_LINE_LOOP);
            glColor3f(color.r(),color.g(),color.b());
            for(size_t i = 1; i < circle.size(); i++)
            {
                //glVertex3f(circle[i-1].x(),circle[i-1].y(),circle[i-1].z());
                glVertex3f(circle[i].x(),circle[i].y(),circle[i].z());
            }
        glEnd();
    }
}

#endif // OCTETOS_AVERSO_SHAPES_HH
