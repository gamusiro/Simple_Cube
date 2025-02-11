#ifndef APP_INCLUDE_RIGIDBODY_H_
#define APP_INCLUDE_RIGIDBODY_H_
#include "Physics.h"
#include "Collider.h"

class RigidBody
{
public:
    RigidBody(Collider& collider) : m_RigidBody(*collider.m_RigidBody){}
    ~RigidBody() = default;

    inline btVector3 GetPosition() const { return m_RigidBody.getWorldTransform().getOrigin(); }
    inline btQuaternion GetRotaiton() const { return m_RigidBody.getWorldTransform().getRotation(); }

    void AddImpulse(const btVector3& impulse);
    void AddImpulse(const btVector3& impulse, const btVector3& rel_pos);

private:
    btRigidBody& m_RigidBody;
};

#endif