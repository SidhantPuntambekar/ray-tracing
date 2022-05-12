#ifndef MATERIAL_H
#define MATERIAL_H

#include "util.h"

struct hit_record;

// Introduce different material surfaces on each sphere
class material 
{
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material // Lambertian reflection characteristic of matte materials
{
    public: 
        color albedo;
        lambertian(const color& a)
        {
            albedo = a;
        }

        virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override
        {
            auto scatterDirection = rec.normal + random_unit_vector();
            scattered = ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;
        }
};

#endif