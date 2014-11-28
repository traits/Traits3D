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
  
  if (!s.create(shader_mill_.vertexCode(GL::VertexShaderCategory::Lines), shader_mill_.fragmentCode()))
    return false;

  shader_.push_back(s);

  if (!s.create(shader_mill_.vertexCode(GL::VertexShaderCategory::Triangles), shader_mill_.fragmentCode()))
    return false;

  shader_.push_back(s);

  return true;
}


bool Protean3D::Plot3D::addPositionData(std::vector<glm::vec3> const& data, GLenum drawmode)
{
  return false;
}

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Protean3D::Plot3D::addPositionData(std::array<std::vector<float>, 3> const& data, size_t xsize, size_t ysize, 
  GLenum xdrawtype /*= GL_STATIC_DRAW*/, 
  GLenum ydrawtype /*= GL_STATIC_DRAW*/, 
  GLenum zdrawtype /*= GL_STATIC_DRAW*/)
{
  vao_.bind();

  if (! (data[0].size() == data[1].size() && data[1].size()  == data[2].size()) )
    return false;

  if (xsize*ysize != data[0].size())
    return false;

  if (!vao_.appendIBO(xsize, ysize, GL_LINE_STRIP))
    return false;
  
  if (!vao_.appendIBO(xsize, ysize, GL_TRIANGLE_STRIP))
    return false;

  GL::VBO::PrimitiveLayout datalayout(1, GL_FLOAT, 0, 0);
  
  vao_.appendVBO(data[0], datalayout, xdrawtype);
  vao_.appendVBO(data[1], datalayout, ydrawtype);
  vao_.appendVBO(data[2], datalayout, zdrawtype);

  for (auto i = 0; i != shader_.size(); ++i)
  {
    vao_.bindShader(0, shader_[i].programId(), "x");
    vao_.bindShader(1, shader_[i].programId(), "y");
    vao_.bindShader(2, shader_[i].programId(), "z");

    shader_[i].use();
    shader_[i].setUniformMatrix(projection_matrix_, GL::ShaderMill::proj_matrix);
    shader_[i].setUniformMatrix(modelview_matrix_, GL::ShaderMill::mv_matrix);

    if (0 == i)
    {
      glm::vec4 color(0.0f, 0.0f, 1.0f, 1.0f);
      shader_[i].setUniformVec4(color, GL::ShaderMill::v_in_color);
    }
    else if (1 == i)
    {
      vao_.bindShader(3, shader_[i].programId(), GL::ShaderMill::v_in_color.c_str());
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
  return vao_.bindShader(3, shader_[1].programId(), GL::ShaderMill::v_in_color.c_str());
}

bool Protean3D::Plot3D::updatePositionData(short index, std::vector<float> const& data)
{
  return vao_.updateVBO(index, data); //todo (index hard-wired in VAO)
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
  //shader_[1].setUniformMatrix(modelview_matrix_, GL::ShaderMill::mv_matrix);
  vao_.drawIBO(1, GL_STATIC_DRAW);

  shader_[0].use();
  shader_[0].setUniformMatrix(modelview_matrix_, GL::ShaderMill::mv_matrix);
  vao_.drawIBO(0, GL_STATIC_DRAW);

  modelview_matrix_ = glm::translate(modelview_matrix_, glm::vec3(-shift, -shift, 0));
}