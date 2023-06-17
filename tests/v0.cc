
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
    verso_here::Point<int,3,float> O;

    verso_here::Point<int,2,float> p2 {1,1};
    /*std::cout << std::endl;
    point2.print(std::cout);
    std::cout << std::endl;*/

    verso_here::Point<int,2,float> p3(1,1);

    CU_ASSERT(p2 == p3);

    verso_here::Point<int,2,float> p6 {2,5};
    verso_here::Point<int,2,float> p7 {-1,2};
    //std::cout << std::endl;
    //p8.print(std::cout);

}

void v0_opnegl_compatible()
{
    glm::vec3 vect1(0,1,2);
    verso_here::Point<int,3,float> p0(vect1);
    CU_ASSERT(p0[0] == 0);
    CU_ASSERT(p0[1] == 1);
    CU_ASSERT(p0[2] == 2);
    CU_ASSERT(sizeof(p0) == sizeof(int) * 3);


    glm::vec4 vect2(0,1,2,3);
    verso_here::Point<int,4,float> p1(vect2);
    CU_ASSERT(p1[0] == 0);
    CU_ASSERT(p1[1] == 1);
    CU_ASSERT(p1[2] == 2);
    CU_ASSERT(p1[3] == 3);
    CU_ASSERT(sizeof(p1) == sizeof(int) * 4);
}

void v0_cpp_features()
{
}


void v0_glm_compatible()
{

}



