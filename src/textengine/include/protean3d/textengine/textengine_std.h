#pragma once

#include <memory>
#include "protean3d/textengine/textengine.h"

namespace Protean3D
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
    bool initializeGL() override;
    bool setTexts(std::vector<std::string> const& texts) override;
    bool drawText(
      std::vector<TextEngine::Position> const& positions,
      std::vector<glm::vec4> const& colors) override;


  private:
    const std::string VertexCode_;
    const std::string FragmentCode_;

    std::unique_ptr<GL::Shader> shader_;
    std::unique_ptr<GL::VAO> vao_;
    std::unique_ptr<GL::VBO> vbo_;

    class GLHider; // pimple OpenGL stuff
    std::unique_ptr<GLHider> tex_atlas_;
    
    class StbHider; // pimple stb stuff
    std::unique_ptr <StbHider> cdata_;

    const size_t quad_points = 6; // character quad rendered by 2 triangles

    std::vector<Text> texts_;
    std::vector<glm::vec4> coords_;
  };
}