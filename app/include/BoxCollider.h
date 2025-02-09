#ifndef APP_INCLUDE_BOXCOLLIDER_H_
#define APP_INCLUDE_BOXCOLLIDER_H_
#include "Collider.h"

class BoxCollider : public Collider
{
public:
    BoxCollider();
    BoxCollider(const ColliderParameter& param);
};

#endif