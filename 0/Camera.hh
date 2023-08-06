
#ifndef OCTETOS_AVERSO_CAMERA_HH
#define OCTETOS_AVERSO_CAMERA_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif


#include <core/3/Exception.hh>
#include "shapes.hh"

namespace oct::verso::v0
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

#endif // OCTETOS_AVERSO_SHAPES_HH
