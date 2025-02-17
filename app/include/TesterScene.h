#ifndef APP_INCLUDE_TESTERSCENE_H_
#define APP_INCLUDE_TESTERSCENE_H_
#include "Scene.h"

class TesterScene : public Scene
{
public:
    TesterScene(){}
    ~TesterScene(){}

    void Create() override;
    void Update() override;
    void Render() override;
    void Destroy() override;

    void KeyEvent(int key, int action) override;

private:
    entt::entity m_MainCamera;
    entt::entity m_GameObject1;   // ゲームオブジェクト(Cube)
    entt::entity m_GameObject2;   // ゲームオブジェクト(Plane)

    MeshRender m_MeshRenderer;
};

#endif