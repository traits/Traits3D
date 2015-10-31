#pragma once

#include <cmath>
#include "traits3d/parametricsurface.h"
#include "traits3d/function.h"

using namespace traits3d;

class Rosenbrock : public Function
{
public:

    Rosenbrock()
    {
    }

    double operator()(double x, double y)
    {
        return 0.7 * log10((1 - x) * (1 - x) + 10 * (y - x * x) * (y - x * x));
    }
    //  QString name() const {return "Almost {\\it Rosenbrock}\\,:\\quad$\\frac{\\ln((1-x)^2 + 100(y-x^2)^2)}{8}$";}
};

class Hat : public Function
{
public:

    Hat()
    {
        //setMinZ(0.3);
        setDomain(0, 10, 0, 10);
    }

    double operator()(double x, double y)
    {
        return 1.0 / (x * x + y * y + 0.5);
        //return x*x*y/(x*x*x*x+y*y);
    }
};


class Ripple : public Function
{
public:

    Ripple()
    {
        double l = 12;
        setDomain(-l, l, -l, l);
    }

    double operator()(double x, double y)
    {
        return (cos(sqrt(x * x + y * y) + cos(sqrt(((x + .913 * 2 * PI) * (x + .913 * 2 * PI)) + y * y))
                    + cos(sqrt(((x - .913 * 2 * PI) * (x - .913 * 2 * PI)) + (y * y)))) * 4);
    }
};

class Saddle : public Function
{
public:

    Saddle()
    {
        //  setMaxZ(0.8);
    }

    double operator()(double x, double y)
    {
        return x * x - y * y;
    }
    //  QString name() const {return "$x^2-y^2$";}
};

class Mex : public Function
{
public:

    Mex()
    {
        //  setMaxZ(0.8);
    }

    double operator()(double x, double y)
    {
        double n = sqrt(x * x + y * y);

        if (n < std::numeric_limits<double>::min())
            return 20;

        return 20 * sin(sqrt(x * x + y * y)) / n;
    }
    //  QString name() const {return "$\\frac{20\\sin\\sqrt{x^2+y^2}}{\\sqrt{x^2+y^2}}$";}
};

class Torus : public ParametricSurface
{
public:

    Torus()
    {
        setDomainResolution(41, 31);
        setDomain(-2 * PI, 0, -2 * PI, 0);
        setPeriodic(true, true);
    }


    Triple operator()(double u, double v)
    {
        double x, y, z;
        double c = 1.9;
        x = (c + cos(v)) * cos(u);
        y = (c + cos(v)) * sin(u);
        z = sin(v) + cos(v);
        return Triple(x, y, z);
    }
};

class Seashell : public ParametricSurface
{
public:

    Seashell()
    {
        setDomainResolution(41, 131);
        setDomain(0, 2 * PI, 0, 2 * PI);
        setPeriodic(true, true);
    }


    Triple operator()(double u, double v)
    {
        double x, y, z;
        double a = 1;
        double b = 6;
        double c = 0.5;
        int n = 3;
        double f = v / (2 * PI);
        x = a * (1 - f) * cos(n * v) * (1 + cos(u)) + c * cos(n * v) ;
        y = a * (1 - f) * sin(n * v) * (1 + cos(u)) + c * sin(n * v) ;
        z = b * f + a * (1 - f) * sin(u);
        return Triple(x, y, z);
    }
};

class Boy : public ParametricSurface
{
public:

    Boy()
    {
        setDomainResolution(141, 131);
        setDomain(0, PI, 0, PI);
        setPeriodic(true, true);
    }


    Triple operator()(double u, double v)
    {
        double x, y, z;
        double a = 2 / 3.;
        double b = sqrt(2.);
        x = a * (cos(u) * cos(2 * v) + b * sin(u) * cos(v)) * cos(u) / (b - sin(2 * u) * sin(3 * v));
        y = a * (cos(u) * sin(2 * v) - b * sin(u) * sin(v)) * cos(u) / (b - sin(2 * u) * sin(3 * v));
        z = b * cos(u) * cos(u) / (b - sin(2 * u) * sin(2 * v));
        return Triple(x, y, z);
    }
};

class Dini : public ParametricSurface
{
public:

    Dini()
    {
        setDomainResolution(141, 35);
        setDomain(0, 5 * PI, 0.001, 2);
        setPeriodic(true, true);
    }


    Triple operator()(double u, double v)
    {
        double x, y, z;
        double a = 5;
        double b = 1;
        x = a * cos(u) * sin(v);
        y = a * sin(u) * sin(v);
        z = a * (cos(v) + log(tan(v / 2))) + b * u;
        return Triple(x, y, z);
    }
};
