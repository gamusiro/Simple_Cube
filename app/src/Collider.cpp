#include "Collider.h"

Collider::~Collider()
{
    m_DynamicsWorld->removeRigidBody(m_RigidBody);
    
    delete m_RigidBody->getMotionState();
    delete m_RigidBody;
    delete m_CollisionShape;
}