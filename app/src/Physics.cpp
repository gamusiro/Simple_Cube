#include "Physics.h"

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
}

void Physics::update(float step)
{
    m_DynamicsWorld->stepSimulation(step);
}

void Physics::term()
{
    delete m_DynamicsWorld;
    delete m_Solver;
    delete m_OverlappingPairCache;
    delete m_CollisionDispatcher;
    delete m_CollisionConfiguration;
}