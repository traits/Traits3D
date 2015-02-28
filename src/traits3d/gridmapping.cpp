#include "traits3d/helper.h"
#include "traits3d/gridmapping.h"

Traits3D::GridMapping::GridMapping()
{
  double d = std::numeric_limits<Triple::value_type>::max();
  hull_p = Box(Triple(-d, -d, -d), Triple(d, d, d));
}

bool Traits3D::GridMapping::setMeshSizeImpl(size_t u_size, size_t v_size)
{
  if (u_size == umesh_p && v_size == vmesh_p)
    return true;

  umesh_p = u_size;
  vmesh_p = v_size;

  dirty_data_p = true;

  return true;
}