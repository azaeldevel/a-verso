
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
template<> Point<int,3,float>::Point()
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
template<> Point<int,3,float>::Point(int x, int y, int z)
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





template<> Point<int,2,float>::Point(std::initializer_list<int> l)
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
template<> Point<int,3,float>::Point(std::initializer_list<int> l)
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
template<> Point<int,4,float>::Point(std::initializer_list<int> l)
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

}
