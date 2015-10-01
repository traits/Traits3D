#include <algorithm>
#include "traits3d/glbase/shader_std.h"
#include "traits3d/glbase/meshrenderer.h"

const std::string Traits3D::GL::MeshRenderer::v_core_delta_ = "v_core_delta";
const std::string Traits3D::GL::MeshRenderer::v_seam_delta_ = "v_seam_delta";


const char *Traits3D::GL::MeshRenderer::VertexCoreCode =
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

const char *Traits3D::GL::MeshRenderer::VertexSeamCode =
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

const char *Traits3D::GL::MeshRenderer::FragmentCode =
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

    core_vbo_ = std::make_unique<VBO>(&vao_p, 3);
    seam_color_vbo_ = std::make_unique<VBO>(&vao_p, 4);
    core_ibo_ = std::make_unique<IBO>(&vao_p);
    offset_vbo_ = std::make_unique<VBO>(&vao_p, 3);
    seam_ibo_ = std::make_unique<IBO>(&vao_p); // Saum
}

void Traits3D::GL::MeshRenderer::createData2(std::vector<TripleF> const &mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize)
{
    if (mesh_data.empty() || mesh_data.size() != xsize * ysize)
        return;

    const IndexMaker::IndexType len_data = mesh_data.size();
    // mesh data
    std::vector<TripleF> mdata(len_data - xsize);
    std::copy(mesh_data.begin() + xsize, mesh_data.end(), mdata.begin());

    if (!core_vbo_->setData(mdata))
        return;

    // offsets
    std::vector<TripleF> odata(mdata);

    for (auto k = 0; k != odata.size(); ++k)
        odata[k] -= mesh_data[k];

    if (!offset_vbo_->setData(odata))
        return;

    //// indexes
    //
    //std::vector<IndexMaker::IndexType> midata(xsize*(ysize-1) + );
    //for (auto k = xsize; k != len_data; ++k)
    //{
    //  midata[k] =
    //}
}

void Traits3D::GL::MeshRenderer::createData(std::vector<TripleF> const &mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize)
{
    if (mesh_data.empty() || mesh_data.size() != xsize * ysize)
        return;

    const IndexMaker::IndexType len_data = xsize * ysize;
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
        mdata[2 * len_data - xsize + i] = mesh_data[i + xsize] - w[0];
        // upper seam
        mdata[3 * len_data - 2 * xsize + i] = mesh_data[i] + w[1];
        // lower seam
        mdata[4 * len_data - 3 * xsize + i] = mesh_data[i + xsize] - w[1];
    }

    auto start = 5 * len_data - 4 * xsize;
    // y direction
    auto i = 0;

    for (auto x = 0; x != xsize - 1; ++x)
    {
        for (auto y = 0; y != ysize; ++y)
        {
            auto row = y * xsize;
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

    if (!core_vbo_->setData(mdata))
        return;

    Color core_color(0, 0.8f, 0, 1);
    Color seam_color(0, 0.8f, 0, 0);
    Traits3D::ColorVector seam_colors(5 * len_data - 4 * xsize);
    // core
    std::fill(begin(seam_colors), begin(seam_colors) + 3 * len_data - 2 * xsize, core_color);
    // seam
    std::fill(begin(seam_colors) + 3 * len_data - 2 * xsize, end(seam_colors), seam_color);

    if (!seam_color_vbo_->setData(seam_colors))
        return;

    // indexes
    std::vector<IndexMaker::IndexType> midata(8 * len_data);
    i = 0;
    start = len_data; // top core data start

    for (auto y = 0; y < ysize - 1; ++y)
    {
        auto row = y * xsize;

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
        auto row = y * xsize;

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
        auto row = y * xsize;

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
        auto row = y * xsize;

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

void Traits3D::GL::MeshRenderer::draw(Transformation const &matrices)
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Color color(0, 0.8f, 0, 1);
    core_shader_.use();
    core_vbo_->bindAttribute(core_shader_.programId(), GL::ShaderCode::Var::v_coordinates);
    core_shader_.setUniformVec4(color, GL::ShaderCode::Var::v_in_color);
    //core_shader_.setProjectionMatrix(proj_matrix);
    core_shader_.setMatrices(matrices);
    core_ibo_->draw();
    GL::State blend(GL_BLEND, GL_TRUE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    seam_shader_.use();
    core_vbo_->bindAttribute(seam_shader_.programId(), GL::ShaderCode::Var::v_coordinates);
    seam_color_vbo_->bindAttribute(seam_shader_.programId(), GL::ShaderCode::Var::v_in_color);
    seam_shader_.setMatrices(matrices);
    seam_ibo_->draw();
}