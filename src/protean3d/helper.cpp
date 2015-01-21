#include "protean3d/helper.h"

Protean3D::Box Protean3D::calcHull(std::vector<glm::vec3> const& data)
{
  Protean3D::Box hull;
  for (auto p : data)
  {
    if (p.x < hull.minVertex.x)
      hull.minVertex.x = p.x;
    if (p.y < hull.minVertex.y)
      hull.minVertex.y = p.y;
    if (p.z < hull.minVertex.z)
      hull.minVertex.z = p.z;

    if (p.x > hull.maxVertex.x)
      hull.maxVertex.x = p.x;
    if (p.y > hull.maxVertex.y)
      hull.maxVertex.y = p.y;
    if (p.z > hull.maxVertex.z)
      hull.maxVertex.z = p.z;
  }
  return hull;
}
