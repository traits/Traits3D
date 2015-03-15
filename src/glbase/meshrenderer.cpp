#include <algorithm>
#include "traits3d/glbase/meshrenderer.h"


const char* Traits3D::GL::MeshRenderer::VertexCoreCode =
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

const char* Traits3D::GL::MeshRenderer::VertexSeamCode =
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
  "in vec4 v_in_color;\n"
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
  if (!core_shader_.create(VertexCoreCode, FragmentCode))
    return; //todo throw
  if (!seam_shader_.create(VertexSeamCode, FragmentCode))
    return; //todo throw

  core_vbo_ = std::make_unique<VBO>(&vao_, 3);
  seam_color_vbo_ = std::make_unique<VBO>(&vao_, 4);
  core_ibo_ = std::make_unique<IBO>(&vao_);
  seam_ibo_ = std::make_unique<IBO>(&vao_); // Saum
}

void Traits3D::GL::MeshRenderer::createData(std::vector<TripleF> const& mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize)
{
  if (mesh_data.empty() || mesh_data.size() != xsize*ysize)
    return;

  const IndexMaker::IndexType len_data = xsize*ysize;
  float delta[] = { 0.01f, 0.004f };

  std::vector<TripleF> mdata(5 * len_data - 4 * xsize + 4 * len_data - 4 * ysize);

  // original data
  std::copy(mesh_data.begin(), mesh_data.end(), mdata.begin());
  
  
  // additional data for core and seams
  
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
    // upper seam
    mdata[3 * len_data - 2 * xsize + i] = mesh_data[i] + w[1];
    // lower seam
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
      // right seam
      mdata[start + 2 * (len_data - ysize) + i] = mesh_data[row + x + 1] - w[1];
      // left seam
      mdata[start + 3 * (len_data - ysize) + i] = mesh_data[row + x] + w[1];
      ++i;
    }    
  }

  if (!core_vbo_->setData(mdata, GL_STATIC_DRAW))
    return;

  Color core_color(0, 0.8f, 0, 1);
  Color seam_color(0, 0.8f, 0, 0);
  Traits3D::ColorVector seam_colors(5 * len_data - 4 * xsize);

  // core
  std::fill(begin(seam_colors), begin(seam_colors) + 3 * len_data - 2 * xsize, core_color);
  // seam
  std::fill(begin(seam_colors) + 3 * len_data - 2 * xsize, end(seam_colors), seam_color);

  if (!seam_color_vbo_->setData(seam_colors, GL_STATIC_DRAW))
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
  core_ibo_->setData(midata, true);


  // seam

  i = 0;
  midata.resize(8 * len_data);

  auto start0 = len_data; // upper core
  auto start1 = 3 * len_data - 2 * xsize; // upper seam
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
  start1 = 4 * len_data - 3 * xsize; // lower seam
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
  seam_ibo_->setData(midata, true);
}

void Traits3D::GL::MeshRenderer::draw(MatrixStack const& matrices)
{
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  Color color(0, 0.8f, 0, 1);
  core_shader_.use();
  core_shader_.bindAttribute(*core_vbo_, GL::ShaderCode::Vertex::v_coordinates);
  core_shader_.setUniformVec4(color, GL::ShaderCode::Vertex::v_in_color);
  //core_shader_.setProjectionMatrix(proj_matrix);
  
  core_shader_.setMatrices(matrices);
  core_ibo_->draw(GL_STATIC_DRAW);

  GL::State blend(GL_BLEND, GL_TRUE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  seam_shader_.use();
  seam_shader_.bindAttribute(*core_vbo_, GL::ShaderCode::Vertex::v_coordinates);
  seam_shader_.bindAttribute(*seam_color_vbo_, GL::ShaderCode::Vertex::v_in_color);
  seam_shader_.setMatrices(matrices);
  seam_ibo_->draw(GL_STATIC_DRAW);
}