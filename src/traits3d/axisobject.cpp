#include <glm/gtc/matrix_transform.hpp>
#include "traits3d/glbase/transformation.h"
#include "traits3d/helper.h"
#include "traits3d/glbase/shader_std.h"
#include "traits3d/textengine/textengine_std.h"
#include "traits3d/axisobject.h"


Traits3D::GL::AxisObject::AxisObject()
    : GL::Object()
{
    shader_.create(GL::ShaderCode::Vertex::Line, GL::ShaderCode::Fragment::Simple);
    vbo_ = std::make_unique<VBO>(&vao_p, 3);
    vbo_->bindAttribute(shader_.programId(), GL::ShaderCode::Var::v_coordinates);
    te_ = std::make_shared<StandardTextEngine>();
    te_->initializeGL();
}

//bool Traits3D::GL::AxisObject::setHull(Traits3D::Box const& hull)
//{
//  vbo_->create(axes_, GL_STATIC_DRAW); //todo (could be dynamic)
//
//  shader_.bindAttribute(*vbo_, GL::ShaderCode::Var::v_coordinates);
//  shader_.setUniformVec4(Color(0.0f, 0.5f, 0.0f, 1.0f), GL::ShaderCode::Var::v_in_color);
//
//  return true;
//}

void Traits3D::GL::AxisObject::draw(GL::Transformation const &matrices)
{
    if (!shader_.initialized())
        return;

    //todo
    updateData();
    shader_.setUniformVec4(axis_color_, GL::ShaderCode::Var::v_in_color);
    shader_.use();
    shader_.setMatrices(matrices);
    vbo_->draw(GL_LINES);

    if (majors_.size() != major_values_.size()) // sanity
        return;

    std::vector<std::string> texts;
    std::vector<FontInfo> finfo;
    std::vector<Color> colors;
    std::vector<TextEngine::Position> positions_2d;
    glm::ivec4 vp = GL::viewPort(); // call this one sparingly

    if (show_label_)
    {
        texts.push_back(label_text_);
        finfo.push_back(label_font_info_);
        colors.push_back(label_color_);
        TripleF center = begin_ + (end_ - begin_) / 2.0f;
        TripleF ticend = center - majorticlength_ * orientation_;
        float max_label_width = 10;
        float label_height = 15;
        float rap = (max_label_width + label_gap_ + label_height) / (ticend - center).length();
        TripleF pos = center - majorticlength_ * orientation_ * (1 + rap);
        pos = GL::World2ViewPort(pos, matrices.mv(), matrices.proj(), vp);
        positions_2d.push_back(TextEngine::Position(TupleF(pos.x, pos.y), number_anchor_));
        TextEngine::adjustPosition(positions_2d[0], static_cast<float>(label_gap_ + number_gap_));
    }

    if (show_numbers_ && !majors_.empty())
    {
        size_t idx = positions_2d.size();
        size_t newsize = idx + majors_.size();
        positions_2d.resize(newsize);
        colors.resize(newsize);
        texts.resize(newsize);
        finfo.resize(newsize);

        for (size_t i = 0; i != majors_.size(); ++i)
        {
            // opposite to tic orientation
            TripleF pos = GL::World2ViewPort(majors_[i] - majorticlength_ * orientation_, matrices.mv(), matrices.proj(), vp);
            positions_2d[i + idx] = TextEngine::Position(TupleF(pos.x, pos.y), number_anchor_);
            TextEngine::adjustPosition(positions_2d[i + idx], static_cast<float>(number_gap_));
            texts[i + idx] = te_->double2text(major_values_[i]);
            finfo[i + idx] = number_font_info_;
            colors[i + idx] = number_color_;
        }
    }

    te_->setTexts(texts, finfo);
    te_->draw(positions_2d, colors);
}

bool Traits3D::GL::AxisObject::setValues(
    Traits3D::Triple const &begin,
    Traits3D::Triple const &end,
    std::vector<Triple> const &majors, std::vector<Triple> const &minors,
    std::vector<double> const &major_values)
{
    if (major_values.size() != majors.size())
        return false;

    major_values_ = major_values;
    std::vector<Triple> tmp(2);
    tmp[0] = begin;
    tmp[1] = end;
    std::vector<TripleF> ftmp = scale(excess_, tmp);
    begin_ = ftmp[0];
    end_ = ftmp[1];

    if (excess_ > 1)
    {
        majors_ = scale(majors, excess_);
        minors_ = scale(minors, excess_);
    }
    else
    {
        majors_ = convert(majors);
        minors_ = convert(minors);
    }

    modified_ = true;
    return true;
}

void Traits3D::GL::AxisObject::setTicOrientation(Triple const &val)
{
    // for safety, add the normalization step
    TripleF tmp = static_cast<TripleF>(glm::normalize(val));

    if (tmp == orientation_)
        return;

    orientation_ = tmp;
    modified_ = true;
}

void Traits3D::GL::AxisObject::setSymmetricTics(bool val)
{
    if (val == symtics_)
        return;

    symtics_ = val;
    modified_ = true;
}

bool Traits3D::GL::AxisObject::updateData()
{
    if (!modified_)
        return true;

    std::vector<TripleF> data(2 + 2 * majors_.size() + 2 * minors_.size());
    data[0] = begin_;
    data[1] = end_;

    if (show_tics_)
    {
        size_t idx = 2;

        for (auto m : majors_)
        {
            data[idx++] = (symtics_) ? m - majorticlength_ * orientation_ : m;
            data[idx++] = m + majorticlength_ * orientation_;
        }

        for (auto m : minors_)
        {
            data[idx++] = (symtics_) ? m - minorticlength_ * orientation_ : m;
            data[idx++] = m + minorticlength_ * orientation_;
        }
    }

    if (!vbo_->setData(data))
        return false;

    modified_ = false;
    return true;
}

void Traits3D::GL::AxisObject::setTicLength(double majorticlen, double minorticlen)
{
    if (majorticlen == majorticlength_ && minorticlen == minorticlength_)
        return;

    majorticlength_ = static_cast<float>(majorticlen);
    minorticlength_ = static_cast<float>(minorticlen);
    modified_ = true;
}

void Traits3D::GL::AxisObject::setNumberFont(Traits3D::FontInfo const &font_info)
{
    number_font_info_ = font_info;
}

void Traits3D::GL::AxisObject::setLabelFont(Traits3D::FontInfo const &font_info)
{
    label_font_info_ = font_info;
}

void Traits3D::GL::AxisObject::setColor(Traits3D::Color const &val)
{
    axis_color_ = val;
}

void Traits3D::GL::AxisObject::setLabelText(std::string const &val)
{
    label_text_ = val;
}

void Traits3D::GL::AxisObject::setLabelPosition(Traits3D::Triple const &pos, Traits3D::TextEngine::Anchor a)
{
    label_position_ = pos;
    label_anchor_ = a;
}

void Traits3D::GL::AxisObject::setLabelColor(Traits3D::Color const &val)
{
    label_color_ = val;
}

void Traits3D::GL::AxisObject::adjustLabel(int val)
{
    label_gap_ = val;
}

void Traits3D::GL::AxisObject::setNumberColor(Traits3D::Color const &val)
{
    number_color_ = val;
}

void Traits3D::GL::AxisObject::adjustNumbers(int val)
{
    number_gap_ = val;
}

void Traits3D::GL::AxisObject::showTics(bool val)
{
    if (val != show_tics_)
        modified_ = true;

    show_tics_ = val;
}

void Traits3D::GL::AxisObject::showLabel(bool val)
{
    if (val != show_label_)
        modified_ = true;

    show_label_ = val;
}

void Traits3D::GL::AxisObject::showNumbers(bool val)
{
    if (val != show_numbers_)
        modified_ = true;

    show_numbers_ = val;
}
