#pragma once

#include "traits3d/helper.h"

namespace traits3d
{
template <typename T>
class Matrix
{
public:
    Matrix() = default;
    explicit Matrix(size_t xsize, size_t ysize)
        : xsize_(xsize), ysize_(ysize)
    {
        if (0 != xsize && 0 != ysize)
        {
            data_p.resize(xsize * ysize);
            return;
        }

        if (0 == xsize)
            ysize_ = 0;
        else if (0 == ysize)
            xsize_ = 0;
    }

    virtual ~Matrix() = default;

    T &operator()(size_t x, size_t y)
    {
        assert(y * xsize_ + x <= data_p.size());
        return data_p[y * xsize_ + x];
    }

    T const &operator()(size_t x, size_t y) const
    {
        assert(y * xsize_ + x <= data_p.size());
        return data_p[y * xsize_ + x];
    }

    //! Invalidates all iterators
    void resize(size_t xsize, size_t ysize)
    {
        if (0 == xsize * ysize)
        {
            data_p.clear();
            xsize_ = ysize_ = 0;
        }
        else
        {
            data_p.resize(xsize * ysize);
            xsize_ = xsize;
            ysize_ = ysize;
        }
    }

    size_t xSize() const
    {
        return xsize_;
    }
    size_t ySize() const
    {
        return ysize_;
    }

    std::vector<T> const &linearBuffer() const
    {
        return data_p;
    }

    virtual bool setData(std::vector<T> const &val, size_t xsize, size_t ysize)
    {
        if (0 == xsize * ysize || val.size() != xsize * ysize)
            return false;

        data_p = val;
        xsize_ = xsize;
        ysize_ = ysize;
        return true;
    }

    // row vectors
    virtual bool setData(std::vector<std::vector<T>> const &val)
    {
        if (val.empty() || val[0].empty())
            return false;

        ysize_ = val.size();
        xsize_ = val[0].size();
        data_p.resize(xsize_ * ysize_);
        auto curr = data_p.begin();

        for (auto const &sv : val)
        {
            if (sv.size() != xsize_)
            {
                data_p.clear();
                xsize_ = ysize_ = 0;
                return false;
            }

            curr = std::copy(sv.begin(), sv.end(), curr);
        }

        return true;
    }

protected:
    std::vector<T> data_p;

private:
    size_t xsize_ = 0;
    size_t ysize_ = 0;
};

// Matrix with data types allowing a hull
template <typename T>
class MatrixH : public Matrix <T>
{
    // cf http://stackoverflow.com/questions/5286922/g-template-parameter-error
    // about using the this pointer in classes derived from template base classes
public:
    Box const &hull() const
    {
        return hull_;
    }

    bool setData(std::vector<T> const &val, size_t xsize, size_t ysize) override
    {
        if (!Matrix<T>::setData(val, xsize, ysize))
            return false;

        hull_ = calculateBox(this->data_p);
        return true;
    }

    bool setData(std::vector<std::vector<T>> const &val) override
    {
        if (!Matrix<T>::setData(val))
        {
            hull_ = Box();
            return false;
        }

        hull_ = calculateBox(this->data_p);
        return true;
    }

    template <typename S>
    MatrixH<S> convert() const
    {
        MatrixH<S> ret;
        ret.setData(traits3d::convert(this->data_p), this->xSize(), this->ySize());
        return ret;
    }

private:
    Box hull_;
};

using MatrixF = MatrixH <TripleF> ;
using MatrixD = MatrixH <Triple> ;
} //ns
