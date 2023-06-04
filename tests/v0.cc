
#include "v0.hh"

#include <0/shapes.hh>


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

    oct::verso::v0::Point<int,2,float> p0;
    /*std::cout << std::endl;
    point1.print(std::cout);
    std::cout << std::endl;*/

    oct::verso::v0::Point<int,2,float> p2({1,1});
    /*std::cout << std::endl;
    point2.print(std::cout);
    std::cout << std::endl;*/

    oct::verso::v0::Point<int,2,float> p3(1,1);

    CU_ASSERT(p2 == p3);


    float slope1 = p0.slope(p2);
    CU_ASSERT(slope1 - 1.0 < infimium);
    //std::cout << "pendiente p0 -> p2 es " << slope1 << "\n";

    float scalar1 = p0 * p2;
    CU_ASSERT(scalar1 - 1.0 < infimium);


    oct::verso::v0::Line<int,2,float> line1;
}





