#include "traits3d/helper.h"
#include "traits3d/gridmapping.h"

Traits3D::GridMapping::GridMapping()
{
  double d = std::numeric_limits<Triple::value_type>::max();
  hull_p = Box(Triple(-d, -d, -d), Triple(d, d, d));
}

bool Traits3D::GridMapping::setMeshSize(size_t u_size, size_t v_size, bool update /*= true*/)
{
  if (u_size == umesh_p && v_size == vmesh_p)
    return true;

  umesh_p = u_size;
  vmesh_p = v_size;

  if (update)
    if (!this->updateData())
      return false;

  return true;
}
