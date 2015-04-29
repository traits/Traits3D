#include <glm/gtc/matrix_transform.hpp>
#include "traits3d/glbase/transformation.h"
#include "traits3d/helper.h"
#include "traits3d/colortable.h"
#include "traits3d/dataobject.h"

Traits3D::GL::DataObject::DataObject()
  : GL::Object()
{
  initShader();
  vbos_[VBOindex::Position] = std::make_unique<VBO>(&vao_p, 3);
  vbos_[VBOindex::DataColor] = std::make_unique<VBO>(&vao_p, 4);

  shader_[ShaderIndex::TriangleStrip].bindAttribute(*vbos_[VBOindex::DataColor], GL::ShaderCode::Vertex::v_in_color);
  for (auto& s : shader_)
  {
    if (!s.second.bindAttribute(*vbos_[VBOindex::Position], GL::ShaderCode::Vertex::v_coordinates))
      return;
  }

  ibos_[IBOindex::Polygons] = std::make_unique<IBO>(&vao_p);
  ibos_[IBOindex::Mesh] = std::make_unique<IBO>(&vao_p);
}

bool Traits3D::GL::DataObject::initShader()
{
  GL::Shader s;

  if (!s.create(GL::ShaderCode::Vertex::Line, GL::ShaderCode::Fragment::Simple))
    return false;

  shader_[ShaderIndex::Lines] = s;

  if (!s.create(GL::ShaderCode::Vertex::TriangleStrip, GL::ShaderCode::Fragment::Simple))
    return false;

  shader_[ShaderIndex::TriangleStrip] = s;

  return true;
}

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Traits3D::GL::DataObject::setPositionData(std::vector<TripleF> const& data,
    size_t xsize, size_t ysize)
{
  data_.modified = true;
  if (!data_.value.setData(data, xsize, ysize))
    return false;

  //mesh_renderer_.createData(data, xsize, ysize);

  return true;
}

bool Traits3D::GL::DataObject::setPositionData(TripleVector const& data,
    size_t xsize, size_t ysize)
{
  std::vector<TripleF> fdata = convert(data);
  return setPositionData(fdata, xsize, ysize);
}

bool Traits3D::GL::DataObject::setPositionData(MatrixF const& data)
{
  return setPositionData(data.linearBuffer(), data.xSize(), data.ySize());
}

bool Traits3D::GL::DataObject::updatePositionData(std::vector<TripleF> const& data)
{
  if (!data_.value.setData(data, data_.value.xSize(), data_.value.ySize()))
    return false;

  return vbos_[VBOindex::Position]->setData(data_.value.linearBuffer());
}

bool Traits3D::GL::DataObject::updatePositionData(TripleVector const& data)
{
  std::vector<TripleF> fdata = convert(data);
  return updatePositionData(fdata);
}

void Traits3D::GL::DataObject::setColor(ColorVector const& data)
{
  colors_ = data;
}

bool Traits3D::GL::DataObject::setMeshColor(Color const& data)
{
  return shader_[ShaderIndex::Lines].setUniformVec4(data, GL::ShaderCode::Vertex::v_in_color);
}

void Traits3D::GL::DataObject::draw(Transformation const& matrices)
{
  shader_[ShaderIndex::TriangleStrip].bindAttribute(*vbos_[VBOindex::DataColor], GL::ShaderCode::Vertex::v_in_color);
  shader_[ShaderIndex::TriangleStrip].bindAttribute(*vbos_[VBOindex::Position], GL::ShaderCode::Vertex::v_coordinates);

  if (data_.modified)
  {
    if ( !ibos_[IBOindex::Mesh]->create(data_.value.xSize(), data_.value.ySize(), GL_LINE_STRIP)
      || !ibos_[IBOindex::Polygons]->create(data_.value.xSize(), data_.value.ySize(), GL_TRIANGLE_STRIP)
      || !vbos_[VBOindex::Position]->setData(data_.value.linearBuffer()))
      return;

    data_.modified = false;
  }

  if (colors_.modified)
  {
    ColorVector colors = Traits3D::ColorTable::createColors(data_.value.linearBuffer(), colors_.value);
    if (colors.size() != data_.value.linearBuffer().size() || !vbos_[VBOindex::DataColor]->setData(colors))
      return;

    colors_.modified = false;
  }

  // polygons
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1, -1);
  shader_[ShaderIndex::TriangleStrip].use();
  shader_[ShaderIndex::TriangleStrip].setMatrices(matrices);
  ibos_[IBOindex::Polygons]->draw(GL_STATIC_DRAW);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //ibos_[IBOindex::Polygons]->draw(GL_STATIC_DRAW);
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
  shader_[ShaderIndex::Lines].setMatrices(matrices);
  ibos_[IBOindex::Mesh]->draw(GL_STATIC_DRAW);
}

void Traits3D::GL::DataObject::setDrawType(GLenum val)
{
  vbos_[VBOindex::Position]->setDrawType(val);
  vbos_[VBOindex::DataColor]->setDrawType(val);

  if (vbos_[VBOindex::Position]->drawTypeModified() || vbos_[VBOindex::DataColor]->drawTypeModified())
    data_.modified = true;
}
