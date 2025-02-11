#ifndef APP_INCLUDE_MESHRENDERER_H_
#define APP_INCLUDE_MESHRENDERER_H_
#include <entt/entt.hpp>

class MeshRender
{
public:
    void Render(const entt::entity& entityCamera, const entt::registry& registry) const;
};

#endif