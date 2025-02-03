#include <cstdint>
#include <glad/glad.h>

#include "Cube.h"

Cube::Cube()
{
    // 三角形の頂点
    float vertices[] =
    {
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
    };

    // 頂点インデックス
    uint32_t indices[] =
    {
        // Ceiling
        0, 1, 2,
        2, 3, 0,
        
        // Floor
        4, 5, 6,
        6, 7, 4,
        
        0, 1, 5,
        5, 4, 0,
        
        1, 2, 6,
        6, 5, 1,
        
        2, 3, 7,
        7, 6, 2,
        
        3, 0, 4,
        4, 7, 3
    };

    // 頂点属性
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    // 頂点バッファ作成
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    uint32_t stride = sizeof(float) * 3;
    uint32_t offset = 0;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)offset);

    // offset += sizeof(float) * 3;
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)offset);

    // インデックスバッファ作成
    m_IndexCount = sizeof(indices) / sizeof(indices[0]);
    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

Cube::~Cube()
{
    glDeleteBuffers(1, &m_IndexBuffer);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteVertexArrays(1, &m_VertexArray);
}

void Cube::Render() const
{
    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}