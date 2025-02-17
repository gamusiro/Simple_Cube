#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
    btVector3 scale(1.0f, 1.0f, 1.0f);
    m_CollisionShape = new btBoxShape(scale);

    btTransform btTransform;
    btTransform.setIdentity();

    float mass = 0.0f;
    float friction = 1.0f;
    btVector3 localInetia(0.0f, 0.0f, 0.0f);
    m_CollisionShape->calculateLocalInertia(mass, localInetia);

    btDefaultMotionState* motion = new btDefaultMotionState(btTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motion, m_CollisionShape, localInetia);
    m_RigidBody = new btRigidBody(rbInfo);
    m_RigidBody->setFriction(friction);

    m_DynamicsWorld->addRigidBody(m_RigidBody);
}

BoxCollider::BoxCollider(const ColliderParameter& param)
{
    m_CollisionShape = new btBoxShape(param.scale);

    btVector3 localInetia;
    m_CollisionShape->calculateLocalInertia(param.mass, localInetia);

    btDefaultMotionState* motion = new btDefaultMotionState(param.transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(param.mass, motion, m_CollisionShape, localInetia);
    m_RigidBody = new btRigidBody(rbInfo);
    m_RigidBody->setFriction(param.friction);

    m_DynamicsWorld->addRigidBody(m_RigidBody);
}