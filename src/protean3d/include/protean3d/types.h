#pragma once

#if defined(_MSC_VER) /* MSVC Compiler */
  #pragma warning ( disable : 4786 )
#endif

#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/geometric.hpp"

#include "protean3d/global.h"
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

using Tuple = glm::dvec2 ;
using TupleF = glm::vec2;
using Triple = glm::dvec3;
using TripleF = glm::vec3;

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
using FreeVectorField = std::vector<FreeVector>;

//! A point field in R^3
using TripleVector = std::vector<Triple>;
//! Holds indices in a TripleVector interpreted as an oriented (first->second) Edge
using Edge = std::pair<size_t,size_t>;
//! Vector of Edges for a graph or cell complex. You need a TripleVector as base for the node data
using EdgeVector = std::vector<Edge>;
//! Holds indices in a TripleVector interpreted as counterclockwise node numbering for a convex polygon
using Cell = std::vector<size_t>;
//! Vector of convex polygons. You need a TripleVector as base for the node data
using CellVector = std::vector<Cell>;

//! Red-Green-Blue-Alpha value
using Color = glm::vec4;

//! A Color field
using ColorVector = std::vector<Color> ;
} // ns


