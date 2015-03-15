#pragma once

#include "traits3d/glbase/glhelper.h"
#include "traits3d/glbase/matrixstack.h"
#include "traits3d/scale.h"
#include "traits3d/autoscaler.h"
#include "traits3d/axisobject.h"
#include "traits3d/fonts/fontinfo.h"
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
    Axis(Triple beg, Triple end); //!< Constructs a new axis with specified limits
    virtual ~Axis(); // dtor
  
    virtual bool initializeGL();
    void draw(GL::MatrixStack const& matrices);

    /** 
    Used to tag the axis as a z-axis. This information is used to draw correct labels.
    The standard value for axes is false;
    */
    void setZ(bool val) {is_z_=val;} 
    bool isZ() const {return is_z_;} //!< Is a z-axis

    void setPosition(const Triple& beg, const Triple& end); //!< Set axis position
    void position(Triple& beg, Triple& end) const {beg = axis_origin_; end = axis_end_;} //!< Returns axis' position
    Triple begin() const { return axis_origin_; } //!< Returns axis' beginning position
    Triple end() const { return axis_end_; } //!< Returns axis' ending position 
    double length() const { return glm::distance(axis_origin_,axis_end_); } //!< Returns axis' length
    void setColor(Color const& val) { axis_color_ = val; }

    void setScale(SCALETYPE val);
    void setScale(std::shared_ptr<Scale> val){ scale_ = val; } //!< This variant sets a user-defined scale object.
    void showTics(bool val) { show_tics_ = val; } //!< Turns scale drawing on or off
    bool hasTics() const { return show_tics_; } //!< Returns, if scale drawing is on or off
    void setTicLength(double majorl, double minorl); //!< Sets tics lengths in world coordinates
    //! Returns tics lengths
    void ticLength(double& majorl, double& minorl) const { majorl = len_major_tics_; minorl = len_minor_tics_; }
    void setTicOrientation(double tx, double ty, double tz); //!< Sets tic orientation
    void setTicOrientation(const Triple& val); //!< Same function as above
    Triple ticOrientation() const { return tic_orientation_;} //!< Returns tic orientation
    void setSymmetricTics( bool b) { symmetric_tics_ = b;} //!< Sets two-sided tics (default is false) 
    void setAutoScale(bool val = true) { autoscale_ = val; } //!< Turns auto-scaling on or off
    bool autoScale() const { return autoscale_; } //!< actual auto-scaling mode

    //! Sets font for axis label
    void showLabel(bool d) { show_label_ = d; } //!< Turns label drawing on or off
    void setLabelFont(FontInfo const& font_info); //!< Sets font for axis label
    void setLabelText(std::string const& val);   //!< Sets label content
    void setLabelPosition(const Triple& pos, TextEngine::Anchor a);
    void setLabelColor(Color const& val);
    void adjustLabel(int val) {label_gap_ = val;} //!< Shifts label in device coordinates dependent on anchor;
      
    void showNumbers(bool d) {show_numbers_ = d;} //!< Turns number drawing on or off
    bool numbers() const {return show_numbers_;} //!< Returns, if number drawing is on or off
    void setNumberColor(Color const& col); //!< Sets the color for axes numbers
    Color numberColor() const {return number_color_;} //!< Returns the color for axes numbers  
    void setNumberFont(FontInfo const& font_info); //!< Sets font for numbering
    void setNumberAnchor(TextEngine::Anchor a) { scale_number_anchor_ = a; } //!< Sets anchor position for numbers
    void adjustNumbers(int val) {number_gap_ = val;} //!< Shifts axis numbers in device coordinates dependent on anchor;

    void setMajors(size_t val); //!< Requests major intervals (maybe changed, if auto-scaling is present)
    void setMinors(size_t val); //!< Requests minor intervals
    size_t majors() const { return majorintervals_; } //!< Returns number of major intervals
    size_t minors() const { return minorintervals_; } //!< Returns number of minor intervals
    TripleVector const& majorPositions() const {return major_positions_;} //!< Returns positions for actual major tics (also if invisible)
    TripleVector const& minorPositions() const {return minor_positions_;} //!< Returns positions for actual minor tics (also if invisible)
  
    void setLimits(double start, double stop) {start_=start; stop_=stop;} //!< Sets interval
    void limits(double& start, double& stop) const {start = start_; stop = stop_;} //!< Returns axis interval
  
  protected:
    std::shared_ptr<GL::AxisObject> globject_p;

  private:
    void init();
    bool prepTicCalculation(Triple& startpoint);
    void recalculateTics(); //!< Enforces recalculation of tic mark positions

    bool is_z_ = false; // identify z-axis

    Triple axis_origin_;
    Triple axis_end_ ;
    TripleVector major_positions_; 
    TripleVector minor_positions_; //! vectors, holding major resp. minor tic positions;

    std::shared_ptr<Scale> scale_;
    double start_ = 0.0;
    double stop_ = 0.0;
    double autostart_ = 0.0; 
    double autostop_ = 0.0;
    double len_major_tics_ = 0.0; 
    double len_minor_tics_ = 0.0;
    Triple tic_orientation_;

    size_t majorintervals_ = 1;
    size_t minorintervals_ = 1;

    bool show_numbers_ = false;
    bool show_tics_ = false;
    bool show_label_ = false;
    bool symmetric_tics_ = false;
    bool autoscale_ = true;

    FontInfo number_font_;
    FontInfo label_font_;
    Color number_color_ = Color(0.0f, 0.0f, 0.0f, 1.0f);
    Color label_color_ = Color(0.0f, 0.0f, 0.0f, 1.0f);
    Color axis_color_ = Color(0.0f, 0.0f, 0.0f, 1.0f);
    int number_gap_ = 0;
    int label_gap_ = 0;
      
    Triple label_position_;
    std::string label_text_;
    TextEngine::Anchor label_anchor_;
    TextEngine::Anchor scale_number_anchor_;
  };
} // ns 


