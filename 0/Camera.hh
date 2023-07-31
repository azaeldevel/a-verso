
#ifndef OCTETOS_AVERSO_CAMERA_HH
#define OCTETOS_AVERSO_CAMERA_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif


#include <core/3/Exception.hh>

namespace oct::verso::v0
{
    namespace core_here = oct::core::v3;

    class Camera
    {
    public:
        Camera() = default;
        Camera(const glm::vec3& position,const glm::vec3& target);

        void set(const glm::vec3& position,const glm::vec3& target);

        float& zoom();
        const float& zoom() const;

        operator glm::mat4&();

        void walking_front(float);
        void walking_back(float);
        void walking_left(float);
        void walking_right(float);
        void walking_up(float);
        void walking_down(float);

        void angle(float);

    private:
        glm::vec3 position,target,direction,rigth,up;
        glm::vec3 front;
        glm::mat4 view;
        float _zoom; //field of view , zoom

        const float sensitivy =  1.1f;
    };
}

#endif // OCTETOS_AVERSO_SHAPES_HH
