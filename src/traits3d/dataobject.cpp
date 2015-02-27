#include <glm/gtc/matrix_transform.hpp>
#include "traits3d/helper.h"
#include "traits3d/colortable.h"
#include "traits3d/dataobject.h"

Traits3D::GL::DataObject::DataObject()
  : GL::Object()
{
  initShader();
  vbos_[VBOindex::Position] = std::make_unique<VBO>(&vao_p);
  vbos_[VBOindex::DataColor] = std::make_unique<VBO>(&vao_p);
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
bool Traits3D::GL::DataObject::addPositionData(std::vector<TripleF> const& data,
    size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  if (!addPositionDataCommon(xsize, ysize, data, drawtype))
    return false;

  calculateBox(data);
  return true;
}

bool Traits3D::GL::DataObject::addPositionData(TripleVector const& data,
    size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  double excess;
  std::vector<TripleF> fdata = Traits3D::GL::scale(excess, data);
  if (!addPositionDataCommon(xsize, ysize, fdata, drawtype))
    return false;

  hull_ = Traits3D::calculateBox(data);
  return true;

}

bool Traits3D::GL::DataObject::updatePositionData(std::vector<TripleF> const& data)
{
  calculateBox(data);

  TripleVector ddata(data.size());
  std::copy(data.begin(), data.end(), ddata.begin());

  ColorVector colors = Traits3D::ColorTable::createColors(ddata, colors_);
  vbos_[VBOindex::DataColor]->setData(colors);

  return vbos_[VBOindex::Position]->setData(data);
}

bool Traits3D::GL::DataObject::updatePositionData(TripleVector const& data)
{
  hull_ = Traits3D::calculateBox(data);

  double excess;
  std::vector<TripleF> fdata = Traits3D::GL::scale(excess, data);

  ColorVector colors = Traits3D::ColorTable::createColors(data, colors_);
  vbos_[VBOindex::DataColor]->setData(colors);

  return vbos_[VBOindex::Position]->setData(fdata);
}

// todo check size against position vector[s]
bool Traits3D::GL::DataObject::addColor(ColorVector const& data)
{
  if (!vbos_[VBOindex::DataColor]->setData(data))
    return false;

  colors_ = data;
  return true;
}

bool Traits3D::GL::DataObject::addMeshColor(Color const& data)
{
  return shader_[ShaderIndex::Lines].setUniformVec4(data, GL::ShaderCode::Vertex::v_in_color);
}


void Traits3D::GL::DataObject::draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix)
{
  // have to rebind here
  shader_[ShaderIndex::TriangleStrip].bindAttribute(*vbos_[VBOindex::DataColor], GL::ShaderCode::Vertex::v_in_color);
  for (auto& s : shader_)
  {
    if (!s.second.bindAttribute(*vbos_[VBOindex::Position], GL::ShaderCode::Vertex::v_coordinates))
      return;
  }

  // polygons
  shader_[ShaderIndex::TriangleStrip].use();
  shader_[ShaderIndex::TriangleStrip].setProjectionMatrix(proj_matrix);
  shader_[ShaderIndex::TriangleStrip].setModelViewMatrix(mv_matrix);
  ibos_[IBOindex::Polygons]->draw(GL_STATIC_DRAW);

  // mesh
  shader_[ShaderIndex::Lines].use();
  shader_[ShaderIndex::Lines].setModelViewMatrix(mv_matrix);

  //todo [educated] hack
  glm::mat4 ttt = proj_matrix;
  ttt[2][2] += 0.0f;
  //ttt[2][2] += 5E-5f;
  shader_[ShaderIndex::Lines].setProjectionMatrix(ttt);
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

  for (auto& s : shader_)
  {
    if (!s.second.bindAttribute(*vbos_[VBOindex::Position], GL::ShaderCode::Vertex::v_coordinates))
      return false;
  }
  return true;
}

void Traits3D::GL::DataObject::calculateBox(std::vector<TripleF> const& data)
{
  if (data.empty())
    return;
  TripleVector ddata(data.size());
  std::copy(data.begin(), data.end(), ddata.begin());

  hull_ = Traits3D::calculateBox(ddata);
}

