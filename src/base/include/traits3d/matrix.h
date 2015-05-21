#pragma once

#include "traits3d/helper.h"

namespace Traits3D
{
  template <typename T>
  class Matrix
  {
  public:
    Matrix() = default;
    explicit Matrix(size_t xsize, size_t ysize)
      :xsize_(xsize), ysize_(ysize)
    {
      if (0 != xsize && 0 != ysize)
      {
        data_.resize(xsize*ysize);
        return;
      }

      if (0 == xsize)
        ysize_ = 0;
      else if (0 == ysize)
        xsize_ = 0;
    }
    
    virtual ~Matrix() = default;

    T& operator()(size_t x, size_t y) 
    { 
      assert(y*xsize_ + x <= data_.size());
      return data_[y*xsize_+x]; 
    }

    T const& operator()(size_t x, size_t y) const
    {
      assert(y*xsize_ + x <= data_.size());
      return data_[y*xsize_ + x];
    }

    //! Invalidates all iterators
    void resize(size_t xsize, size_t ysize)
    {
      if (0 == xsize*ysize)
      {
        data_.clear();
        xsize_ = ysize_ = 0;
      }
      else
      {
        data_.resize(xsize*ysize);
        xsize_ = xsize;
        ysize_ = ysize;
      }
    }

    size_t xSize() const { return xsize_; }
    size_t ySize() const { return ysize_; }
    Box const& hull() const { return hull_; }

    std::vector<T> const& linearBuffer() const { return data_; }

    bool setData(std::vector<T> const& val, size_t xsize, size_t ysize)
    {
      if (0 == xsize*ysize || val.size() != xsize*ysize)
        return false;

      data_ = val;
      xsize_ = xsize;
      ysize_ = ysize;
      hull_ = Traits3D::calculateBox(data_);

      return true;
    }
    
    // row vectors
    bool setData(std::vector<std::vector<T>> const& val)
    {
      if (val.empty() || val[0].empty())
        return false;

      ysize_ = val.size();
      xsize_ = val[0].size();

      data_.resize(xsize_*ysize_);

      auto curr = data_.begin();
      for (auto const& sv : val)
      {
        if (sv.size() != xsize_)
        {
          data_.clear();
          xsize_ = ysize_ = 0;
          hull_ = Box();
          return false;
        }
        curr = std::copy(sv.begin(), sv.end(), curr);
      }

      hull_ = Traits3D::calculateBox(data_);
      return true;
    }

    template <typename S>
    Matrix<S> convert() const
    {
      Matrix<S> ret;
      ret.setData(Traits3D::convert(data_), xsize_, ysize_);
      return ret;
    }

  private:
    size_t xsize_ = 0;
    size_t ysize_ = 0;

    std::vector<T> data_;
    Traits3D::Box hull_;
  };

  using MatrixF = Matrix < TripleF > ;
  using MatrixD = Matrix < Triple > ;
} //ns
