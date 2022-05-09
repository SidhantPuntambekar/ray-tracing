#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>
#include <cmath>

using namespace std;

void writeColor(ostream &out, color pixelColor)
{
    // Write translated [0, 255] value of each color component
    out << static_cast<int>(255.999 * pixelColor.x()) << ' ' << static_cast<int>(255.999 * pixelColor.y()) << ' ' << static_cast<int>(255.999 * pixelColor.z()) << '\n';
}

#endif