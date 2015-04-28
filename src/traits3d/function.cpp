#include "traits3d/helper.h"
#include "traits3d/function.h"

Traits3D::Function::Function()
  : Traits3D::GridMapping()
{
}

/**
\return false for pathological cases (min >= max), true else 
*/
bool Traits3D::Function::setDomain(double min_x, double max_x, double min_y, double max_y)
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

  dirty_data_p = true;

  return true;
}


/**
\return false for pathological cases (min >= max), true else
*/
bool Traits3D::Function::setRange(double min_z, double max_z)
{
  if ((min_z >= max_z))
    return false;

  if (equal(min_z, hull_p.minVertex.z) && equal(max_z, hull_p.maxVertex.z))
    return true;

  hull_p.minVertex.z = min_z;
  hull_p.maxVertex.z = max_z;

  dirty_data_p = true;

  return true;
}


Traits3D::MatrixD const& Traits3D::Function::data()
{
  if (dirty_data_p)
    if (updateData())
      dirty_data_p = false;

  return data_p;
}


Traits3D::MatrixF Traits3D::Function::dataF()
{
  MatrixD const& d = data();
  return d.convert<TripleF>();
}

bool Traits3D::Function::updateData()
{
  if ((umesh_p < 2) || (vmesh_p < 2) )
    return false;
  
  data_p.resize(umesh_p, vmesh_p);
  
  /* get the data */

  Triple& hmax = hull_p.maxVertex;
  Triple& hmin = hull_p.minVertex;

  double dx = (hmax.x - hmin.x) / (umesh_p - 1);
  double dy = (hmax.y - hmin.y) / (vmesh_p - 1);
  
  double zmin = std::numeric_limits<double>::max();
  double zmax = -zmin;

  for (size_t iy = 0; iy != vmesh_p; ++iy) 
  {
    for (size_t ix = 0; ix != umesh_p; ++ix) 
    {
      Triple& d = data_p(ix,iy);

      d.x = hmin.x + ix*dx;
      d.y = hmin.y + iy*dy;
      d.z = operator()(d.x, d.y);
      
      if (d.z > hmax.z)
        d.z = hmax.z;
      else if (d.z < hmin.z)
        d.z = hmin.z;

      if (zmin > d.z)
        zmin = d.z;
    
      if (zmax < d.z)
        zmax = d.z;
    }
  }

  hmin.z = zmin;
  hmax.z = zmax;

  return true;
}

