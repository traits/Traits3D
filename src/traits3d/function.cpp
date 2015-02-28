#include "traits3d/helper.h"
#include "traits3d/function.h"

Traits3D::Function::Function()
  : Traits3D::GridMapping()
{
}

/**
\return false for pathological cases (min >= max), true else 
*/
bool Traits3D::Function::setDomain(double min_x, double max_x, double min_y, double max_y, bool update /*= true*/)
{
  if (min_x >= max_x || min_y >= max_y)
    return false;

  if ( equal(min_x, hull_p.minVertex.x) && equal(max_x, hull_p.maxVertex.x)
    && equal(min_x, hull_p.minVertex.y) && equal(max_x, hull_p.maxVertex.y))
    return true;

  hull_p.minVertex.x = min_x;
  hull_p.maxVertex.x = max_x;
  hull_p.minVertex.y = min_y;
  hull_p.maxVertex.y = max_y;

  if (update)
    if (!updateData())
      return false;

  return true;
}


/**
\return false for pathological cases (min >= max), true else
*/
bool Traits3D::Function::setRange(double min_z, double max_z, bool update /*= true*/)
{
  if ((min_z >= max_z))
    return false;

  if (equal(min_z, hull_p.minVertex.z) && equal(max_z, hull_p.maxVertex.z))
    return true;

  if (update)
    if (!updateData())
      return false;

  hull_p.minVertex.z = min_z;
  hull_p.maxVertex.z = max_z;

  return true;
}

bool Traits3D::Function::updateData()
{
	if ((umesh_p < 2) || (vmesh_p < 2) )
		return false;
	
  data_p.resize(umesh_p * vmesh_p);
	
	/* get the data */

  Triple& hmax = hull_p.maxVertex;
  Triple& hmin = hull_p.minVertex;

	double dx = (hmax.x - hmin.x) / (umesh_p - 1);
	double dy = (hmax.y - hmin.y) / (vmesh_p - 1);
	
  double zmin = std::numeric_limits<double>::max();
  double zmax = -zmin;

	for (size_t iy = 0; iy != vmesh_p; ++iy) 
	{
    size_t row_idx = iy*umesh_p;
		for (size_t ix = 0; ix != umesh_p; ++ix) 
		{
      size_t idx = row_idx + ix;
      data_p[idx] = operator()(hmin.x + ix*dx, hmin.y + iy*dy);
			
			if (data_p[idx] > hmax.z)
        data_p[idx] = hmax.z;
      else if (data_p[idx] < hmin.z)
        data_p[idx] = hmin.z;

      if (zmin > data_p[idx])
        zmin = data_p[idx];
    
      if (zmax < data_p[idx])
        zmax = data_p[idx];
    }
	}

  hmin.z = zmin;
  hmax.z = zmax;

	return true;
}

