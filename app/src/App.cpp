#include "App.h"

void App::Run()
{
    init();

    while(!glfwWindowShouldClose(m_Window))
    {
        float curTime = glfwGetTime();
        float deltaTime = curTime - m_LastTime;

        glClearColor(0.5f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // {// 物理演算更新
        //     dynamicsWorld->stepSimulation(1.0f / 60.0f);

        //     {// キューブリジッドボディ
        //         btVector3 btPos = cubeRigidBody->getWorldTransform().getOrigin();
        //         btQuaternion btRot = cubeRigidBody->getWorldTransform().getRotation();

        //         glm::vec3 pos = glm::vec3(btPos.x(), btPos.y(), btPos.z());
        //         glm::quat rot = glm::quat(btRot.w(), btRot.x(), btRot.y(), btRot.z());

        //         //printf("Position X: %f Y: %f Z: %f\n", pos.x, pos.y, pos.z);
        //         //printf("Rotation X: %f Y: %f Z: %f W: %f\n", rot.x, rot.y, rot.z, rot.w);
        //         Transform& transform = registry.get<Transform>(GameObject1);
        //         transform.SetPosition(pos);
        //         transform.SetRotation(rot);
        //     }
        // }

        // {// 入力処理
        //     if(glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        //     {
        //         btVector3 impulse(0.0f, 1.0f, 0.0f);    // 力量
        //         btVector3 rel_pos(0.0f, 0.0f, 0.0f);    // オブジェクトの中心からの相対座標
        //         cubeRigidBody->applyImpulse(impulse, rel_pos);
        //     }
        // }

        
        {// レンダリング

            // カメラ設定
            PerspectiveCamera& cam = m_Registry.get<PerspectiveCamera>(m_MainCamera);
            glm::vec3 eye = glm::vec3(0.0f, 10.0f, -15.0f);
            glm::vec3 tar = glm::vec3(0.0f);
            glm::vec3 up  = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::mat4 vp = cam.GetProjectionMatrix() * Camera::CulcViewMatrix(eye, tar, up);

            {// レンダリング (Cube)
                auto view = m_Registry.view<Transform, Cube, Shader>();
                for(auto entity : view)
                {
                    Transform& transform = m_Registry.get<Transform>(entity);
                    Cube& cube = m_Registry.get<Cube>(entity);
                    Shader& shader = m_Registry.get<Shader>(entity);

                    shader.Bind();
                    shader.Set("u_Transform", transform.GetTransformMatrix());
                    shader.Set("u_ViewProjection", vp);
                    cube.Render();
                    shader.Unbind();
                }
            }

            {// レンダリング (Plane)
                auto view = m_Registry.view<Transform, Plane, Shader>();
                for(auto entity : view)
                {
                    Transform& transform = m_Registry.get<Transform>(entity);
                    Plane& plane = m_Registry.get<Plane>(entity);
                    Shader& shader = m_Registry.get<Shader>(entity);

                    shader.Bind();
                    shader.Set("u_Transform", transform.GetTransformMatrix());
                    shader.Set("u_ViewProjection", vp);
                    plane.Render();
                    shader.Unbind();
                }
            }

        }
        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        m_LastTime = curTime;
    }
    term();
}


void App::init()
{
    const int width = 1280;
    const int height = 780;
    const float velocity = 10.0f;

    m_CollisionConfiguration    = new btDefaultCollisionConfiguration();
    m_CollisionDispatcher       = new btCollisionDispatcher(m_CollisionConfiguration);
    m_OverlappingPairCache      = new btDbvtBroadphase();
    m_Solver                    = new btSequentialImpulseConstraintSolver();
    m_DynamicsWorld             = new btDiscreteDynamicsWorld(m_CollisionDispatcher, m_OverlappingPairCache, m_Solver, m_CollisionConfiguration);

    // GLFW 初期化
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    m_Window = glfwCreateWindow(width, height, "Physics App", nullptr, nullptr);
    
    // GLAD 初期化
    glfwMakeContextCurrent(m_Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    m_MainCamera = m_Registry.create();
    m_GameObject1 = m_Registry.create();
    m_GameObject2 = m_Registry.create();

    {// カメラオブジェクト
        m_Registry.emplace<Transform>(m_MainCamera);
    
        PerspectiveCamera cam(glm::radians(45.0f), float(width) / float(height), 0.3f, 100.0f);
        m_Registry.emplace<PerspectiveCamera>(m_MainCamera, cam);
    }

    {// キューブオブジェクト
        Transform transform;
        transform.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f)); // x: 0 y: 10 z: 0
        transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_Registry.emplace<Transform>(m_GameObject1, transform);
        m_Registry.emplace<Cube>(m_GameObject1);
        m_Registry.emplace<Shader>(m_GameObject1, SHADER_DIR "default.vert", SHADER_DIR "red.frag");

        // 物理演算に必要なクラス
        // btVector3 scale(1.0f, 1.0f, 1.0f);
        // cubeShape = new btBoxShape(scale);

        // btVector3 pos(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);
        // btQuaternion rot(transform.GetQuaternion().w, transform.GetQuaternion().x, transform.GetQuaternion().y, transform.GetQuaternion().z);
        // btTransform btTransform;
        // btTransform.setIdentity();
        // btTransform.setOrigin(pos);
        // btTransform.setRotation(rot);
        // printf("Rotation X: %f Y: %f Z: %f W: %f\n", rot.x(), rot.y(), rot.z(), rot.w());

        // float mass = 1.0f;
        // btVector3 localInetia;
        // cubeShape->calculateLocalInertia(mass, localInetia);

        // btDefaultMotionState* motion = new btDefaultMotionState(btTransform);
        // btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motion, cubeShape, localInetia);
        // cubeRigidBody = new btRigidBody(rbInfo);
        // cubeRigidBody->setFriction(1.0f);

        // dynamicsWorld->addRigidBody(cubeRigidBody);
    }

    {// プレーンオブジェクト
        Transform transform;
        transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        transform.SetScale(glm::vec3(5.0f, 0.2f, 5.0f));  // x: 5 y: 0.2 z: 5
        m_Registry.emplace<Transform>(m_GameObject2, transform);
        m_Registry.emplace<Plane>(m_GameObject2);
        m_Registry.emplace<Shader>(m_GameObject2, SHADER_DIR "default.vert", SHADER_DIR "white.frag");

        // 物理演算に必要なクラス
        // btVector3 scale(5.0f, 0.2f, 5.0f);
        // planeShape = new btBoxShape(scale);

        // btVector3 pos(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);
        // btQuaternion rot(transform.GetQuaternion().w, transform.GetQuaternion().x, transform.GetQuaternion().y, transform.GetQuaternion().z);
        // btTransform btTransform;
        // btTransform.setIdentity();
        // btTransform.setOrigin(pos);
        // btTransform.setRotation(rot);
        // printf("Rotation X: %f Y: %f Z: %f W: %f\n", rot.x(), rot.y(), rot.z(), rot.w());
        
        // float mass = 0.0f;
        // btVector3 localInetia;
        // planeShape->calculateLocalInertia(mass, localInetia);

        // btDefaultMotionState* motion = new btDefaultMotionState(btTransform);
        // btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motion, planeShape, localInetia);
        // planeRigidBody = new btRigidBody(rbInfo);
        // planeRigidBody->setFriction(1.0f);

        // dynamicsWorld->addRigidBody(planeRigidBody);
    }

    // ビューポート指定
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    // ゲームループ
    m_LastTime = glfwGetTime();
}

void App::term()
{
    // GLFW 終了
    glfwDestroyWindow(m_Window);
    glfwTerminate();

    delete m_DynamicsWorld;
    delete m_Solver;
    delete m_OverlappingPairCache;
    delete m_CollisionDispatcher;
    delete m_CollisionConfiguration;
}