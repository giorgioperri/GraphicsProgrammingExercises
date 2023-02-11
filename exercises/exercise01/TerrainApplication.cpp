#define STB_PERLIN_IMPLEMENTATION

#include "TerrainApplication.h"
#include <ituGL/geometry/VertexAttribute.h>
#include <stb_perlin.h>

#include <cmath>
#include <iostream>

// Helper structures. Declared here only for this exercise
struct Vector2
{
    Vector2() : Vector2(0.f, 0.f) {}
    Vector2(float x, float y) : x(x), y(y) {}
    float x, y;
};

struct Vector3
{
    Vector3() : Vector3(0.f,0.f,0.f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    float x, y, z;

    Vector3 Normalize() const
    {
        float length = std::sqrt(1 + x * x + y * y);
        return Vector3(x / length, y / length, z / length);
    }
};

// (todo) 01.8: Declare an struct with the vertex format
struct Vertex
{
    Vector3 position;
    Vector2 texCoord;
    Vector3 color;
    Vector3 normal;
};


TerrainApplication::TerrainApplication()
    : Application(1024, 1024, "Terrain demo"), m_gridX(64), m_gridY(64), m_shaderProgram(0)
{
}

void TerrainApplication::Initialize()
{
    Application::Initialize();

    // Build shaders and store in m_shaderProgram
    BuildShaders();

    std::vector<int> m_triangleIndices;
    std::vector<Vertex> m_vertices;

    //Using 2 nested loops, create a list of positions for the grid. Each quad will need 6 vertices (2 triangles).
    for (int i = 0; i < m_gridX; i++)
    {
        for (int j = 0; j < m_gridY; j++)
        {
            Vertex V1 = Vertex();
            Vertex V2 = Vertex();
            Vertex V3 = Vertex();
            Vertex V4 = Vertex();

            //using a scale of 1/m_gridX x 1/m_gridY, so the total size of the grid is 1
            float xScale = 1.0f / m_gridX;
            float yScale = 1.0f / m_gridY;

            //calculate the position of the vertices
            float x = i * xScale;
            float y = j * yScale;

            //move the vertices to the center of the screen
            x -= 0.5f;
            y -= 0.5f;

            //-------------------vertex positions-------------------

            float height = stb_perlin_fbm_noise3(x, y, 0, 2, 0.5f, 6) * 0.5f;
            float height1 = stb_perlin_fbm_noise3(x, y + yScale, 0, 2, 0.5f, 6) * 0.5f;
            float height2 = stb_perlin_fbm_noise3(x + xScale, y, 0, 2, 0.5f, 6)  * 0.5f;
            float height3 = stb_perlin_fbm_noise3(x + xScale, y + yScale, 0, 2, 0.5f, 6) * 0.5f;

            V1.position = Vector3(x, y, height);
            V2.position = Vector3(x, y + yScale, height1);
            V3.position = Vector3(x + xScale, y, height2);
            V4.position = Vector3(x + xScale, y + yScale, height3);

            //-------------------texture coordinates-------------------

            V1.texCoord = Vector2(0, 0);
            V2.texCoord = Vector2(0, 1);
            V3.texCoord = Vector2(1, 0);
            V4.texCoord = Vector2(1, 1);

            //-------------------triangle indices-------------------

            int index = i * 4 + j * 4 * m_gridX;

            //first triangle
            m_triangleIndices.push_back(index);
            m_triangleIndices.push_back(index + 1);
            m_triangleIndices.push_back(index + 2);

            //second triangle
            m_triangleIndices.push_back(index + 2);
            m_triangleIndices.push_back(index + 1);
            m_triangleIndices.push_back(index + 3);

            //-------------------colors-------------------

            float colorShading = height + 0.5f;

            Vector3 waterColor = Vector3(0.2f * colorShading, 0.5f * colorShading, 0.7f * colorShading);
            Vector3 sandColor = Vector3(0.8f * colorShading, 0.7f * colorShading, 0.5f * colorShading);
            Vector3 grassColor = Vector3(0.2f * colorShading, 0.7f * colorShading, 0.2f * colorShading);
            Vector3 rockColor = Vector3(0.5f * colorShading, 0.5f * colorShading, 0.5f * colorShading);
            Vector3 snowColor = Vector3(1.0f * colorShading, 1.0f * colorShading, 1.0f * colorShading);

            if (height < 0)
            {
                V1.color = waterColor;
                V2.color = waterColor;
                V3.color = waterColor;
                V4.color = waterColor;
            }
            else if (height < 0.1f)
            {
                V1.color = sandColor;
                V2.color = sandColor;
                V3.color = sandColor;
                V4.color = sandColor;
            }
            else if (height < 0.25f)
            {
                V1.color = grassColor;
                V2.color = grassColor;
                V3.color = grassColor;
                V4.color = grassColor;
            }
            else if (height < 0.31f)
            {
                V1.color = rockColor;
                V2.color = rockColor;
                V3.color = rockColor;
                V4.color = rockColor;
            }
            else
            {
                V1.color = snowColor;
                V2.color = snowColor;
                V3.color = snowColor;
                V4.color = snowColor;
            }

            //-------------------add vertices to the list-------------------

            m_vertices.push_back(V1);
            m_vertices.push_back(V2);
            m_vertices.push_back(V3);
            m_vertices.push_back(V4);
        }
    }

    for (int i = 0; i < m_gridX; i++)
    {
        for (int j = 0; j < m_gridY; j++)
        {
            int index = i * 4 + j * 4 * m_gridX;

            Vertex& V1 = m_vertices[index];     // BOTTOM LEFT
            Vertex& V2 = m_vertices[index + 1]; // TOP LEFT
            Vertex& V3 = m_vertices[index + 2]; // BOTTOM RIGHT
            Vertex& V4 = m_vertices[index + 3]; // TOP RIGHT

            Vertex V1left = (i == 0) ? V1 : m_vertices[index - 4];
            Vertex V1right = (i == m_gridX - 1) ? V1 : V3;
            Vertex V1up = (j == m_gridY - 1) ? V1 : V2;
            Vertex V1down = (j == 0) ? V1 : m_vertices[index - 4 * m_gridX];

            Vertex V2left = (i == 0) ? V2 : m_vertices[index - 4];
            Vertex V2right = (i == m_gridX - 1) ? V2 : V4;
            Vertex V2up = (j == m_gridY - 1) ? V2 : m_vertices[index + 4 * m_gridX + 1];
            Vertex V2down = (j == 0) ? V2 : V1;

            Vertex V3left = (i == 0) ? V3 : V1;
            Vertex V3right = (i == m_gridX - 1) ? V3 : m_vertices[index + 4];
            Vertex V3up = (j == m_gridY - 1) ? V3 : V4;
            Vertex V3down = (j == 0) ? V3 : m_vertices[index - 4 * m_gridX];

            Vertex V4left = (i == 0) ? V4 : V2;
            Vertex V4right = (i == m_gridX - 1) ? V4 : m_vertices[index + 4];
            Vertex V4up = (j == m_gridY - 1) ? V4 : m_vertices[index + 4 * m_gridX + 1];
            Vertex V4down = (j == 0) ? V4 : V3;

            float V1deltaX = (V1right.position.z - V1left.position.z) / (V1right.position.x - V1left.position.x);
            float V1deltaY = (V1up.position.z - V1down.position.z) / (V1up.position.y - V1down.position.y);

            float V2deltaX = (V2right.position.z - V2left.position.z) / (V2right.position.x - V2left.position.x);
            float V2deltaY = (V2up.position.z - V2down.position.z) / (V2up.position.y - V2down.position.y);

            float V3deltaX = (V3right.position.z - V3left.position.z) / (V3right.position.x - V3left.position.x);
            float V3deltaY = (V3up.position.z - V3down.position.z) / (V3up.position.y - V3down.position.y);

            float V4deltaX = (V4right.position.z - V4left.position.z) / (V4right.position.x - V4left.position.x);
            float V4deltaY = (V4up.position.z - V4down.position.z) / (V4up.position.y - V4down.position.y);

            V1.normal = Vector3(V1deltaX, V1deltaY, 1).Normalize();
            V2.normal = Vector3(V2deltaX, V2deltaY, 1).Normalize();
            V3.normal = Vector3(V3deltaX, V3deltaY, 1).Normalize();
            V4.normal = Vector3(V4deltaX, V4deltaY, 1).Normalize();
        }
    }

    //allocate data to the vbo
    m_vao.Bind();
    m_vbo.Bind();
    m_ebo.Bind();

    //allocate data to the vbo for the vertex positions and the texture coordinates and the colors
    m_vbo.AllocateData(std::span(m_vertices));
    m_ebo.AllocateData(std::span(m_triangleIndices));

    VertexAttribute position(Data::Type::Float, 3);
    m_vao.SetAttribute(0, position, 0, sizeof(Vertex));

    VertexAttribute texCoord(Data::Type::Float, 2);
    m_vao.SetAttribute(1, texCoord, position.GetSize(), sizeof(Vertex));

    VertexAttribute color(Data::Type::Float, 3);
    m_vao.SetAttribute(2, color, position.GetSize() + texCoord.GetSize(), sizeof(Vertex));

    VertexAttribute normal(Data::Type::Float, 3);
    m_vao.SetAttribute(3, normal, position.GetSize() + texCoord.GetSize() + color.GetSize(), sizeof(Vertex));

    m_vbo.Unbind();
    m_vao.Unbind();
    m_ebo.Unbind();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TerrainApplication::Update()
{
    Application::Update();

    UpdateOutputMode();
}

void TerrainApplication::Render()
{
    Application::Render();

    // Clear color and depth
    GetDevice().Clear(true, Color(0.0f, 0.0f, 0.0f, 1.0f), true, 1.0f);

    // Set shader to be used
    glUseProgram(m_shaderProgram);

    m_vao.Bind();
    glEnable(GL_DEPTH_TEST);3
    glDrawElements(GL_TRIANGLES, m_gridX * m_gridY * 6, GL_UNSIGNED_INT, 0);
}

void TerrainApplication::Cleanup()
{
    Application::Cleanup();
}

void TerrainApplication::BuildShaders()
{
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "layout (location = 2) in vec3 aColor;\n"
        "layout (location = 3) in vec3 aNormal;\n"
        "uniform mat4 Matrix = mat4(1);\n"
        "out vec2 texCoord;\n"
        "out vec3 color;\n"
        "out vec3 normal;\n"
        "void main()\n"
        "{\n"
        "   texCoord = aTexCoord;\n"
        "   color = aColor;\n"
        "   normal = aNormal;\n"
        "   gl_Position = Matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "uniform uint Mode = 0u;\n"
        "in vec2 texCoord;\n"
        "in vec3 color;\n"
        "in vec3 normal;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   switch (Mode)\n"
        "   {\n"
        "   default:\n"
        "   case 0:\n"
        "       FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "       break;\n"
        "   case 1:\n"
        "       FragColor = vec4(fract(texCoord), 0.0f, 1.0f);\n"
        "       break;\n"
        "   case 2:\n"
        "       FragColor = vec4(color, 1.0f);\n"
        "       break;\n"
        "   case 3:\n"
        "       FragColor = vec4(normalize(normal), 1.0f);\n"
        "       break;\n"
        "   case 4:\n"
        "       FragColor = vec4(color * max(dot(normalize(normal), normalize(vec3(1,0,1))), 0.2f), 1.0f);\n"
        "       break;\n"
        "   }\n"
        "}\n\0";

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    m_shaderProgram = shaderProgram;
}

void TerrainApplication::UpdateOutputMode()
{
    for (int i = 0; i <= 4; ++i)
    {
        if (GetMainWindow().IsKeyPressed(GLFW_KEY_0 + i))
        {
            int modeLocation = glGetUniformLocation(m_shaderProgram, "Mode");
            glUseProgram(m_shaderProgram);
            glUniform1ui(modeLocation, i);
            break;
        }
    }
    if (GetMainWindow().IsKeyPressed(GLFW_KEY_TAB))
    {
        const float projMatrix[16] = { 0, -1.294f, -0.721f, -0.707f, 1.83f, 0, 0, 0, 0, 1.294f, -0.721f, -0.707f, 0, 0, 1.24f, 1.414f };
        int matrixLocation = glGetUniformLocation(m_shaderProgram, "Matrix");
        glUseProgram(m_shaderProgram);
        glUniformMatrix4fv(matrixLocation, 1, false, projMatrix);
    }
}
