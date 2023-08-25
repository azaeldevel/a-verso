
#ifndef OCTETOS_AVERSO_CAMERA_HH
#define OCTETOS_AVERSO_CAMERA_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif


#include <core/3/Exception.hh>
#include "shapes.hh"
#include <numbers/0/matrix.hh>

namespace oct::verso::v0::v1
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const numbers::vector<float,3>& position,const numbers::vector<float,3>& target);

        void set(const numbers::vector<float,3>& position,const numbers::vector<float,3>& target);

        void walking_front(float);
        void walking_back(float);
        void walking_left(float);
        void walking_right(float);
        void walking_up(float);
        void walking_down(float);
        //
        void rotate_up(float);

        //numbers::matrix<float,4,4,float>& lookAt();
        void lookAt();
        void lookAt(const numbers::vector<float,3>& position,const numbers::vector<float,3>& target);

        void perspective(double fov,double aspect,double near,double far);

    private:
        numbers::vector<float,3> position,target,direction,rigth,up,front;
        //numbers::matrix<float,4,4,float> view;

    };
}
namespace oct::verso::v0::v2
{
    //namespace core_here = oct::core::v3;

    class Camera
    {
    public:
        Camera() = default;
        Camera(const Point<float,3>& position,const Point<float,3>& target);

        void set(const Point<float,3>& position,const Point<float,3>& target);

        float& zoom();
        const float& zoom() const;

        operator glm::mat4&();

        void walking_front(float);
        void walking_back(float);
        void walking_left(float);
        void walking_right(float);
        void walking_up(float);
        void walking_down(float);

    private:
        Point<float,3> position,target,direction,rigth,up;
        Point<float,3> front;
        glm::mat4 view;
        float _zoom; //field of view , zoom

        const float sensitivy =  1.1f;

    private:
        glm::mat4 lookAt();
    };
}
namespace oct::verso::v0
{
}

#endif // OCTETOS_AVERSO_SHAPES_HH
