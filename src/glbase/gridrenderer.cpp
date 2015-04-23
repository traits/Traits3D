#include <algorithm>
#include "traits3d/glbase/gridrenderer.h"


const char* Traits3D::GL::GridRenderer::VertexCode =
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

const char* Traits3D::GL::GridRenderer::FragmentCode =
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

Traits3D::GL::GridRenderer::GridRenderer()
{
  if (!shader_.create(VertexCode, FragmentCode))
    return; //todo throw

  vbo_ = std::make_unique<VBO>(&vao_p, 3);
}

bool Traits3D::GL::GridRenderer::createData(
  std::vector<TripleF> const& start_u, std::vector<TripleF> const& stop_u,
  std::vector<TripleF> const& start_v, std::vector<TripleF> const& stop_v)
{
  size_t u_cnt = start_u.size();
  size_t v_cnt = start_v.size();
  
  if (0 == u_cnt || 0 == v_cnt || u_cnt != stop_u.size() || v_cnt != stop_v.size())
    return false;

  // fill VBO

  vbo_data_.resize(2 * (u_cnt + v_cnt));

  for (auto u = 0; u != u_cnt; ++u)
  {
    vbo_data_[2 * u] = start_u[u];
    vbo_data_[2 * u + 1] = stop_u[u];
  }

  size_t start = 2 * u_cnt;
  for (auto v = 0; v != v_cnt; ++v)
  {
    vbo_data_[start + 2 * v] = start_v[v];
    vbo_data_[start + 2 * v + 1] = stop_v[v];
  }

  return vbo_->setData(vbo_data_, GL_STATIC_DRAW);
}

void Traits3D::GL::GridRenderer::draw(Transformation const& matrices)
{
  if (!shader_.use())
    return;

  shader_.bindAttribute(*vbo_, GL::ShaderCode::Vertex::v_coordinates);
  shader_.setUniformVec4(color_, GL::ShaderCode::Vertex::v_in_color);
  shader_.setMatrices(matrices);
  vbo_->draw(GL_LINES);
}