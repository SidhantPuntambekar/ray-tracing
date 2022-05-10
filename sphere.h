#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "hittable.h"
#include "vec3.h"
using namespace std;

class sphere : public hittable 
{
    public:
        point3 center;
        double radius;

        sphere() {}
        sphere(point3 cen, double r) 
        {
            center = cen;
            radius = r;
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    vec3 originShift = r.getOrigin() - center;
    auto a = r.getDirection().euclidean_norm_squared();
    auto half_b = dot(originShift, r.getDirection());
    auto c = originShift.euclidean_norm_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) 
    {
        return false;
    }

    double discriminantSquareRoot = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - discriminantSquareRoot) / a;
    if (root < t_min || t_max < root) 
    {
        root = (-half_b + discriminantSquareRoot) / a;
        if (root < t_min || t_max < root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.destination(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

#endif