#pragma once

#include <memory>
#include <map>
#include "traits3d/types.h"
#include "traits3d/glbase/ibo.h"
#include "traits3d/glbase/vbo.h"
#include "traits3d/glbase/shader.h"
#include "traits3d/glbase/globject.h"

namespace Traits3D
{
namespace GL
{
class MeshRenderer : public GL::Object
{
public:
    static const char *VertexCoreCode;
    static const char *VertexSeamCode;
    static const char *FragmentCode;

    MeshRenderer();

    void createData2(std::vector<TripleF> const &mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize);
    void createData(std::vector<TripleF> const &mesh_data, IndexMaker::IndexType xsize, IndexMaker::IndexType ysize);
    void draw(Transformation const &matrices) override;

private:
    Shader core_shader_;
    Shader seam_shader_;
    std::unique_ptr<VBO> core_vbo_;
    std::unique_ptr<VBO> offset_vbo_;
    std::unique_ptr<VBO> seam_color_vbo_;
    std::unique_ptr<IBO> core_ibo_;
    std::unique_ptr<IBO> seam_ibo_;

    static const std::string v_core_delta_;
    static const std::string v_seam_delta_;
};
} // ns
} // ns
