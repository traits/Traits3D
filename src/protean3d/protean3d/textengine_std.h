#pragma once

#include <memory>
#include "textengine/stb_truetype.h"
#include "protean3d/glbase/vao.h"
#include "protean3d/glbase/vbo.h"
#include "protean3d/glbase/shader.h"
#include "protean3d/textengine.h"

namespace Protean3D
{
  class StandardTextEngine : public TextEngine
  {
  public:
    StandardTextEngine();
    bool initializeGL() override;
    bool setColor(Color const &color) override;
    bool setText(std::vector<std::string> const& texts) override;
    bool drawText(std::vector<TextEngine::Position> const& positions) override;


  private:
    const std::string VertexCode_;
    const std::string FragmentCode_;

    GL::Shader shader_;
    std::unique_ptr<GL::VAO> vao_;
    std::unique_ptr<GL::VBO> vbo_;

    GLuint  tex_atlas_;
    std::vector<stbtt_bakedchar> cdata;

    const size_t quad_points = 6; // character quad rendered by 2 triangles

    std::vector<Text> texts_;
    std::vector<glm::vec4> coords_;
  };
}