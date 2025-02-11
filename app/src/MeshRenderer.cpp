#include "MeshRenderer.h"

#include "Camera.h"
#include "Transform.h"
#include "Shader.h"
#include "Cube.h"
#include "Plane.h"

void MeshRender::Render(const entt::entity& entityCamera, const entt::registry& registry) const
{
    // カメラ設定
    const PerspectiveCamera& cam = registry.get<PerspectiveCamera>(entityCamera);
    glm::vec3 eye = glm::vec3(0.0f, 10.0f, -15.0f);
    glm::vec3 tar = glm::vec3(0.0f);
    glm::vec3 up  = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 vp = cam.GetProjectionMatrix() * Camera::CulcViewMatrix(eye, tar, up);

    {// レンダリング (Cube)
        auto view = registry.view<Transform, Cube, Shader>();
        for(auto entity : view)
        {
            const Transform& transform = view.get<Transform>(entity);
            const Cube& cube = view.get<Cube>(entity);
            const Shader& shader = view.get<Shader>(entity);

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
            const Transform& transform = view.get<Transform>(entity);
            const Plane& plane = view.get<Plane>(entity);
            const Shader& shader = view.get<Shader>(entity);

            shader.Bind();
            shader.Set("u_Transform", transform.GetTransformMatrix());
            shader.Set("u_ViewProjection", vp);
            plane.Render();
            shader.Unbind();
        }
    }
}