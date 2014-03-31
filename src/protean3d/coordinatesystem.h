#pragma once

#include <list>
#include "axis.h"
//#include "colorlegend.h"

namespace Protean3D
{

//! A coordinate system with different styles (BOX, FRAME)
class PROTEAN3D_EXPORT CoordinateSystem
{

public:
	explicit CoordinateSystem(Protean3D::Triple blb = Protean3D::Triple(0,0,0), Protean3D::Triple ftr = Protean3D::Triple(0,0,0), Protean3D::COORDSTYLE = Protean3D::BOX);
  ~CoordinateSystem();	
	
	void init(Protean3D::Triple beg = Protean3D::Triple(0,0,0), Protean3D::Triple end = Protean3D::Triple(0,0,0));
	//! Set style for the coordinate system (NOCOORD, FRAME or BOX)
  void setStyle(Protean3D::COORDSTYLE s,	Protean3D::AXIS frame_1 = Protean3D::X1, 
																			Protean3D::AXIS frame_2 = Protean3D::Y1, 
																			Protean3D::AXIS frame_3 = Protean3D::Z1);
  Protean3D::COORDSTYLE style() const { return style_;} 	//!< Return style oft the coordinate system 
	void setPosition(Protean3D::Triple first, Protean3D::Triple second); //!< first == front_left_bottom, second == back_right_top
	
	void setAxesColor(Protean3D::RGBA val); //!< Set common color for all axes
	//! Set common font for all axis numberings
	//void setNumberFont(Protean3D::Label::Font const& font);
	//! Set common color for all axis numberings
	void setNumberColor(Protean3D::RGBA val);
  void setStandardScale(); //!< Sets an linear axis with real number items

 	void adjustNumbers(int val); //!< Fine tunes distance between axis numbering and axis body
	void adjustLabels(int val); //!< Fine tunes distance between axis label and axis body

	//! Sets color for the grid lines
  void setGridLinesColor(Protean3D::RGBA val) {gridlinecolor_ = val;}
	
	//! Set common font for all axis labels
	//void setLabelFont(Protean3D::Label::Font const& font);
	//! Set common color for all axis labels
	void setLabelColor(Protean3D::RGBA val);

	//! Set line width for tic marks and axes
	void setLineWidth(double val, double majfac = 0.9, double minfac = 0.5);
	//! Set length for tic marks
	void setTicLength(double major, double minor);

	//! Switch autoscaling of axes
  void setAutoScale(bool val = true);

	Protean3D::Triple first() const { return first_;}
	Protean3D::Triple second() const { return second_;}

	void setAutoDecoration(bool val = true) {autodecoration_ = val;}
	bool autoDecoration() const { return autodecoration_;}

	void setLineSmooth(bool val = true) {smooth_ = val;} //!< draw smooth axes
	bool lineSmooth() const {return smooth_;}            //!< smooth axes ? 

	void draw();
	
	//! Defines whether a grid between the major and/or minor tics should be drawn
  void setGridLines(bool majors, bool minors, int sides = Protean3D::NOSIDEGRID); 
  int grids() const {return sides_;} //!< Returns grids switched on
	
	//! The vector of all 12 axes - use them to set axis properties individually.
  std::vector<Axis> axes;


private:
  static unsigned const asize = 12;

  void attach(unsigned idx);
  void detach(unsigned idx);
  void detachAll();

	void destroy();
	
	Protean3D::Triple first_, second_;
	Protean3D::COORDSTYLE style_;
	
	Protean3D::RGBA gridlinecolor_;

	bool smooth_;
	
	void chooseAxes();
	void autoDecorateExposedAxis(Axis& ax, bool left);
  void drawMajorGridLines(); //!< Draws a grid between the major tics on the site
	void drawMinorGridLines(); //!< Draws a grid between the minor tics on the site
  void drawMajorGridLines(Protean3D::Axis&, Protean3D::Axis&); //! Helper
  void drawMinorGridLines(Protean3D::Axis&, Protean3D::Axis&); //! Helper
  void recalculateAxesTics();

	bool autodecoration_;
	bool majorgridlines_, minorgridlines_;
  int  sides_;

  std::list<unsigned> aidx_;
};

} // ns


