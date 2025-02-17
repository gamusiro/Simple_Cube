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
#include "RigidBody.h"

// 物理演算
#include "Physics.h"
#include "Collider.h"

// ユーティリティ
#include "utils.h"

// システム
#include "MeshRenderer.h"

// シーン
#include "Scene.h"
#include "TesterScene.h"



class App
{
public:
    void Run();

private:
    void init();
    void term();

private:
    GLFWwindow* m_Window;
    std::unique_ptr<Scene> m_Scene;

    float m_LastTime;
};

#endif