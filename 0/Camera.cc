
#include <GL/glu.h>

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

#include "Camera.hh"
namespace oct::verso::v0::v1
{
    Camera::Camera(const Point<float,3>& p,const Point<float,3>& t)
        :
        position(p),
        target(t),
        direction(nums_here::normalize(position - target)),
        rigth(nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction)),
        up(nums_here::normalize(direction * rigth)),
        front(nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f)))
    {
    }

    void Camera::set(const Point<float,3>& p,const Point<float,3>& t)
    {
        position = p;
        target = t;
        direction = nums_here::normalize(position - target);
        rigth = nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction);
        up = nums_here::normalize(direction * rigth);
        front = nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f));
    }

    void Camera::walking_front(float speed)
    {
        position += front * speed;
    }
    void Camera::walking_back(float speed)
    {
        position -= front * speed;
    }
    void Camera::walking_left(float speed)
    {
        position += nums_here::normalize(front * up) * speed;
    }
    void Camera::walking_right(float speed)
    {
        position -= nums_here::normalize(front * up) * speed;
    }
    void Camera::walking_up(float speed)
    {
        position += up * speed;
    }
    void Camera::walking_down(float speed)
    {
        position -= up * speed;
    }

    void Camera::lookAt()
    {
        gluLookAt((double)position.x(),(double)position.y(),(double)position.z(),(double)target.x(),(double)target.y(),(double)target.z(),(double)up.x(),(double)up.y(),(double)up.z());
    }

}
namespace oct::verso::v0::v2
{
    Camera::Camera(const Point<float,3>& p,const Point<float,3>& t)
        :
        position(p),
        target(t),
        direction(nums_here::normalize(position - target)),
        rigth(nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction)),
        up(nums_here::normalize(direction * rigth)),
        front(nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f))),
        view(lookAt()),
        _zoom(45.0f)
    {
    }

    void Camera::set(const Point<float,3>& p,const Point<float,3>& t)
    {
        position = p;
        target = t;
        direction = nums_here::normalize(position - target);
        rigth = nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction);
        up = nums_here::normalize(direction * rigth);
        front = nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f));
        view = lookAt();
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
        //position.printLn(std::cout);
        position += front * speed;

        view = lookAt();
        //position.printLn(std::cout);
        //std::cout << std::endl;
    }
    void Camera::walking_back(float speed)
    {
        position -= front * speed;
        view = lookAt();
    }
    void Camera::walking_left(float speed)
    {
        position += nums_here::normalize(front * up) * speed;
        view = lookAt();
    }
    void Camera::walking_right(float speed)
    {
        position -= nums_here::normalize(front * up) * speed;
        view = lookAt();
    }
    void Camera::walking_up(float speed)
    {
        position += up * speed * sensitivy;
        view = lookAt();
    }
    void Camera::walking_down(float speed)
    {
        position -= up * speed * sensitivy;
        view = lookAt();
    }

    glm::mat4 Camera::lookAt()
    {
        return glm::lookAt(reinterpret_cast<glm::vec3&>(position),reinterpret_cast<glm::vec3&>(target),reinterpret_cast<glm::vec3&>(up));
    }


}
