#pragma once

#include <list>
#include "axis.h"

namespace traits3d
{
namespace gl
{
class LineRenderer;
}

//! A coordinate system with different styles (BOX, FRAME)
class TRAITS3D_EXPORT Coordinates
{
public:
    explicit Coordinates(Triple blb = Triple(0, 0, 0),
                         Triple ftr = Triple(0, 0, 0),
                         COORDINATESTYLE = BOX);
    ~Coordinates();

    void init(Triple beg = Triple(0, 0, 0), Triple end = Triple(0, 0, 0));
    void init(Box hull);
    virtual bool initializeGL();

    //! Set style for the coordinate system (NOCOORDINATES, FRAME or BOX)
    void setStyle(COORDINATESTYLE s,  AXIS frame_1 = X1,
                  AXIS frame_2 = Y1,
                  AXIS frame_3 = Z1);
    COORDINATESTYLE style() const
    {
        return style_;   //!< Return style oft the coordinate system
    }
    void setPosition(Triple first, Triple second); //!< first == front_left_bottom, second == back_right_top
    void setAxesColor(Color const &val); //!< Set common color for all axes
    //! Set common font for all axis numberings
    void setNumberFont(FontInfo const &font);
    //! Set common color for all axis numberings
    void setNumberColor(Color const &val);
    void setStandardScale(); //!< Sets an linear axis with real number items

    //! Sets color for the grid lines
    void setGridLineColor(Color const &val)
    {
        gridlinecolor_ = val;
    }
    //! Set common font for all axis labels
    void setLabelFont(FontInfo const &font);
    //! Set common color for all axis labels
    void setLabelColor(Color const &val);

    //! Set length for tic marks
    void setTicLength(double major, double minor);
    //! Switch autoscaling of axes
    void setAutoScale(bool val = true);

    Triple first() const
    {
        return first_;
    }
    Triple second() const
    {
        return second_;
    }

    void setAutoDecoration(bool val = true)
    {
        autodecoration_ = val;
    }
    bool autoDecoration() const
    {
        return autodecoration_;
    }

    void draw(gl::Transformation const &matrices);

    //! Defines whether a grid between the major and/or minor tics should be drawn
    void setGridLines(bool majors, bool minors, int sides = NOSIDEGRID);
    int grids() const
    {
        return sides_;   //!< Returns grids switched on
    }

    //! The vector of all 12 axes - use them to set axis properties individually.
    std::vector<Axis> axes;

private:
    static unsigned const asize = 12;

    Triple first_, second_;
    COORDINATESTYLE style_;

    void chooseAxes(gl::Transformation const &matrices, glm::ivec4 const &viewport);
    void autoDecorateExposedAxis(Axis &ax, Triple const &projected_ax, bool left);
    void drawMajorGridLines(gl::Transformation const &matrices); //!< Draws a grid between the major tics on the site
    void drawMinorGridLines(gl::Transformation const &matrices); //!< Draws a grid between the minor tics on the site
    void drawMajorGridLines(AXIS a0, AXIS a1, AXIS b0, AXIS b1, gl::Transformation const &matrices); //! Helper
    void drawMinorGridLines(AXIS a0, AXIS a1, AXIS b0, AXIS b1, gl::Transformation const &matrices); //! Helper

    bool autodecoration_;
    bool majorgridlines_, minorgridlines_;
    int  sides_;
    std::shared_ptr<gl::LineRenderer> grid_renderer_; //todo use multiple renderers
    Color gridlinecolor_ = Color(0, 0, 0, 1);

    std::list<size_t> aidx_;
    void attach(size_t idx);
    void detach(size_t idx);
};
} // ns


