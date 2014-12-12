#include <glm/gtc/matrix_transform.hpp>
#include "dataobject.h"


Protean3D::GL::DataObject::DataObject()
  : GL::Object()
{
  initShader();
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
    shader_p[i].bindAttribute(vao_p.vbo(0), GL::ShaderCode::Vertex::v_coordinates);
    shader_p[i].setProjectionMatrix(projection_matrix_p);
    shader_p[i].setModelViewMatrix(modelview_matrix_p);
  }

  calcHull(data);
  return true;
}


// todo check size against position vector[s]
bool Protean3D::GL::DataObject::addColor(std::vector<glm::vec4> const& data)
{
  vao_p.bind();
  GL::VBO::PrimitiveLayout datalayout(4, GL_FLOAT, 0, 0);
  if (!vao_p.appendVBO(data, datalayout, GL_STATIC_DRAW))
    return false;
  return shader_p[1].bindAttribute(vao_p.vbo(1), GL::ShaderCode::Vertex::v_in_color);
}

bool Protean3D::GL::DataObject::addMeshColor(glm::vec4 const& data)
{
  vao_p.bind();
  return shader_p[0].setUniformVec4(data, GL::ShaderCode::Vertex::v_in_color);
}

bool Protean3D::GL::DataObject::updatePositionData(std::vector<glm::vec3> const& data)
{
  calcHull(data);
  return vao_p.updateVBO(0, data); //todo
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
  shader_p[1].use();
  shader_p[1].setModelViewMatrix(modelview_matrix_p);
  vao_p.drawIBO(1, GL_STATIC_DRAW);


  // mesh
  shader_p[0].use();
  shader_p[0].setModelViewMatrix(modelview_matrix_p);
  
  //todo [educated] hack 
  glm::mat4 ttt = projection_matrix_p;
  ttt[2][2] += 5E-4;
  shader_p[0].setProjectionMatrix(ttt);

  vao_p.drawIBO(0, GL_STATIC_DRAW);

  modelview_matrix_p = glm::translate(modelview_matrix_p, glm::vec3(-shift, -shift, 0));
}

void Protean3D::GL::DataObject::calcHull(std::vector<glm::vec3> const& data)
{
  hull_ = Protean3D::Box(); // reset
  for (auto p : data)
  {
    if (p.x < hull_.minVertex.x)
      hull_.minVertex.x = p.x;
    if (p.y < hull_.minVertex.y)
      hull_.minVertex.y = p.y;
    if (p.z < hull_.minVertex.z)
      hull_.minVertex.z = p.z;

    if (p.x > hull_.maxVertex.x)
      hull_.maxVertex.x = p.x;
    if (p.y > hull_.maxVertex.y)
      hull_.maxVertex.y = p.y;
    if (p.z > hull_.maxVertex.z)
      hull_.maxVertex.z = p.z;
  }
}
