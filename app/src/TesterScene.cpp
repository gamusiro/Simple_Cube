#include "TesterScene.h"

#define ASSET_DIR "assets/"
#define SHADER_DIR ASSET_DIR "shaders/"


void TesterScene::Create()
{
    const int width = 1280;
    const int height = 780;

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
}

void TesterScene::Update()
{
}

void TesterScene::Render()
{
    m_MeshRenderer.Render(m_MainCamera, m_Registry);
}

void TesterScene::Destroy()
{

}

void TesterScene::KeyEvent(int key, int action)
{
    if(key == 32){
        printf("KeyCallback: %d\n", key);
        RigidBody& rigidbody = m_Registry.get<RigidBody>(m_GameObject1);
        rigidbody.AddImpulse(btVector3(0.0f, 5.0f, 0.0f));
    }
}