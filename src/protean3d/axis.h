#pragma once

//#include "protean3d/label.h"
#include "scale.h"
#include "autoscaler.h"

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

  void setPosition(const Protean3D::Triple& beg, const Protean3D::Triple& end); //!< Positionate axis
  void position(Protean3D::Triple& beg, Protean3D::Triple& end) const {beg = beg_; end = end_;} //!< Returns axis' position
  Protean3D::Triple begin() const { return beg_; } //!< Returns axis' beginning position
  Protean3D::Triple end() const { return end_; } //!< Returns axis' ending position 
  double length() const { return (end_-beg_).length(); } //!< Returns axis' length

  void setTicOrientation(double tx, double ty, double tz); //!< Sets tic orientation
  void setTicOrientation(const Protean3D::Triple& val); //!< Same function as above
  Protean3D::Triple ticOrientation() const { return orientation_;} //!< Returns tic orientation
  void setSymmetricTics( bool b) { symtics_ = b;} //!< Sets two-sided tics (default is false) 
  void setScale(Protean3D::SCALETYPE);
  void setScale(Scale* item);
  void setAutoScale(bool val = true) {autoscale_ = val;} //!< Turns Autoscaling on or off
  bool autoScale() const { return autoscale_;} //!< actual Autoscaling mode

  void setMajors(int val); //!< Requests major intervals (maybe changed, if autoscaling is present)
  void setMinors(int val); //!< Requests minor intervals
  int majors() const { return majorintervals_; } //!< Returns number of major intervals
  int minors() const { return minorintervals_; } //!< Returns number of minor intervals
  Protean3D::TripleVector const& majorPositions() const {return majorpos_;} //!< Returns positions for actual major tics (also if invisible)
  Protean3D::TripleVector const& minorPositions() const {return minorpos_;} //!< Returns positions for actual minor tics (also if invisible)
  
  void setLimits(double start, double stop) {start_=start; stop_=stop;} //!< Sets interval
  void limits(double& start, double& stop) const {start = start_; stop = stop_;} //!< Returns axis interval
  void recalculateTics(); //!< Enforces recalculation of ticmark positions


private:

  void init();
  bool prepTicCalculation(Triple& startpoint);

  Protean3D::Triple biggestNumberString();

  Protean3D::Triple beg_, end_;
  Protean3D::TripleVector majorpos_, minorpos_; //! vectors, holding major resp. minor tic positions;

  double start_, stop_, autostart_, autostop_;
  Protean3D::Triple orientation_;

  int majorintervals_, minorintervals_;

  bool symtics_;
  bool autoscale_;

  std::shared_ptr<Protean3D::Scale> scale_;
};

} // ns 


