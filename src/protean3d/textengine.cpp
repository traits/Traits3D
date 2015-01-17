#include <numeric>
#include "textengine.h"

Protean3D::TextEngine::Hull::Hull()
  : bl(std::numeric_limits<float>::max(), std::numeric_limits<float>::max())
  , tr(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max())
{
}

bool Protean3D::TextEngine::setText(std::string const& text)
{
  std::vector<std::string> textv(1, text);
  return this->setText(textv);
}

std::string Protean3D::TextEngine::d2t(double val)
{
  return std::to_string(val);
}

