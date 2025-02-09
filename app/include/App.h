#ifndef APP_INCLUDE_APP_H_
#define APP_INCLUDE_APP_H_
#include <iostream>
#include <memory>

// 外部ライブラリ
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <entt/entt.hpp>
#include <btBulletDynamicsCommon.h>

// コンポーネント
#include "Transform.h"
#include "Cube.h"
#include "Plane.h"
#include "Shader.h"
#include "Camera.h"


#define ASSET_DIR "assets/"
#define SHADER_DIR ASSET_DIR "shaders/"


// class Collider : public Physics
// {
// protected:
//     btCollisionShape* m_CollisionShape;
//     btRigidBody* m_RigidBody;

// private:
//     friend class RigidBody;
// };

// class RigidBody
// {
// public:
//     RigidBody(Collider& collider);
//     ~RigidBody();

//     void AddImpulese()
//     {
//         btVector3 impulse(0.0f, 1.0f, 0.0f);    // 力量
//         btVector3 rel_pos(0.0f, 0.0f, 0.0f);    // オブジェクトの中心からの相対座標
//         m_Collider.m_RigidBody->applyImpulse(impulse, rel_pos);
//     }

// private:
//     Collider& m_Collider;
// };


class App
{
public:
    void Run();

private:
    void init();
    void term();

private:
    btCollisionConfiguration*               m_CollisionConfiguration;
    btCollisionDispatcher*                  m_CollisionDispatcher;
    btBroadphaseInterface*                  m_OverlappingPairCache;
    btSequentialImpulseConstraintSolver*    m_Solver;
    btDiscreteDynamicsWorld*                m_DynamicsWorld;

    btCollisionShape* m_CubeShape;
    btCollisionShape* m_PlaneShape;

    btRigidBody* m_CubeRigidBody;
    btRigidBody* m_PlaneRigidBody;



    GLFWwindow* m_Window;
    entt::registry m_Registry;
    entt::entity m_MainCamera;
    entt::entity m_GameObject1;   // ゲームオブジェクト(Cube)
    entt::entity m_GameObject2;   // ゲームオブジェクト(Plane)

    float m_LastTime;
};

#endif