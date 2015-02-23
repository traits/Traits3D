#include <numeric>
#include <iomanip> 
#include <sstream>
#include "traits3d/textengine/textengine.h"

Traits3D::TextEngine::Hull::Hull()
  : bl(std::numeric_limits<float>::max(), std::numeric_limits<float>::max())
  , tr(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max())
{
}

bool Traits3D::TextEngine::appendDouble(double value, std::streamsize precision /*= 6*/)
{
  return this->appendText(double2text(value, precision));
}

bool Traits3D::TextEngine::setDouble(double value, std::streamsize precision /*= 6*/, size_t index /*= 0*/)
{
  return this->setText(double2text(value,precision), index);
}

std::string Traits3D::TextEngine::double2text(double value, std::streamsize precision /*= 6*/)
{
  std::ostringstream os;
  os << std::setprecision(precision) << value;
  return os.str();

  //os.clear();
  //os.str(std::string()); // clear stream
}
