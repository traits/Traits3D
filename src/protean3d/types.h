#pragma once

#if defined(_MSC_VER) /* MSVC Compiler */
  #pragma warning ( disable : 4786 )
#endif

#include "global.h"
#include "helper.h"
//#include "protean3d/gl/helper.h"

// Common namespace for all Protean3D classes
namespace Protean3D
{

const double PI = 3.14159265358979323846264338328;

//! Plotting style
enum PLOTSTYLE
{
	NOPLOT     , //!< No visible data
	WIREFRAME  , //!< Wireframe style
	HIDDENLINE , //!< Hidden Line style
	FILLED     , //!< Color filled polygons w/o edges 
	FILLEDMESH , //!< Color filled polygons w/ separately colored edges
  POINTS     , //!< User defined style (used by Enrichments)
  USER         //!< User defined style (used by Enrichments)
};

//! Shading style
enum SHADINGSTYLE
{
	FLAT,      //!< Flat shading (OpenGL)
	GOURAUD    //!< Gouraud Shading (OpenGL)
};

//! Style of Coordinate system
enum COORDSTYLE
{
	NOCOORD, //!< Coordinate system is not visible 
	BOX,     //!< Boxed
	FRAME		 //!< Frame - 3 visible axes
};

//! Different types of axis scales
enum SCALETYPE
{
	LINEARSCALE,//!< Linear scaling 
	LOG10SCALE,	//!< Logarithmic scaling (base 10)
  USERSCALE   //!< User-defined (for extensions)
};

//! Plotting style for floor data (projections)
enum FLOORSTYLE
{
	NOFLOOR,   //!< Empty floor
	FLOORISO,  //!< Isoline projections visible
	FLOORDATA //!< Projected polygons visible
};

//! The 12 axes
/**
\image html axes.png 
*/
enum AXIS
{
	X1 = 0,   //!<  1st x-axis
	X2 = 3,   //!<  2nd x-axis
	X3 = 4,   //!<  3th x-axis
	X4 = 5,   //!<  4th x-axis
	Y1 = 1,   //!<  1st y-axis
	Y2 = 8,   //!<  2nd y-axis
	Y3 = 7,   //!<  3th y-axis
	Y4 = 6,   //!<  4th y-axis
	Z1 = 2,   //!<  1st z-axis
	Z2 = 9,   //!<  2nd z-axis
	Z3 = 11,  //!<  3th z-axis
	Z4 = 10   //!<  4th z-axis
};

//! The 6 sides
enum SIDE
{
  NOSIDEGRID = 0,
  LEFT   = 1 << 0,
  RIGHT  = 1 << 1,
  CEIL   = 1 << 2,
  FLOOR  = 1 << 3,
  FRONT  = 1 << 4,
  BACK   = 1 << 5
};

//! Possible anchor points for drawing operations
enum ANCHOR
{
	BottomLeft,
	BottomRight,
	BottomCenter,
	TopLeft,
	TopRight,
	TopCenter,
	CenterLeft,
	CenterRight,
	Center
};


//! Tuple <tt>[x,y]</tt>
struct PROTEAN3D_EXPORT Tuple
{
	Tuple() : x(0), y(0) {} //!< Calls Tuple(0,0)
	Tuple(double X, double Y) : x(X), y(Y) {} //!< Initialize Tuple with x and y
	//! Tuple coordinates
  double x,y; 
};

//! Triple <tt>[x,y,z]</tt>
/**
Consider Triples also as vectors in R^3
*/
struct PROTEAN3D_EXPORT Triple
{
	//! Initialize Triple with x,y and z
	explicit Triple(double xv = 0,double yv = 0,double zv = 0) 
		: x(xv), y(yv), z(zv)
	{
	}
  
	//! Triple coordinates
	double x,y,z; 

	Triple& operator+=(Triple t)
	{
		x += t.x;
		y += t.y;
		z += t.z;

		return *this;
	}
	
	Triple& operator-=(Triple t)
	{
		x -= t.x;
		y -= t.y;
		z -= t.z;

		return *this;
	}
	Triple& operator*=(double d)
	{
		x *= d;
		y *= d;
		z *= d;

		return *this;
	}
	Triple& operator/=(double d)
	{
		x /= d;
		y /= d;
		z /= d;

		return *this;
	}
	Triple& operator*=(Triple t) // scale
	{
		x *= t.x;
		y *= t.y;
		z *= t.z;

		return *this;
	}

	bool operator!=(Triple t) const
	{
		return !isPracticallyZero(x,t.x) || !isPracticallyZero(y,t.y) || !isPracticallyZero(z,t.z);
	}
	
	bool operator==(Triple t) const
	{
		return !operator!=(t);
	}

	double length() const
	{
		double l2 = x*x + y*y + z*z;
		return (isPracticallyZero(l2)) ? 0 :sqrt(l2);
	}
	
	void normalize()
	{
		double l = length();
		if (l)
			*this /= l;
	}
};

inline const Triple operator+(const Triple& t, const Triple& t2)
{
	return Triple(t) += t2;
}
inline const Triple operator-(const Triple& t, const Triple& t2)
{
	return Triple(t) -= t2;
}
inline const Triple operator*(double d, const Triple& t)
{
	return Triple(t) *= d;
}
inline const Triple operator*(const Triple& t, double d)
{
	return Triple(t) *= d;
}
inline const Triple operator/(double d, const Triple& t)
{
	return Triple(t) /= d;
}
inline const Triple operator/(const Triple& t, double d)
{
	return Triple(t) /= d;
}
inline const Triple operator*(const Triple& t, const Triple& t2)
{
	return Triple(t) *= t2;
}

//! Box spanned by 2 Triples
/**
Please use \em normalized boxes:\n\n
minVertex.x <= maxVertex.x\n
minVertex.y <= maxVertex.y\n
minVertex.z <= maxVertex.z\n
*/
struct PROTEAN3D_EXPORT Box
{
	//! Construct non-initialized Box
	Box()
	{
	}

	//! Construct initialized Box
	/**
		minv -> minVertex\n
		maxv -> maxVertex\n
	*/
	Box(Triple minv, Triple maxv)
	: minVertex(minv), maxVertex(maxv)
	{
	}
	
	Triple minVertex;
	Triple maxVertex;
};

inline Box sum(const Box& a, const Box& b)
{
  Triple mi = a.minVertex - b.minVertex;
  mi.x = (mi.x<0) ? a.minVertex.x : b.minVertex.x; 
  mi.y = (mi.y<0) ? a.minVertex.y : b.minVertex.y; 
  mi.z = (mi.z<0) ? a.minVertex.z : b.minVertex.z; 
  
  Triple ma = a.maxVertex - b.maxVertex;
  ma.x = (ma.x>0) ? a.maxVertex.x : b.maxVertex.x; 
  ma.y = (ma.y>0) ? a.maxVertex.y : b.maxVertex.y; 
  ma.z = (ma.z>0) ? a.maxVertex.z : b.maxVertex.z; 

  return Box(mi, ma);
}

//! Free vector
/**
	FreeVectors represent objects like normal vectors and other vector fields inside R^3 
*/
struct PROTEAN3D_EXPORT FreeVector
{
	FreeVector()
	{
	}

	//! Construct initialized vector
	/**
		b -> base\n
		e -> top\n
	*/
	FreeVector(Triple b, Triple t)
	: base(b), top(t)
	{
	}
	
	Triple base;
	Triple top;
};

//! A free vector field in R^3
typedef std::vector<FreeVector> FreeVectorField;

//! A point field in R^3
typedef std::vector<Triple> TripleVector;
//! Holds indices in a TripleVector interpreted as an oriented (first->second) Edge
typedef std::pair<unsigned,unsigned> Edge;
//! Vector of Edges for a graph or cell complex. You need a TripleVector as base for the node data
typedef std::vector<Edge> EdgeVector;
//! Holds indices in a TripleVector interpreted as counterclockwise node numbering for a convex polygon
typedef std::vector<unsigned> Cell;
//! Vector of convex polygons. You need a TripleVector as base for the node data
typedef std::vector<Cell> CellVector;
//! Returns the sum over the sizes of the single cells
unsigned tesselationSize(Protean3D::CellVector const& t);
//! Rectangular hull for point cloud
PROTEAN3D_EXPORT Protean3D::Box hull(TripleVector const& data);

//! Red-Green-Blue-Alpha value
struct PROTEAN3D_EXPORT RGBA
{
	RGBA()
		: r(0), g(0), b(0), a(1)
		{}
	RGBA(double rr, double gg, double bb, double aa = 1)
		: r(rr), g(gg), b(bb), a(aa)
		{}
	double r,g,b,a;
};

//! A Color field
typedef std::vector<RGBA> ColorVector;

////! simplified glut routine (glUnProject): windows coordinates_p --> object coordinates_p 
///**
//	Don't rely on (use) this in display lists !
//*/
//inline Triple ViewPort2World(Triple win, bool* err = 0)
//{
//  Triple ret;
//  bool retb = GL::ViewPort2World(ret.x, ret.y, ret.z, win.x, win.y, win.z);
//  if (err)
//    *err = retb;
//
//  return ret;
//}

////! simplified glut routine (glProject): object coordinates_p --> windows coordinates_p 
///**
//	Don't rely on (use) this in display lists !
//*/
//inline Triple World2ViewPort(Triple obj,	bool* err = 0)
//{
//  Triple ret;
//  bool retb = GL::World2ViewPort(ret.x, ret.y, ret.z, obj.x, obj.y, obj.z);
//  if (err)
//    *err = retb;
//
//  return ret;
//}

#ifndef PROTEAN3D_NOT_FOR_DOXYGEN

inline Triple normalizedCross(Triple const& u, Triple const& v)
{
	Triple n;

  /* compute the cross product (u x v for right-handed [ccw]) */
  n.x = u.y * v.z - u.z * v.y;
  n.y = u.z * v.x - u.x * v.z;
  n.z = u.x * v.y - u.y * v.x;

  /* normalize */
  double l = n.length();
  if (l)
	{
		n /= l;
	}
	else
	{
		n = Triple(0,0,0);
	}
	
	return n;
}

inline Triple normalizedCross(Triple const& center, 
                              Triple const& v0, 
                              Triple const& v1)
{
  return normalizedCross(v0-center, v1-center);
}

inline double dotProduct(Triple const& u, Triple const& v)
{
	return u.x*v.x + u.y*v.y + u.z*v.z;
}

//! rad to degree
inline double rad2deg(double rad)
{
  return 180*rad/Protean3D::PI;
}
  
//! Angle of line ccw to positive x axis in degree's
inline double angle(double sx, double sy, double ex, double ey)
{
  const double dx = ex - sx;
  const double dy = ey - sy;

  const double theta = rad2deg(atan2(dy, dx));

  return theta < 0 ? theta + 360 : theta;
}

void convexhull2d( std::vector<unsigned>& idx, const std::vector<Protean3D::Tuple>& src );


#endif // PROTEAN3D_NOT_FOR_DOXYGEN 

} // ns


