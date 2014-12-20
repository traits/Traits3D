#pragma once

#if defined(_MSC_VER) /* MSVC Compiler */
  #pragma warning ( disable : 4786 )
#endif

#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "global.h"
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
enum COORDINATESTYLE
{
	NOCOORDINATES,  //!< Coordinate system is not visible 
	BOX,            //!< Boxed
	FRAME		        //!< Frame - 3 visible axes
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


typedef glm::dvec2 Tuple;
typedef glm::dvec3 Triple;

//! Box spanned by 2 Triples
/**
Please use \em normalized boxes:\n\n
minVertex[0] <= maxVertex[0]\n
minVertex[1] <= maxVertex[1]\n
minVertex[2] <= maxVertex[2]\n
*/
struct PROTEAN3D_EXPORT Box
{
	//! Construct degenerated Box with minVertex components set to max(double) and maxVertex comp's to min(double)
	Box()
    : Box(
       Triple(std::numeric_limits<Triple::value_type>::max()),
       Triple(std::numeric_limits<Triple::value_type>::min())
         )
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
  mi[0] = (mi[0]<0) ? a.minVertex[0] : b.minVertex[0]; 
  mi[1] = (mi[1]<0) ? a.minVertex[1] : b.minVertex[1]; 
  mi[2] = (mi[2]<0) ? a.minVertex[2] : b.minVertex[2]; 
  
  Triple ma = a.maxVertex - b.maxVertex;
  ma[0] = (ma[0]>0) ? a.maxVertex[0] : b.maxVertex[0]; 
  ma[1] = (ma[1]>0) ? a.maxVertex[1] : b.maxVertex[1]; 
  ma[2] = (ma[2]>0) ? a.maxVertex[2] : b.maxVertex[2]; 

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
typedef glm::vec4 Color;

//! A Color field
typedef std::vector<Color> ColorVector;

////! simplified glut routine (glUnProject): windows coordinates_p --> object coordinates_p 
///**
//	Don't rely on (use) this in display lists !
//*/
//inline Triple ViewPort2World(Triple win, bool* err = 0)
//{
//  Triple ret;
//  bool retb = GL::ViewPort2World(ret.x, ret[1], ret[2], win.x, win[1], win[2]);
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
//  bool retb = GL::World2ViewPort(ret.x, ret[1], ret[2], obj.x, obj[1], obj[2]);
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
  n[0] = u[1] * v[2] - u[2] * v[1];
  n[1] = u[2] * v[0] - u[0] * v[2];
  n[2] = u[0] * v[1] - u[1] * v[0];

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
	return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
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


