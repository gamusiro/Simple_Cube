#ifndef APP_INCLUDE_COLLIDER_H_
#define APP_INCLUDE_COLLIDER_H_
#include "Physics.h"


typedef struct
{
    btVector3 scale;
    btTransform transform;
    float mass;
    float friction;
} ColliderParameter;

class Collider : public Physics
{
public:
    virtual ~Collider();

protected:
    btCollisionShape*   m_CollisionShape;
    btRigidBody*        m_RigidBody;
    ColliderParameter   m_ColliderParam;

private:
    friend class RigidBody;
};

#endif