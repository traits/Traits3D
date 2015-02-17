#pragma once

#include <list>
#include "axis.h"

namespace Protean3D
{
  //! A coordinate system with different styles (BOX, FRAME)
  class PROTEAN3D_EXPORT Coordinates
  {
    public:
	    explicit Coordinates(Protean3D::Triple blb = Protean3D::Triple(0,0,0), 
                           Protean3D::Triple ftr = Protean3D::Triple(0,0,0), 
                           Protean3D::COORDINATESTYLE = Protean3D::BOX);
      ~Coordinates();	
	
      void init(Protean3D::Triple beg = Protean3D::Triple(0, 0, 0), Protean3D::Triple end = Protean3D::Triple(0, 0, 0));
      void init(Protean3D::Box hull);
      virtual bool initializeGL();

      //! Set style for the coordinate system (NOCOORDINATES, FRAME or BOX)
      void setStyle(Protean3D::COORDINATESTYLE s,	Protean3D::AXIS frame_1 = Protean3D::X1, 
									  Protean3D::AXIS frame_2 = Protean3D::Y1, 
									  Protean3D::AXIS frame_3 = Protean3D::Z1);
      Protean3D::COORDINATESTYLE style() const { return style_;} 	//!< Return style oft the coordinate system 
	    void setPosition(Protean3D::Triple first, Protean3D::Triple second); //!< first == front_left_bottom, second == back_right_top
      void setStandardScale(); //!< Sets an linear axis with real number items
	
      //! Set length for tic marks
      void setTicLength(double major, double minor);
      //! Switch autoscaling of axes
      void setAutoScale(bool val = true);

	    Protean3D::Triple first() const { return first_;}
	    Protean3D::Triple second() const { return second_;}

	    void setAutoDecoration(bool val = true) {autodecoration_ = val;}
	    bool autoDecoration() const { return autodecoration_;}

      void draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix);
	
	    //! Defines whether a grid between the major and/or minor tics should be drawn
      void setGridLines(bool majors, bool minors, int sides = Protean3D::NOSIDEGRID); 
      int grids() const {return sides_;} //!< Returns grids switched on
	
	    //! The vector of all 12 axes - use them to set axis properties individually.
      std::vector<Axis> axes;

    private:
      static unsigned const asize = 12;
	
	    Protean3D::Triple first_, second_;
	    Protean3D::COORDINATESTYLE style_;
		
      void chooseAxes(glm::dmat4 const& proj_matrix, glm::dmat4 const& mv_matrix, glm::ivec4 const& viewport);
      void autoDecorateExposedAxis(Axis& ax, Triple const& projected_ax, bool left);
      void drawMajorGridLines(); //!< Draws a grid between the major tics on the site
	    void drawMinorGridLines(); //!< Draws a grid between the minor tics on the site
      void drawMajorGridLines(Protean3D::Axis&, Protean3D::Axis&); //! Helper
      void drawMinorGridLines(Protean3D::Axis&, Protean3D::Axis&); //! Helper
      void recalculateAxesTics();

	    bool autodecoration_;
	    bool majorgridlines_, minorgridlines_;
      int  sides_;

      std::list<size_t> aidx_;
      void attach(size_t idx);
      void detach(size_t idx);
    };
} // ns


