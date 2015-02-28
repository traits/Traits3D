#include "traits3d/helper.h"
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

bool Traits3D::ParametricSurface::setDomain(double min_u, double max_u, double min_v, double max_v, bool update /*= true*/)
{
  if (min_u >= max_u || min_v >= max_v)
    return false;

  if (equal(min_u, minu_p) && equal(max_u, maxu_p) && equal(min_v, minv_p) && equal(max_u, maxu_p))
    return true;

  minu_p = min_u;
  maxu_p = max_u;
  minv_p = min_v;
  maxv_p = max_v;

  if (update)
    if (!updateData())
      return false;

  return true;
}

bool Traits3D::ParametricSurface::setHull(Traits3D::Box const& hull, bool update /*= true*/)
{
  if (equal(hull, hull_p))
    return true;

  hull_p = hull;

  if (update)
    if (!updateData())
      return false;
}


bool Traits3D::ParametricSurface::updateData()
{
  if ((umesh_p < 2) || (vmesh_p < 2))
    return false;

  data_p.resize(umesh_p * vmesh_p);

	/* get the data */

	double du = (maxu_p - minu_p) / (umesh_p - 1);
	double dv = (maxv_p - minv_p) / (vmesh_p - 1);
	
  Triple& hmax = hull_p.maxVertex;
  Triple& hmin = hull_p.minVertex;

  double d = std::numeric_limits<double>::max();
  Triple tmin(d, d, d);
  Triple tmax(-d, -d, -d);

  for (size_t iv = 0; iv != vmesh_p; ++iv)
  {
    size_t v_start = iv*umesh_p;
    for (size_t iu = 0; iu != umesh_p; ++iu)
    {
      size_t idx = v_start + iu;
      Triple& p = data_p[idx];

      p = operator()(minu_p + iu*du, minv_p + iv*dv);

      if (p.x > hmax.x)
        p.x = hmax.x;
      else if (p.x < hmin.x)
        p.x = hmin.x;

      if (p.y > hmax.y)
        p.y = hmax.y;
      else if (p.y < hmin.y)
        p.y = hmin.y;
      
      if (p.z > hmax.z)
        p.z = hmax.z;
      else if (p.z < hmin.z)
        p.z = hmin.z;

      if (tmin.x > p.x)
        tmin.x = p.x;
      if (tmax.x < p.x)
        tmax.x = p.x;

      if (tmin.y > p.y)
        tmin.y = p.y;
      if (tmax.y < p.y)
        tmax.y = p.y;

      if (tmin.z > p.z)
        tmin.z = p.z;
      if (tmax.z < p.z)
        tmax.z = p.z;
    }
  }

  hull_p = Box(tmin, tmax);

	return true;
}
