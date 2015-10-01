#include <algorithm>
#include "traits3d/helper.h"
#include "traits3d/glbase/shader_std.h"
#include "traits3d/glbase/linerenderer.h"


const char *Traits3D::GL::LineRenderer::VertexCodeSingleColor =
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

const char *Traits3D::GL::LineRenderer::VertexCodeColorField =
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

const char *Traits3D::GL::LineRenderer::FragmentCode =
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

Traits3D::GL::LineRenderer::LineRenderer()
{
    if (!single_color_shader_.create(VertexCodeSingleColor, FragmentCode))
        return; //todo throw

    if (!color_field_shader_.create(VertexCodeColorField, FragmentCode))
        return; //todo throw

    position_vbo_ = std::make_unique<VBO>(&vao_p, 3);
    color_vbo_ = std::make_unique<VBO>(&vao_p, 4);
}

bool Traits3D::GL::LineRenderer::createGrid(
    std::vector<TripleF> const &start_u, std::vector<TripleF> const &stop_u,
    std::vector<TripleF> const &start_v, std::vector<TripleF> const &stop_v)
{
    size_t u_cnt = start_u.size();
    size_t v_cnt = start_v.size();

    if (0 == u_cnt || 0 == v_cnt || u_cnt != stop_u.size() || v_cnt != stop_v.size())
        return false;

    // fill VBO
    position_vbo_data_.resize(2 * (u_cnt + v_cnt));

    for (auto u = 0; u != u_cnt; ++u)
    {
        position_vbo_data_[2 * u] = start_u[u];
        position_vbo_data_[2 * u + 1] = stop_u[u];
    }

    size_t start = 2 * u_cnt;

    for (auto v = 0; v != v_cnt; ++v)
    {
        position_vbo_data_[start + 2 * v] = start_v[v];
        position_vbo_data_[start + 2 * v + 1] = stop_v[v];
    }

    if (position_vbo_->setData(position_vbo_data_))
    {
        type_ = Type::Grid;
        return true;
    }

    type_ = Type::None;
    return false;
}

bool Traits3D::GL::LineRenderer::createStripes(std::vector<std::vector<TripleF>> const &stripes,
        std::vector<ColorVector> const &colors /*= std::vector<ColorVector>()*/)
{
    if (stripes.empty())
        return false;

    if (colors.empty())
        single_color_ = true;
    else if (!Traits3D::equalSizes(stripes, colors, true))
        return false;
    else
        single_color_ = false;

    size_t len = Traits3D::addSizes(stripes);
    position_vbo_data_.resize(len);

    if (!single_color_)
        color_vbo_data_.resize(len);

    size_t pos = 0;

    for (auto i = 0; i != stripes.size(); ++i)
    {
        std::copy(stripes[i].begin(), stripes[i].end(), position_vbo_data_.begin() + pos);

        if (!single_color_)
            std::copy(colors[i].begin(), colors[i].end(), color_vbo_data_.begin() + pos);

        pos += stripes[i].size();
    }

    if (position_vbo_->setData(position_vbo_data_))
    {
        if (single_color_ || (!single_color_ && color_vbo_->setData(color_vbo_data_)))
        {
            type_ = Type::LineStripe;
            return true;
        }
    }

    type_ = Type::None;
    return false;
}

bool Traits3D::GL::LineRenderer::createStripe(std::vector<TripleF> const &stripe, ColorVector const &colors /*= ColorVector()*/)
{
    std::vector<std::vector<TripleF>> ts(1, stripe);
    std::vector<ColorVector> tc(1, colors);

    if (colors.empty())
        tc.clear();

    return createStripes(ts, tc);
}

void Traits3D::GL::LineRenderer::draw(Transformation const &matrices)
{
    if (Type::None == type_)
        return;

    if (single_color_)
    {
        if (!single_color_shader_.use())
            return;

        position_vbo_->bindAttribute(single_color_shader_.programId(), GL::ShaderCode::Var::v_coordinates);
        single_color_shader_.setUniformVec4(color_, GL::ShaderCode::Var::v_in_color);
        single_color_shader_.setMatrices(matrices);
        position_vbo_->draw(GL_LINES);
    }
    else // color vbo
    {
        if (!color_field_shader_.use())
            return;

        position_vbo_->bindAttribute(color_field_shader_.programId(), GL::ShaderCode::Var::v_coordinates);
        color_vbo_->bindAttribute(color_field_shader_.programId(), GL::ShaderCode::Var::v_in_color);
        color_field_shader_.setMatrices(matrices);
        position_vbo_->draw(GL_LINE_STRIP);
    }
}
