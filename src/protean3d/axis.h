#pragma once

#include "protean3d/label.h"
#include "protean3d/scale.h"
#include "protean3d/autoscaler.h"

namespace Protean3D
{

//! Autoscalable axis with caption. 
/*!
  Axes are highly customizable especially in terms
  of labeling and scaling.
*/
class PROTEAN3D_EXPORT Axis : public Drawable
{

public:

  Axis(); //!< Constructs standard axis
  Axis(Protean3D::Triple beg, Protean3D::Triple end); //!< Constructs a new axis with specified limits
  virtual ~Axis(); // dtor
  
  virtual void draw(); //!< Draws axis

  /** 
  Used to tag the axis as a z-axis. This information is used to draw correct labels.
  The standard value for axes is false;
  */
  void setZ(bool val) {isZ_=val;} 
  bool isZ() const {return isZ_;} //!< Is a z-axis

  void setPosition(const Protean3D::Triple& beg, const Protean3D::Triple& end); //!< Positionate axis
  void position(Protean3D::Triple& beg, Protean3D::Triple& end) const {beg = beg_; end = end_;} //!< Returns axis' position
  Protean3D::Triple begin() const { return beg_; } //!< Returns axis' beginning position
  Protean3D::Triple end() const { return end_; } //!< Returns axis' ending position 
  double length() const { return (end_-beg_).length(); } //!< Returns axis' length

  void setTicLength(double majorl, double minorl); //!< Sets tics lengths in world coordinates
  //! Returns tics lengths
  void ticLength(double& majorl, double& minorl) const {majorl = lmaj_; minorl = lmin_;}
  void setTicOrientation(double tx, double ty, double tz); //!< Sets tic orientation
  void setTicOrientation(const Protean3D::Triple& val); //!< Same function as above
  Protean3D::Triple ticOrientation() const { return orientation_;} //!< Returns tic orientation
  void setSymmetricTics( bool b) { symtics_ = b;} //!< Sets two-sided tics (default is false) 
    
  //! Sets font for axis label
  void setLabelFont(Protean3D::Label::Font const& font); //!< Sets font for axis label
  Protean3D::Label::Font const& labelFont() const {return labelfont_;} //!< Returns current label font 
  
  void setLabelString(Protean3D::Label::String const& name);   //!< Sets label content
  void setLabelPosition(const Protean3D::Triple& pos, Protean3D::ANCHOR);
  void setLabelColor(Protean3D::RGBA col);
  void setLabel(bool d) {drawLabel_ = d;} //!< Turns label drawing on or off
  void adjustLabel(int val) {labelgap_ = val;} //!< Shifts label in device coordinates dependent on anchor;

  void setScaling(bool d) {drawTics_ = d;} //!< Turns scale drawing on or off
  bool scaling() const {return drawTics_;} //!< Returns, if scale drawing is on or off
  void setScale(Protean3D::SCALETYPE);
  void setScale(Scale* item);
  void setNumbers(bool d) {drawNumbers_ = d;} //!< Turns number drawing on or off
  bool numbers() const {return drawNumbers_;} //!< Returns, if number drawing is on or off
  void setNumberColor(Protean3D::RGBA col); //!< Sets the color for axes numbers
  Protean3D::RGBA numberColor() const {return numbercolor_;} //!< Returns the color for axes numbers  
  void setNumberFont(Protean3D::Label::Font const&); //!< Sets font for numbering
  Protean3D::Label::Font const& numberFont() const {return numberfont_;} //!< Returns current numbering font
  void setNumberAnchor(Protean3D::ANCHOR a) { scaleNumberAnchor_ = a;} //!< Sets anchor position for numbers
  void adjustNumbers(int val) {numbergap_ = val;} //!< Shifts axis numbers in device coordinates dependent on anchor;

  void setAutoScale(bool val = true) {autoscale_ = val;} //!< Turns Autoscaling on or off
  bool autoScale() const { return autoscale_;} //!< actual Autoscaling mode

  void setMajors(int val); //!< Requests major intervals (maybe changed, if autoscaling is present)
  void setMinors(int val); //!< Requests minor intervals
  int majors() const { return majorintervals_; } //!< Returns number of major intervals
  int minors() const { return minorintervals_; } //!< Returns number of minor intervals
  Protean3D::TripleVector const& majorPositions() const {return majorpos_;} //!< Returns positions for actual major tics (also if invisible)
  Protean3D::TripleVector const& minorPositions() const {return minorpos_;} //!< Returns positions for actual minor tics (also if invisible)
  
  //! Sets line width for axis components
  void setLineWidth(double val, double majfac = 0.9, double minfac = 0.5);
  double lineWidth() const { return lineWidth_;} //!< Returns line width for axis body
  double majLineWidth() const { return majLineWidth_;} //!< Returns Line width for major tics
  double minLineWidth() const { return minLineWidth_;} //!< Returns Line width for minor tics

  void setLimits(double start, double stop) {start_=start; stop_=stop;} //!< Sets interval
  void limits(double& start, double& stop) const {start = start_; stop = stop_;} //!< Returns axis interval
  void recalculateTics(); //!< Enforces recalculation of ticmark positions


private:

  void init();
  void drawBase();
  void drawTics();
  void drawTicLabel(Protean3D::Triple Pos, int mtic);
  Protean3D::Triple drawTic(Protean3D::Triple nadir, double length);
  void drawLabel();
  bool prepTicCalculation(Triple& startpoint);

  Protean3D::Triple biggestNumberString();
  
  
  Protean3D::ANCHOR scaleNumberAnchor_;
  Protean3D::Label label_;
  std::vector<Protean3D::Label> markerLabel_;

  Protean3D::Triple beg_, end_;
  Protean3D::TripleVector majorpos_, minorpos_; //! vectors, holding major resp. minor tic positions;

  Protean3D::Triple ncube_beg_, ncube_end_; //!< enclosing box for axis numbering

  double start_, stop_, autostart_, autostop_;
  double lmaj_, lmin_;
  Protean3D::Triple orientation_;

  int majorintervals_, minorintervals_;

  double lineWidth_, majLineWidth_, minLineWidth_;
  bool symtics_;
  bool drawNumbers_, drawTics_, drawLabel_;
  bool autoscale_;
  Protean3D::Label::Font numberfont_, labelfont_;
  Protean3D::RGBA  numbercolor_;

  int numbergap_, labelgap_; 

  std::shared_ptr<Protean3D::Scale> scale_;

  bool isZ_; // identify z-axis
};

} // ns 


