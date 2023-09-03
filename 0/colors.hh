
#ifndef OCTETOS_AVERSO_COLORS_HH
#define OCTETOS_AVERSO_COLORS_HH

#include "common.hh"

namespace oct::verso::v0
{
    template<numbers::number T = float, size_t L = 4> class Color : public core::array<T,L>
    {
    private:
        typedef core::array<T,L> BASE;
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

        operator Color<float,L>()
        {
            Color<float,L> newcolor;
            for(size_t i = 0; i < L; i++) newcolor[i] = float(BASE::data[i]) / float(255);
            return newcolor;
        }
    };


    template<numbers::number T> class RGB : public Color<T,3>
    {
    private:
        typedef Color<T,3> BASE;
    public:
        RGB() = default;
        constexpr RGB(const T& v) : BASE(v)
        {
        }
        constexpr RGB(const RGB& v) : BASE(v)
        {
        }
        constexpr RGB(const std::initializer_list<T>& l) : BASE(l)
        {
        }

        /*
        void active() const
        {
            glColor3f(BASE::data[0],BASE::data[1],BASE::data[2]);
        }
        */
    };

    template<numbers::number T> class RGBA : public Color<T,4>
    {
    private:
        typedef Color<T,4> BASE;
    public:
        RGBA() = default;
        constexpr RGBA(const T& v) : BASE(v)
        {
        }
        constexpr RGBA(const RGBA& v) : BASE(v)
        {
        }
        constexpr RGBA(const std::initializer_list<T>& l) : BASE(l)
        {
        }


        /*
        void active() const
        {
            glColor4f(BASE::data[0],BASE::data[1],BASE::data[2],BASE::data[3]);
        }
        */


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
        constexpr const T& a() const
        {
            return BASE::data[3];
        }

        operator RGBA<float>()
        {
            RGBA<float> newcolor;
            for(size_t i = 0; i < 4; i++) newcolor[i] = float(BASE::data[i]) / float(255);
            return newcolor;
        }
    };


    namespace colors
    {
        static const RGBA<unsigned char> red    {255,0,0,255};
        static const RGBA<unsigned char> green  {0,255,0,255};
        static const RGBA<unsigned char> blue   {0,0,255,255};
        static const RGBA<unsigned char> black  {0,0,0,255};
        static const RGBA<unsigned char> white  {255,255,255,255};
        static const RGBA<unsigned char> gray   {20,20,20,255};

        //themes
        //static const Color<int> rgba{255,255,255,1};
        static const RGBA<unsigned char> coordenade {200,200,180,150};
        static const RGBA<unsigned char> empty {0,0,0,255};
    }

}

#endif
