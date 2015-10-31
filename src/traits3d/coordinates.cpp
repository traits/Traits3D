#include <glm/gtc/type_ptr.hpp>
#include "traits3d/glbase/transformation.h"
#include "traits3d/glbase/linerenderer.h"
#include "traits3d/helper.h"
#include "traits3d/coordinates.h"

namespace traits3d
{

Coordinates::Coordinates(Triple first, Triple second, COORDINATESTYLE st)
{
    autodecoration_ = true;
    axes = std::vector<Axis>(asize);
    setStyle(st);
    init(first, second);
    setGridLines(false, false);
}

Coordinates::~Coordinates()
{
}

void Coordinates::init(Triple first, Triple second)
{
    for (unsigned i = 0; i != axes.size(); ++i)
        axes[i].setScale(LINEARSCALE);

    Triple dv = second - first;
    setPosition(first, second);
    double majl = glm::length(dv) / 100; // 1 %
    setTicLength(majl, 0.6 * majl);
    const double ori = -1; // inward tics
    axes[X1].setPosition(first, first + Triple(dv.x, 0, 0));                     // front bottom x
    axes[Y1].setPosition(first, first + Triple(0, dv.y, 0));                        // bottom left  y
    axes[Z1].setPosition(first + Triple(0, dv.y, 0), first + Triple(0, dv.y, dv.z));    // back left z
    axes[X1].setTicOrientation(0, -ori, 0);
    axes[Y1].setTicOrientation(-ori, 0, 0);
    axes[Z1].setTicOrientation(-ori, 0, 0);
    axes[X1].setLimits(first.x, second.x);
    axes[X2].setLimits(first.x, second.x);
    axes[X3].setLimits(first.x, second.x);
    axes[X4].setLimits(first.x, second.x);
    axes[Y1].setLimits(first.y, second.y);
    axes[Y2].setLimits(first.y, second.y);
    axes[Y3].setLimits(first.y, second.y);
    axes[Y4].setLimits(first.y, second.y);
    axes[Z1].setLimits(first.z, second.z);
    axes[Z2].setLimits(first.z, second.z);
    axes[Z3].setLimits(first.z, second.z);
    axes[Z4].setLimits(first.z, second.z);
    // remaining x axes
    axes[X2].setPosition(first + Triple(0, 0, dv.z), first + Triple(dv.x, 0, dv.z)); // front top x
    axes[X3].setPosition(first + Triple(0, dv.y, dv.z), second);                          // back top x
    axes[X4].setPosition(first + Triple(0, dv.y, 0), first + Triple(dv.x, dv.y, 0)); // back bottom x
    axes[X2].setTicOrientation(0, -ori, 0);
    axes[X3].setTicOrientation(0, ori, 0);
    axes[X4].setTicOrientation(0, ori, 0);
    // remaining y axes
    axes[Y2].setPosition(first + Triple(dv.x, 0, 0), first + Triple(dv.x, dv.y, 0)); // bottom right y
    axes[Y3].setPosition(first + Triple(dv.x, 0, dv.z), second);                     // top right y
    axes[Y4].setPosition(first + Triple(0, 0, dv.z), first + Triple(0, dv.y, dv.z)); // top left y
    axes[Y2].setTicOrientation(ori, 0, 0);
    axes[Y3].setTicOrientation(ori, 0, 0);
    axes[Y4].setTicOrientation(-ori, 0, 0);
    // remaining z axes
    axes[Z2].setPosition(first, first + Triple(0, 0, dv.z));                        // front left z
    axes[Z4].setPosition(first + Triple(dv.x, dv.y, 0), second);                        // back right z
    axes[Z3].setPosition(first + Triple(dv.x, 0, 0), first + Triple(dv.x, 0, dv.z)); // front right z
    axes[Z2].setTicOrientation(-ori, 0, 0);
    axes[Z4].setTicOrientation(ori, 0, 0);
    axes[Z3].setTicOrientation(ori, 0, 0);
    axes[X1].setLabelText("X");
    axes[X2].setLabelText("X");
    axes[X3].setLabelText("X");
    axes[X4].setLabelText("X");
    axes[Y1].setLabelText("Y");
    axes[Y2].setLabelText("Y");
    axes[Y3].setLabelText("Y");
    axes[Y4].setLabelText("Y");
    axes[Z1].setLabelText("Z");
    axes[Z2].setLabelText("Z");
    axes[Z3].setLabelText("Z");
    axes[Z4].setLabelText("Z");
    setStyle(style_);
}

void Coordinates::init(Box hull)
{
    init(hull.minVertex, hull.maxVertex);
}

bool Coordinates::initializeGL()
{
    for (auto &a : axes)
    {
        if (!a.initializeGL())
            return false;
    }

    grid_renderer_ = std::make_shared<gl::LineRenderer>();
    return (grid_renderer_) ? true : false;
}

void Coordinates::setTicLength(double major, double minor)
{
    for (auto &a : axes)
        a.setTicLength(major, minor);
}

void Coordinates::draw(gl::Transformation const &matrices)
{
    //GL::StateBewarer sb(GL_LINE_SMOOTH, true);
    //
    //if (!lineSmooth())
    //  sb.turnOff();
    //
    if (autoDecoration())
        chooseAxes(matrices, gl::viewPort());

    for (auto it : aidx_)
        axes[it].draw(matrices);

    if (style_ == NOCOORDINATES)
        return;

    if (majorgridlines_)
        drawMajorGridLines(matrices);

    if (minorgridlines_)
        drawMinorGridLines(matrices);
}


//! build convex hull (6 axes: 2 x, 2 y, 2 z) and choose one of them at a time for scales, labels etc.
void Coordinates::chooseAxes(
    gl::Transformation const &matrices, glm::ivec4 const &viewport)
{
    TripleVector beg(axes.size());
    TripleVector end(axes.size());
    std::vector<Tuple> src(2 * axes.size());
    glm::dmat4 const &proj_matrix = matrices.proj();
    glm::dmat4 const &mv_matrix = matrices.mv();
    size_t i;

    // collect axes viewport coordinates and initialize
    for (i = 0; i != axes.size(); ++i)
    {
        if (style() != NOCOORDINATES)
            attach(i);

        beg[i] = gl::World2ViewPort(axes[i].begin(), mv_matrix, proj_matrix, viewport);
        end[i] = gl::World2ViewPort(axes[i].end(), mv_matrix, proj_matrix, viewport);
        src[i] = Tuple(beg[i].x, beg[i].y);
        src[axes.size() + i] = Tuple(end[i].x, end[i].y);
        axes[i].showTics(false);
        axes[i].showNumbers(false);
        axes[i].showLabel(false);
    }

    std::vector<size_t> idx;
    convexhull2d(idx, src);
    int rem_x = -1;
    int rem_y = -1;
    int rem_z = -1;
    bool left;
    int choice_x = -1;
    int choice_y = -1;
    int choice_z = -1;
    int other_x = -1;
    int other_y = -1;
    int other_z = -1;

    //traverse convex hull
    for (size_t k = 0; k != idx.size(); ++k)
    {
        Triple one, two;

        if (idx[k] >= axes.size()) // is end point
            one = end[idx[k] - axes.size()];
        else                       // is begin point
            one = beg[idx[k]];

        size_t next = idx[(k + 1) % idx.size()]; // next point in cv (considered as ring buffer of points)

        if (next >= axes.size())
            two = end[next - axes.size()];
        else
            two = beg[next];

        for (i = 0; i != axes.size(); ++i)
        {
            if (
                (equal(one, beg[i]) && equal(two, end[i]))
                ||
                (equal(two, beg[i]) && equal(one, end[i]))
            )
            {
                if (i == X1 || i == X2 || i == X3 || i == X4) // x Achsen
                {
                    if (rem_x >= 0) // schon zweite Achse der konvexen Huelle ?
                    {
                        // untere der beiden x Achsen
                        double y = std::min(std::min(end[rem_x].y, end[i].y), std::min(beg[rem_x].y, beg[i].y));
                        choice_x = static_cast<int>(
                                       (equal(y, beg[i].y) || equal(y, end[i].y)) ? i : rem_x);
                        other_x = (choice_x == (int)i) ? rem_x : (int)i;
                        left = (beg[choice_x].x < beg[other_x].x || end[choice_x].x < end[other_x].x)
                               ? true
                               : false;
                        autoDecorateExposedAxis(axes[choice_x], end[choice_x] - beg[choice_x], left);
                        rem_x = -1;
                    }
                    else
                        rem_x = static_cast<int>(i);
                }
                else if (i == Y1 || i == Y2 || i == Y3 || i == Y4)
                {
                    if (rem_y >= 0)
                    {
                        // untere der beiden y Achsen
                        double y = std::min(std::min(end[rem_y].y, end[i].y), std::min(beg[rem_y].y, beg[i].y));
                        choice_y = static_cast<int>(
                                       (equal(y, beg[i].y) || equal(y, end[i].y)) ? i : rem_y);
                        other_y = (choice_y == (int)i) ? rem_y : (int)i;
                        left = (beg[choice_y].x < beg[other_y].x || end[choice_y].x < end[other_y].x)
                               ? true
                               : false;
                        autoDecorateExposedAxis(axes[choice_y], end[choice_y] - beg[choice_y], left);
                        rem_y = -1;
                    }
                    else
                        rem_y = static_cast<int>(i);
                }
                else if (i == Z1 || i == Z2 || i == Z3 || i == Z4)
                {
                    if (rem_z >= 0)
                    {
                        // hintere der beiden z Achsen
                        double z = std::max(std::max(end[rem_z].z, end[i].z), std::max(beg[rem_z].z, beg[i].z));
                        choice_z = static_cast<int>(
                                       (equal(z, beg[i].z) || equal(z, end[i].z)) ? i : rem_z);
                        other_z = (choice_z == (int)i) ? rem_z : (int)i;
                        rem_z = -1;
                    }
                    else
                        rem_z = static_cast<int>(i);
                }
            }
        } // for axes
    } // for idx

    // fit z axis in - the on-the-wall axis if the decorated axes build a continuous line, the opposite else
    if (choice_x >= 0 && choice_y >= 0 && choice_z >= 0)
    {
        left = (beg[choice_z].x < beg[other_z].x || end[choice_z].x < end[other_z].x)
               ? true
               : false;

        if (
            equal(axes[choice_z].begin(), axes[choice_x].begin())
            || equal(axes[choice_z].begin(), axes[choice_x].end())
            || equal(axes[choice_z].begin(), axes[choice_y].begin())
            || equal(axes[choice_z].begin(), axes[choice_y].end())
            || equal(axes[choice_z].end(), axes[choice_x].begin())
            || equal(axes[choice_z].end(), axes[choice_x].end())
            || equal(axes[choice_z].end(), axes[choice_y].begin())
            || equal(axes[choice_z].end(), axes[choice_y].end())
        )
            autoDecorateExposedAxis(axes[choice_z], end[choice_z] - beg[choice_z], left);
        else
        {
            autoDecorateExposedAxis(axes[other_z], end[choice_z] - beg[choice_z], !left);
            choice_z = other_z; // for FRAME
        }
    }

    if (style() == FRAME)
    {
        for (i = 0; i != axes.size(); ++i)
        {
            if ((int)i != choice_x && (int)i != choice_y && (int)i != choice_z)
                detach(i);
        }
    }
}


void Coordinates::autoDecorateExposedAxis(Axis &ax, Triple const &projected_ax, bool left)
{
    Tuple diff = Tuple(projected_ax.x, projected_ax.y);
    double s = glm::length(diff);

    if (isZero(s))
        return;

    ax.showTics(true);
    ax.showNumbers(true);
    ax.showLabel(true);
    // anchor position changes for critical angle of 5 degrees between label and projected axis
    const double switch_angle = sin(glm::radians(5.0));
    const double sina = fabs(diff.y / s);

    if (left) // leftmost (compared with antagonist in CV)  axis -> draw decorations on the left side
    {
        if (diff.x >= 0 && diff.y >= 0 && sina < switch_angle)           // 0..switch angle, 1st quadrant
            ax.setNumberAnchor(TextEngine::Anchor::BottomCenter);
        else if (diff.x >= 0 && diff.y >= 0)                             // >= switch angle, 1st quadrant
            ax.setNumberAnchor(TextEngine::Anchor::CenterRight);
        else if (diff.x <= 0 && diff.y >= 0 && sina >= switch_angle)    // ... 2nd quadrant etc.
            ax.setNumberAnchor(TextEngine::Anchor::CenterRight);
        else if (diff.x <= 0 && diff.y >= 0)
            ax.setNumberAnchor(TextEngine::Anchor::TopCenter);
        else if (diff.x <= 0 && diff.y <= 0 && sina <= switch_angle)
            ax.setNumberAnchor(TextEngine::Anchor::BottomCenter);
        else if (diff.x <= 0 && diff.y <= 0)
            ax.setNumberAnchor(TextEngine::Anchor::CenterRight);
        else if (diff.x >= 0 && diff.y <= 0 && sina >= switch_angle)
            ax.setNumberAnchor(TextEngine::Anchor::CenterRight);
        else if (diff.x >= 0 && diff.y <= 0)
            ax.setNumberAnchor(TextEngine::Anchor::TopCenter);
    }
    else // rightmost axis
    {
        if (diff.x >= 0 && diff.y >= 0 && sina <= switch_angle)
            ax.setNumberAnchor(TextEngine::Anchor::TopCenter);
        else if (diff.x >= 0 && diff.y >= 0)
            ax.setNumberAnchor(TextEngine::Anchor::CenterLeft);
        else if (diff.x <= 0 && diff.y >= 0 && sina >= switch_angle)
            ax.setNumberAnchor(TextEngine::Anchor::CenterLeft);
        else if (diff.x <= 0 && diff.y >= 0)
            ax.setNumberAnchor(TextEngine::Anchor::BottomCenter);
        else if (diff.x <= 0 && diff.y <= 0 && sina <= switch_angle)
            ax.setNumberAnchor(TextEngine::Anchor::TopCenter);
        else if (diff.x <= 0 && diff.y <= 0)
            ax.setNumberAnchor(TextEngine::Anchor::CenterLeft);
        else if (diff.x >= 0 && diff.y <= 0 && sina >= switch_angle)
            ax.setNumberAnchor(TextEngine::Anchor::CenterLeft);
        else if (diff.x >= 0 && diff.y <= 0)
            ax.setNumberAnchor(TextEngine::Anchor::BottomCenter);
    }
}


void Coordinates::setPosition(Triple first, Triple second)
{
    first_ = first;
    second_ = second;
}


void Coordinates::setAxesColor(Color const &val)
{
    for (auto &a : axes)
        a.setColor(val);
}


void Coordinates::setNumberFont(FontInfo const &font)
{
    for (auto &a : axes)
        a.setNumberFont(font);
}


void Coordinates::setNumberColor(Color const &val)
{
    for (auto &a : axes)
        a.setNumberColor(val);
}

void Coordinates::setAutoScale(bool val)
{
    for (auto &a : axes)
        a.setAutoScale(val);
}

void Coordinates::setStandardScale()
{
    for (auto &a : axes)
        a.setScale(LINEARSCALE);
}


void Coordinates::setLabelFont(FontInfo const &font)
{
    for (auto &a : axes)
        a.setLabelFont(font);
}


void Coordinates::setLabelColor(Color const &val)
{
    for (auto &a : axes)
        a.setLabelColor(val);
}

void Coordinates::setStyle(COORDINATESTYLE s, AXIS frame_1,
                           AXIS frame_2, AXIS frame_3)
{
    style_ = s;

    switch (s)
    {
        case NOCOORDINATES:
        {
            aidx_.clear();
        }
        break;

        case BOX:
        {
            for (size_t i = 0; i != axes.size(); ++i)
                attach(i);
        }
        break;

        case FRAME:
        {
            aidx_.clear();

            if (!autoDecoration())
            {
                attach(frame_1);
                attach(frame_2);
                attach(frame_3);
            }
        }
        break;

        default:
            break;
    }
}

/**
The axis used for tic calculation is chosen randomly from the respective pair.
For most cases an identical tic distribution is therefore recommended.
\param majors  Draw grid between major tics
\param minors  Draw grid between minor tics
\param sides   Side(s), where the grid should be drawn
*/
void Coordinates::setGridLines(bool majors, bool minors, int sides)
{
    sides_ = sides;
    majorgridlines_ = majors;
    minorgridlines_ = minors;
}

void Coordinates::drawMajorGridLines(gl::Transformation const &matrices)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //setLineWidth(axes[X1].majLineWidth());
    grid_renderer_->setColor(gridlinecolor_);

    if (sides_ & FLOOR)
        drawMajorGridLines(X1, X4, Y1, Y2, matrices);

    if (sides_ & CEIL)
        drawMajorGridLines(X2, X3, Y3, Y4, matrices);

    if (sides_ & LEFT)
        drawMajorGridLines(Y1, Y4, Z1, Z2, matrices);

    if (sides_ & RIGHT)
        drawMajorGridLines(Y2, Y3, Z3, Z4, matrices);

    if (sides_ & FRONT)
        drawMajorGridLines(X1, X2, Z2, Z3, matrices);

    if (sides_ & BACK)
        drawMajorGridLines(X3, X4, Z4, Z1, matrices);
}

void Coordinates::drawMinorGridLines(gl::Transformation const &matrices)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //setLineWidth(axes[X1].minLineWidth());
    grid_renderer_->setColor(gridlinecolor_);

    if (sides_ & FLOOR)
        drawMinorGridLines(X1, X4, Y1, Y2, matrices);

    if (sides_ & CEIL)
        drawMinorGridLines(X2, X3, Y3, Y4, matrices);

    if (sides_ & LEFT)
        drawMinorGridLines(Y1, Y4, Z1, Z2, matrices);

    if (sides_ & RIGHT)
        drawMinorGridLines(Y2, Y3, Z3, Z4, matrices);

    if (sides_ & FRONT)
        drawMinorGridLines(X1, X2, Z2, Z3, matrices);

    if (sides_ & BACK)
        drawMinorGridLines(X3, X4, Z4, Z1, matrices);
}

void Coordinates::drawMajorGridLines(AXIS a0, AXIS a1, AXIS b0, AXIS b1, gl::Transformation const &matrices)
{
    std::vector<TripleF> ub = convert(axes[a0].majorPositions()); //todo convert (check double values)
    std::vector<TripleF> ue = convert(axes[a1].majorPositions());
    std::vector<TripleF> vb = convert(axes[b0].majorPositions());
    std::vector<TripleF> ve = convert(axes[b1].majorPositions());
    grid_renderer_->createGrid(ub, ue, vb, ve);
    grid_renderer_->draw(matrices);
}

void Coordinates::drawMinorGridLines(AXIS a0, AXIS a1, AXIS b0, AXIS b1, gl::Transformation const &matrices)
{
    std::vector<TripleF> ub = convert(axes[a0].minorPositions());
    std::vector<TripleF> ue = convert(axes[a1].minorPositions());
    std::vector<TripleF> vb = convert(axes[b0].minorPositions());
    std::vector<TripleF> ve = convert(axes[b1].minorPositions());
    grid_renderer_->createGrid(ub, ue, vb, ve);
    grid_renderer_->draw(matrices);
}

void Coordinates::attach(size_t idx)
{
    if (aidx_.end() == std::find(aidx_.begin(), aidx_.end(), idx))
        aidx_.push_back(idx);
}

void Coordinates::detach(size_t idx)
{
    auto it = std::find(aidx_.begin(), aidx_.end(), idx);

    if (it != aidx_.end())
        aidx_.erase(it);
}

} // ns