#include "textengine.h"

bool Protean3D::TextEngine::drawText(std::string const& text, glm::vec2 const& position,
  Protean3D::Color const& color)
{
  std::vector<std::string> textv(1, text);
  std::vector<glm::vec2> posv(1, position);
  return this->drawText(textv, posv, color);
}

