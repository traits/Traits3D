#include "glhelper.h"

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
  std::vector<glm::vec3> ret(val.size());
  exc = excess(val);

  if (exc > 1)
  {
    for (auto i = 0; i != val.size(); ++i)
    {
      ret[i] = (val[i] / exc);
    }
  }
  else
  {
    for (auto i = 0; i != val.size(); ++i)
    {
      ret[i].x = static_cast<GLfloat>(val[i].x);
      ret[i].y = static_cast<GLfloat>(val[i].y);
      ret[i].z = static_cast<GLfloat>(val[i].z);
    }
  }
  return ret;
}
