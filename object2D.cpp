#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateDiamond(
    const std::string& name,
    glm::vec3 center,
    float d1,
    float d2,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 middle = center;

    std::vector<VertexFormat> vertices =
    {
        //O - 0
        VertexFormat(middle, color),

        //A - 1
        VertexFormat(middle + glm::vec3(0, d1, 0), color),

        //E - 2
        VertexFormat(middle + glm::vec3(d2/3, d1/3, 0), color),

        //G - 3
        VertexFormat(middle + glm::vec3(d2/3 + d1, d1/3, 0), color),

        //H - 4 
        VertexFormat(middle + glm::vec3(d2/3 + d1, -d1/3, 0), color),

        //F - 5
        VertexFormat(middle + glm::vec3(d2/3, -d1/3, 0), color),

        //C - 6
        VertexFormat(middle + glm::vec3(0, -d1, 0), color),

        //B - 7
        VertexFormat(middle + glm::vec3(-d2, 0, 0), color),

        //D - 8
        VertexFormat(center + glm::vec3(d2, 0, 0), color)
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = {1, 8, 6, 2};

    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(3);
        indices.push_back(5);
        
        indices.push_back(3);
        indices.push_back(4);
        indices.push_back(5);

        indices.push_back(1);
        indices.push_back(6);
        indices.push_back(7);
    }

    diamond->InitFromData(vertices, indices);
    return diamond;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float l,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;

    std::vector<VertexFormat> vertices =
    {
        // 0 - 0
        VertexFormat(corner, color),

        // B - 1
        VertexFormat(corner + glm::vec3(0.5 * l, -l, 0), color),

        //C - 2
        VertexFormat(corner + glm::vec3(l, 0, 0), color),

        //D - 3
        VertexFormat(corner + glm::vec3(0.5 * l, l, 0), color),

        //E - 4
        VertexFormat(corner + glm::vec3(-0.5 * l, l, 0), color),

        //F - 5
        VertexFormat(corner + glm::vec3(-l, 0, 0), color),

        //A - 6
        VertexFormat(corner + glm::vec3(-0.5 * l, -l, 0), color)
    };

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices = { 5, 4, 6, 4};

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(1);
        indices.push_back(6);

        indices.push_back(4);
        indices.push_back(3);
        indices.push_back(1);

        indices.push_back(3);
        indices.push_back(2);
        indices.push_back(1);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float l,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;

    std::vector<VertexFormat> vertices =
    {
        // 0 - 0
        VertexFormat(corner, color),

        // A - 1
        VertexFormat(corner + glm::vec3(0, l + l/2, 0), color),

        //B - 2
        VertexFormat(corner + glm::vec3(l + l/2, l/2, 0), color),

        //C - 3
        VertexFormat(corner + glm::vec3(l, -l, 0), color),

        //D - 4
        VertexFormat(corner + glm::vec3(- l, -l, 0), color),

        //E - 5
        VertexFormat(corner + glm::vec3(-l - l/2, l/2, 0), color),

        //F - 6
        VertexFormat(corner + glm::vec3(0, -l/4, 0), color),
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = {6, 4, 1, 3};

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(6);
        indices.push_back(1);

        indices.push_back(6);
        indices.push_back(5);
        indices.push_back(2);
    }

    star->InitFromData(vertices, indices);
    return star;
}
