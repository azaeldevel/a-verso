

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

#include "Camera.hh"
namespace oct::verso::v0
{
    Camera::Camera(const Point<float,3>& p,const Point<float,3>& t)
        :
        position(p),
        target(t),
        direction(nums_here::normalize(position - target)),
        rigth(nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction)),
        up(nums_here::normalize(direction * rigth)),
        front(nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f))),
        view(lookAt(position,target,up)),
        _zoom(45.0f)
    {
    }

    void Camera::set(const Point<float,3>& p,const Point<float,3>& t)
    {
        position = p;
        target = t;
        direction = nums_here::normalize(position-target);
        rigth = nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction);
        up = nums_here::normalize(direction * rigth);
        front = nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f));
        view = lookAt(position,target,up);
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
        view = lookAt(position,target,up);
    }
    void Camera::walking_back(float speed)
    {
        position -= front * speed * sensitivy;
        view = lookAt(position,target,up);
    }
    void Camera::walking_left(float speed)
    {
        position += nums_here::normalize(front* up) * speed;
        view = lookAt(position,target,up);
    }
    void Camera::walking_right(float speed)
    {
        position -= nums_here::normalize(front* up) * speed * sensitivy;
        view = lookAt(position,target,up);
    }
    void Camera::walking_up(float speed)
    {
        position += up * speed * sensitivy;
        view = lookAt(position,target,up);
    }
    void Camera::walking_down(float speed)
    {
        position -= up * speed * sensitivy;
        view = lookAt(position,target,up);
    }

    glm::mat4 Camera::lookAt(const Point<float,3>& p,const Point<float,3>& t,const Point<float,3>& u)
    {
        glm::mat4 mat;
        //mat = glm::lookAt(position,target,up);

        return mat;
    }


    void Camera::angle(float t)
    {


    }



}

