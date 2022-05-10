#include "util.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"

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
color ray_color(const ray& r)
{
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r); // Call hit_sphere to generate a sphere at (0, 0, -1) center with radius 0.5 and ray trace r
    if (t > 0.0) // If  
    {
        vec3 N = unit_vector(r.destination(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.getDirection());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); //blendedValue = (1 - t) * startValue + t * endValue
}

// Simple portable pixmap format (PPM) Image Output
int main()
{
    // Create a default 16:9 aspect ratio pixel image
    const auto aspect_ratio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspect_ratio);

    // Simulated camera for Ray Tracer 
    auto viewportHeight = 2.0;
    auto viewportWidth = aspect_ratio * viewportHeight;
    auto focalLength = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    auto lowerLeft = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n"; // PPM output

    for (int i = imageHeight - 1; i >= 0; i--) // For each row in the image
    {
        cerr << "\rDEBUG: Scanlines remaining: " << i << ' ' << flush; // Stdout debug error
        for (int j = 0; j < imageWidth; j++) // For each column in the image
        {
            auto u = double(j) / (imageWidth - 1);
            auto v = double(i) / (imageHeight - 1);
            ray r = ray(origin, (lowerLeft + u * horizontal + (v * vertical - origin)));
            color pixelColor = ray_color(r);
            writeColor(cout, pixelColor);
        }
    }

    cerr << "\nDEBUG: Done\n"; // Debug section done
}
