#include "traits3d/helper.h"
#include "traits3d/gridmapping.h"

Traits3D::GridMapping::GridMapping()
{
	setMesh(0,0);
	setDomain(0,0,0,0);

  double d = std::numeric_limits<Triple::value_type>::max();
  restrictRange(Box(Triple(-d, -d, -d), Triple(d, d, d)));
}

void Traits3D::GridMapping::setMesh(size_t columns, size_t rows)
{
	umesh_p = columns;
	vmesh_p = rows;
}

bool Traits3D::GridMapping::setDomain(double minu, double maxu, double minv, double maxv)
{
	minu_p = minu;
	maxu_p = maxu;
	minv_p = minv;
	maxv_p = maxv;

  if (minu_p > maxu_p)
    std::swap(minu_p, maxu_p);
  if (minv_p > maxv_p)
    std::swap(minv_p, maxv_p);

  if ( equal(minu_p, maxu_p) || equal(minu_p, maxu_p) )
    return false;

  return true;
}

void Traits3D::GridMapping::restrictRange(Traits3D::Box const& p)
{
	range_p = p;
}

