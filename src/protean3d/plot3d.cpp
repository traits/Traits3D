#include <glm/gtc/matrix_transform.hpp>

#include "plot3d.h"


Protean3D::Plot3D::Plot3D()
{
  view_angle = 65.0f * static_cast<GLfloat>(Protean3D::PI) / 180;
  aspect_ratio = 4.0f / 3.0f;
  z_near = 1.0f;
  z_far = 100.f;

  projection_matrix_ = glm::perspective(view_angle, aspect_ratio, z_near, z_far);
  modelview_matrix_ = glm::rotate(glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3(1, 0, 0));

  /* Set the camera position */
  modelview_matrix_[3][0] = -5.0f;
  modelview_matrix_[3][1] = -4.0f;
  modelview_matrix_[3][2] = -7.0f;

  initShader();
}

Protean3D::Plot3D::~Plot3D()
{

}

bool Protean3D::Plot3D::initShader()
{
  GL::Shader s;
  
  if (!s.create(GL::ShaderCode::Vertex::Line, GL::ShaderCode::Fragment::Simple))
    return false;

  shader_.push_back(s);

  if (!s.create(GL::ShaderCode::Vertex::TriangleStrip, GL::ShaderCode::Fragment::Simple))
    return false;

  shader_.push_back(s);

  return true;
}


/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Protean3D::Plot3D::addPositionData(std::vector<glm::vec3> const& data,
  size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/) 
{
  vao_.bind();

  if (xsize*ysize != data.size())
    return false;

  if (!vao_.appendIBO(xsize, ysize, GL_LINE_STRIP))
    return false;
  
  if (!vao_.appendIBO(xsize, ysize, GL_TRIANGLE_STRIP))
    return false;

  GL::VBO::PrimitiveLayout datalayout(3, GL_FLOAT, 0, 0);
  
  vao_.appendVBO(data, datalayout, drawtype);

  for (auto i = 0; i != shader_.size(); ++i)
  {
    shader_[i].bindAttribute(vao_.vbo(0), GL::ShaderCode::Vertex::v_coordinates);
    shader_[i].setProjectionMatrix(projection_matrix_);
    shader_[i].setModelViewMatrix(modelview_matrix_);

    if (0 == i)
    {
      shader_[i].setUniformVec4(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), GL::ShaderCode::Vertex::v_in_color);
    }
  }
  return true;
}

// todo check size against position vector[s]
bool Protean3D::Plot3D::addColorData(std::vector<glm::vec4> const& data)
{
  vao_.bind();
  GL::VBO::PrimitiveLayout datalayout(4, GL_FLOAT, 0, 0);
  if (!vao_.appendVBO(data, datalayout, GL_STATIC_DRAW))
    return false;
  return shader_[1].bindAttribute(vao_.vbo(1), GL::ShaderCode::Vertex::v_in_color);
}

bool Protean3D::Plot3D::updatePositionData(std::vector<glm::vec3> const& data)
{
  return vao_.updateVBO(0, data); //todo
}

void Protean3D::Plot3D::draw()
{
  this->setData();
  /* render the next frame */
  glClear(GL_COLOR_BUFFER_BIT);

  float shift = 5.0f;
  modelview_matrix_ = glm::translate(modelview_matrix_, glm::vec3(shift, shift, 0));
  modelview_matrix_ = glm::rotate(modelview_matrix_, glm::radians(1.0f), glm::vec3(0, 0, 1));

  shader_[1].use();
  //shader_[1].setModelViewMatrix(modelview_matrix_);
  vao_.drawIBO(1, GL_STATIC_DRAW);

  shader_[0].use();
  shader_[0].setModelViewMatrix(modelview_matrix_);
  vao_.drawIBO(0, GL_STATIC_DRAW);

  modelview_matrix_ = glm::translate(modelview_matrix_, glm::vec3(-shift, -shift, 0));
}