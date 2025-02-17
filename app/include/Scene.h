#ifndef APP_INCLUDE_SCENE_H_
#define APP_INCLUDE_SCENE_H_
#include <entt/entt.hpp>

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

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Create() {}
    virtual void Update() {}
    virtual void Render() {}
    virtual void Destroy() {}
    void InternalUpdate();

    virtual void ResizeEvent(int width, int height) {}
    virtual void KeyEvent(int key, int action) {}

protected:
    template<typename Comp, typename... Args>
    Comp& AddComponent(entt::entity entity, Args&&... args)
    {
        return m_Registry.emplace<Comp>(std::forward<Args>(args)..);
    }

    template<typename Comp>
    void RemoveComponent(entt::entity entity)
    {
        m_Registry.remove<Comp>(entity);
    }

    template<typename Comp>
    bool HasComponent(entt::entity entity)
    {
        return m_Registry.any_of<Comp>(entity);
    }

    template<typename Comp>
    Comp& GetComponent(entt::entity entity)
    {
        static_assert(HasComponent<Comp>(entity), "Don't have component");
        return m_Registry.get<Comp>(entity);
    }

protected:
    entt::registry m_Registry;
};

#endif