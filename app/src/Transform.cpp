#include "Transform.h"


Transform::Transform()
    :m_Position(glm::vec3()),
    m_Rotation(glm::quat()),
    m_Scaling(glm::vec3(1.0f))
{
    calcTransform();
}

Transform::Transform(const glm::vec3& pos, const glm::vec3& deg, const glm::vec3& scl)
    :m_Position(pos),
    m_Rotation(glm::yawPitchRoll(deg.y, deg.x, deg.z)),
    m_Scaling(scl)
{
    calcTransform();
}

void Transform::SetPosition(float x, float y, float z)
{
    m_Position = glm::vec3(x, y, z);
    calcTransform();
}

void Transform::SetPosition(const glm::vec3& pos)
{
    m_Position = pos;
    calcTransform();
}

void Transform::SetRotation(float degX, float degY, float degZ)
{
    m_Rotation = glm::yawPitchRoll(degY, degX, degZ);
    calcTransform();
}

void Transform::SetRotation(const glm::vec3& degrees)
{
    m_Rotation = glm::yawPitchRoll(degrees.y, degrees.x, degrees.z);
    calcTransform();
}

void Transform::SetRotation(const glm::quat& quat)
{
    m_Rotation = quat;
    calcTransform();
}

void Transform::SetScale(float x, float y, float z)
{
    m_Scaling = glm::vec3(x, y, z);
    calcTransform();
}

void Transform::SetScale(const glm::vec3& scale)
{
    m_Scaling = scale;
    calcTransform();
}

void Transform::calcTransform()
    {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
        glm::mat4 rotation = glm::toMat4(m_Rotation);
        glm::mat4 scale =  glm::scale(glm::mat4(1.0f), m_Scaling);
        m_TransformMat = translate * rotation * scale;
    }