#include <numeric>
#include <iomanip> 
#include <sstream>
#include "protean3d/textengine/textengine.h"

Protean3D::TextEngine::Hull::Hull()
  : bl(std::numeric_limits<float>::max(), std::numeric_limits<float>::max())
  , tr(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max())
{
}

bool Protean3D::TextEngine::setText(std::string const& val)
{
  std::vector<std::string> textv(1, val);
  return this->setTexts(textv);
}


bool Protean3D::TextEngine::setDoubleStrings(
  std::vector<double> const& values,
  int precision/* = 6*/)
{
  std::ostringstream os;
  std::vector<std::string> text(values.size());
  for (size_t i = 0; i != values.size(); ++i)
  {
    os << std::setprecision(precision) << values[i];
    text[i] = os.str();
    os.clear();
    os.str(std::string()); // clear stream
  }
  return setTexts(text);
}