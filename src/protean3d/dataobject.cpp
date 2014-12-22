#include <glm/gtc/matrix_transform.hpp>
#include "helper.h"
#include "colortable.h"
#include "dataobject.h"

Protean3D::GL::DataObject::DataObject()
  : GL::Object()
{
  initShader();
  vbos_[VBOindex::Position] = std::make_unique<VBO>(&vao_p);
  vbos_[VBOindex::DataColor] = std::make_unique<VBO>(&vao_p);
  ibos_[IBOindex::Polygons] = std::make_unique<IBO>(&vao_p);
  ibos_[IBOindex::Mesh] = std::make_unique<IBO>(&vao_p);
}


bool Protean3D::GL::DataObject::initShader()
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
bool Protean3D::GL::DataObject::addPositionData(std::vector<glm::vec3> const& data,
  size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/) 
{
  if (xsize*ysize != data.size())
    return false;

  if (!ibos_[IBOindex::Mesh]->create(xsize, ysize, GL_LINE_STRIP))
    return false;
  
  if (!ibos_[IBOindex::Polygons]->create(xsize, ysize, GL_TRIANGLE_STRIP))
    return false;
  
  vbos_[VBOindex::Position]->create(data, drawtype);

  for (auto& s : shader_)
  {
    s.second.bindAttribute(*vbos_[VBOindex::Position], GL::ShaderCode::Vertex::v_coordinates);
    //s.second.setProjectionMatrix(projection_matrix_p);
    //s.second.setModelViewMatrix(modelview_matrix_p);
  }

  hull_ = calcHull(data);
  return true;
}


// todo check size against position vector[s]
bool Protean3D::GL::DataObject::addColor(ColorVector const& data)
{
  if (!vbos_[VBOindex::DataColor]->create(data, GL_STATIC_DRAW))
    return false;
  
  colors_ = data;
  return shader_[ShaderIndex::TriangleStrip].bindAttribute(*vbos_[VBOindex::DataColor], GL::ShaderCode::Vertex::v_in_color);
}

bool Protean3D::GL::DataObject::addMeshColor(Color const& data)
{
  return shader_[ShaderIndex::Lines].setUniformVec4(data, GL::ShaderCode::Vertex::v_in_color);
}

bool Protean3D::GL::DataObject::updatePositionData(std::vector<glm::vec3> const& data)
{
  hull_ = calcHull(data);

  ColorVector colors = Protean3D::ColorTable::createColors(data, colors_);
  vbos_[VBOindex::DataColor]->update(colors);

  return vbos_[VBOindex::Position]->update(data);
}

void Protean3D::GL::DataObject::draw()
{
  // polygons
  shader_[ShaderIndex::TriangleStrip].use();
  shader_[ShaderIndex::TriangleStrip].setProjectionMatrix(projection_matrix_p);
  shader_[ShaderIndex::TriangleStrip].setModelViewMatrix(modelview_matrix_p);
  ibos_[IBOindex::Polygons]->draw(GL_STATIC_DRAW);

  // mesh  
  shader_[ShaderIndex::Lines].use();
  //shader_p[0].use();
  shader_[ShaderIndex::Lines].setModelViewMatrix(modelview_matrix_p);
  
  //todo [educated] hack 
  glm::mat4 ttt = projection_matrix_p;
  ttt[2][2] += 0.0f;
  //ttt[2][2] += 5E-5f;
  shader_[ShaderIndex::Lines].setProjectionMatrix(ttt);
  shader_[ShaderIndex::Lines].setModelViewMatrix(modelview_matrix_p);
  ibos_[IBOindex::Mesh]->draw(GL_STATIC_DRAW);
}
