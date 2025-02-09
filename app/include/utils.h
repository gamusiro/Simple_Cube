#ifndef APP_INCLUDE_UTILS_H_
#define APP_INCLUDE_UTILS_H_

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>

#include "Transform.h"

glm::vec3 ConvertVec3ToGLMFromBullet(const btVector3& value);
glm::vec4 ConvertVec4ToGLMFromBullet(const btVector4& value);
glm::quat ConvertQuatToGLMFromBullet(const btQuaternion& value);

btVector3 ConvertVec3ToBulletFromGLM(const glm::vec3& value);
btVector4 ConvertVec4ToBulletFromGLM(const glm::vec4& value);
btQuaternion ConvertQuatToBulletFromGLM(const glm::quat& value);

#endif