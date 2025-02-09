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

        {// 物理演算更新
            const float step = 1.0f / 60.0f;
            Physics::update(step);

            auto view = m_Registry.view<Transform, RigidBody>();
            for(auto entity : view)
            {
                Transform& transform = view.get<Transform>(entity);
                RigidBody& rigidbody = view.get<RigidBody>(entity);

                transform.SetPosition(ConvertVec3ToGLMFromBullet(rigidbody.GetPosition()));
                transform.SetRotation(ConvertQuatToGLMFromBullet(rigidbody.GetRotaiton()));
            }
        }

        {// 入力処理
            // if(glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
            // {
            //     btVector3 impulse(0.0f, 1.0f, 0.0f);    // 力量
            //     btVector3 rel_pos(0.0f, 0.0f, 0.0f);    // オブジェクトの中心からの相対座標
            //     m_CubeRigidBody->applyImpulse(impulse, rel_pos);
            // }
        }

        
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

    Physics::init();

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

        ColliderParameter param;
        param.transform.setOrigin(ConvertVec3ToBulletFromGLM(transform.GetPosition()));
        param.transform.setRotation(ConvertQuatToBulletFromGLM(transform.GetQuaternion()));
        param.scale = btVector3(1.0f, 1.0f, 1.0f);
        param.friction = 1.0f;
        param.mass = 1.0f;
        BoxCollider& collider = m_Registry.emplace<BoxCollider>(m_GameObject1, param);
        m_Registry.emplace<RigidBody>(m_GameObject1, collider);
    }

    {// プレーンオブジェクト
        Transform transform;
        transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        transform.SetScale(glm::vec3(5.0f, 0.2f, 5.0f));  // x: 5 y: 0.2 z: 5
        m_Registry.emplace<Transform>(m_GameObject2, transform);
        m_Registry.emplace<Plane>(m_GameObject2);
        m_Registry.emplace<Shader>(m_GameObject2, SHADER_DIR "default.vert", SHADER_DIR "white.frag");

        ColliderParameter param;
        param.transform.setOrigin(ConvertVec3ToBulletFromGLM(transform.GetPosition()));
        param.transform.setRotation(ConvertQuatToBulletFromGLM(transform.GetQuaternion()));
        param.scale = btVector3(5.0f, 0.02f, 5.0f);
        param.friction = 1.0f;
        param.mass = 0.0f;
        BoxCollider& collider = m_Registry.emplace<BoxCollider>(m_GameObject2, param);
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

    Physics::term();
}