#include "Physics.h"

#include "Transform.h"
#include "RigidBody.h"
#include "utils.h"

btCollisionConfiguration*               Physics::m_CollisionConfiguration;
btCollisionDispatcher*                  Physics::m_CollisionDispatcher;
btBroadphaseInterface*                  Physics::m_OverlappingPairCache;
btSequentialImpulseConstraintSolver*    Physics::m_Solver;
btDiscreteDynamicsWorld*                Physics::m_DynamicsWorld;

void Physics::init()
{
    m_CollisionConfiguration    = new btDefaultCollisionConfiguration();
    m_CollisionDispatcher       = new btCollisionDispatcher(m_CollisionConfiguration);
    m_OverlappingPairCache      = new btDbvtBroadphase();
    m_Solver                    = new btSequentialImpulseConstraintSolver();
    m_DynamicsWorld             = new btDiscreteDynamicsWorld(m_CollisionDispatcher, m_OverlappingPairCache, m_Solver, m_CollisionConfiguration);

    m_DynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));
}

void Physics::update(entt::registry& registry)
{
    m_DynamicsWorld->stepSimulation(k_DELTA_STEP);

    auto view = registry.view<Transform, RigidBody>();
    for(auto entity : view)
    {
        Transform& transform = view.get<Transform>(entity);
        RigidBody& rigidbody = view.get<RigidBody>(entity);

        transform.SetPosition(ConvertVec3ToGLMFromBullet(rigidbody.GetPosition()));
        transform.SetRotation(ConvertQuatToGLMFromBullet(rigidbody.GetRotaiton()));
    }
}

void Physics::term()
{
    delete m_DynamicsWorld;
    delete m_Solver;
    delete m_OverlappingPairCache;
    delete m_CollisionDispatcher;
    delete m_CollisionConfiguration;
}