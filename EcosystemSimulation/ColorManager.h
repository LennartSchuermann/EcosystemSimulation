#pragma once

#include <math.h>
#include "MathLib.h"

using rgb = struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
};

using hsv = struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
};

hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);
rgb mix2Colors(rgb firstColor, rgb secondColor);
rgb createRandomRgb();