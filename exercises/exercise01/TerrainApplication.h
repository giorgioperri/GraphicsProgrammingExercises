#pragma once

#include <ituGL/application/Application.h>
#include <ituGL/geometry/VertexArrayObject.h>
#include <ituGL/geometry/VertexBufferObject.h>
#include <vector>

class TerrainApplication : public Application
{
public:
    TerrainApplication();

protected:
    void Initialize() override;
    void Update() override;
    void Render() override;
    void Cleanup() override;

private:
    void BuildShaders();
    void UpdateOutputMode();

private:
    unsigned int m_gridX, m_gridY;
    unsigned int m_shaderProgram;

    VertexArrayObject m_vao;
    VertexBufferObject m_vbo;

    // (todo) 01.5: Declare an EBO

};
