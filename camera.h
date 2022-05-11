// Antialiasing

#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"
#include <iostream>
using namespace std;

class camera
{
    private: 
        point3 origin;
        point3 lowerLeft;
        vec3 horizontal;
        vec3 vertical;

    public:
        camera() 
        {
            auto aspect_ratio = 16.0 / 9.0;
            auto viewportHeight = 2.0;
            auto viewportWidth = aspect_ratio * viewportHeight;
            auto focalLength = 1.0;

            origin = point3(0, 0, 0);
            horizontal = vec3(viewportWidth, 0.0, 0.0);
            vertical = vec3(0.0, viewportHeight, 0.0);
            lowerLeft = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);
        }

        ray getRay(double u, double v) const 
        {
            return ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
        }
};

#endif