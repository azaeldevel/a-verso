
#ifndef OCTETOS_AVERSO_CAMERA_HH
#define OCTETOS_AVERSO_CAMERA_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif

#include "common.hh"
#include <core/3/Exception.hh>
#include "shapes.hh"
#include <numbers/0/matrix.hh>

namespace oct::verso::v0::v1
{

    GLM_FUNC_DECL glm::mat4 lookAt (glm::vec3 const &eye, glm::vec3 const &center, glm::vec3 const &up);
    template<class T> GLM_FUNC_DECL glm::mat4	perspective (T const &fovy, T const &aspect, T const &near, T const &far)
    {
        return glm::perspective(fovy,aspect,near,far);
    }


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

        void lookAt();
        void lookAt(const numbers::vector<float,3>& position,const numbers::vector<float,3>& target);
        numbers::matrix<float,4,4,float> projection();

        void perspective(double fov,double aspect,double near,double far);
        void orthogonal(double left,double right,double bottom,double top,double nearVal,double farVal);

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
        Camera(const numbers::vector<float,3>& position,const numbers::vector<float,3>& target);

        glm::mat4 lookAt(const numbers::vector<float,3>& position,const numbers::vector<float,3>& target);

        operator glm::mat4&();

        void walking_front(float);
        void walking_back(float);
        void walking_left(float);
        void walking_right(float);
        void walking_up(float);
        void walking_down(float);

    private:
        numbers::vector<float,3> position,target,direction,rigth,up,front;
        glm::mat4 view;


    private:
        glm::mat4& lookAt();
    };
}
namespace oct::verso::v0
{
}

#endif // OCTETOS_AVERSO_SHAPES_HH
