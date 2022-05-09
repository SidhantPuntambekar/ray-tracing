#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// P(t) = A + tb, A is the ray origin and b is the ray direction. Ray parameter t is a real number / scalar
class ray 
{
    public:
        point3 origin; // 3D point representing origin of ray
        vec3 direction; // vector with direction

        ray() {}
        ray(const point3& orig, const vec3& dir)
        {
            origin = orig;
            direction = dir;
        }

        point3 getOrigin() const // Getter for origin
        {
            return origin;
        }

        vec3 getDirection() const // Getter for direction
        {
            return direction;
        }

        point3 destination(double t) const
        {
            return origin + t * direction;
        }
};

#endif