#include <numeric>
#include "textengine.h"

Protean3D::TextEngine::Hull::Hull()
  : bl(std::numeric_limits<float>::max(), std::numeric_limits<float>::max())
  , tr(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max())
{
}

bool Protean3D::TextEngine::drawText(std::string const& text, TupleF const& position)
{
  std::vector<std::string> textv(1, text);
  std::vector<TupleF> posv(1, position);
  return this->drawText(textv, posv);
}

