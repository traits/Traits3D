#include "traits3d/gridmapping.h"

Traits3D::GridMapping::GridMapping()
{
	setMeshSize(0,0);

  double d = std::numeric_limits<Triple::value_type>::max();
  hull_p = Box(Triple(-d, -d, -d), Triple(d, d, d));
}

void Traits3D::GridMapping::setMeshSize(size_t u_size, size_t v_size)
{
  umesh_p = u_size;
  vmesh_p = v_size;
}
