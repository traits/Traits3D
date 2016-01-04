#include "traits3d/helper.h"
#include "traits3d/axis.h"

namespace traits3d
{

Axis::Axis()
{
    init();
};

Axis::~Axis()
{
}

Axis::Axis(Triple beg, Triple end)
{
    init();
    setPosition(beg, end);
}

void Axis::init()
{
    scale_ = std::shared_ptr<Scale>(new LinearScale);
    number_font_ = FontInfo("OpenSans Regular", 24);
    label_font_ = FontInfo("OpenSans Italic", 36);
    tic_orientation_ = Triple(1.0, 0.0, 0.0);
    scale_number_anchor_ = TextEngine::Anchor::Center;
    label_anchor_ = TextEngine::Anchor::Center;
    label_text_ = "X";
}

void Axis::setPosition(const Triple &beg, const Triple &end)
{
    axis_origin_ = beg;
    axis_end_ = end;
}

void Axis::setMajors(size_t val)
{
    if (val == majorintervals_)
        return;

    majorintervals_ = (!val) ? 1 : val; // always >= 1
}

/*!
\see LogScale::setMinors().
*/
void Axis::setMinors(size_t val)
{
    if (val == minorintervals_)
        return;

    minorintervals_ = (!val) ? 1 : val; // always >= 1
}

void Axis::setTicLength(double majorl, double minorl)
{
    len_major_tics_ = majorl;
    len_minor_tics_ = minorl;
}

void Axis::setTicOrientation(double tx, double ty, double tz)
{
    setTicOrientation(Triple(tx, ty, tz));
}

void Axis::setTicOrientation(const Triple &val)
{
    tic_orientation_ = (equal(val, Triple(0.0, 0.0, 0.0)))
                       ? Triple(1.0, 0.0, 0.0)
                       : glm::normalize(val);
}

bool Axis::prepTicCalculation(Triple &startpoint)
{
    if (equal(start_, stop_))
        return false;

    autostart_ = start_;
    autostop_ = stop_;

    if (autoScale())
    {
        setMajors(scale_->autoscale(autostart_, autostop_, start_, stop_, majors()));

        if (equal(autostart_, autostop_))
            return false;
    }

    scale_->setLimits(start_, stop_);
    scale_->setMajors(majors());
    scale_->setMinors(minors());
    scale_->setMajorLimits(autostart_, autostop_);
    scale_->calculate();
    startpoint = axis_end_ - axis_origin_;
    return true;
}

void Axis::recalculateTics()
{
    Triple runningpoint;
    major_positions_.clear();
    minor_positions_.clear();

    if (false == prepTicCalculation(runningpoint))
        return;

    unsigned int i;

    for (i = 0; i != scale_->majors_p.size(); ++i)
    {
        double t = (scale_->majors_p[i] - start_) / (stop_ - start_);
        major_positions_.push_back(axis_origin_ + t * runningpoint);
    }

    for (i = 0; i != scale_->minors_p.size(); ++i)
    {
        double t = (scale_->minors_p[i] - start_) / (stop_ - start_);
        minor_positions_.push_back(axis_origin_ + t * runningpoint);
    }
}

void Axis::setNumberFont(FontInfo const &font_info)
{
    number_font_ = font_info;
}

void Axis::setNumberColor(Color const &col)
{
    number_color_ = col;
}

void Axis::setLabelFont(FontInfo const &font_info)
{
    label_font_ = font_info;
}

void Axis::setLabelText(std::string const &val)
{
    label_text_ = val;
}

/*!
  Sets label position in conjunction with an anchoring strategy
  */
void Axis::setLabelPosition(const Triple &pos, TextEngine::Anchor a)
{
    label_position_ = pos;
    label_anchor_ = a;
}

//! Sets color for label
void Axis::setLabelColor(Color const &val)
{
    label_color_ = val;
}

/*
  Sets one of the predefined scaling types.
  \warning Too small intervals in logarithmic scales lead to
  empty scales (or perhaps a scale only containing an isolated
  major tic). Better switch to linear scales in such cases.
  */
void Axis::setScale(SCALETYPE val)
{
    switch (val)
    {
        case LINEARSCALE:
            setScale(std::shared_ptr<Scale>(new LinearScale));
            break;

        case LOG10SCALE:
            setScale(std::shared_ptr<Scale>(new LogScale));
            setMinors(9);
            break;

        default:
            break;
    }
}

void Axis::draw(glb::Transformation const &matrices)
{
    //todo performance!
    recalculateTics();
    globject_p->setValues(axis_origin_, axis_end_, major_positions_, minor_positions_, scale_->majors_p);
    globject_p->setColor(axis_color_);
    globject_p->showLabel(show_label_);

    if (show_label_)
    {
        globject_p->setLabelFont(label_font_);
        globject_p->setLabelText(label_text_);
        globject_p->setLabelPosition(label_position_, label_anchor_);
        globject_p->setLabelColor(label_color_);
        globject_p->adjustLabel(label_gap_);
    }

    globject_p->showTics(show_tics_);
    globject_p->setSymmetricTics(symmetric_tics_);
    globject_p->setTicOrientation(tic_orientation_);
    globject_p->setTicLength(len_major_tics_, len_minor_tics_);
    globject_p->showNumbers(show_numbers_);

    if (show_numbers_)
    {
        globject_p->setNumberFont(number_font_);
        globject_p->setNumberColor(number_color_);
        globject_p->setNumberAnchor(scale_number_anchor_);
        globject_p->adjustNumbers(number_gap_);
    }

    //end todo
    globject_p->draw(matrices);
}

bool Axis::initializeGL()
{
    globject_p = std::make_shared<gl::AxisObject>();
    return (globject_p) ? true : false;
}

} // ns