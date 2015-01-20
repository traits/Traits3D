#pragma once

#include "glhelper.h"
#include "scale.h"
#include "autoscaler.h"
#include "axisobject.h"

namespace Protean3D
{

//! Autoscalable axis with caption. 
/*!
  Axes are highly customizable especially in terms
  of labeling and scaling.
*/
class PROTEAN3D_EXPORT Axis
{

public:
  Axis(); //!< Constructs standard axis
  Axis(Protean3D::Triple beg, Protean3D::Triple end); //!< Constructs a new axis with specified limits
  virtual ~Axis(); // dtor
  
  virtual bool initializeGL();
  void draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix);

  void setPosition(const Protean3D::Triple& beg, const Protean3D::Triple& end); //!< Positionate axis
  void position(Protean3D::Triple& beg, Protean3D::Triple& end) const {beg = beg_; end = end_;} //!< Returns axis' position
  Protean3D::Triple begin() const { return beg_; } //!< Returns axis' beginning position
  Protean3D::Triple end() const { return end_; } //!< Returns axis' ending position 
  double length() const { return glm::distance(beg_,end_); } //!< Returns axis' length
  void setColor(Color val) { color_ = val; }

  void showTics(bool d) { draw_tics_ = d; } //!< Turns scale drawing on or off
  void setTicLength(double majorl, double minorl); //!< Sets tics lengths in world coordinates
  //! Returns tics lengths
  void ticLength(double& majorl, double& minorl) const { majorl = lmaj_; minorl = lmin_; }
  void setTicOrientation(double tx, double ty, double tz); //!< Sets tic orientation
  void setTicOrientation(const Protean3D::Triple& val); //!< Same function as above
  Protean3D::Triple ticOrientation() const { return orientation_;} //!< Returns tic orientation
  void setSymmetricTics( bool b) { symtics_ = b;} //!< Sets two-sided tics (default is false) 

  void setScaling(bool d) {draw_tics_ = d;} //!< Turns scale drawing on or off
  bool scaling() const {return draw_tics_;} //!< Returns, if scale drawing is on or off
  void setScale(Protean3D::SCALETYPE);
  void setScale(std::shared_ptr<Protean3D::Scale> scale){ scale_ = scale; } //!< This variant sets a user-defined scale object.
  void setNumbers(bool d) {draw_numbers_ = d;} //!< Turns number drawing on or off
  bool numbers() const {return draw_numbers_;} //!< Returns, if number drawing is on or off
  void setNumberColor(Protean3D::Color col); //!< Sets the color for axes numbers
  Protean3D::Color numberColor() const {return numbercolor_;} //!< Returns the color for axes numbers  
  void setNumberAnchor(Protean3D::ANCHOR a) { scaleNumberAnchor_ = a;} //!< Sets anchor position for numbers
  void adjustNumbers(int val) {numbergap_ = val;} //!< Shifts axis numbers in device coordinates dependent on anchor;
  void setAutoScale(bool val = true) {autoscale_ = val;} //!< Turns Autoscaling on or off
  bool autoScale() const { return autoscale_;} //!< actual Autoscaling mode

  void setMajors(size_t val); //!< Requests major intervals (maybe changed, if autoscaling is present)
  void setMinors(size_t val); //!< Requests minor intervals
  size_t majors() const { return majorintervals_; } //!< Returns number of major intervals
  size_t minors() const { return minorintervals_; } //!< Returns number of minor intervals
  Protean3D::TripleVector const& majorPositions() const {return majorpos_;} //!< Returns positions for actual major tics (also if invisible)
  Protean3D::TripleVector const& minorPositions() const {return minorpos_;} //!< Returns positions for actual minor tics (also if invisible)
  
  void setLimits(double start, double stop) {start_=start; stop_=stop;} //!< Sets interval
  void limits(double& start, double& stop) const {start = start_; stop = stop_;} //!< Returns axis interval
  void recalculateTics(); //!< Enforces recalculation of ticmark positions
  
protected:
  std::shared_ptr<GL::AxisObject> globject_p;

private:
  void init();
  bool prepTicCalculation(Triple& startpoint);

  Protean3D::Triple biggestNumberString();
  Protean3D::ANCHOR scaleNumberAnchor_;
  Protean3D::Triple beg_, end_;
  Protean3D::TripleVector majorpos_, minorpos_; //! vectors, holding major resp. minor tic positions;

  double start_, stop_, autostart_, autostop_;
  double lmaj_ = 0.0;
  double lmin_ = 0.0;
  Protean3D::Triple orientation_;

  size_t majorintervals_, minorintervals_;

  bool symtics_;
  bool draw_numbers_, draw_tics_, draw_label_;
  bool autoscale_;
  Protean3D::Color numbercolor_, color_;

  int numbergap_; 
  std::shared_ptr<Protean3D::Scale> scale_;
};

} // ns 


