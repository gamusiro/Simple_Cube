#include "RigidBody.h"

void RigidBody::AddImpulse(const btVector3& impulse)
{
    btVector3 pos (0.0f, 0.0f, 0.0f);
    m_RigidBody.applyImpulse(impulse, pos);
}
void RigidBody::AddImpulse(const btVector3& impulse, const btVector3& rel_pos)
{
    m_RigidBody.applyImpulse(impulse, rel_pos);
}