#include <glm/gtc/matrix_transform.hpp>
#include "helper.h"
#include "color.h"
#include "dataobject.h"

const std::map<Protean3D::GL::DataObject::VBOindex, size_t> Protean3D::GL::DataObject::vidx =
{
  { VBOindex::Position, 0 },
  { VBOindex::DataColor, 1 },
};

const std::map<Protean3D::GL::DataObject::ShaderIndex, size_t>
Protean3D::GL::DataObject::EnumedContainer<Protean3D::GL::Shader, Protean3D::GL::DataObject::ShaderIndex>::idx_map =
{
  { Protean3D::GL::DataObject::ShaderIndex::Lines, 0 },
  { Protean3D::GL::DataObject::ShaderIndex::TriangleStrip, 1 },
};

Protean3D::GL::DataObject::DataObject()
  : GL::Object(), shader_(shader_p)
{
  initShader();

//  vidx[VBOindex::Position] = 0;
//  vidx[VBOindex::DataColor] = 1;
}


bool Protean3D::GL::DataObject::initShader()
{
  GL::Shader s;
  
  if (!s.create(GL::ShaderCode::Vertex::Line, GL::ShaderCode::Fragment::Simple))
    return false;

  shader_p.push_back(s);

  if (!s.create(GL::ShaderCode::Vertex::TriangleStrip, GL::ShaderCode::Fragment::Simple))
    return false;

  shader_p.push_back(s);

  return true;
}

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Protean3D::GL::DataObject::addPositionData(std::vector<glm::vec3> const& data,
  size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/) 
{
  vao_p.bind();

  if (xsize*ysize != data.size())
    return false;

  if (!vao_p.appendIBO(xsize, ysize, GL_LINE_STRIP))
    return false;
  
  if (!vao_p.appendIBO(xsize, ysize, GL_TRIANGLE_STRIP))
    return false;

  GL::VBO::PrimitiveLayout datalayout(3, GL_FLOAT, 0, 0);
  
  vao_p.appendVBO(data, datalayout, drawtype);

  for (auto i = 0; i != shader_p.size(); ++i)
  {
    shader_p[i].bindAttribute(vbo(VBOindex::Position), GL::ShaderCode::Vertex::v_coordinates);
    shader_p[i].setProjectionMatrix(projection_matrix_p);
    shader_p[i].setModelViewMatrix(modelview_matrix_p);
  }

  hull_ = calcHull(data);
  return true;
}


// todo check size against position vector[s]
bool Protean3D::GL::DataObject::addColor(ColorVector const& data)
{
  vao_p.bind();
  GL::VBO::PrimitiveLayout datalayout(4, GL_FLOAT, 0, 0);
  if (!vao_p.appendVBO(data, datalayout, GL_STATIC_DRAW)) //todo Reihenfolge vbo's!
    return false;
  
  colors_ = data;
  return shader_[ShaderIndex::TriangleStrip].bindAttribute(vbo(VBOindex::DataColor), GL::ShaderCode::Vertex::v_in_color);
}

bool Protean3D::GL::DataObject::addMeshColor(glm::vec4 const& data)
{
  vao_p.bind();
  return shader_[ShaderIndex::Lines].setUniformVec4(data, GL::ShaderCode::Vertex::v_in_color);
}

bool Protean3D::GL::DataObject::updatePositionData(std::vector<glm::vec3> const& data)
{
  hull_ = calcHull(data);

  if (vao_p.vboCount() > 1)
  {
    ColorVector colors = Protean3D::Color::createColors(data, colors_);
    updateVBO(VBOindex::DataColor, colors);
  }
  return updateVBO(VBOindex::Position, data);
}

void Protean3D::GL::DataObject::draw()
{
  //this->setData();
  /* render the next frame */
  //glClear(GL_COLOR_BUFFER_BIT);

  vao_p.bind();

  float shift = 5.0f;
  modelview_matrix_p = glm::translate(modelview_matrix_p, glm::vec3(shift, shift, 0));
  modelview_matrix_p = glm::rotate(modelview_matrix_p, glm::radians(1.0f), glm::vec3(0, 0, 1));

  // polygons
  shader_[ShaderIndex::TriangleStrip].use();
  shader_[ShaderIndex::TriangleStrip].setModelViewMatrix(modelview_matrix_p);
  vao_p.drawIBO(1, GL_STATIC_DRAW);


  // mesh
  
  shader_[ShaderIndex::Lines].use();
  //shader_p[0].use();
  shader_[ShaderIndex::Lines].setModelViewMatrix(modelview_matrix_p);
  
  //todo [educated] hack 
  glm::mat4 ttt = projection_matrix_p;
  ttt[2][2] += 5E-4f;
  shader_[ShaderIndex::Lines].setProjectionMatrix(ttt);

  vao_p.drawIBO(0, GL_STATIC_DRAW);

  modelview_matrix_p = glm::translate(modelview_matrix_p, glm::vec3(-shift, -shift, 0));
}

