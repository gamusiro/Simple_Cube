#ifndef APP_INCLUDE_PHYSICS_H_
#define APP_INCLUDE_PHYSICS_H_
#include <btBulletDynamicsCommon.h>

class Physics
{
private:
    static void init();
    static void update(float step);
    static void term();

private:
    static btCollisionConfiguration*               m_CollisionConfiguration;
    static btCollisionDispatcher*                  m_CollisionDispatcher;
    static btBroadphaseInterface*                  m_OverlappingPairCache;
    static btSequentialImpulseConstraintSolver*    m_Solver;
    
protected:
    static btDiscreteDynamicsWorld* m_DynamicsWorld;

private:
    friend class App;
};

#endif