#include "App.h"

void App::Run()
{
    init();

    float fixed = 0.0f;
    while(!glfwWindowShouldClose(m_Window))
    {
        float curTime = glfwGetTime();
        float deltaTime = curTime - m_LastTime;

        glClearColor(0.5f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        fixed += deltaTime;
        if(fixed > 1.0f / 60.0f)
        {
            fixed = 0.0f;
            m_Scene->InternalUpdate();
            m_Scene->Update();
        }

        m_Scene->Render();
        
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
    m_Window = glfwCreateWindow(width, height, "Physics App", nullptr, nullptr);
    
    // GLAD 初期化
    glfwMakeContextCurrent(m_Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // シーンの初期化
    m_Scene = std::make_unique<TesterScene>();
    m_Scene->Create();

    // コールバック関数
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
        app->m_Scene->KeyEvent(key, action);
    });

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
        
        // ビューポート指定
        glViewport(0, 0, width, height);
        app->m_Scene->ResizeEvent(width, height);
    });
    
    glEnable(GL_DEPTH_TEST);

    // ゲームループ
    m_LastTime = glfwGetTime();
}

void App::term()
{
    // シーンの終了処理
    m_Scene->Destroy();

    // GLFW 終了
    glfwDestroyWindow(m_Window);
    glfwTerminate();

    Physics::term();
}