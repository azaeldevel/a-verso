
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
    verso_here::Point<int,2,float> p0{0,0};
    /*std::cout << std::endl;
    point1.print(std::cout);
    std::cout << std::endl;*/
    verso_here::Point<int,3,float> O{0,0,0};

    verso_here::Point<int,2,float> p2 {1,1};
    /*std::cout << std::endl;
    point2.print(std::cout);
    std::cout << std::endl;*/

    verso_here::Point<int,2,float> p3(1,1);

    CU_ASSERT(p2 == p3);

    verso_here::Point<float,2,float> p6 {2,5};
    verso_here::Point<float,2,float> p7 {-1,2};
    float comp_1 = p6.comp(p7);
    //std::cout << "Componente de (2,5) en la direccion de (-1,2) es " << comp_1 << std::endl;
    CU_ASSERT((8/sqrt(5)) - comp_1 < infimium);

    verso_here::Point<float,3,float> p9 {-1,2,3};
    verso_here::Point<float,3,float> p8{-1,2,3};
    p8.normalize();
    /*std::cout << "El vector normal de (-1,2,3) es ";
    p8.printLn(std::cout);*/
    CU_ASSERT(p8.length() - 1.0 < infimium);

    verso_here::Point<float,3,float> p10{2, 3, 1};
    verso_here::Point<float,3,float> p11{3, 1, -9};
    //verso_here::Point<float,3,float> p12 = p10 * p11;
    /*std::cout << "Producto crusado es ";
    p12.printLn(std::cout);*/


    const float v_triangle_1[3 * 3] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
    verso_here::Triangle<float,3,float> triangle1(v_triangle_1);
    //p1
    CU_ASSERT(triangle1[0][0] + 1.0f < infimium);
    CU_ASSERT(triangle1[0][1] + 1.0f < infimium);
    CU_ASSERT(triangle1[0][2] < infimium);
    //p2
    CU_ASSERT(triangle1[1][0] - 1.0f < infimium);
    CU_ASSERT(triangle1[1][1] + 1.0f < infimium);
    CU_ASSERT(triangle1[1][2] < infimium);

    const float v_cube_1[36 * 3] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
	};
    verso_here::Cube<float,3,float> cube1(v_cube_1);
    //p1
    CU_ASSERT(cube1[0][0] + 1.0f < infimium);
    CU_ASSERT(cube1[0][1] + 1.0f < infimium);
    CU_ASSERT(cube1[0][2] + 1.0f < infimium);
    //p36
    CU_ASSERT(cube1[35][0] - 1.0f < infimium);
    CU_ASSERT(cube1[35][1] + 1.0f < infimium);
    CU_ASSERT(cube1[35][2] - 1.0f < infimium);


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


    verso_here::Point<int,4,float> p2;
    p2 = vect2;
    CU_ASSERT(p2[0] == 0);
    CU_ASSERT(p2[1] == 1);
    CU_ASSERT(p2[2] == 2);
    CU_ASSERT(p2[3] == 3);
    CU_ASSERT(sizeof(p2) == sizeof(int) * 4);

    glm::vec3 vect3(0,9,7);
    verso_here::Point<int,3,float> p3(vect3);
    CU_ASSERT(p3[0] == 0);
    CU_ASSERT(p3[1] == 9);
    CU_ASSERT(p3[2] == 7);
    CU_ASSERT(sizeof(p3) == sizeof(int) * 3);
}

void v0_cpp_features()
{
}


void v0_glm_compatible()
{

}



