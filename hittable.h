#ifndef HITTABLE_H
#define HITTABLE_H

#include <iostream>
#include "ray.h"
using namespace std;

struct hit_record
{
    point3 p; // Point where hit
    vec3 normal; // Normal vector to hit point
    double t; // Scalar for ray

    bool front_face; // Determine if the ray is pointing from the inside of the sphere or outside of the sphere by determining the direction of the normal vectors

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.getDirection(), outward_normal) < 0; // dot product of the two vectors, where if their dot is positive, the ray is inside the sphere
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable
{
    public:
        virtual bool hit(const ray& r, double tMin, double tMax, hit_record& rec) const = 0;
};

#endif