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

        // 物理演算更新
        Physics::update(m_Registry);

        // {// 入力処理
        //     RigidBody& rigidBody = m_Registry.get<RigidBody>(m_GameObject1);
        //     if(glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        //     {
        //         btVector3 impulse(0.0f, 1.0f, 0.0f);    // 力量
        //         btVector3 rel_pos(0.0f, 0.0f, 0.0f);    // オブジェクトの中心からの相対座標
        //         rigidBody.AddImpulse(impulse, rel_pos);
        //     }
        // }

        // 描画処理
        m_MeshRenderer.Render(m_MainCamera, m_Registry);

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