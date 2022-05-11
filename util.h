#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include "ray.h"
#include "vec3.h"

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

inline double random_double() 
{
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) 
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) // Set x's value to a value in the range [min, max]
{
    if (x < min) 
    {
        return min;
    }
    if (x > max) 
    {
        return max;
    }
    return x;
}

#endif