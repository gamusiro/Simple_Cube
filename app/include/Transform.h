#ifndef APP_INCLUDE_TRANSFORM_H_
#define APP_INCLUDE_TRANSFORM_H_
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>


class Transform
{
public:
    Transform();
    Transform(const glm::vec3& pos, const glm::vec3& deg, const glm::vec3& scl);
    ~Transform() = default;

public:
    void SetPosition(float x, float y, float z);
    void SetPosition(const glm::vec3& pos);
    void SetRotation(float degX, float degY, float degZ);
    void SetRotation(const glm::vec3& degrees);
    void SetRotation(const glm::quat& quat);
    void SetScale(float x, float y, float z);
    void SetScale(const glm::vec3& scale);

    inline const glm::vec3 GetPosition() const { return m_Position; }
    inline const glm::vec3 GetRotation() const { return glm::eulerAngles(m_Rotation); }
    inline const glm::quat GetQuaternion() const { return m_Rotation; }
    inline const glm::vec3 GetScale() const { return m_Scaling; }
    inline const glm::vec3 GetForward() const { return glm::normalize(m_Rotation * glm::vec3(0, 0, -1)); }
    inline const glm::vec3 GetUp() const { return glm::normalize(m_Rotation * glm::vec3(0, 1, 0)); }
    inline const glm::mat4 GetTransformMatrix() const { return m_TransformMat; }
private:
    void calcTransform();

private:
    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::vec3 m_Scaling;

    glm::mat4 m_TransformMat;
};

#endif