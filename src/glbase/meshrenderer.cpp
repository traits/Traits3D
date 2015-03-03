#include "traits3d/glbase/meshrenderer.h"


const char* Traits3D::GL::MeshRenderer::VertexCode =
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "uniform mat4 proj_matrix; \n"
  "uniform mat4 mv_matrix; \n"
  "layout (location = 0) in vec3 v_coordinates;\n"
  "in vec3 v_normals;\n"
  "uniform vec4 v_in_color;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = proj_matrix * mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "}"
};

const char* Traits3D::GL::MeshRenderer::FragmentCode =
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec4 v_out_color;\n"
  "out vec4 frag_color;\n"
  "void main()\n"
  "{"
  "  frag_color = v_out_color;\n"
  "}"
};

Traits3D::GL::MeshRenderer::MeshRenderer()
{
  if (!shader_.create(VertexCode, FragmentCode))
    return; //todo throw

  vbo_ = std::make_unique<VBO>(&vao_, 3);
  ibo_ = std::make_unique<IBO>(&vao_);
}

void Traits3D::GL::MeshRenderer::createData(std::vector<TripleF> const& mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize)
{
  if (mesh_data.empty())
    return;

  float delta = 0.1f;

  std::vector<TripleF> mdata_;
  mdata_.resize(2 * (mesh_data.size()));

  for (size_t y = 0; y < ysize; y += 1)
  {
    size_t row = y*xsize;
    for (size_t x = 0; x < xsize; ++x)
    {
      mdata_[2 * row + x] = mesh_data[row + x];
      mdata_[2 * row + xsize + x] = (y != ysize - 1) ? mesh_data[row + x] + delta*(mesh_data[row + x + xsize] - mesh_data[row + x]) : mesh_data[row + x];
    }
  }

  if (!vbo_->setData(mdata_, GL_STATIC_DRAW))
    return;

  std::vector<IndexMaker::IndexType> midata;

  for (auto y = 0; y < 2 * ysize - 1; y += 2)
  {
    auto row = y*xsize;
    for (auto x = 0; x < xsize; ++x)
    {
      midata.push_back(2 * row + x);
      midata.push_back(2 * row + xsize + x);
    }
    if (y == 2 * ysize - 2)
      break;
    midata.push_back(std::numeric_limits<IndexMaker::IndexType>::max());
  }

  ibo_->setData(midata, true);
}

void Traits3D::GL::MeshRenderer::draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix)
{
  Color color(0, 0.8f, 0, 1);
  shader_.use();

  shader_.bindAttribute(*vbo_, GL::ShaderCode::Vertex::v_coordinates);
  shader_.setUniformVec4(color, GL::ShaderCode::Vertex::v_in_color);
  shader_.setProjectionMatrix(proj_matrix);
  shader_.setModelViewMatrix(mv_matrix);

  ibo_->draw(GL_STATIC_DRAW);
}