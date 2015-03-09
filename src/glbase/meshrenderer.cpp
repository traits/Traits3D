#include <algorithm>
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
  ibo_core_ = std::make_unique<IBO>(&vao_);
  ibo_border_ = std::make_unique<IBO>(&vao_); // Saum
}

void Traits3D::GL::MeshRenderer::createData(std::vector<TripleF> const& mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize)
{
  if (mesh_data.empty() || mesh_data.size() != xsize*ysize)
    return;

  const IndexMaker::IndexType len_data = xsize*ysize;
  float delta[] = { 0.02f, 0.008f };

  std::vector<TripleF> mdata(5 * len_data - 4 * xsize + 4 * len_data - 4 * ysize);

  // original data
  std::copy(mesh_data.begin(), mesh_data.end(), mdata.begin());
  
  
  // additional data for core and rims
  
  TripleF w[2];

  // x direction
  for (auto i = 0; i != len_data - xsize; ++i)
  {
    w[0] = delta[0] * glm::normalize(mesh_data[i + xsize] - mesh_data[i]);
    w[1] = (delta[0] + delta[1]) * glm::normalize(mesh_data[i + xsize] - mesh_data[i]);

    // upper core
    mdata[len_data + i] = mesh_data[i] + w[0];
    // lower core
    mdata[2 * len_data - xsize + i] = mesh_data[i+xsize] - w[0];
    // upper rim
    mdata[3 * len_data - 2 * xsize + i] = mesh_data[i] + w[1];
    // lower rim
    mdata[4 * len_data - 3 * xsize + i] = mesh_data[i+xsize] - w[1];
  }

  auto start = 5 * len_data - 4 * xsize;
  // y direction
  auto i = 0;
  for (auto x = 0; x != xsize - 1; ++x)
  {
    for (auto y = 0; y != ysize; ++y)
    {
      auto row = y*xsize;
      w[0] = delta[0] * glm::normalize(mesh_data[row + x + 1] - mesh_data[row + x]);
      w[1] = w[0] * (1 + delta[1]);

      // right core
      mdata[start + i] = mesh_data[row + x] + w[0];
      // left core
      mdata[start + len_data - ysize + i] = mesh_data[row + x + 1] - w[0];
      // right rim
      mdata[start + 2 * (len_data - ysize) + i] = mesh_data[row + x + 1] - w[1];
      // left rim
      mdata[start + 3 * (len_data - ysize) + i] = mesh_data[row + x] + w[1];
      ++i;
    }    
  }

  if (!vbo_->setData(mdata, GL_STATIC_DRAW))
    return;

  // indexes
  std::vector<IndexMaker::IndexType> midata(8*len_data);

  i = 0;
  start = len_data; // top core data start
  for (auto y = 0; y < ysize - 1; ++y)
  {
    auto row = y*xsize;
    for (auto x = 0; x < xsize; ++x)
    {
      midata[i++] = row + x;
      midata[i++] = start + row + x;
    }
    midata[i++] = std::numeric_limits<IndexMaker::IndexType>::max();
  }
  start = 2 * len_data - xsize; // bottom core data start
  for (auto y = 0; y < ysize - 1; ++y)
  {
    auto row = y*xsize;
    for (auto x = 0; x < xsize; ++x)
    {
      midata[i++] = start + row + x;
      midata[i++] = row + xsize + x;
    }
    midata[i++] = std::numeric_limits<IndexMaker::IndexType>::max();
  }


  midata.resize(i - 1);
  ibo_core_->setData(midata, true);


  // rim

  i = 0;
  midata.resize(8 * len_data);

  auto start0 = len_data; // upper core
  auto start1 = 3 * len_data - 2 * xsize; // upper rim
  for (auto y = 0; y < ysize - 1; ++y)
  {
    auto row = y*xsize;
    for (auto x = 0; x < xsize; ++x)
    {
      midata[i++] = start0 + row + x;
      midata[i++] = start1 + row + x;
    }
    midata[i++] = std::numeric_limits<IndexMaker::IndexType>::max();
  }

  start0 = 2 * len_data - xsize; // lower core
  start1 = 4 * len_data - 3 * xsize; // lower rim
  for (auto y = 0; y < ysize - 1; ++y)
  {
    auto row = y*xsize;
    for (auto x = 0; x < xsize; ++x)
    {
      midata[i++] = start1 + row + x;
      midata[i++] = start0 + row + x;
    }
    midata[i++] = std::numeric_limits<IndexMaker::IndexType>::max();
  }

  midata.resize(i - 1);
  ibo_border_->setData(midata, true);
}

void Traits3D::GL::MeshRenderer::draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix)
{

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  Color color(0, 0.8f, 0, 1);
  shader_.use();

  shader_.bindAttribute(*vbo_, GL::ShaderCode::Vertex::v_coordinates);
  shader_.setUniformVec4(color, GL::ShaderCode::Vertex::v_in_color);
  shader_.setProjectionMatrix(proj_matrix);
  shader_.setModelViewMatrix(mv_matrix);

  ibo_core_->draw(GL_STATIC_DRAW);

  shader_.setUniformVec4(Color(0,0,0.8f,1), GL::ShaderCode::Vertex::v_in_color);
  ibo_border_->draw(GL_STATIC_DRAW);
}