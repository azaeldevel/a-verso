
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
    verso_here::Point<int,2,float> p8 = p7.normal();
    //std::cout << std::endl;
    //p8.print(std::cout);

    float compt1 = p6.comp(p7);
    //std::cout << "\nComponente de p6 sobre p7 es " << compt1 << "\n";
    CU_ASSERT(abs(compt1 - 3.5777) < infimium);

    float compt2 = p6.comp(p8);
    //std::cout << "\nComponente de p6 sobre p8 es " << compt2 << "\n";
    CU_ASSERT(abs(compt2  + 4.02492) < infimium);

    std::vector<verso_here::Point<float,3,float>> circle_1;
    verso_here::Point<float,3,float> cricle_delta(8,9,0);
    cricle_delta.unit();
    CU_ASSERT(cricle_delta.length() - 1.0 < infimium);
    //cricle_delta.printLn(std::cout);
    verso_here::circle(O,10.0f,cricle_delta,circle_1);
    CU_ASSERT(circle_1.size() == 41);
    //std::cout << "size : " << circle_1.size() << "\n";
    /*for(const verso_here::Point<int,3,float>& p : circle_1)
    {
        p.printLn(std::cout);
    }*/


    std::vector<verso_here::Point<float,3,float>> camera_path;
    verso_here::Point<float,3,float> camera_path_delta;
    camera_path_delta = glm::vec3(8,9,0);
    camera_path_delta.unit();
    CU_ASSERT(camera_path_delta.length() - 1.0 < infimium);
    //std::cout << "Length : " << camera_path_delta.length()  << "\n";
    verso_here::circle(O,10.0f,camera_path_delta,camera_path);
    /*std::cout << "size : " << camera_path.size() << "\n";
    for(const verso_here::Point<float,3,float>& p : camera_path)
    {
        p.printLn(std::cout);
    }*/
}

void v0_opnegl_compatible()
{
    verso_here::Point<int,2,float> p2D {0,0};
    CU_ASSERT(sizeof(p2D) == sizeof(int) * 2);//compilble with opengl array

    verso_here::Point<int,3,float> p3D {0,0,0};
    CU_ASSERT(sizeof(p3D) == sizeof(int) * 3);//compilble with opengl array

    verso_here::Point<int,3,float> p3D_1 {0,1,2};
    CU_ASSERT(p3D_1[0] == 0);
    CU_ASSERT(p3D_1[1] == 1);
    CU_ASSERT(p3D_1[2] == 2);
    int* p3D_1_array = p3D_1;
    CU_ASSERT(p3D_1_array[0] == 0);
    CU_ASSERT(p3D_1_array[1] == 1);
    CU_ASSERT(p3D_1_array[2] == 2);
}

void v0_cpp_features()
{
    verso_here::Point<int,2,float> p2D_0;
    CU_ASSERT(p2D_0[0] == 0);
    CU_ASSERT(p2D_0[1] == 0);

    verso_here::Point<int,3,float> p3D_0;
    CU_ASSERT(p3D_0[0] == 0);
    CU_ASSERT(p3D_0[1] == 0);
    CU_ASSERT(p3D_0[2] == 0);

    verso_here::Point<int,4,float> p4D_0;
    CU_ASSERT(p4D_0[0] == 0);
    CU_ASSERT(p4D_0[1] == 0);
    CU_ASSERT(p4D_0[2] == 0);
    CU_ASSERT(p4D_0[3] == 0);


    verso_here::Point<int,2,float> p2D_1 {0,1};
    CU_ASSERT(p2D_1[0] == 0);
    CU_ASSERT(p2D_1[1] == 1);

    verso_here::Point<int,3,float> p3D_1 {0,1,2};
    CU_ASSERT(p3D_1[0] == 0);
    CU_ASSERT(p3D_1[1] == 1);
    CU_ASSERT(p3D_1[2] == 2);

    verso_here::Point<int,4,float> p4D_1 {0,1,2,3};
    CU_ASSERT(p4D_1[0] == 0);
    CU_ASSERT(p4D_1[1] == 1);
    CU_ASSERT(p4D_1[2] == 2);
    CU_ASSERT(p4D_1[3] == 3);



    verso_here::Point<int,2,float> p2D_2(0,1);
    CU_ASSERT(p2D_2[0] == 0);
    CU_ASSERT(p2D_2[1] == 1);

    verso_here::Point<int,3,float> p3D_2(0,1,2);
    CU_ASSERT(p3D_2[0] == 0);
    CU_ASSERT(p3D_2[1] == 1);
    CU_ASSERT(p3D_2[2] == 2);

    verso_here::Point<int,4,float> p4D_2(0,1,2,3);
    CU_ASSERT(p4D_2[0] == 0);
    CU_ASSERT(p4D_2[1] == 1);
    CU_ASSERT(p4D_2[2] == 2);
    CU_ASSERT(p4D_2[3] == 3);
}


void v0_glm_compatible()
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



