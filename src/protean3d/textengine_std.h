#pragma once

#include <memory>
#include "textengine/stb_truetype.h"
#include "vao.h"
#include "vbo.h"
#include "shader.h"
#include "textengine.h"

namespace Protean3D
{
  class StandardTextEngine : public TextEngine
  {
  public:
    StandardTextEngine();
    bool initializeGL() override;
    bool drawText(
      std::vector<std::string> const& texts,
      std::vector<TupleF> const& positions
      ) override;

    bool setColor(Protean3D::Color const &color) override;

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
  };
}