#pragma once

#include <memory>
#include <array>
#include "traits3d/textengine/textengine.h"

namespace Traits3D
{
  namespace GL
  {
    class VAO;
    class VBO;
    class Shader;
  }

  class StandardTextEngine : public TextEngine
  {
  public:
    StandardTextEngine();
    ~StandardTextEngine();
    bool initializeGL() override;
    bool setTexts(std::vector<std::string> const& texts) override;
    bool appendText(std::string const& texts) override;
    bool setText(std::string const& texts, size_t index = 0) override;

    bool draw(
      std::vector<TextEngine::Position> const& positions,
      std::vector<Traits3D::Color> const& colors) override;

  protected:
    void clear() override;

  private:
    const std::string VertexCode_;
    const std::string FragmentCode_;

    std::unique_ptr<GL::Shader> shader_;
    std::unique_ptr<GL::VAO> vao_;
    std::unique_ptr<GL::VBO> vbo_;
    
    class GlStbHider; // pimple OpenGL & stb stuff
    std::unique_ptr <GlStbHider> pimpl_;

    // character quad (6 positions of two describing triangles)
    using Quad = std::array < glm::vec4, 6 >;
    // quads for all characters in text
    using Quads = std::vector < Quad >;

    struct TextQuad
    {
      Text text;
      Quads coordinates;
    };

    std::vector<TextQuad> textquads_;
  
    bool setText(TextQuad& tq, std::string const& text);
    bool createFontTexture(std::string const& font_name, size_t glyph_cnt, float font_height);
  };
}