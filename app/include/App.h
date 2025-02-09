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
#include "BoxCollider.h"

// 物理演算
#include "Physics.h"
#include "Collider.h"

// ユーティリティ
#include "utils.h"




#define ASSET_DIR "assets/"
#define SHADER_DIR ASSET_DIR "shaders/"


class App
{
public:
    void Run();

private:
    void init();
    void term();

private:
    //btCollisionShape* m_CubeShape;
    //btCollisionShape* m_PlaneShape;

    //btRigidBody* m_CubeRigidBody;
    //btRigidBody* m_PlaneRigidBody;



    GLFWwindow* m_Window;
    entt::registry m_Registry;
    entt::entity m_MainCamera;
    entt::entity m_GameObject1;   // ゲームオブジェクト(Cube)
    entt::entity m_GameObject2;   // ゲームオブジェクト(Plane)

    float m_LastTime;
};

#endif