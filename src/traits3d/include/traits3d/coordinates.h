#pragma once

#include <list>
#include "axis.h"

namespace Traits3D
{
  namespace GL
  {
    class LineRenderer;
  }

  //! A coordinate system with different styles (BOX, FRAME)
  class TRAITS3D_EXPORT Coordinates
  {
    public:
      explicit Coordinates(Traits3D::Triple blb = Traits3D::Triple(0,0,0), 
                           Traits3D::Triple ftr = Traits3D::Triple(0,0,0), 
                           Traits3D::COORDINATESTYLE = Traits3D::BOX);
      ~Coordinates();  
  
      void init(Traits3D::Triple beg = Traits3D::Triple(0, 0, 0), Traits3D::Triple end = Traits3D::Triple(0, 0, 0));
      void init(Traits3D::Box hull);
      virtual bool initializeGL();

      //! Set style for the coordinate system (NOCOORDINATES, FRAME or BOX)
      void setStyle(Traits3D::COORDINATESTYLE s,  Traits3D::AXIS frame_1 = Traits3D::X1, 
                    Traits3D::AXIS frame_2 = Traits3D::Y1, 
                    Traits3D::AXIS frame_3 = Traits3D::Z1);
      Traits3D::COORDINATESTYLE style() const { return style_;}   //!< Return style oft the coordinate system 
      void setPosition(Traits3D::Triple first, Traits3D::Triple second); //!< first == front_left_bottom, second == back_right_top
      void setAxesColor(Traits3D::Color const& val); //!< Set common color for all axes
      //! Set common font for all axis numberings
      void setNumberFont(Traits3D::FontInfo const& font);
      //! Set common color for all axis numberings
      void setNumberColor(Traits3D::Color const& val);
      void setStandardScale(); //!< Sets an linear axis with real number items
  
      //! Sets color for the grid lines
      void setGridLineColor(Traits3D::Color const& val) { gridlinecolor_ = val; }
      //! Set common font for all axis labels
      void setLabelFont(Traits3D::FontInfo const& font);
      //! Set common color for all axis labels
      void setLabelColor(Traits3D::Color const& val);

      //! Set length for tic marks
      void setTicLength(double major, double minor);
      //! Switch autoscaling of axes
      void setAutoScale(bool val = true);

      Traits3D::Triple first() const { return first_;}
      Traits3D::Triple second() const { return second_;}

      void setAutoDecoration(bool val = true) {autodecoration_ = val;}
      bool autoDecoration() const { return autodecoration_;}

      void draw(GL::Transformation const& matrices);
  
      //! Defines whether a grid between the major and/or minor tics should be drawn
      void setGridLines(bool majors, bool minors, int sides = Traits3D::NOSIDEGRID); 
      int grids() const {return sides_;} //!< Returns grids switched on
  
      //! The vector of all 12 axes - use them to set axis properties individually.
      std::vector<Axis> axes;

    private:
      static unsigned const asize = 12;
  
      Traits3D::Triple first_, second_;
      Traits3D::COORDINATESTYLE style_;
    
      void chooseAxes(GL::Transformation const& matrices, glm::ivec4 const& viewport);
      void autoDecorateExposedAxis(Axis& ax, Triple const& projected_ax, bool left);
      void drawMajorGridLines(GL::Transformation const& matrices); //!< Draws a grid between the major tics on the site
      void drawMinorGridLines(GL::Transformation const& matrices); //!< Draws a grid between the minor tics on the site
      void drawMajorGridLines(AXIS a0, AXIS a1, AXIS b0, AXIS b1, GL::Transformation const& matrices); //! Helper
      void drawMinorGridLines(AXIS a0, AXIS a1, AXIS b0, AXIS b1, GL::Transformation const& matrices); //! Helper

      bool autodecoration_;
      bool majorgridlines_, minorgridlines_;
      int  sides_;
      std::shared_ptr<GL::LineRenderer> grid_renderer_; //todo use multiple renderers
      Color gridlinecolor_ = Color(0, 0, 0, 1);

      std::list<size_t> aidx_;
      void attach(size_t idx);
      void detach(size_t idx);
    };
} // ns


