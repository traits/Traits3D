#pragma once

#include <memory>
#include <map>
#include "traits3d/types.h"
#include "glb/vbo.h"
#include "glb/shader.h"
#include "glb/globject.h"

namespace traits3d
{
namespace gl
{
class LineRenderer : public glb::Object
{
public:
    LineRenderer();

    void setColor(Color const &val)
    {
        color_ = val;
    }

    bool createGrid(
        std::vector<TripleF> const &start_u, std::vector<TripleF> const &stop_u,
        std::vector<TripleF> const &start_v, std::vector<TripleF> const &stop_v);

    bool createStripes(
        std::vector<std::vector<TripleF>> const &stripes,
        std::vector<ColorVector> const &colors = std::vector<ColorVector>());

    bool createStripe(
        std::vector<TripleF> const &stripe,
        ColorVector const &colors = ColorVector());

    void draw(glb::Transformation const &matrices) override;

private:
    enum class Type
    {
        None,
        Grid,
        LineStripe
    };

    Type type_ = Type::None;
    bool single_color_ = true;

    static const char *VertexCodeSingleColor;
    static const char *VertexCodeColorField;
    static const char *FragmentCode;

    glb::Shader single_color_shader_;
    glb::Shader color_field_shader_;
    std::unique_ptr<glb::VBO> position_vbo_;
    std::vector<TripleF> position_vbo_data_;
    std::unique_ptr<glb::VBO> color_vbo_;
    ColorVector color_vbo_data_;
    Color color_ = Color(0, 0, 0, 1);
};
} // ns
} // ns