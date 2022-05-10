#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <limits>
#include <memory>
#include "ray.h"
#include "vec3.h"
#include <cstdlib>

using namespace std;
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385; // RIP C++ doesn't have a library for pi so need to hardcode unfortunately

// Utility Functions
inline double degrees_to_radians(double degrees) 
{
    double radians = degrees * pi / 180.0;
    return radians;
}

inline double radians_to_degrees(double radians) 
{
    double degrees = radians * 180.0 / pi;
    return degrees;
}

#endif