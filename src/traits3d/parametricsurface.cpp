#include "traits3d/parametricsurface.h"


Traits3D::ParametricSurface::ParametricSurface()
:GridMapping()
{
}

void Traits3D::ParametricSurface::setPeriodic(bool u, bool v)
{
  uperiodic_p = u;
  vperiodic_p = v;
}

bool Traits3D::ParametricSurface::updateData()
{
  if ((umesh_p < 2) || (vmesh_p < 2))
    return false;

  data_p.resize(umesh_p * vmesh_p);

	/* get the data */

	double du = (maxu_p - minu_p) / (umesh_p - 1);
	double dv = (maxv_p - minv_p) / (vmesh_p - 1);
	
  for (size_t iv = 0; iv != vmesh_p; ++iv)
  {
    size_t v_start = iv*umesh_p;
    for (size_t iu = 0; iu != umesh_p; ++iu)
    {
      size_t idx = v_start + iu;
      data_p[idx] = operator()(minu_p + iu*du, minv_p + iv*dv);

      if (data_p[idx].x > range_p.maxVertex.x)
        data_p[idx].x = range_p.maxVertex.x;
      else if (data_p[idx].x < range_p.minVertex.x)
        data_p[idx].x = range_p.minVertex.x;

      if (data_p[idx].y > range_p.maxVertex.y)
        data_p[idx].y = range_p.maxVertex.y;
      else if (data_p[idx].y < range_p.minVertex.y)
        data_p[idx].y = range_p.minVertex.y;
      
      if (data_p[idx].z > range_p.maxVertex.z)
        data_p[idx].z = range_p.maxVertex.z;
      else if (data_p[idx].z < range_p.minVertex.z)
        data_p[idx].z = range_p.minVertex.z;
    }
  }

	return true;
}
