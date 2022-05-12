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

            // If the random unit vector we generate is exactly opposite the normal vector, the two will sum to zero, which will result in a zero scatter direction vector
            // Catch degenerate scatter direction
            if (scatterDirection.near_zero())
            {
                scatterDirection = rec.normal;
            }

            scattered = ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;
        }
};

class metal : public material 
{
    public:
        color albedo;
        metal(const color& a) : albedo(a) {}

        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
        {
            vec3 reflected = reflect(unit_vector(r_in.getDirection()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.getDirection(), rec.normal) > 0);
        }
};

#endif