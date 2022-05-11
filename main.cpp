#include "util.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>
using namespace std;

// Create a basic sphere in terms of vectors (to hide component wise math), monte carlo simulation by coloring any pixel red that hits a sphere placed on -1 at the z-axis
double hit_sphere(const point3& center, double radius, const ray& r)
{
    vec3 originShift = r.getOrigin() - center;
    auto a = r.getDirection().euclidean_norm_squared(); // Squared length of ray direction vector
    auto halfB = dot(originShift, r.getDirection());
    auto c = originShift.euclidean_norm_squared() - (radius * radius); // Squared length of origin shifted vector - radius of sphere squared
    auto discriminant = (halfB * halfB) - (a * c);
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        double shading = (-halfB - sqrt(discriminant)) / (a);
        return shading;
    }
}

// Returns the color of the background (which should be a simple gradient)
color ray_color(const ray& r, const hittable& world) 
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) 
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.getDirection());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t)* color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

// Simple portable pixmap format (PPM) Image Output
int main()
{
    // Image
    // Create a default 16:9 aspect ratio pixel image
    const double aspect_ratio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspect_ratio);
    const int samples_per_pixel = 100;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    camera cam; // Abstract camera code into a separate class and declare an instance of it in the renderer

    // Render Sphere and World
    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n"; // PPM output

    for (int i = imageHeight - 1; i >= 0; i--) // For each row in the image
    {
        cerr << "\rDEBUG: Scanlines remaining: " << i << ' ' << flush; // Stdout debug error
        for (int j = 0; j < imageWidth; j++) // For each column in the image
        {
            color pixelColor(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                auto u = double(j + random_double()) / (imageWidth - 1);
                auto v = double(i + random_double()) / (imageHeight - 1);
                ray r = cam.getRay(u, v);
                pixelColor += ray_color(r, world);
            }
            writeColor(cout, pixelColor, samples_per_pixel);
        }
    }

    cerr << "\nDEBUG: Done\n"; // Debug section done
}
