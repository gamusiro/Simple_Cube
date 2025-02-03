#ifndef APP_INCLUDE_CAMERA_H_
#define APP_INCLUDE_CAMERA_H_
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

class Camera
{
public:
	virtual ~Camera() = default;
    inline const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

public:
	static const glm::mat4 CulcViewMatrix(const Transform& transform);
	static const glm::mat4 CulcViewMatrix(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);

protected:
    virtual void culculate() = 0;

protected:
    glm::mat4 m_ProjectionMatrix;
};

class OrthographicsCamera : public Camera
{
public:
	OrthographicsCamera();
	OrthographicsCamera(float left, float right, float bottom, float top);
	~OrthographicsCamera() = default;

protected:
	void culculate() override;

private:
	float m_Left;
	float m_Right;
	float m_Bottom;
	float m_Top;
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera();
	PerspectiveCamera(float fovy, float aspect, float znear, float zfar);
	~PerspectiveCamera() = default;

protected:
	void culculate() override;

private:
	float m_Fovy;
	float m_Aspect;
	float m_Znear;
	float m_Zfar;
};

#endif