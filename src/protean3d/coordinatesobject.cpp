#include <glm/gtc/matrix_transform.hpp>
#include "coordinatesobject.h"


Protean3D::GL::CoordinatesObject::CoordinatesObject()
  : GL::Object()
{
  initShader();
}


bool Protean3D::GL::CoordinatesObject::initShader()
{
  GL::Shader s;
  
  if (!s.create(GL::ShaderCode::Vertex::Line, GL::ShaderCode::Fragment::Simple))
    return false;

  shader_p.push_back(s);

  return true;
}

bool Protean3D::GL::CoordinatesObject::setHull(Protean3D::Box const& hull)
{
  hull_ = hull;
  vao_p.bind();

  //todo

  
  float x = hull.minVertex.x;
  float X = hull.maxVertex.x;
  float y = hull.minVertex.y;
  float Y = hull.maxVertex.y;
  float z = hull.minVertex.z;
  float Z = hull.maxVertex.z;

  axes_.resize(24);

  axes_[0] = glm::vec3(x, y, z);
  axes_[1] = glm::vec3(X, y, z);
  axes_[2] = glm::vec3(x, y, Z);
  axes_[3] = glm::vec3(X, y, Z);
  axes_[4] = glm::vec3(x, Y, z);
  axes_[5] = glm::vec3(X, Y, z);
  axes_[6] = glm::vec3(x, Y, Z);
  axes_[7] = glm::vec3(X, Y, Z);

  axes_[8] = glm::vec3(x, y, z);
  axes_[9] = glm::vec3(x, Y, z);
  axes_[10] = glm::vec3(X, y, z);
  axes_[11] = glm::vec3(X, Y, z);
  axes_[12] = glm::vec3(x, y, Z);
  axes_[13] = glm::vec3(x, Y, Z);
  axes_[14] = glm::vec3(X, y, Z);
  axes_[15] = glm::vec3(X, Y, Z);
  
  axes_[16] = glm::vec3(x, y, z);
  axes_[17] = glm::vec3(x, y, Z);
  axes_[18] = glm::vec3(x, Y, z);
  axes_[19] = glm::vec3(x, Y, Z);
  axes_[20] = glm::vec3(X, y, z);
  axes_[21] = glm::vec3(X, y, Z);
  axes_[22] = glm::vec3(X, Y, z);
  axes_[23] = glm::vec3(X, Y, Z);


  GL::VBO::PrimitiveLayout datalayout(3, GL_FLOAT, 0, 0);

  vao_p.appendVBO(axes_, datalayout, GL_STATIC_DRAW); //todo (could be dynamic)

  shader_p[0].bindAttribute(vao_p.vbo(0), GL::ShaderCode::Vertex::v_coordinates);
  shader_p[0].setUniformVec4(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), GL::ShaderCode::Vertex::v_in_color);

  return true;
}

//bool Protean3D::GL::CoordinatesObject::updatePositionData(std::vector<glm::vec3> const& data)
//{
//  return vao_p.updateVBO(0, data); //todo
//}

void Protean3D::GL::CoordinatesObject::draw()
{
  vao_p.bind();

  vao_p.updateVBO(0, axes_); //todo

  float shift = 5.0f;
  modelview_matrix_p = glm::translate(modelview_matrix_p, glm::vec3(shift, shift, 0));
  modelview_matrix_p = glm::rotate(modelview_matrix_p, glm::radians(1.0f), glm::vec3(0, 0, 1));

  shader_p[0].use();
  shader_p[0].setProjectionMatrix(projection_matrix_p);
  shader_p[0].setModelViewMatrix(modelview_matrix_p);
  vao_p.vbo(0).draw(GL_LINES, 0, 24);
  modelview_matrix_p = glm::translate(modelview_matrix_p, glm::vec3(-shift, -shift, 0));
}
