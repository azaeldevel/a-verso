
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

template<> Point<int,2,float>::Point(int x, int y)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,2,float>::Point(int x, int y)\n";
#endif*/
    point[0] = x;
    point[1] = y;
}
template<> Point<int,3,float>::Point(int x, int y,int z)
{
/*#ifdef OCTETOS_AVERSO_TTD
    std::cout << "template<> Point<int,3,float>::Point(int x, int y,int z)\n";
#endif*/
    point[0] = x;
    point[1] = y;
    point[2] = z;
}

}
