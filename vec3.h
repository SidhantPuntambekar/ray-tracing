#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

using namespace std;

class vec3 
{       
    public: 
        double e[3];
        vec3() { e[0] = 0; e[1] = 0; e[2] = 0; } // 3D vector default constructor
        vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; } // 3D vector parametrized constructor

        // X, Y, Z components of 3D vector
        double x() const
        {
            return e[0];
        }

        double y() const
        {
            return e[1];
        }

        double z() const 
        {
            return e[2];
        }

        vec3 operator-() const 
        {
            return vec3(-e[0], -e[1], -e[2]);
        }

        double operator[](int i) const // Pass by value getter 
        {
            return e[i];
        }

        double& operator[](int i) // Pass by reference getter
        {
            return e[i];
        }

        vec3& operator+=(const vec3 &v) // Pass by reference vector addition
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double t) // Pass by reference scalar multiplication
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) // Pass by reference scalar division
        {
            return *this *= 1 / t;
        }

        double euclidean_norm_squared() const 
        {
            double euclid_norm = e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
            return euclid_norm;
        }

        double length() const
        {
            return sqrt(euclidean_norm_squared());
        }
};

// Type aliases for vec3
using point3 = vec3; // 3D points
using color = vec3; // RGB color

// vec3 util functions

inline std::ostream& operator<<(ostream &out, const vec3 &v) // Outstream print
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) // Vector addition
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) // Vector subtraction
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) // Vector-vector multiplication
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) // Scalar-vector multiplication
{
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) // 
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t) // Scalar-vector division 
{
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) // Vector dot product 
{
    double dotProd = u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
    return dotProd;
}

inline vec3 cross(const vec3 &u, const vec3 &v) // Vector cross product
{
    vec3 crossProd = vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    return crossProd;
}

inline vec3 unit_vector(vec3 v) // Normalize to unit vector
{
    return v / v.length();
}

#endif