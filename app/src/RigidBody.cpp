#include "RigidBody.h"

void RigidBody::AddImpulse(const btVector3& impulse)
{
    m_RigidBody.applyCentralImpulse(impulse);
}

void RigidBody::AddImpulse(const btVector3& impulse, const btVector3& rel_pos)
{
    m_RigidBody.applyImpulse(impulse, rel_pos);
}