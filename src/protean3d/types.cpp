#if defined(_MSC_VER) /* MSVC Compiler */
#pragma warning ( disable : 4786 )
#endif

#include <stdlib.h> // qsort
#include <algorithm>

#include "types.h"

using namespace Protean3D;

#ifndef PROTEAN3D_NOT_FOR_DOXYGEN

namespace {
  // convex hull
  
  typedef double coordinate_type;

  int ccw(coordinate_type **P, int i, int j, int k) {
    coordinate_type	a = P[i][0] - P[j][0],
      b = P[i][1] - P[j][1],
      c = P[k][0] - P[j][0],
      d = P[k][1] - P[j][1];
    return a*d - b*c <= 0;	   /* true if points i, j, k counterclockwise */
  }


#define CMPM(c,A,B) \
  v = (*(coordinate_type**)A)[c] - (*(coordinate_type**)B)[c];\
  if (v>0) return 1;\
  if (v<0) return -1;

  int cmpl(const void *a, const void *b) {
    double v;
    CMPM(0,a,b);
    CMPM(1,b,a);
    return 0;
  }

  int cmph(const void *a, const void *b) {return cmpl(b,a);}


  int make_chain(coordinate_type** V, int n, int (*cmp)(const void*, const void*)) {
    int i, j, s = 1;
    coordinate_type* t;

    qsort(V, n, sizeof(coordinate_type*), cmp);
    for (i=2; i<n; i++) {
      for (j=s; j>=1 && ccw(V, i, j, j-1); j--){}
      s = j+1;
      t = V[s]; V[s] = V[i]; V[i] = t;
    }
    return s;
  }

  int _ch2d(coordinate_type **P, int n)  {
    int u = make_chain(P, n, cmpl);		/* make lower hull */
    if (!n) return 0;
    P[n] = P[0];
    return u+make_chain(P+u, n-u+1, cmph);	/* make upper hull */
  }


} // ns anon

void Protean3D::convexhull2d( std::vector<size_t>& idx, const std::vector<Tuple>& src )
{
    idx.clear();
    if (src.empty())
        return;
    if (src.size()==1)
    {
        idx.push_back(0);
        return;
    }
    coordinate_type** points = new coordinate_type*[src.size()+1] ;
    coordinate_type* P = new coordinate_type[src.size()*2];

    int i;
		for (i=0; i<(int)src.size(); ++i)
    {
        points[i] = &P[2*i];
        points[i][0] = src[i].x;
        points[i][1] = src[i].y;
    }

    coordinate_type* start = points[0];
    int m = _ch2d( points, static_cast<int>(src.size()) );
    idx.resize(m);
    
		for (i=0; i<m; ++i)
 		{
			idx[i] = (points[i] - start)/2;
		}
    delete [] points;
		delete [] P;
}

size_t Protean3D::tesselationSize(Protean3D::CellVector const& t)
{
	size_t ret = 0;
	
	for (unsigned i=0; i!=t.size(); ++i)
		ret += t[i].size();
	
	return ret;
}

Protean3D::Box Protean3D::hull(TripleVector const& data)
{
  Box hull(Triple(DBL_MAX,DBL_MAX,DBL_MAX),Triple(-DBL_MAX,-DBL_MAX,-DBL_MAX));
  for (unsigned i = 0; i!=data.size(); ++i)
	{
		if (data[i].x < hull.minVertex.x)
			hull.minVertex.x = data[i].x;
		if (data[i].y < hull.minVertex.y)
			hull.minVertex.y = data[i].y;
		if (data[i].z < hull.minVertex.z)
			hull.minVertex.z = data[i].z;
		
		if (data[i].x > hull.maxVertex.x)
			hull.maxVertex.x = data[i].x;
		if (data[i].y > hull.maxVertex.y)
			hull.maxVertex.y = data[i].y;
		if (data[i].z > hull.maxVertex.z)
			hull.maxVertex.z = data[i].z;
	}
  return hull;
}

#endif // PROTEAN3D_NOT_FOR_DOXYGEN