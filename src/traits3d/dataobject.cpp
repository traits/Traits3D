#include <glm/gtc/matrix_transform.hpp>
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
    size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  data_ = data;
  if (!addPositionDataCommon(xsize, ysize, data_, drawtype))
    return false;

  hull_ = Traits3D::calculateBox(data);
  return true;
}

bool Traits3D::GL::DataObject::setPositionData(TripleVector const& data,
    size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  double excess;
  data_ = Traits3D::GL::scale(excess, data);
  if (!addPositionDataCommon(xsize, ysize, data_, drawtype))
    return false;

  hull_ = Traits3D::calculateBox(data);
  return true;

}

bool Traits3D::GL::DataObject::updatePositionData(std::vector<TripleF> const& data)
{
  hull_ = Traits3D::calculateBox(data);
  data_ = data;

  ColorVector colors = Traits3D::ColorTable::createColors(data, colors_);
  if (!vbos_[VBOindex::DataColor]->setData(colors))
    return false;

  return vbos_[VBOindex::Position]->setData(data_);
}

bool Traits3D::GL::DataObject::updatePositionData(TripleVector const& data)
{
  hull_ = Traits3D::calculateBox(data);

  double excess;
  data_ = Traits3D::GL::scale(excess, data);

  ColorVector colors = Traits3D::ColorTable::createColors(data, colors_);
  if (!vbos_[VBOindex::DataColor]->setData(colors))
    return false;

  return vbos_[VBOindex::Position]->setData(data_);
}

//todo check size against position vector[s]
bool Traits3D::GL::DataObject::setColor(ColorVector const& data)
{
  ColorVector colors = Traits3D::ColorTable::createColors(data_, data);
  if (!vbos_[VBOindex::DataColor]->setData(colors))
    return false;

  colors_ = data;
  return true;
}

bool Traits3D::GL::DataObject::setMeshColor(Color const& data)
{
  return shader_[ShaderIndex::Lines].setUniformVec4(data, GL::ShaderCode::Vertex::v_in_color);
}


void Traits3D::GL::DataObject::draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix)
{
  // polygons
  shader_[ShaderIndex::TriangleStrip].use();
  shader_[ShaderIndex::TriangleStrip].setProjectionMatrix(proj_matrix);
  shader_[ShaderIndex::TriangleStrip].setModelViewMatrix(mv_matrix);
  ibos_[IBOindex::Polygons]->draw(GL_STATIC_DRAW);

  // mesh
  shader_[ShaderIndex::Lines].use();
  ////todo [educated] hack
  //glm::mat4 ttt = proj_matrix;
  //ttt[2][2] += 5E-5f;
  //shader_[ShaderIndex::Lines].setProjectionMatrix(ttt);
  shader_[ShaderIndex::Lines].setProjectionMatrix(proj_matrix);
  shader_[ShaderIndex::Lines].setModelViewMatrix(mv_matrix);
  ibos_[IBOindex::Mesh]->draw(GL_STATIC_DRAW);
}

bool Traits3D::GL::DataObject::addPositionDataCommon(size_t xsize, size_t ysize, std::vector<TripleF> const &data, GLenum drawtype)
{
  if (xsize*ysize != data.size())
    return false;

  if (!ibos_[IBOindex::Mesh]->create(xsize, ysize, GL_LINE_STRIP))
    return false;

  if (!ibos_[IBOindex::Polygons]->create(xsize, ysize, GL_TRIANGLE_STRIP))
    return false;

  if (!vbos_[VBOindex::Position]->setData(data, drawtype))
    return false;

  return true;
}


