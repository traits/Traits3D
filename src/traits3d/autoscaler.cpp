#include "traits3d/helper.h"
#include "traits3d/autoscaler.h"

namespace
{
double floorExt(int &exponent, double x, std::vector<double> const &sortedmantissi)
{
    if (x == 0.0)
    {
        exponent = 0;
        return 0.0;
    }

    double sign = (x > 0) ? 1.0 : -1.0;
    double lx = log10(fabs(x));
    exponent = (int)floor(lx);
    double fr = pow(10.0, lx - exponent); // always >=1 because lx always >= exponent

    if (fr >= 10.0)
    {
        fr = 1.0;
        ++exponent;
    }
    else // >= 1
    {
        for (int i = (int)sortedmantissi.size() - 1; i >= 0; --i)
        {
            if (fr >= sortedmantissi[i])
            {
                fr = sortedmantissi[i];
                break;
            }
        }
    }

    return sign * fr;
}

/*
  \brief Find the largest value out of [+/-]{1,2,5}*10^n
  smaller than or equal to x
  \return the values mantissa
  \param n returns the values exponent
  \param x input value
*/
double floor125(int &n, double x)
{
    std::vector<double> m(2);
    m[0] = 1;
    m[1] = 2;
    m[2] = 5;
    return floorExt(n, x, m);
}
} // anon ns

namespace traits3d
{

//! Initializes with an {1,2,5} sequence of mantissas
LinearAutoScaler::LinearAutoScaler()
{
    init(0, 1, 1);
    mantissi_ = std::vector<double>(3);
    mantissi_[0] = 1;
    mantissi_[1] = 2;
    mantissi_[2] = 5;
}
//! Initialize with interval [0,1] and one requested interval
/*!
\param mantisse An increasing ordered vector of values representing
mantisse values between 1 and 9.
*/
LinearAutoScaler::LinearAutoScaler(std::vector<double> &mantisse)
{
    init(0, 1, 1);

    if (mantisse.empty())
    {
        mantissi_ = std::vector<double>(3);
        mantissi_[0] = 1;
        mantissi_[1] = 2;
        mantissi_[2] = 5;
        return;
    }

    mantissi_ = mantisse;
}


//! Initialize with interval [start,stop] and number of requested intervals
/**
  Switchs start and stop, if stop < start and sets intervals = 1 if ivals < 1
  */
void LinearAutoScaler::init(double start, double stop, size_t ivals)
{
    start_ = start;
    stop_ = stop;
    intervals_ = ivals ? ivals : 1;

    if (start_ > stop_)
        std::swap(start_, stop_);
}

/*!
\return Anchor value

\verbatim
|_______|____________ _ _ _ _  _____|_____________|________________

0     m*10^n                      start         anchor := c*m*10^n

c 'minimal' (anchor-start < m*10^n)
\endverbatim
*/
double LinearAutoScaler::anchorvalue(double start, double m, int n)
{
    double stepval = m * pow(10.0, n);
    return  stepval * ceil(start / stepval);
}

/*!
\return New number of intervals (:= l_intervals + r_intervals)
\param l_intervals  Number of intervals left from anchor
\param r_intervals  Number of intervals right from anchor

\verbatim
-l_intervals * i    -2 * i    -i                 +r_intervals * i
|
|______|_______ _ _ _ ____|____|___ _ _ _ _ _ _ _|_______|_______|_ _ _ _ _ _ _____|__|_____
|                  |                                      |                    |
0   i := m*10^n         start                                  anchor               stop

c 'minimal' (anchor-start < m*10^n)
\endverbatim
*/
int LinearAutoScaler::segments(int &l_intervals, int &r_intervals, double start, double stop, double anchor, double m, int n)
{
    double val = m * pow(10.0, n);
    double delta = (stop - anchor) / val;
    r_intervals = (int)floor(delta); // right side intervals
    delta = (anchor - start) / val;
    l_intervals = (int)floor(delta); // left side intervals
    return r_intervals + l_intervals;
}

/*!
  \brief Does the actual scaling
  \return Number of intervals after rescaling. This will in the most cases differ
  from the requested interval number!  Always >0.
  \param a Start value after scaling (always >= start)
  \param b Stop value after scaling  (always <= stop)
  \param start Start value
  \param stop Stop value
  \param ivals Requested intervals
  \return Number of intervals after autoscaling

  If the given interval has zero length the function returns the current
  interval number and a and b remain unchanged.
  */
size_t LinearAutoScaler::execute(double &a, double &b, double start, double stop, size_t ivals)
{
    init(start, stop, ivals);
    double delta = stop_ - start_; // always >= 0

    if (isZero(delta))
        return intervals_;

    double c;
    int n;
    c = floorExt(n, delta, mantissi_);
    int l_ival, r_ival;
    double anchor = anchorvalue(start_, c, n);
    int ival = segments(l_ival, r_ival, start_, stop_, anchor, c, n);

    if (ival >= static_cast<int>(intervals_))
    {
        a = anchor - l_ival * c * pow(10.0, n);
        b = anchor + r_ival * c * pow(10.0, n);
        intervals_ = ival;
        return intervals_;
    }

    int prev_ival, prev_l_ival, prev_r_ival;
    double prev_anchor;
    double prev_c;
    int prev_n;

    while (1)
    {
        prev_c = c;
        prev_n = n;
        prev_anchor = anchor;
        prev_ival = ival;
        prev_l_ival = l_ival;
        prev_r_ival = r_ival;

        if (int(c) == 1)
        {
            c = mantissi_.back();
            --n;
        }
        else
        {
            for (size_t i = mantissi_.size() - 1; i > 0; --i)
            {
                if (int(c) == mantissi_[i])
                {
                    c = mantissi_[i - 1];
                    break;
                }
            }
        }

        anchor = anchorvalue(start_, c, n);
        ival = segments(l_ival, r_ival, start_, stop_, anchor, c, n);
        int prev_diff = static_cast<int>(intervals_) - prev_ival;
        int actual_diff = ival - static_cast<int>(intervals_);

        if (prev_diff >= 0 && actual_diff >= 0)
        {
            if (prev_diff < actual_diff)
            {
                c = prev_c;
                n = prev_n;
                anchor = prev_anchor;
                ival = prev_ival;
                l_ival = prev_l_ival;
                r_ival = prev_r_ival;
            }

            a = anchor - l_ival * c * pow(10.0, n);
            b = anchor + r_ival * c * pow(10.0, n);
            intervals_ = static_cast<size_t>(ival);
            break;
        }
    }

    return intervals_;
}

} // ns