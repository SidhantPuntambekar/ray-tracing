#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>
using namespace std;

// Create a basic sphere in terms of vectors (to hide component wise math), monte carlo simulation by coloring any pixel red that hits a sphere placed on -1 at the z-axis
bool hit_sphere(const point3& center, double radius, const ray& r)
{
    vec3 originShift = r.getOrigin() - center;
    auto a = dot(r.getDirection(), r.getDirection());
    auto b = 2.0 * dot(originShift, r.getDirection());
    auto c = dot(originShift, originShift) - radius * radius;
    auto discriminant = (b * b) - 4 * a * c;
    return (discriminant > 0);
}

// Returns the color of the background (which should be a simple gradient)
color ray_color(const ray& r)
{
    if (hit_sphere(point3(0,0,-1), 0.5, r))
    {
        return color(1, 0, 0);
    }
    vec3 unitDirection = unit_vector(r.getDirection());
    auto t = 0.5*(unitDirection.y() + 1);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); //blendedValue = (1 - t) * startValue + t * endValue
}

// Simple portable pixmap format (PPM) Image Output
int main()
{
    // Create a default 16:9 aspect ratio pixel image
    const auto aspect_ratio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspect_ratio);

    // Camera for Ray Tracer 
    auto viewportHeight = 2.0;
    auto viewportWidth = aspect_ratio * viewportHeight;
    auto focalLength = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    auto lowerLeft = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n"; // PP

    for (int i = imageHeight - 1; i >= 0; i--) // For each row in the image
    {
        cerr << "\rDEBUG: Scanlines remaining: " << i << ' ' << flush;
        for (int j = 0; j < imageWidth; j++) // For each column in the image
        {
            auto u = double(j) / (imageWidth - 1);
            auto v = double(i) / (imageHeight - 1);
            ray r = ray(origin, (lowerLeft + u * horizontal + (v * vertical - origin)));
            color pixelColor = ray_color(r);
            writeColor(cout, pixelColor);
        }
    }

    cerr << "\nDEBUG: Done\n";
}
