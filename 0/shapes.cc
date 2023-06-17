
#include "shapes.hh"

namespace oct::verso::v0
{

template<> Point<int,2,float>::Point()
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point()\n";
#endif*/
    point[0] = 0;
    point[1] = 0;
}
template<> Point<float,2,float>::Point()
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point()\n";
#endif*/
    point[0] = 0;
    point[1] = 0;
}
template<> Point<int,3,float>::Point()
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point()\n";
#endif*/
    point[0] = 0;
    point[1] = 0;
    point[2] = 0;
}
template<> Point<float,3,float>::Point()
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point()\n";
#endif*/
    point[0] = 0;
    point[1] = 0;
    point[2] = 0;
}
template<> Point<int,4,float>::Point()
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point()\n";
#endif*/
    point[0] = 0;
    point[1] = 0;
    point[2] = 0;
    point[3] = 0;
}

template<> Point<int,2,float>::Point(int p[2])
{
    for(unsigned char i = 0; i < 2; i++)
    {
        point[i] = p[i];
    }
}
template<> Point<int,3,float>::Point(int p[3])
{
    for(unsigned char i = 0; i < 3; i++)
    {
        point[i] = p[i];
    }
}
template<> Point<int,4,float>::Point(int p[4])
{
    for(unsigned char i = 0; i < 4; i++)
    {
        point[i] = p[i];
    }
}

template<> Point<int,2,float>::Point(int x, int y)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point(int x, int y)\n";
#endif*/
    point[0] = x;
    point[1] = y;
}
template<> Point<int,3,float>::Point(int x, int y)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point(int x, int y)\n";
#endif*/
    point[0] = x;
    point[1] = y;
    point[2] = 0;
}
template<> Point<float,3,float>::Point(float x, float y)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point(int x, int y)\n";
#endif*/
    point[0] = x;
    point[1] = y;
    point[2] = 0;
}
template<> Point<int,3,float>::Point(int x, int y, int z)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(int x, int y,int z)\n";
#endif*/
    point[0] = x;
    point[1] = y;
    point[2] = z;
}
template<> Point<float,3,float>::Point(float x, float y, float z)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(int x, int y,int z)\n";
#endif*/
    point[0] = x;
    point[1] = y;
    point[2] = z;
}
template<> Point<int,4,float>::Point(int x, int y,int z,int w)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(int x, int y,int z,int w)\n";
#endif*/
    point[0] = x;
    point[1] = y;
    point[2] = z;
    point[3] = w;
}


template<> Point<int,2,float>::Point(const Point<int,2,float>& p)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(int x, int y,int z,int w)\n";
#endif*/
    point[0] = p.point[0];
    point[1] = p.point[1];
}
template<> Point<float,2,float>::Point(const Point<float,2,float>& p)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(int x, int y,int z,int w)\n";
#endif*/
    point[0] = p.point[0];
    point[1] = p.point[1];
}
template<> Point<int,3,float>::Point(const Point<int,3,float>& p)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(int x, int y,int z,int w)\n";
#endif*/
    point[0] = p.point[0];
    point[1] = p.point[1];
    point[2] = p.point[2];
}
template<> Point<float,3,float>::Point(const Point<float,3,float>& p)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(int x, int y,int z,int w)\n";
#endif*/
    point[0] = p.point[0];
    point[1] = p.point[1];
    point[2] = p.point[2];
}





template<> Point<int,2,float>::Point(std::initializer_list<int>& l)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point(std::initializer_list<int> l)\n";
#endif*/
    unsigned char i = 0;
    for(const int& c : l)
    {
        point[i] = c;
        i++;
    }
}
template<> Point<int,3,float>::Point(std::initializer_list<int>& l)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(std::initializer_list<int> l)\n";
#endif*/
    unsigned char i = 0;
    for(const int& c : l)
    {
        point[i] = c;
        i++;
    }
}
template<> Point<int,4,float>::Point(std::initializer_list<int>& l)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,4,float>::Point(std::initializer_list<int> l)\n";
#endif*/
    unsigned char i = 0;
    for(const int& c : l)
    {
        point[i] = c;
        i++;
    }
}

template<> Point<int,3,float>::Point(const glm::vec<3,int,glm::packed_highp>& v)
{
    for(size_t i = 0; i < 3; i++)
    {
        point[i] = v[i];
    }
}
template<> Point<int,4,float>::Point(const glm::vec<4,int,glm::packed_highp>& v)
{
    point[0] = v[0];
    point[1] = v[1];
    point[2] = v[2];
    point[3] = v[3];
}
template<> Point<float,3,float>::Point(const glm::vec<3,float,glm::packed_highp>& v)
{
    for(size_t i = 0; i < 3; i++)
    {
        point[i] = v[i];
    }
}





template<> Point<int,3,float>& Point<int,3,float>::operator =(const glm::vec<3,int,glm::packed_highp>& v)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,4,float>::Point(std::initializer_list<int> l)\n";
#endif*/
    point[0] = v[0];
    point[1] = v[1];
    point[2] = v[2];

    return *this;
}
template<> Point<int,4,float>& Point<int,4,float>::operator =(const glm::vec<4,int,glm::packed_highp>& v)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,4,float>::Point(std::initializer_list<int> l)\n";
#endif*/
    point[0] = v[0];
    point[1] = v[1];
    point[2] = v[2];
    point[3] = v[3];

    return *this;
}
template<> Point<float,3,float>& Point<float,3,float>::operator =(const glm::vec<3,float,glm::packed_highp>& v)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<float,3,float>& Point<float,3,float>::operator =(const glm::vec<3,float,glm::packed_highp>& v)\n";
#endif*/
    for(size_t i = 0; i < 3; i++)
    {
        point[i] = v[i];
    }

    return *this;
}





template<> Point<int,2,float> Point<int,2,float>::normal() const
{
    Point v;
    v.point[0] = point[1] * -1;
    v.point[1] = point[0];

    return v;
}
template<> Point<float,2,float> Point<float,2,float>::normal() const
{
    Point v;
    v.point[0] = point[1] * -1;
    v.point[1] = point[0];

    return v;
}

/**
*
*
*/
template<> Point<int,3,float> Point<int,3,float>::normal() const
{
    Point v;
    core_here::exception("En desarrollo.");

    return v;
}
/**
*
*
*/
template<> Point<float,3,float> Point<float,3,float>::normal() const
{
    Point v;
    core_here::exception("En desarrollo.");

    return v;
}




template<> int Point<int,2,float>::z() const
{
    return 0;
}
template<> int Point<int,3,float>::z() const
{
    return point[2];
}
template<> float Point<float,3,float>::z() const
{
    return point[2];
}

template<> int& Point<int,3,float>::z()
{
    return point[2];
}
template<> float& Point<float,3,float>::z()
{
    return point[2];
}


template<> int&  Point<int,2,float>::operator [] (unsigned char i)
{
    return point[i];
}
template<> int&  Point<int,3,float>::operator [] (unsigned char i)
{
    return point[i];
}

template<> const int& Point<int,2,float>::operator [] (unsigned char i) const
{
    return point[i];
}
template<> const int& Point<int,3,float>::operator [] (unsigned char i) const
{
    return point[i];
}

template<> Point<int,2,float>::operator int*()
{
    return point;
}
template<> Point<int,3,float>::operator int*()
{
    return point;
}

template<> Point<int,2,float>::operator const int*() const
{
    return point;
}
template<> Point<int,3,float>::operator const int*() const
{
    return point;
}


template<> bool Point<int,3,float>::is_plane_xy() const
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

/*
template<> void circle(const Point<int,3,float>& center,float radio,const Point<float,3,float>& delta,std::vector<Point<int,3,float>>& rest)
{

#ifdef OCTETOS_AVERSO_TTD
    float lu = delta.length();
    if(1.0 - abs(lu) > 0.001) core_here::exception("El vector delta debe se un vector unitario");
#endif // OCTETOS_AVERSO_TTD

    if(delta.is_plane_xy())//plano x,y
    {
        float dp = delta.length();
        //primer cuadrante
        std::cout << "primer cuadrante\n";
        rest.push_back(Point<int,3,float>(radio,0));
        while(rest.back().x() > 0)
        {
            rest.push_back(rest.back());
            rest.back().x() -= dp;
            rest.back().y() += dp;
            rest.back().printLn(std::cout);
        }

        //segundo cuadrante
        std::cout << "segundo cuadrante\n";
        while(rest.back().y() > 0)
        {
            rest.push_back(rest.back());
            rest.back().x() -= dp;
            rest.back().y() -= dp;
            rest.back().printLn(std::cout);
        }

        //tercer cuadrante
        std::cout << "tercer cuadrante\n";
        while(rest.back().x() < 0)
        {
            rest.push_back(rest.back());
            rest.back().x() += dp;
            rest.back().y() -= dp;
            rest.back().printLn(std::cout);
        }

        //cuarto cuadrante
        std::cout << "cuarto cuadrante\n";
        while(rest.back().y() < 0)
        {
            rest.push_back(rest.back());
            rest.back().x() += dp;
            rest.back().y() += dp;
            rest.back().printLn(std::cout);
        }
    }
    else
    {
        core_here::exception("Plano de dibujo desconocido");
    }
}*/



}
