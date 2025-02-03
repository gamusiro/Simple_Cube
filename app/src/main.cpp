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


int main()
{
    const int width = 1280;
    const int height = 780;
    const float velocity = 10.0f;

    // Bullet3 初期化
    btCollisionConfiguration*               collisionConfiguration;
    btCollisionDispatcher*                  collisionDispatcher;
    btBroadphaseInterface*                  overlappingPairCache;
    btSequentialImpulseConstraintSolver*    solver;
    btDiscreteDynamicsWorld*                dynamicsWorld;

    collisionConfiguration    = new btDefaultCollisionConfiguration();
    collisionDispatcher       = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache      = new btDbvtBroadphase();
    solver                    = new btSequentialImpulseConstraintSolver();
    dynamicsWorld             = new btDiscreteDynamicsWorld(collisionDispatcher, overlappingPairCache, solver, collisionConfiguration);


    // GLFW 初期化
    GLFWwindow* window;
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, height, "Physics App", nullptr, nullptr);
    
    // GLAD 初期化
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // ENTT オブジェクト
    entt::registry registry;
    entt::entity MainCamera = registry.create();    // ゲームオブジェクト(Camera)
    entt::entity GameObject1 = registry.create();   // ゲームオブジェクト(Cube)
    entt::entity GameObject2 = registry.create();   // ゲームオブジェクト(Plane)

    // 物理演算用オブジェクト
    btCollisionShape* cubeShape;
    btRigidBody* cubeRigidBody;

    btCollisionShape* planeShape;
    btRigidBody* planeRigidBody;

    {// カメラオブジェクト
        registry.emplace<Transform>(MainCamera);
    
        PerspectiveCamera cam(glm::radians(45.0f), float(width) / float(height), 0.3f, 100.0f);
        registry.emplace<PerspectiveCamera>(MainCamera, cam);
    }

    {// キューブオブジェクト
        Transform transform;
        transform.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f)); // x: 0 y: 10 z: 0
        transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        registry.emplace<Transform>(GameObject1, transform);
        registry.emplace<Cube>(GameObject1);
        registry.emplace<Shader>(GameObject1, SHADER_DIR "default.vert", SHADER_DIR "red.frag");

        // 物理演算に必要なクラス
        btVector3 scale(1.0f, 1.0f, 1.0f);
        cubeShape = new btBoxShape(scale);

        btVector3 pos(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);
        btQuaternion rot(transform.GetQuaternion().w, transform.GetQuaternion().x, transform.GetQuaternion().y, transform.GetQuaternion().z);
        btTransform btTransform;
        btTransform.setIdentity();
        btTransform.setOrigin(pos);
        btTransform.setRotation(rot);
        printf("Rotation X: %f Y: %f Z: %f W: %f\n", rot.x(), rot.y(), rot.z(), rot.w());

        float mass = 1.0f;
        btVector3 localInetia;
        cubeShape->calculateLocalInertia(mass, localInetia);

        btDefaultMotionState* motion = new btDefaultMotionState(btTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motion, cubeShape, localInetia);
        cubeRigidBody = new btRigidBody(rbInfo);
        cubeRigidBody->setFriction(1.0f);

        dynamicsWorld->addRigidBody(cubeRigidBody);
    }

    {// プレーンオブジェクト
        Transform transform;
        transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        transform.SetScale(glm::vec3(5.0f, 0.2f, 5.0f));  // x: 5 y: 0.2 z: 5
        registry.emplace<Transform>(GameObject2, transform);
        registry.emplace<Plane>(GameObject2);
        registry.emplace<Shader>(GameObject2, SHADER_DIR "default.vert", SHADER_DIR "white.frag");

        // 物理演算に必要なクラス
        btVector3 scale(5.0f, 0.2f, 5.0f);
        planeShape = new btBoxShape(scale);

        btVector3 pos(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);
        btQuaternion rot(transform.GetQuaternion().w, transform.GetQuaternion().x, transform.GetQuaternion().y, transform.GetQuaternion().z);
        btTransform btTransform;
        btTransform.setIdentity();
        btTransform.setOrigin(pos);
        btTransform.setRotation(rot);
        printf("Rotation X: %f Y: %f Z: %f W: %f\n", rot.x(), rot.y(), rot.z(), rot.w());
        
        float mass = 0.0f;
        btVector3 localInetia;
        planeShape->calculateLocalInertia(mass, localInetia);

        btDefaultMotionState* motion = new btDefaultMotionState(btTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motion, planeShape, localInetia);
        planeRigidBody = new btRigidBody(rbInfo);
        planeRigidBody->setFriction(1.0f);

        dynamicsWorld->addRigidBody(planeRigidBody);
    }

    // ビューポート指定
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    // ゲームループ
    float lastTime = glfwGetTime();
    while(!glfwWindowShouldClose(window))
    {
        float curTime = glfwGetTime();
        float deltaTime = curTime - lastTime;

        glClearColor(0.5f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {// 物理演算更新
            dynamicsWorld->stepSimulation(1.0f / 60.0f);

            {// キューブリジッドボディ
                btVector3 btPos = cubeRigidBody->getWorldTransform().getOrigin();
                btQuaternion btRot = cubeRigidBody->getWorldTransform().getRotation();

                glm::vec3 pos = glm::vec3(btPos.x(), btPos.y(), btPos.z());
                glm::quat rot = glm::quat(btRot.w(), btRot.x(), btRot.y(), btRot.z());

                //printf("Position X: %f Y: %f Z: %f\n", pos.x, pos.y, pos.z);
                //printf("Rotation X: %f Y: %f Z: %f W: %f\n", rot.x, rot.y, rot.z, rot.w);
                Transform& transform = registry.get<Transform>(GameObject1);
                transform.SetPosition(pos);
                transform.SetRotation(rot);
            }
        }

        {// 入力処理
            if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                btVector3 impulse(0.0f, 1.0f, 0.0f);    // 力量
                btVector3 rel_pos(0.0f, 0.0f, 0.0f);    // オブジェクトの中心からの相対座標
                cubeRigidBody->applyImpulse(impulse, rel_pos);
            }
        }

        
        {// レンダリング

            // カメラ設定
            PerspectiveCamera& cam = registry.get<PerspectiveCamera>(MainCamera);
            glm::vec3 eye = glm::vec3(0.0f, 10.0f, -15.0f);
            glm::vec3 tar = glm::vec3(0.0f);
            glm::vec3 up  = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::mat4 vp = cam.GetProjectionMatrix() * Camera::CulcViewMatrix(eye, tar, up);

            {// レンダリング (Cube)
                auto view = registry.view<Transform, Cube, Shader>();
                for(auto entity : view)
                {
                    Transform& transform = registry.get<Transform>(entity);
                    Cube& cube = registry.get<Cube>(entity);
                    Shader& shader = registry.get<Shader>(entity);

                    shader.Bind();
                    shader.Set("u_Transform", transform.GetTransformMatrix());
                    shader.Set("u_ViewProjection", vp);
                    cube.Render();
                    shader.Unbind();
                }
            }

            {// レンダリング (Plane)
                auto view = registry.view<Transform, Plane, Shader>();
                for(auto entity : view)
                {
                    Transform& transform = registry.get<Transform>(entity);
                    Plane& plane = registry.get<Plane>(entity);
                    Shader& shader = registry.get<Shader>(entity);

                    shader.Bind();
                    shader.Set("u_Transform", transform.GetTransformMatrix());
                    shader.Set("u_ViewProjection", vp);
                    plane.Render();
                    shader.Unbind();
                }
            }

        }
        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = curTime;
    }

    // GLFW 終了
    glfwDestroyWindow(window);
    glfwTerminate();

    // Bullet 終了
    dynamicsWorld->removeRigidBody(planeRigidBody);
    delete planeRigidBody->getMotionState();
    delete planeRigidBody;
    delete planeShape;

    dynamicsWorld->removeRigidBody(cubeRigidBody);
    delete cubeRigidBody->getMotionState();
    delete cubeRigidBody;
    delete cubeShape;

    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete collisionDispatcher;
    delete collisionConfiguration;

    return 0;
}