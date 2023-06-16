
#include "v0.hh"

#include <0/shapes.hh>


namespace verso_here = oct::verso::v0;


int v0_init(void)
{


	return 0;
}
int v0_clean(void)
{


	return 0;
}


void v0_developing()
{

}

void v0_math()
{
    verso_here::Point<int,2,float> p0;
    /*std::cout << std::endl;
    point1.print(std::cout);
    std::cout << std::endl;*/

    verso_here::Point<int,2,float> p2({1,1});
    /*std::cout << std::endl;
    point2.print(std::cout);
    std::cout << std::endl;*/

    verso_here::Point<int,2,float> p3(1,1);

    CU_ASSERT(p2 == p3);

    float slope1 = p0.slope(p2);
    CU_ASSERT(slope1 - 1.0 < infimium);
    //std::cout << "pendiente p0 -> p2 es " << slope1 << "\n";

    float scalar1 = p0 * p2;
    CU_ASSERT(scalar1 - 1.0 < infimium);


    verso_here::Point<int,2,float> p4(10,10);
    verso_here::Point<int,2,float> p5;
    p5.move(p4);
    CU_ASSERT(p5.x() == 10);
    CU_ASSERT(p5.y() == 10);
    //p5.print(std::cout);

    float dist1 = p0.distance(p5);
    //std::cout << "distancia p0 -> p5 es " << dist1 << "\n";
    CU_ASSERT(dist1 - 14.142135624 < infimium);

    oct::verso::v0::Line<int,2,float> line1;
    line1.set(p0,p5);
    //std::cout << std::endl;
    //line1.print(std::cout);
    line1.move(p4);
    //std::cout << std::endl;
    //line1.print(std::cout);


    oct::verso::v0::Line<int,2,float> line2;
    //std::cout << std::endl;
    //line2.print(std::cout);
    line2.resize(100);
    //std::cout << std::endl;
    //line2.print(std::cout);

    verso_here::Point<int,2,float> p6 {2,5};
    verso_here::Point<int,2,float> p7 {-1,2};
    verso_here::Point<int,2,float> p8 = p7.ortho();
    //std::cout << std::endl;
    //p8.print(std::cout);

    float compt1 = p6.comp(p7);
    //std::cout << "\nComponente de p6 sobre p7 es " << compt1 << "\n";
    CU_ASSERT(abs(compt1 - 3.5777) < infimium);

    float compt2 = p6.comp(p8);
    //std::cout << "\nComponente de p6 sobre p8 es " << compt2 << "\n";
    CU_ASSERT(abs(compt2  + 4.02492) < infimium);
}

void v0_opnegl_compatible()
{
    verso_here::Point<int,2,float> p2D {0,0};
    CU_ASSERT(sizeof(p2D) == sizeof(int) * 2);//compilble with opengl array

    verso_here::Point<int,3,float> p3D {0,0,0};
    CU_ASSERT(sizeof(p3D) == sizeof(int) * 3);//compilble with opengl array
}





