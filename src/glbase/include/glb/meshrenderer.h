#pragma once

#include <memory>
#include <map>
#include "traits3d/types.h"
#include "glb/ibo.h"
#include "glb/vbo.h"
#include "glb/shader.h"
#include "glb/globject.h"

namespace traits3d
{
namespace gl
{
class MeshRenderer : public glb::Object
{
public:
    static const char *VertexCoreCode;
    static const char *VertexSeamCode;
    static const char *FragmentCode;

    MeshRenderer();

    void createData2(std::vector<TripleF> const &mesh_data, glb::IndexMaker::IndexType xsize, glb::IndexMaker::IndexType ysize);
    void createData(std::vector<TripleF> const &mesh_data, glb::IndexMaker::IndexType xsize, glb::IndexMaker::IndexType ysize);
    void draw(glb::Transformation const &matrices) override;

private:
    glb::Shader core_shader_;
    glb::Shader seam_shader_;
    std::unique_ptr<glb::VBO> core_vbo_;
    std::unique_ptr<glb::VBO> offset_vbo_;
    std::unique_ptr<glb::VBO> seam_color_vbo_;
    std::unique_ptr<glb::IBO> core_ibo_;
    std::unique_ptr<glb::IBO> seam_ibo_;

    static const std::string v_core_delta_;
    static const std::string v_seam_delta_;
};
} // ns
} // ns
