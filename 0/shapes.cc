
#include "shapes.hh"

namespace oct::verso::v0
{


/*
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
}*/

/*
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
*/


template<> constexpr Point<int,2,float>& Point<int,2,float>::operator = (const Point<int,2,float>& p)
{
    BASE::x = p.x;
    BASE::y = p.y;

    return *this;
}
template<> constexpr Point<float,2>& Point<float,2,float>::operator = (const Point<float,2>& p)
{
    BASE::x = p.x;
    BASE::y = p.y;


    return *this;
}
template<> constexpr Point<int,3,float>& Point<int,3,float>::operator = (const Point<int,3,float>& p)
{
    BASE::x = p.x;
    BASE::y = p.y;
    BASE::z = p.z;

    return *this;
}
template<> constexpr Point<float,3>& Point<float,3,float>::operator = (const Point<float,3>& p)
{
    BASE::x = p.x;
    BASE::y = p.y;
    BASE::z = p.z;

    return *this;
}

template<> constexpr Point<int,2,float>& Point<int,2,float>::operator = (const glm::vec<2,int,glm::packed_highp>& p)
{
    BASE::x = p.x;
    BASE::y = p.y;

    return *this;
}
template<> constexpr Point<int,3,float>& Point<int,3,float>::operator = (const glm::vec<3,int,glm::packed_highp>& p)
{
    BASE::x = p.x;
    BASE::y = p.y;
    BASE::z = p.z;

    return *this;
}
template<> constexpr Point<float,3>& Point<float,3>::operator = (const glm::vec<3,float,glm::packed_highp>& p)
{
    BASE::x = p.x;
    BASE::y = p.y;
    BASE::z = p.z;

    return *this;
}




/*
template<> float Point<int,2,float>::length() const
{
    float d = 0;

    d +=  pow(vector::x,2);
    d +=  pow(vector::y,2);

    return sqrt(d);
}
template<> float Point<float,2,float>::length() const
{
    float d = 0;

    d +=  pow(vector::x,2);
    d +=  pow(vector::y,2);

    return sqrt(d);
}

template<> float Point<int,3,float>::length() const
{
    float d = 0;

    d +=  pow(vector::x,2);
    d +=  pow(vector::y,2);
    d +=  pow(vector::z,2);

    return sqrt(d);
}
template<> float Point<float,3,float>::length() const
{
    float d = 0;

    d +=  pow(vector::x,2);
    d +=  pow(vector::y,2);
    d +=  pow(vector::z,2);

    return sqrt(d);
}*/




#ifdef OCTETOS_AVERSO_TTD
    /*template<> void Point<int,3,float>::print(std::ostream& out)const
    {
        out << "(";
            out << vector::x << ",";
            out << vector::y;
            out << "," << vector::z;
        out << ")";
    }
    template<> void Point<float,3,float>::print(std::ostream& out)const
    {
        out << "(";
            out << vector::x << ",";
            out << vector::y;
            out << "," << vector::z;
        out << ")";
    }

    template<> void Point<int,3,float>::printLn(std::ostream& out)const
    {
        out << "(";
            out << vector::x << ",";
            out << vector::y;
            out << "," << vector::z;
        out << ")\n";
    }
    template<> void Point<float,3,float>::printLn(std::ostream& out)const
    {
        out << "(";
            out << vector::x << ",";
            out << vector::y;
            out << "," << vector::z;
        out << ")\n";
    }*/
#endif // OCTETOS_AVERSO_TTD
}
