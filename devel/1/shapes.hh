
#ifndef OCTETOS_AVERSO_V1_SHAPES_HH
#define OCTETOS_AVERSO_V1_SHAPES_HH

#include <numbers/0/shapes.hh>
#include "colors.hh"


namespace oct::verso::v1
{


    /*
                P1-------P2
                |        |
                |        |
                |        |
                P4-------P3
    */
    /**
    *\brief Cuadrilatero
    *\param C tipo de dato para la coordenada
    *\param D dimension del espacio
    *\param V Tipo de datos para calculos
    **/
    template<core::number C, core::index auto D = 3, core::index auto P = 6,core::number V = C>
    class Rectangle : public numbers::Plane<C,D,P,V>
    {
    public:
        typedef numbers::Plane<C,D,P,V> BASE;
    public:
        Rectangle() = default;

        /**
        *\brief Contrulle un triangulo con los 3 puntos indicados
        **/
        constexpr Rectangle(const numbers::vector<C,D> vs[4]) : BASE(vs)
        {
        }

        /**
        *\brief Contrulle un triangulo equilatero con centro geometro en O y la longitud indicada
        **/
        constexpr Rectangle(const numbers::vector<C,D>& O, const C& length)
        {
            create(O,length);
        }


        /**
        *\brief Contrulle un rectangulo con centro geometro en O y la longitud indicada
        **/
        constexpr void create(const numbers::vector<C,D>& O, const C& length)//const C& height, const C& width
        {
            V m = length / V(2);

            //asignado coordenas en x
            BASE::data[0][0] = O.x() - m;
            BASE::data[1][0] = O.x() + m;
            BASE::data[2][0] = O.x() - m;
            //second triangle
            if constexpr(P == 6)
            {
                BASE::data[3][0] = O.x() + m;
                BASE::data[4][0] = O.x() + m;
                BASE::data[5][0] = O.x() - m;
            }
            else if constexpr(P == 4)
            {
                BASE::data[3][0] = O.x() - m;
            }

            //asignado coordenas en y
            BASE::data[0][1] = O.y() + m;
            BASE::data[1][1] = O.y() + m;
            BASE::data[2][1] = O.y() - m;
            //second triangle
            if constexpr(P == 6)
            {
                BASE::data[3][1] = O.y() + m;
                BASE::data[4][1] = O.y() - m;
                BASE::data[5][1] = O.y() - m;
            }
            else if constexpr(P == 4)
            {
                BASE::data[3][1] = O.y() - m;

            }

            //asignado coordenas en z
            if constexpr(D == 3)
            {
                BASE::data[0][2] = 0;
                BASE::data[1][2] = 0;
                BASE::data[2][2] = 0;
                BASE::data[3][2] = 0;
                BASE::data[4][2] = 0;
                BASE::data[5][2] = 0;
            }
        }

        /**
        *\brief Contrulle un rectangulo con centro geometro en O y la longitudes indicadas
        **/
        constexpr void create(const numbers::vector<C,D>& O, const C& height, const C& width)//const C& height, const C& width
        {
            V w = width / V(2);
            V h = height / V(2);

            //asignado coordenas en x
            BASE::data[0][0] = O.x() - w;
            BASE::data[1][0] = O.x() + w;
            BASE::data[2][0] = O.x() - w;
            //second triangle
            if constexpr(P == 6)
            {
                BASE::data[3][0] = O.x() + w;
                BASE::data[4][0] = O.x() + w;
                BASE::data[5][0] = O.x() - w;
            }
            else if constexpr(P == 4)
            {
                BASE::data[3][0] = O.x() - w;
            }

            //asignado coordenas en y
            BASE::data[0][1] = O.y() + h;
            BASE::data[1][1] = O.y() + h;
            BASE::data[2][1] = O.y() - h;
            //second triangle
            if constexpr(P == 6)
            {
                BASE::data[3][1] = O.y() + h;
                BASE::data[4][1] = O.y() - h;
                BASE::data[5][1] = O.y() - h;
            }
            else if constexpr(P == 4)
            {
                BASE::data[3][1] = O.y() - h;

            }

            //asignado coordenas en z
            if constexpr(D == 3)
            {
                BASE::data[0][2] = 0;
                BASE::data[1][2] = 0;
                BASE::data[2][2] = 0;
                BASE::data[3][2] = 0;
                BASE::data[4][2] = 0;
                BASE::data[5][2] = 0;
            }
        }

    };

}

#endif
