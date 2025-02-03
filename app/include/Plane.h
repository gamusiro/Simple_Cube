#ifndef APP_INCLUDE_PLANE_H_
#define APP_INCLUDE_PLANE_H_
#include <cstdint>

class Plane
{
public:
    Plane();
    ~Plane();
    void Render() const;

private:
    uint32_t m_VertexArray;
    uint32_t m_VertexBuffer;
    uint32_t m_IndexBuffer;
    uint32_t m_IndexCount;
};

#endif