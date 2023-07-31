

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

#include "Camera.hh"
namespace oct::verso::v0
{
    Camera::Camera(const glm::vec3& p,const glm::vec3& t)
        :
        position(p),
        target(t),
        direction(glm::normalize(position-target)),
        rigth(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction))),
        up(glm::cross(direction, rigth)),
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        view(glm::lookAt(position,target,up)),
        _zoom(45.0f)
    {
    }

    void Camera::set(const glm::vec3& p,const glm::vec3& t)
    {
        position = p;
        target = t;
        direction = glm::normalize(position-target);
        rigth = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
        up = glm::normalize(glm::cross(direction, rigth));
        front = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
        view = glm::lookAt(position,target,up);
        _zoom = 45.0f;
    }

    float& Camera::zoom()
    {
        return _zoom;
    }
    const float& Camera::zoom() const
    {
        return _zoom;
    }

    Camera::operator glm::mat4&()
    {
        return view;
    }

    void Camera::walking_front(float speed)
    {
        position += front * speed * sensitivy;
        view = glm::lookAt(position,target,up);
    }
    void Camera::walking_back(float speed)
    {
        position -= front * speed * sensitivy;
        view = glm::lookAt(position,target,up);
    }
    void Camera::walking_left(float speed)
    {
        position += glm::normalize(glm::cross(front, up)) * speed;
        view = glm::lookAt(position,target,up);
    }
    void Camera::walking_right(float speed)
    {
        position -= glm::normalize(glm::cross(front, up)) * speed * sensitivy;
        view = glm::lookAt(position,target,up);
    }
    void Camera::walking_up(float speed)
    {
        position += up * speed * sensitivy;
        view = glm::lookAt(position,target,up);
    }
    void Camera::walking_down(float speed)
    {
        position -= up * speed * sensitivy;
        view = glm::lookAt(position,target,up);
    }


    void Camera::angle(float t)
    {
        glm::mat4 r = glm::mat4(1.0f);
        r[0] = glm::vec4(front.x,front.y,front.z,1.0f);
        r = glm::rotate(r, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        front.x = r[0].x;
        front.y= r[0].y;
        front.z = r[0].z;
    }



}

