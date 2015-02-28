#include "traits3d/function.h"

Traits3D::Function::Function()
  : Traits3D::GridMapping()
{
}

void Traits3D::Function::setMinZ(double val)
{
	range_p.minVertex.z = val;
}

void Traits3D::Function::setMaxZ(double val)
{
	range_p.maxVertex.z = val;
}

bool Traits3D::Function::updateData()
{
	if ((umesh_p < 2) || (vmesh_p < 2) )
		return false;
	
  data_p.resize(umesh_p * vmesh_p);
	
	/* get the data */

  if (maxu_p > range_p.maxVertex.x)
    maxu_p = range_p.maxVertex.x;
  else if (minu_p < range_p.minVertex.x)
    minu_p = range_p.minVertex.x;
  
  if (maxv_p > range_p.maxVertex.y)
    maxv_p = range_p.maxVertex.y;
  else if (minv_p < range_p.minVertex.y)
    minv_p = range_p.minVertex.y;

	double dx = (maxu_p - minu_p) / (umesh_p - 1);
	double dy = (maxv_p - minv_p) / (vmesh_p - 1);
	
	for (size_t iy = 0; iy != vmesh_p; ++iy) 
	{
    size_t row_idx = iy*umesh_p;
		for (size_t ix = 0; ix != umesh_p; ++ix) 
		{
      size_t idx = row_idx + ix;
      data_p[idx] = operator()(minu_p + ix*dx, minv_p + iy*dy);
			
			if (data_p[idx] > range_p.maxVertex.z)
        data_p[idx] = range_p.maxVertex.z;
      else if (data_p[idx] < range_p.minVertex.z)
        data_p[idx] = range_p.minVertex.z;
		}
	}

	return true;
}

