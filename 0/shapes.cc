
#include "shapes.hh"

namespace oct::verso::v0
{



template<> Point<int,2,float>::Point(int p[2])
{
    vector::x = p[0];
    vector::y = p[1];
}
template<> Point<int,3,float>::Point(int p[3])
{
    vector::x = p[0];
    vector::y = p[1];
    vector::z = p[1];
}


template<> Point<int,2,float>::Point(std::initializer_list<int>& l)
{
    if(l.size() > 2) throw core_here::exception("La cantidad de datos indicados excede la capacidad del objetos");
    unsigned char i = 0;

    for(const int& c : l)
    {
        switch(i)
        {
        case 0:
            vector::x = c;
            break;
        case 1:
            vector::y = c;
            break;
        default:
            ;
        }
        i++;
    }
}
template<> Point<int,3,float>::Point(std::initializer_list<int>& l)
{
    if(l.size() > 3) throw core_here::exception("La cantidad de datos indicados excede la capacidad del objetos");
    unsigned char i = 0;

    for(const int& c : l)
    {
        switch(i)
        {
        case 0:
            vector::x = c;
            break;
        case 1:
            vector::y = c;
            break;
        case 2:
            vector::z = c;
            break;
        default:
            ;
        }
        i++;
    }
}
template<> Point<int,4,float>::Point(std::initializer_list<int>& l)
{
    if(l.size() > 4) throw core_here::exception("La cantidad de datos indicados excede la capacidad del objetos");
    unsigned char i = 0;

    for(const int& c : l)
    {
        switch(i)
        {
        case 0:
            vector::x = c;
            break;
        case 1:
            vector::y = c;
            break;
        case 2:
            vector::z = c;
            break;
        case 3:
            vector::w = c;
            break;
        default:
            ;
        }
        i++;
    }
}


}
