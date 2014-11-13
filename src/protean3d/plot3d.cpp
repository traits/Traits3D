#include "plot3d.h"


Protean3D::Plot3D::Plot3D()
  :drawmode_(GL_POINTS)
{
  modelview_matrix_ = glm::mat4
  (
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
  projection_matrix_ = glm::mat4
  (  
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );

//todo color
  vertex_shader_src_ =
#ifdef GL_ES_VERSION_2_0
    "#version 100\n"
#else
    "#version 150\n"
#endif
    "uniform mat4 project;\n"
    "uniform mat4 modelview;\n"
    "in float x;\n"
    "in float y;\n"
    "in float z;\n"
    "out vec4 vcolor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = project * modelview * vec4(x, y, z, 1.0);\n"
    "   vcolor = vec4(y, y, y, 1.0);\n"
    "}\n";

  fragment_shader_src_ =
#ifdef GL_ES_VERSION_2_0
    "#version 100\n"
#else
    "#version 150\n"
#endif
    "in vec4 vcolor; \n"
    "out vec4 gl_FragColor;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vcolor; \n"
    "}\n";

  view_angle = 45.0f;
  aspect_ratio = 4.0f / 3.0f;
  z_near = 1.0f;
  z_far = 100.f;

  initMatrices();
}

Protean3D::Plot3D::~Plot3D()
{

}


/**********************************************************************
* OpenGL helper functions
*********************************************************************/

/**********************************************************************
* Geometry creation functions
*********************************************************************/

/**********************************************************************
* OpenGL helper functions
*********************************************************************/

void Protean3D::Plot3D::initMatrices()
{
  /* Compute the projection matrix */
  float f = 1.0f / tanf(view_angle / 2.0f);
  projection_matrix_[0][0] = f / aspect_ratio;
  projection_matrix_[1][1] = f;
  projection_matrix_[2][2] = (z_far + z_near) / (z_near - z_far);
  projection_matrix_[2][3] = -1.0f;
  projection_matrix_[3][2] = 2.0f * (z_far * z_near) / (z_near - z_far);

  /* Set the camera position */
  modelview_matrix_[3][0] = -5.0f;
  modelview_matrix_[3][1] = -5.0f;
  modelview_matrix_[3][2] = -20.0f;
}

void Protean3D::Plot3D::draw()
{
  /* render the next frame */
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(drawmode_, vao_.iboSize(0), GL_UNSIGNED_INT, 0); //todo ibo indexing

  this->updateAfter();
}

bool Protean3D::Plot3D::addPositionData(std::vector<glm::vec3> const& data, std::vector<GLuint> indexes, GLenum drawmode)
{
  return false;
}

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Protean3D::Plot3D::addPositionData(std::array<std::vector<float>, 3> const& data, std::vector<GLuint> indexes, GLenum drawmode,
  GLenum xdrawtype /*= GL_STATIC_DRAW*/, 
  GLenum ydrawtype /*= GL_STATIC_DRAW*/, 
  GLenum zdrawtype /*= GL_STATIC_DRAW*/)
{
  if (!shader_.initialized())
    if (!shader_.create(vertex_shader_src_, fragment_shader_src_))
      return false;

  drawmode_ = drawmode;

  vao_.bind();

  if (! (data[0].size() == data[1].size() && data[1].size()  == data[2].size()) )
    return false;

  vao_.appendIBO(indexes);

  GL::VBO::PrimitiveLayout datalayout;
  datalayout.components = 1;
  datalayout.type = GL_FLOAT;
  datalayout.stride = 0;
  datalayout.offset = 0;

  vao_.appendVBO(data[0], datalayout, shader_.programId(), "x", xdrawtype);
  vao_.appendVBO(data[1], datalayout, shader_.programId(), "y", ydrawtype);
  vao_.appendVBO(data[2], datalayout, shader_.programId(), "z", zdrawtype);

  glUseProgram(shader_.programId());

  shader_.setUniformMatrix(projection_matrix_, "project");
  shader_.setUniformMatrix(modelview_matrix_, "modelview");

  return true;
}

bool Protean3D::Plot3D::addColorData(std::vector<glm::vec3> const& data)
{
  return false;
}

bool Protean3D::Plot3D::updatePositionData(short index, std::vector<float> const& data)
{
  return vao_.updateVBO(index, data); //todo (index hard-wired in VAO)
}
