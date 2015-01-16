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
    bool drawText(std::string const& text) override;
    bool drawLabel(double val) override;
  private:
    const std::string VertexCode_;
    const std::string FragmentCode_;

    GL::Shader shader_;
    std::unique_ptr<GL::VAO> vao_;
    std::unique_ptr<GL::VBO> vbo_;

    GLuint  tex_atlas_;
    void drawAt(float x, float y, std::string text, float scale, Protean3D::Color const& color);
    
    std::vector<stbtt_bakedchar> cdata; // ASCII 32..126 is 95 glyphs
  };
}