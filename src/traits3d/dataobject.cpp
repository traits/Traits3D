#include <glm/gtc/matrix_transform.hpp>
#include "glb/transformation.h"
#include "traits3d/helper.h"
#include "traits3d/colortable.h"
#include "traits3d/light.h"
#include "glb/shader_std.h"
#include "traits3d/dataobject.h"

namespace traits3d
{
namespace gl
{

DataObject::DataObject()
    : Object()
{
    initShader();
    vbos_[VBOindex::Positions] = std::make_unique<glb::VBO>(&vao_p, 3);
    vbos_[VBOindex::Normals] = std::make_unique<glb::VBO>(&vao_p, 3);
    vbos_[VBOindex::DataColors] = std::make_unique<glb::VBO>(&vao_p, 4);
    vbos_[VBOindex::DataColors]->bindAttribute(shader_[ShaderIndex::TriangleStrip].programId(), glb::shadercode::Var::v_in_color);

    for (auto &s : shader_)
    {
        if (!vbos_[VBOindex::Positions]->bindAttribute(s.second.programId(), glb::shadercode::Var::v_coordinates))
            return;
    }

    ibos_[IBOindex::Polygons] = std::make_unique<glb::IBO>(&vao_p);
    ibos_[IBOindex::Mesh] = std::make_unique<glb::IBO>(&vao_p);
}

bool DataObject::initShader()
{
    glb::Shader s;

    if (!s.create(glb::shadercode::Vertex::Line, glb::shadercode::Fragment::Simple))
        return false;

    shader_[ShaderIndex::Lines] = s;

    //if (!s.create(GL::shadercode::Vertex::TriangleStrip, GL::shadercode::Fragment::Simple))
    //  return false;

    if (!s.create(glb::shadercode::Vertex::Blinn, glb::shadercode::Fragment::Blinn))
        return false;

    shader_[ShaderIndex::TriangleStrip] = s;
    return true;
}

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool DataObject::setPositionData(std::vector<TripleF> const &data,
                                 size_t xsize, size_t ysize)
{
    vertices_.modified = true;

    if (!vertices_.value.setData(data, xsize, ysize))
        return false;

    //if (maintain_normals_)
    {
        if (!calculateNormals(normals_, vertices_.value))
            return false;
    }
    //mesh_renderer_.createData(data, xsize, ysize);
    return true;
}

bool DataObject::setPositionData(TripleVector const &data,
                                 size_t xsize, size_t ysize)
{
    std::vector<TripleF> fdata = convert(data);
    return setPositionData(fdata, xsize, ysize);
}

bool DataObject::setPositionData(MatrixF const &data)
{
    return setPositionData(data.linearBuffer(), data.xSize(), data.ySize());
}

bool DataObject::updatePositionData(std::vector<TripleF> const &data)
{
    if (!vertices_.value.setData(data, vertices_.value.xSize(), vertices_.value.ySize()))
        return false;

    //if (maintain_normals_)
    {
        if (!calculateNormals(normals_, vertices_.value) || !vbos_[VBOindex::Normals]->setData(normals_.linearBuffer()))
            return false;
    }
    return vbos_[VBOindex::Positions]->setData(vertices_.value.linearBuffer());
}

bool DataObject::updatePositionData(TripleVector const &data)
{
    std::vector<TripleF> fdata = convert(data);
    return updatePositionData(fdata);
}

void DataObject::setColor(ColorVector const &data)
{
    colors_ = data;
}

bool DataObject::setMeshColor(Color const &data)
{
    return shader_[ShaderIndex::Lines].setUniformVec4(data, glb::shadercode::Var::v_in_color);
}

void DataObject::draw(glb::Transformation const &matrices)
{
    vbos_[VBOindex::DataColors]->bindAttribute(shader_[ShaderIndex::TriangleStrip].programId(), glb::shadercode::Var::v_in_color);
    vbos_[VBOindex::Positions]->bindAttribute(shader_[ShaderIndex::TriangleStrip].programId(), glb::shadercode::Var::v_coordinates);
    //if (maintain_normals_)
    vbos_[VBOindex::Normals]->bindAttribute(shader_[ShaderIndex::TriangleStrip].programId(), glb::shadercode::Var::v_normals);

    if (vertices_.modified)
    {
        if (!ibos_[IBOindex::Mesh]->create(vertices_.value.xSize(), vertices_.value.ySize(), GL_LINE_STRIP)
            || !ibos_[IBOindex::Polygons]->create(vertices_.value.xSize(), vertices_.value.ySize(), GL_TRIANGLE_STRIP)
            || !vbos_[VBOindex::Positions]->setData(vertices_.value.linearBuffer()))
            return;

        if (/*maintain_normals_ &&*/ !vbos_[VBOindex::Normals]->setData(normals_.linearBuffer()))
            return;

        vertices_.modified = false;
    }

    if (colors_.modified)
    {
        ColorVector colors = ColorTable::createColors(vertices_.value.linearBuffer(), colors_.value);

        if (colors.size() != vertices_.value.linearBuffer().size() || !vbos_[VBOindex::DataColors]->setData(colors))
            return;

        colors_.modified = false;
    }

    Light bulb;
    bulb.enable(true);
    TripleF bpos(hull().minVertex.x, hull().minVertex.y,
                 hull().minVertex.z + 2 * (hull().maxVertex.z - hull().minVertex.z));
    bulb.setPosition(bpos);
    TripleF lightpos_eye_space = glm::vec3(matrices.lightMatrix() * glm::vec4(bulb.position(), 1.0));
    shader_[ShaderIndex::TriangleStrip].setUniformVec3(lightpos_eye_space, glb::shadercode::Var::light_position);
    // polygons
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, -1);
    shader_[ShaderIndex::TriangleStrip].use();
    setStdMatrices(shader_[ShaderIndex::TriangleStrip], matrices);
    ibos_[IBOindex::Polygons]->draw();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //ibos_[IBOindex::Polygons]->draw();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_FILL);
    //mesh_renderer_.draw(matrices);
    //return;
    // mesh
    shader_[ShaderIndex::Lines].use();
    ////todo [educated] hack
    //glm::mat4 ttt = proj_matrix;
    //ttt[2][2] += 5E-5f;
    //shader_[ShaderIndex::Lines].setProjectionMatrix(ttt);
    setStdMatrices(shader_[ShaderIndex::Lines], matrices);
    ibos_[IBOindex::Mesh]->draw();
}

void DataObject::setDrawType(GLenum val)
{
    vbos_[VBOindex::Positions]->setDrawType(val);
    vbos_[VBOindex::DataColors]->setDrawType(val);

    if (vbos_[VBOindex::Positions]->drawTypeModified()
        || vbos_[VBOindex::DataColors]->drawTypeModified()
        || ibos_[IBOindex::Polygons]->drawTypeModified()
        || ibos_[IBOindex::Mesh]->drawTypeModified()
       )
        vertices_.modified = true;
}

bool DataObject::maintainNormals(bool val)
{
    if (val == maintain_normals_)
        return true;

    for (auto &s : shader_)
    {
        if (val)
        {
            if (!vbos_[VBOindex::Normals]->bindAttribute(s.second.programId(), glb::shadercode::Var::v_normals))
                return false;
        }
        else
        {
            if (!vbos_[VBOindex::Normals]->unbindAttribute(s.second.programId(), glb::shadercode::Var::v_normals))
                return false;
        }
    }

    maintain_normals_ = val;
    return true;
}

bool DataObject::calculateNormals(Matrix<TripleF> &result, MatrixF const &positions)
{
    result.resize(positions.xSize(), positions.ySize());

    // all normals become (0,0,1) vectors
    if (1 == positions.xSize() || 1 == positions.ySize())
        return result.setData(std::vector<TripleF>(positions.linearBuffer().size(), TripleF(0, 0, 1)), positions.xSize(), positions.ySize());

    size_t x, y;
    auto nc = [&](size_t xoffs0, size_t yoffs0, size_t xoffs1, size_t yoffs1) -> TripleF
    {
        return glm::normalize(
            glm::cross(positions(x + xoffs0, y + yoffs0) - positions(x, y), positions(x + xoffs1, y + yoffs1) - positions(x, y))
        );
    };
    // inner normals
    std::vector<TripleF> q(4);

    if (positions.xSize() > 2 || positions.ySize() > 2)
    {
        for (x = 1; x < positions.xSize() - 1; ++x)
        {
            for (y = 1; y < positions.ySize() - 1; ++y)
            {
                q[0] = nc(1, 0, 0, 1);
                q[1] = nc(0, 1, -1, 0);
                q[2] = nc(-1, 0, 0, -1);
                q[3] = nc(0, -1, 1, 0);
                result(x, y) = glm::normalize(std::accumulate(q.begin(), q.end(), TripleF(0, 0, 0)));
            }
        }
    }

    // boundary without corners
    q.resize(2);

    for (x = 1; x < positions.xSize() - 1; ++x)
    {
        // lower boundary
        y = 0;
        q[0] = nc(1, 0, 0, 1);
        q[1] = nc(0, 1, -1, 0);
        result(x, y) = glm::normalize(std::accumulate(q.begin(), q.end(), TripleF(0, 0, 0)));
        // upper boundary
        y = positions.ySize() - 1;
        q[0] = nc(-1, 0, 0, -1);
        q[1] = nc(0, -1, 1, 0);
        result(x, y) = glm::normalize(std::accumulate(q.begin(), q.end(), TripleF(0, 0, 0)));
    }

    for (y = 1; y < positions.ySize() - 1; ++y)
    {
        // left boundary
        x = 0;
        q[0] = nc(0, -1, 1, 0);
        q[1] = nc(1, 0, 0, 1);
        result(x, y) = glm::normalize(std::accumulate(q.begin(), q.end(), TripleF(0, 0, 0)));
        // right boundary
        x = positions.xSize() - 1;
        q[0] = nc(0, 1, -1, 0);
        q[1] = nc(-1, 0, 0, -1);
        result(x, y) = glm::normalize(std::accumulate(q.begin(), q.end(), TripleF(0, 0, 0)));
    }

    // corners
    x = 0;
    y = 0;
    result(x, y) = nc(1, 0, 0, 1);
    x = positions.xSize() - 1;
    y = 0;
    result(x, y) = nc(0, 1, -1, 0);
    x = positions.xSize() - 1;
    y = positions.ySize() - 1;
    result(x, y) = nc(-1, 0, 0, -1);
    x = 0;
    y = positions.ySize() - 1;
    result(x, y) = nc(0, -1, 1, 0);
    return true;
}

} // ns
} // ns