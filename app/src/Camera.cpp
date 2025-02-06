#include "Camera.h"

const glm::mat4 CulcViewMatrix(const Transform& transform)
{
    const glm::vec3 eye = transform.GetPosition();
    const glm::vec3 fwd = transform.GetForward();
    const glm::vec3 up  = transform.GetUp();
    return glm::lookAt(eye, eye + fwd, up);
}

const glm::mat4 Camera::CulcViewMatrix(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
    return glm::lookAt(eye, target, up);
}

OrthographicsCamera::OrthographicsCamera()
    :m_Left(-1.0f), m_Right(1.0f), m_Bottom(1.0f), m_Top(-1.0f)
{
    calculate();
}

OrthographicsCamera::OrthographicsCamera(float left, float right, float bottom, float top)
    :m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top)
{
    calculate();
}

void OrthographicsCamera::calculate()
{
    m_ProjectionMatrix = glm::ortho(m_Left, m_Right, m_Bottom, m_Top);
}

PerspectiveCamera::PerspectiveCamera()
    :m_Fovy(glm::radians(45.0f)),
    m_Aspect(1.0f),
    m_Znear(0.1f), m_Zfar(100.0f)
{
    calculate();
}

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float znear, float zfar)
    :m_Fovy(fovy),
    m_Aspect(aspect),
    m_Znear(znear), m_Zfar(zfar)
{
    calculate();
}

void PerspectiveCamera::calculate()
{
    m_ProjectionMatrix = glm::perspective(m_Fovy, m_Aspect, m_Znear, m_Zfar);
}