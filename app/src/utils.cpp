#include "utils.h"


glm::vec3 ConvertVec3ToGLMFromBullet(const btVector3& value)
{
    return glm::vec3(value.x(), value.y(), value.z());
}

glm::vec4 ConvertVec4ToGLMFromBullet(const btVector4& value)
{
    return glm::vec4(value.x(), value.y(), value.z(), value.w());
}

glm::quat ConvertQuatToGLMFromBullet(const btQuaternion& value)
{
    return glm::quat(value.w(), value.x(), value.y(), value.z());
}

btVector3 ConvertVec3ToBulletFromGLM(const glm::vec3& value)
{
    return btVector3(value.x, value.y, value.z);
}

btVector4 ConvertVec4ToBulletFromGLM(const glm::vec4& value)
{
    return btVector4(value.x, value.y, value.z, value.w);
}

btQuaternion ConvertQuatToBulletFromGLM(const glm::quat& value)
{
    return btQuaternion(value.w, value.x, value.y, value.z);
}