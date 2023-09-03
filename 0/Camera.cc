
#include <GL/glu.h>

#ifdef OCTETOS_AVERSO_TTD
    #include <iostream>
#endif // OCTETOS_AVERSO_DEBUG

#include "Camera.hh"
namespace oct::verso::v0::v1
{
    GLM_FUNC_DECL glm::mat4 lookAt (glm::vec3 const &eye, glm::vec3 const &center, glm::vec3 const &up)
    {
        return glm::lookAt(eye,center,up);
    }

    /*numbers::matrix<float,4,4,float> Camera::projection()
    {
        numbers::vector<float,3, float> const f(numbers::normalize(target - position));
		numbers::vector<float,3, float> const s(numbers::normalize(up * f));
		numbers::vector<float,3, float> const u(f * s);

		numbers::matrix<float,4,4,float> Result(1);
		Result[0][0] = s.x();
		Result[1][0] = s.y();
		Result[2][0] = s.z();
		Result[0][1] = u.x();
		Result[1][1] = u.y();
		Result[2][1] = u.z();
		Result[0][2] = f.x();
		Result[1][2] = f.y();
		Result[2][2] = f.z();
		Result[3][0] = -numbers::scalar(s, position);
		Result[3][1] = -numbers::scalar(u, position);
		Result[3][2] = -numbers::scalar(f, position);
		return Result;
    }*/

    Camera::Camera(const numbers::vector<float,3>& p,const numbers::vector<float,3>& t)
        :
        position(p),
        target(t),
        direction(nums_here::normalize(position - target)),
        rigth(nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction)),
        up(nums_here::normalize(direction * rigth)),
        front(nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f)))
    {
    }

    void Camera::lookAt()
    {
        glLoadIdentity();
        gluLookAt((double)position.x(),(double)position.y(),(double)position.z(),(double)target.x(),(double)target.y(),(double)target.z(),(double)up.x(),(double)up.y(),(double)up.z());
    }
    void Camera::lookAt(const numbers::vector<float,3>& p,const numbers::vector<float,3>& t)
    {
        position = p;
        target = t;
        direction = nums_here::normalize(position - target);
        rigth = nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction);
        up = nums_here::normalize(direction * rigth);
        front = nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f));
        glLoadIdentity();
        gluLookAt((double)position.x(),(double)position.y(),(double)position.z(),(double)target.x(),(double)target.y(),(double)target.z(),(double)up.x(),(double)up.y(),(double)up.z());
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

    void Camera::rotate_up(float speed)
    {

    }

    void Camera::perspective(double fov,double aspect,double near,double far)
    {
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluPerspective(fov,aspect,near,far);
    }
    void Camera::orthogonal(double left,double right,double bottom,double top,double nearVal,double farVal)
    {
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        glOrtho(left,right,bottom,top,nearVal,farVal);
    }


}
namespace oct::verso::v0::v2
{
    Camera::Camera(const numbers::vector<float,3>& p,const numbers::vector<float,3>& t)
        :
        position(p),
        target(t),
        direction(nums_here::normalize(position - target)),
        rigth(nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction)),
        up(nums_here::normalize(direction * rigth)),
        front(nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f))),
        view(lookAt())
    {
    }

    void Camera::set(const numbers::vector<float,3>& p,const numbers::vector<float,3>& t)
    {
        position = p;
        target = t;
        direction = nums_here::normalize(position - target);
        rigth = nums_here::normalize(Point<float,3>(0.0f, 1.0f, 0.0f) * direction);
        up = nums_here::normalize(direction * rigth);
        front = nums_here::normalize(Point<float,3>(0.0f, 0.0f, -1.0f));
        //view = lookAt();
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
        position += up * speed;
        view = lookAt();
    }
    void Camera::walking_down(float speed)
    {
        position -= up * speed;
        view = lookAt();
    }

    glm::mat4& Camera::lookAt()
    {
        view = glm::lookAt(reinterpret_cast<glm::vec3&>(position),reinterpret_cast<glm::vec3&>(target),reinterpret_cast<glm::vec3&>(up));
        return view;
    }


}
