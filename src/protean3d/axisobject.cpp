#include <glm/gtc/matrix_transform.hpp>
#include "axisobject.h"


Protean3D::GL::AxisObject::AxisObject()
  : GL::Object()
{
  shader_.create(GL::ShaderCode::Vertex::Line, GL::ShaderCode::Fragment::Simple);

  vbo_ = std::make_unique<VBO>(&vao_p);
}

//bool Protean3D::GL::AxisObject::setHull(Protean3D::Box const& hull)
//{
//  vbo_->create(axes_, GL_STATIC_DRAW); //todo (could be dynamic)
//
//  shader_.bindAttribute(*vbo_, GL::ShaderCode::Vertex::v_coordinates);
//  shader_.setUniformVec4(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f), GL::ShaderCode::Vertex::v_in_color);
// 
//  return true;
//}

void Protean3D::GL::AxisObject::draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix)
{
  //todo 
  setTicLength(0.3, 0.2);
  setSymmetricTics(true);
  updateData();
  shader_.bindAttribute(*vbo_, GL::ShaderCode::Vertex::v_coordinates);
  shader_.setUniformVec4(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f), GL::ShaderCode::Vertex::v_in_color);
  shader_.use();
  shader_.setProjectionMatrix(proj_matrix);
  shader_.setModelViewMatrix(mv_matrix);
  vbo_->draw(GL_LINES);
}

void Protean3D::GL::AxisObject::setValues(Protean3D::Triple const& begin, Protean3D::Triple const& end, 
  std::vector<Triple> const& majors, std::vector<Triple> const& minors)
{
  std::vector<Triple> tmp(2);
  tmp[0] = begin;
  tmp[1] = end;

  std::vector<TripleF> ftmp = scale(excess_, tmp);

  begin_ = ftmp[0];
  end_ = ftmp[1];

  if (excess_ > 1)
  {
    majors_ = GL::scale(majors, excess_);
    minors_ = GL::scale(minors, excess_);
  }
  else
  {
    majors_ = GL::convert(majors);
    minors_ = GL::convert(minors);
  }
  modified_ = true;
}

void Protean3D::GL::AxisObject::setTicOrientation(Triple const& val)
{
  // for safety, add the normalization step
  TripleF tmp = static_cast<TripleF>(glm::normalize(val));
  if (tmp == orientation_)
    return;

  orientation_ = tmp;
  modified_ = true;
}

void Protean3D::GL::AxisObject::setSymmetricTics(bool val)
{
  if (val == symtics_)
    return;

  symtics_ = val;
  modified_ = true;
}

bool Protean3D::GL::AxisObject::updateData()
{
  if (!modified_)
    return true;

  std::vector<TripleF> data(2 + 2*majors_.size() + 2*minors_.size());

  data[0] = begin_;
  data[1] = end_;

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

  if (!vbo_->setData(data))
    return false;

  modified_ = false;
  return true;
}

void Protean3D::GL::AxisObject::setTicLength(double majorticlen, double minorticlen)
{
  if (majorticlen == majorticlength_ && minorticlen == minorticlength_)
    return;

  majorticlength_ = static_cast<float>(majorticlen);
  minorticlength_ = static_cast<float>(minorticlen);
  modified_ = true;
}