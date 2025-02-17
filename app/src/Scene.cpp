#include "Scene.h"


void Scene::InternalUpdate()
{
    Physics::update(m_Registry);
}