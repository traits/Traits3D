#include "protean3d/glhelper.h"

GLfloat Protean3D::GL::excess(std::vector<glm::dvec3> const& val)
{
  GLfloat ret = 0;
  for (auto v : val)
  {
    ret = std::max(ret, excess(v));
  }
  return ret;
}


std::vector<glm::vec3> Protean3D::GL::scale(double& exc, std::vector<glm::dvec3> const& val)
{
  exc = excess(val);
  if (exc > 1)
    return scale(val, exc);
  else
    return convert(val);
}

std::vector<glm::vec3> Protean3D::GL::scale(std::vector<glm::dvec3> const& val, double excess)
{
  std::vector<glm::vec3> ret(val.size());
  for (auto i = 0; i != val.size(); ++i)
  {
    ret[i] = (val[i] / excess);
  }
  return ret;
}

std::vector<glm::vec3> Protean3D::GL::convert(std::vector<glm::dvec3> const& val)
{
  std::vector<glm::vec3> ret(val.size());
  for (auto i = 0; i != val.size(); ++i)
  {
    ret[i] = static_cast<glm::vec3>(val[i]);
  }
  return ret;
}
