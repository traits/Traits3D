#include "coordinates.h"

using namespace std;
using namespace Protean3D;


Coordinates::Coordinates(Protean3D::Triple first, Protean3D::Triple second, Protean3D::COORDINATESTYLE st)
{
	autodecoration_ = true;
	axes = std::vector<Axis>(asize);
  setStyle(st);
	init(first,second);
	setGridLines(false, false);
}

Coordinates::~Coordinates()
{
}

void Coordinates::init(Protean3D::Triple first, Protean3D::Triple second)
{
  for (unsigned i=0; i!=axes.size(); ++i)
    axes[i].setScale(LINEARSCALE);
		
	Triple dv = second - first;
	
	setPosition(first, second);
	
	double majl =  glm::length(dv) / 100; // 1 %
	//setTicLength(majl, 0.6 * majl);

	axes[X1].setPosition(first, first+Triple(dv.x,    0,     0));												// front bottom x
	axes[Y1].setPosition(first, first+Triple(   0, dv.y,     0));												// bottom left  y
	axes[Z1].setPosition (first+Triple(   0, dv.y, 0), first+Triple(   0, dv.y, dv.z));	// back left z
	axes[X1].setTicOrientation(0,-1,0);
	axes[Y1].setTicOrientation(-1,0,0);
	axes[Z1].setTicOrientation(-1,0,0);
	
	axes[X1].setLimits(first.x, second.x);
	axes[X2].setLimits(first.x, second.x);
	axes[X3].setLimits(first.x, second.x);
	axes[X4].setLimits(first.x, second.x);
	
	axes[Y1].setLimits(first.y, second.y);
	axes[Y2].setLimits(first.y, second.y);
	axes[Y3].setLimits(first.y, second.y);
	axes[Y4].setLimits(first.y, second.y);
	
	axes[Z1].setLimits(first.z, second.z);
	axes[Z2].setLimits(first.z, second.z);
	axes[Z3].setLimits(first.z, second.z);
	axes[Z4].setLimits(first.z, second.z);

	// remaining x axes 
	axes[X2].setPosition(first+Triple( 0,    0, dv.z), first+Triple( dv.x,    0, dv.z));	// front top x
	axes[X3].setPosition(first+Triple( 0, dv.y, dv.z), second);		  											// back top x
	axes[X4].setPosition(first+Triple( 0, dv.y,    0), first+Triple( dv.x, dv.y,    0));	// back bottom x
	axes[X2].setTicOrientation(0,-1,0);
	axes[X3].setTicOrientation(0,1,0);
	axes[X4].setTicOrientation(0,1,0);
	
	// remaining y axes 
	axes[Y2].setPosition(first+Triple(dv.x, 0,    0), first+Triple(dv.x, dv.y,  0)); // bottom right y
	axes[Y3].setPosition(first+Triple(dv.x, 0, dv.z), second);											 // top right y
	axes[Y4].setPosition(first+Triple(0,    0, dv.z), first+Triple(0,  dv.y, dv.z)); // top left y
	axes[Y2].setTicOrientation(1,0,0);
	axes[Y3].setTicOrientation(1,0,0);
	axes[Y4].setTicOrientation (-1,0,0);

	// remaining z axes 
	axes[Z2].setPosition(first, first+Triple(   0,    0,  dv.z));												// front left z
	axes[Z4].setPosition(first+Triple(dv.x, dv.y, 0), second );                         // back right z
	axes[Z3].setPosition(first+Triple(dv.x,    0, 0), first+Triple(dv.x,    0, dv.z));	// front right z
	axes[Z2].setTicOrientation(-1,0,0);
	axes[Z4].setTicOrientation(1,0,0);
	axes[Z3].setTicOrientation(1,0,0);
	
	setStyle(style_);
}

//void CoordinateSystem::draw()
//{	
	//GL::StateBewarer sb(GL_LINE_SMOOTH, true);
	//
	//if (!lineSmooth())
	//	sb.turnOff();
	//	

	//if (autoDecoration())
	//	chooseAxes();
	//
 // saveGLState();
 // for (std::list<unsigned>::iterator it = aidx_.begin(); it!=aidx_.end(); ++it)
 // {
 //   axes[*it].draw();
 // }
 // restoreGLState();

	//if( style_ == NOCOORDINATES)
	//	return;

 // if (majorgridlines_ || minorgridlines_)
 //   recalculateAxesTics();
 // if (majorgridlines_)
 //   drawMajorGridLines();
	//if (minorgridlines_)
	//	drawMinorGridLines();
//}


//! build convex hull (6 axes: 2 x, 2 y, 2 z) and choose one of them at a time for scales, labels etc.  
void Coordinates::chooseAxes()
{
	//vector<Triple> beg(axes.size());
	//vector<Triple> end(axes.size());
	//vector<Tuple> src(2*axes.size());

	//unsigned i;
	//// collect axes viewport coordinates and initialize
	//for (i=0; i!=axes.size(); ++i)
	//{
	//	if (style() != NOCOORDINATES)
	//		attach(i);
	//	
	//	beg[i] = World2ViewPort(axes[i].begin());
	//	end[i] = World2ViewPort(axes[i].end());
	//	src[i] = Tuple(beg[i].x, beg[i].y);
	//	src[axes.size()+i] = Tuple(end[i].x, end[i].y);

	//	axes[i].setScaling(false);
	//	axes[i].setNumbers(false);
	//	axes[i].setLabel(false);
	//}

	//vector<unsigned> idx;
	//convexhull2d(idx,src);

	//int rem_x = -1;
	//int rem_y = -1;
	//int rem_z = -1;


	//bool left;

	//int choice_x = -1; 
	//int	choice_y = -1;
	//int choice_z = -1;

 // int other_x = -1;
 // int other_y = -1;
 // int other_z = -1;

	////traverse convex hull
	//for (unsigned k=0; k!=idx.size(); ++k)
	//{
	//	Triple one, two;
	//	
	//	if (idx[k] >= axes.size()) // is end point
	//		one = end[idx[k]-axes.size()];
	//	else                       // is begin point  
	//		one = beg[idx[k]];

	//	unsigned int next = idx[(k+1) % idx.size()];  // next point in cv (considered as ring buffer of points)

	//	if (next >= axes.size()) 
	//		two = end[next-axes.size()];
	//	else
	//		two = beg[next];
	//	
	//	for (i=0; i!=axes.size(); ++i)
	//	{			
	//		if (
	//				(one == beg[i] && two == end[i])
	//				||
	//				(two == beg[i] && one == end[i])
	//			 )
	//		{
	//			if (i==X1 || i==X2 || i==X3 || i==X4)  // x Achsen
	//			{
	//				if (rem_x>=0) // schon zweite Achse der konvexen Huelle ?
	//				{
	//					// untere der beiden x Achsen
	//					double y = min(min(end[rem_x].y,end[i].y),min(beg[rem_x].y,beg[i].y));
	//					choice_x = (y == beg[i].y || y == end[i].y) ? i : rem_x;
	//											
	//					other_x = (choice_x == (int)i) ? rem_x : (int)i;
	//					left = (beg[choice_x].x < beg[other_x].x || end[choice_x].x < end[other_x].x) 
	//						? true
	//						: false;
	//					
	//					autoDecorateExposedAxis(axes[choice_x], left);

	//					rem_x = -1;
	//				}
	//				else
	//				{
	//					rem_x = i;
	//				}
	//			}
	//			else if (i==Y1 || i==Y2 || i==Y3 || i==Y4)
	//			{
	//				if (rem_y>=0)
	//				{
	//					// untere der beiden y Achsen
	//					double y = min(min(end[rem_y].y,end[i].y),min(beg[rem_y].y,beg[i].y));
	//					choice_y = (y == beg[i].y || y == end[i].y) ? i : rem_y;
	//					
	//					other_y = (choice_y == (int)i) ? rem_y : (int)i;
	//					left = (beg[choice_y].x < beg[other_y].x || end[choice_y].x < end[other_y].x) 
	//						? true
	//						: false;
	//					autoDecorateExposedAxis(axes[choice_y], left);

	//					rem_y = -1;
	//				}
	//				else
	//				{
	//					rem_y = i;
	//				}
	//			}
	//			else if (i==Z1 || i==Z2 || i==Z3 || i==Z4)
	//			{
	//				if (rem_z>=0)
	//				{
	//					// hintere der beiden z Achsen
	//					double z = max(max(end[rem_z].z,end[i].z),max(beg[rem_z].z,beg[i].z));
	//					choice_z = (z == beg[i].z || z == end[i].z) ? i : rem_z;

	//					other_z = (choice_z == (int)i) ? rem_z : (int)i;
	//											
	//					rem_z = -1;

	//				}
	//				else
	//				{
	//					rem_z = i;
	//				}
	//			}
	//		}
	//	} // for axes
	//} // for idx

	//// fit z axis in - the onthewall axis if the decorated axes build a continous line, the opposite else 
	//if (choice_x>=0 && choice_y>=0 && choice_z>=0)
	//{
	//	left = (beg[choice_z].x < beg[other_z].x || end[choice_z].x < end[other_z].x) 
	//		? true
	//		: false;
	//	

	//	if (
	//				axes[choice_z].begin() == axes[choice_x].begin() 
	//		||	axes[choice_z].begin() == axes[choice_x].end()
	//		||	axes[choice_z].begin() == axes[choice_y].begin() 
	//		||	axes[choice_z].begin() == axes[choice_y].end()
	//		||	axes[choice_z].end() == axes[choice_x].begin() 
	//		||	axes[choice_z].end() == axes[choice_x].end()
	//		||	axes[choice_z].end() == axes[choice_y].begin() 
	//		||	axes[choice_z].end() == axes[choice_y].end()
	//		
	//		)
	//	{
	//		autoDecorateExposedAxis(axes[choice_z], left);
	//	}

	//	else
	//	{
	//		autoDecorateExposedAxis(axes[other_z], !left);
	//		choice_z = other_z; // for FRAME
	//	}
	//}
	//
	//if (style() == FRAME)
	//{
	//	for (i=0; i!=axes.size(); ++i)
	//	{
	//		if ((int)i!=choice_x && (int)i!=choice_y && (int)i!=choice_z)
	//			detach(i);
	//	}
	//}
}


void Coordinates::autoDecorateExposedAxis(Axis& ax, bool left)
{
	//Triple diff = World2ViewPort(ax.end()) - World2ViewPort(ax.begin());

	//diff = Triple(diff.x,diff.y,0); // projection
	//
	//double s = glm::distance(diff);
	//
	//if (!s)
	//	return;

	//ax.setScaling(true);
	//ax.setNumbers(true);
	//ax.setLabel(true);

	//const double SQRT_2 = 0.7071067;
	//double sina = fabs(diff.y / s);


	//if (left) // leftmost (compared with antagonist in CV)  axis -> draw decorations on the left side
	//{
	//	if ( diff.x >= 0 && diff.y >= 0 && sina < SQRT_2)          // 0..Pi/4 
	//	{
	//		ax.setNumberAnchor(BottomCenter);
	//	}
	//	else if ( diff.x >= 0 && diff.y >= 0  && !left)            // octant 2
	//	{
	//		ax.setNumberAnchor(CenterRight);
	//	}
	//	else if ( diff.x <= 0 && diff.y >= 0  && sina >= SQRT_2)    // octant 3
	//	{
	//		ax.setNumberAnchor(CenterRight);
	//	}
	//	else if ( diff.x <= 0 && diff.y >= 0 )                      // octant 4
	//	{
	//		ax.setNumberAnchor(TopCenter);
	//	}
	//	else if ( diff.x <= 0 && diff.y <= 0  && sina <= SQRT_2)    // octant 5
	//	{
	//		ax.setNumberAnchor(BottomCenter);
	//	}
	//	else if ( diff.x <= 0 && diff.y <= 0)                      // octant 6
	//	{
	//		ax.setNumberAnchor(CenterRight);
	//	}
	//	else if ( diff.x >= 0 && diff.y <= 0  && sina >= SQRT_2)    // octant 7
	//	{
	//		ax.setNumberAnchor(CenterRight);
	//	}
	//	else if ( diff.x >= 0 && diff.y <= 0)                      // octant 8
	//	{
	//		ax.setNumberAnchor(TopCenter);
	//	}
	//}	
	//else // rightmost axis
	//{
	//	if ( diff.x >= 0 && diff.y >= 0 && sina <= SQRT_2)
	//	{
	//		ax.setNumberAnchor(TopCenter);
	//	}
	//	else if ( diff.x >= 0 && diff.y >= 0  && !left) 
	//	{
	//		ax.setNumberAnchor(CenterLeft);
	//	}
	//	else if ( diff.x <= 0 && diff.y >= 0  && sina >= SQRT_2) 
	//	{
	//		ax.setNumberAnchor(CenterLeft);
	//	}
	//	else if ( diff.x <= 0 && diff.y >= 0) 
	//	{
	//		ax.setNumberAnchor(BottomCenter);
	//	}
	//	else if ( diff.x <= 0 && diff.y <= 0  && sina <= SQRT_2) 
	//	{
	//		ax.setNumberAnchor(TopCenter);
	//	}
	//	else if ( diff.x <= 0 && diff.y <= 0) 
	//	{
	//		ax.setNumberAnchor(CenterLeft);
	//	}
	//	else if ( diff.x >= 0 && diff.y <= 0  && sina >= SQRT_2) 
	//	{
	//		ax.setNumberAnchor(CenterLeft);
	//	}
	//	else if ( diff.x >= 0 && diff.y <= 0) 
	//	{
	//		ax.setNumberAnchor(BottomCenter);
	//	}
	//}
}


void Coordinates::setPosition(Triple first, Triple second)
{
	first_ = first;
	second_ = second;
}

void Coordinates::setAutoScale(bool val)
{
	for (unsigned i=0; i!=axes.size(); ++i)
		axes[i].setAutoScale(val);
}

void Coordinates::recalculateAxesTics()
{
	for (unsigned i=0; i!=axes.size(); ++i)
		axes[i].recalculateTics();
}

void Coordinates::setStandardScale()
{
	for (unsigned i=0; i!=axes.size(); ++i)
    axes[i].setScale(LINEARSCALE);
}

void Coordinates::setStyle(Protean3D::COORDINATESTYLE s, Protean3D::AXIS frame_1, 
                                Protean3D::AXIS frame_2, Protean3D::AXIS frame_3) 
{ 
	//style_ = s;

	//switch (s)
	//{
	//	case NOCOORDINATES:
	//		{
	//			for (unsigned i=0; i!=axes.size(); ++i)
	//				detach (i);
	//		}
	//		break;
	//	case BOX:
	//		{
	//			for (unsigned i=0; i!=axes.size(); ++i)
	//				attach (i);
	//		}
	//		break;
	//	case FRAME:
	//		{
	//			for (unsigned i=0; i!=axes.size(); ++i)
	//				detach (i);
	//			if (!autoDecoration())
	//			{
	//				attach(frame_1);
	//				attach(frame_2);
	//				attach(frame_3);
	//			}
	//		}
	//		break;
	//	default:
	//		break;
	//}
}

/**
The axis used for tic calculation is chosen randomly from the respective pair.
For most cases an identical tic distribution is therefore recommended.
\param majors  Draw grid between major tics
\param minors  Draw grid between minor tics
\param sides   Side(s), where the grid should be drawn
*/
void Coordinates::setGridLines(bool majors, bool minors, int sides) 
{
	sides_ = sides;
  majorgridlines_ = majors; 
	minorgridlines_ = minors;
} 

void Coordinates::drawMajorGridLines()
{
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4d(gridlinecolor_.r,gridlinecolor_.g,gridlinecolor_.b,gridlinecolor_.a);		
	//setLineWidth(axes[X1].majLineWidth());

 // glBegin( GL_LINES );
 // if (sides_ & Protean3D::FLOOR)  
 // {
	//	drawMajorGridLines(axes[X1],axes[X4]);
	//	drawMajorGridLines(axes[Y1],axes[Y2]);
 // }
 // if (sides_ & Protean3D::CEIL)  
 // {
	//	drawMajorGridLines(axes[X2],axes[X3]);
	//	drawMajorGridLines(axes[Y3],axes[Y4]);
 // }
 // if (sides_ & Protean3D::LEFT)  
 // {
	//	drawMajorGridLines(axes[Y1],axes[Y4]);
	//	drawMajorGridLines(axes[Z1],axes[Z2]);
 // }
 // if (sides_ & Protean3D::RIGHT)  
 // {
	//	drawMajorGridLines(axes[Y2],axes[Y3]);
	//	drawMajorGridLines(axes[Z3],axes[Z4]);
 // }
 // if (sides_ & Protean3D::FRONT)  
 // {
	//	drawMajorGridLines(axes[X1],axes[X2]);
	//	drawMajorGridLines(axes[Z2],axes[Z3]);
 // }
 // if (sides_ & Protean3D::BACK) 
 // {
	//	drawMajorGridLines(axes[X3],axes[X4]);
	//	drawMajorGridLines(axes[Z4],axes[Z1]);
 // }
 // glEnd();
}

void Coordinates::drawMinorGridLines()
{
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4d(gridlinecolor_.r,gridlinecolor_.g,gridlinecolor_.b,gridlinecolor_.a);		
	//setLineWidth(axes[X1].minLineWidth());

 // glBegin( GL_LINES );
 // if (sides_ & Protean3D::FLOOR)  
 // {
	//	drawMinorGridLines(axes[X1],axes[X4]);
	//	drawMinorGridLines(axes[Y1],axes[Y2]);
 // }
 // if (sides_ & Protean3D::CEIL)  
 // {
	//	drawMinorGridLines(axes[X2],axes[X3]);
	//	drawMinorGridLines(axes[Y3],axes[Y4]);
 // }
 // if (sides_ & Protean3D::LEFT)  
 // {
	//	drawMinorGridLines(axes[Y1],axes[Y4]);
	//	drawMinorGridLines(axes[Z1],axes[Z2]);
 // }
 // if (sides_ & Protean3D::RIGHT)  
 // {
	//	drawMinorGridLines(axes[Y2],axes[Y3]);
	//	drawMinorGridLines(axes[Z3],axes[Z4]);
 // }
 // if (sides_ & Protean3D::FRONT)  
 // {
	//	drawMinorGridLines(axes[X1],axes[X2]);
	//	drawMinorGridLines(axes[Z2],axes[Z3]);
 // }
 // if (sides_ & Protean3D::BACK)  
 // {
	//	drawMinorGridLines(axes[X3],axes[X4]);
	//	drawMinorGridLines(axes[Z4],axes[Z1]);
 // }
 // glEnd();
}

void Coordinates::drawMajorGridLines(Axis& a0, Axis& a1)
{
 // Triple d = a1.begin()-a0.begin();

 // for (unsigned int i=0; i!=a0.majorPositions().size(); ++i)
	//{
	//	glVertex3d( a0.majorPositions()[i].x, a0.majorPositions()[i].y, a0.majorPositions()[i].z ); 
	//	glVertex3d( a0.majorPositions()[i].x + d.x, a0.majorPositions()[i].y + d.y, a0.majorPositions()[i].z +d.z); 
	//}
}

void Coordinates::drawMinorGridLines(Axis& a0, Axis& a1)
{
 // Triple d = a1.begin()-a0.begin();

 // for (unsigned int i=0; i!=a0.minorPositions().size(); ++i)
	//{
	//	glVertex3d( a0.minorPositions()[i].x, a0.minorPositions()[i].y, a0.minorPositions()[i].z ); 
	//	glVertex3d( a0.minorPositions()[i].x + d.x, a0.minorPositions()[i].y + d.y, a0.minorPositions()[i].z +d.z); 
	//}
}
