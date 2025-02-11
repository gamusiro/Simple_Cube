#ifndef APP_INCLUDE_PHYSICS_H_
#define APP_INCLUDE_PHYSICS_H_
#include <btBulletDynamicsCommon.h>
#include <entt/entt.hpp>

class Physics
{
private:
    static void init();
    static void update(entt::registry& registry);
    static void term();

private:
    static btCollisionConfiguration*               m_CollisionConfiguration;
    static btCollisionDispatcher*                  m_CollisionDispatcher;
    static btBroadphaseInterface*                  m_OverlappingPairCache;
    static btSequentialImpulseConstraintSolver*    m_Solver;
    
protected:
    static btDiscreteDynamicsWorld* m_DynamicsWorld;

private:
    constexpr static btScalar k_DELTA_STEP = 1.0f / 60.0f;
    friend class App;
};

#endif