#pragma once

#include "traits3d/glbase/glhelper.h"
#include "traits3d/scale.h"
#include "traits3d/autoscaler.h"
#include "traits3d/axisobject.h"
#include "traits3d/textengine/textengine.h"

namespace Traits3D
{
  //! Auto-scalable axis with caption. 
  /*!
    Axes are highly customizable especially in terms
    of labeling and scaling.
  */
  class TRAITS3D_EXPORT Axis
  {
    public:
      Axis(); //!< Constructs standard axis
      Axis(Traits3D::Triple beg, Traits3D::Triple end); //!< Constructs a new axis with specified limits
      virtual ~Axis(); // dtor
  
      virtual bool initializeGL();
      void draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix);

      /** 
      Used to tag the axis as a z-axis. This information is used to draw correct labels.
      The standard value for axes is false;
      */
      void setZ(bool val) {isZ_=val;} 
      bool isZ() const {return isZ_;} //!< Is a z-axis

      void setPosition(const Traits3D::Triple& beg, const Traits3D::Triple& end); //!< Positionate axis
      void position(Traits3D::Triple& beg, Traits3D::Triple& end) const {beg = beg_; end = end_;} //!< Returns axis' position
      Traits3D::Triple begin() const { return beg_; } //!< Returns axis' beginning position
      Traits3D::Triple end() const { return end_; } //!< Returns axis' ending position 
      double length() const { return glm::distance(beg_,end_); } //!< Returns axis' length
      void setColor(Color const& val) { color_ = val; }

      void setTicLength(double majorl, double minorl); //!< Sets tics lengths in world coordinates
      //! Returns tics lengths
      void ticLength(double& majorl, double& minorl) const { majorl = lmaj_; minorl = lmin_; }
      void setTicOrientation(double tx, double ty, double tz); //!< Sets tic orientation
      void setTicOrientation(const Traits3D::Triple& val); //!< Same function as above
      Traits3D::Triple ticOrientation() const { return orientation_;} //!< Returns tic orientation
      void setSymmetricTics( bool b) { symtics_ = b;} //!< Sets two-sided tics (default is false) 
  
      void setScaling(bool d) {draw_tics_ = d;} //!< Turns scale drawing on or off
      bool scaling() const {return draw_tics_;} //!< Returns, if scale drawing is on or off
      void setScale(Traits3D::SCALETYPE);
      void setScale(std::shared_ptr<Traits3D::Scale> scale){ scale_ = scale; } //!< This variant sets a user-defined scale object.
      void setNumbers(bool d) {draw_numbers_ = d;} //!< Turns number drawing on or off
      bool numbers() const {return draw_numbers_;} //!< Returns, if number drawing is on or off
      void setNumberColor(Color const& col); //!< Sets the color for axes numbers
      Traits3D::Color numberColor() const {return numbercolor_;} //!< Returns the color for axes numbers  
      void setNumberAnchor(Traits3D::TextEngine::Anchor a) { scaleNumberAnchor_ = a; } //!< Sets anchor position for numbers
      void adjustNumbers(int val) {numbergap_ = val;} //!< Shifts axis numbers in device coordinates dependent on anchor;
      void setAutoScale(bool val = true) {autoscale_ = val;} //!< Turns Autoscaling on or off
      bool autoScale() const { return autoscale_;} //!< actual Autoscaling mode

      void setMajors(size_t val); //!< Requests major intervals (maybe changed, if autoscaling is present)
      void setMinors(size_t val); //!< Requests minor intervals
      size_t majors() const { return majorintervals_; } //!< Returns number of major intervals
      size_t minors() const { return minorintervals_; } //!< Returns number of minor intervals
      Traits3D::TripleVector const& majorPositions() const {return majorpos_;} //!< Returns positions for actual major tics (also if invisible)
      Traits3D::TripleVector const& minorPositions() const {return minorpos_;} //!< Returns positions for actual minor tics (also if invisible)
  
      void setLimits(double start, double stop) {start_=start; stop_=stop;} //!< Sets interval
      void limits(double& start, double& stop) const {start = start_; stop = stop_;} //!< Returns axis interval
      void recalculateTics(); //!< Enforces recalculation of ticmark positions
  
    protected:
      std::shared_ptr<GL::AxisObject> globject_p;

    private:
      void init();
      bool prepTicCalculation(Triple& startpoint);

      Traits3D::Triple biggestNumberString();
      Traits3D::TextEngine::Anchor scaleNumberAnchor_;
      Traits3D::Triple beg_, end_;
      Traits3D::TripleVector majorpos_, minorpos_; //! vectors, holding major resp. minor tic positions;

      double start_, stop_, autostart_, autostop_;
      double lmaj_ = 0.0;
      double lmin_ = 0.0;
      Traits3D::Triple orientation_;

      size_t majorintervals_, minorintervals_;

      bool symtics_;
      bool draw_numbers_, draw_tics_, draw_label_;
      bool autoscale_;
      Traits3D::Color numbercolor_, color_;

      int numbergap_; 
      std::shared_ptr<Traits3D::Scale> scale_;

      bool isZ_ = false; // identify z-axis
  };
} // ns 


