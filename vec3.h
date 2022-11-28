#ifndef VECH
#define VECH

// 3D Vector
#include <math.h>
#include <stdlib.h>
#include <iostream>

// Vectors will be used for 3D coordinates that will be used for raytracing, and also for colours
class Vec3D {
public:
    Vec3D() {}
    Vec3D(float e0, float e1, float e2);

    inline float x() const {return e[0];}
    inline float y() const {return e[1];}
    inline float z() const {return e[2];}
    inline float r() const {return e[0];}
    inline float g() const {return e[1];}
    inline float b() const {return e[2];}

    inline const Vec3D& operator+() const {return *this;}
    inline Vec3D operator-() const {return Vec3D(-e[0], -e[1], -e[2]);}
    inline float operator[](int i) const {return e[i];}
    inline float& operator[](int i) {return e[i];}

    inline Vec3D& operator+=(const Vec3D &v2);
    inline Vec3D& operator-=(const Vec3D &v2);
    inline Vec3D& operator*=(const Vec3D &v2);
    inline Vec3D& operator/=(const Vec3D &v2);
    inline Vec3D& operator*=(const float t);
    //inline vec3& operator/=(const float t);

    inline Vec3D& operator/=(const double t) {return *this *= 1/t;}

    inline float length() const {return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}
    inline float length_squared() const {return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
    inline void make_unit_vector();


    float e[3];
};

inline std::istream& operator>>(std::istream &is, Vec3D &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, Vec3D &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void Vec3D::make_unit_vector(){
    float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}

inline Vec3D operator+(const Vec3D &v1, const Vec3D &v2) {
    return Vec3D(v1.e[0]+v2.e[0],v1.e[1]+v2.e[1],v1.e[2]+v2.e[2]);
}
inline Vec3D operator-(const Vec3D &v1, const Vec3D &v2) {
    return Vec3D(v1.e[0]-v2.e[0],v1.e[1]-v2.e[1],v1.e[2]-v2.e[2]);
}
inline Vec3D operator*(const Vec3D &v1, const Vec3D &v2) {
    return Vec3D(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1],v1.e[2]*v2.e[2]);
}
inline Vec3D operator/(const Vec3D &v1, const Vec3D &v2) {
    return Vec3D(v1.e[0]/v2.e[0],v1.e[1]/v2.e[1],v1.e[2]/v2.e[2]);
}
inline Vec3D operator*(float t, const Vec3D &v) {
 return Vec3D(t*v.e[0],t*v.e[1],t*v.e[2]);
}
inline Vec3D operator*(const Vec3D &v,float t) {
 return Vec3D(t*v.e[0],t*v.e[1],t*v.e[2]);
}
inline Vec3D operator/(float t, const Vec3D &v) {
    return Vec3D(t/v.e[0],t/v.e[1],t/v.e[2]);
}
inline Vec3D operator/(const Vec3D &v, float t) {
    return Vec3D(v.e[0]/t,v.e[1]/t,v.e[2]/t);
}

inline float dot (const Vec3D &v1, const Vec3D &v2) {
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; 
}

inline Vec3D cross(const Vec3D &v1, const Vec3D &v2) {
    return Vec3D(v1.e[1]*v2.e[2] - v1.e[2]*v2[1], 
    -(v1.e[0]*v2.e[2] - v1.e[2]*v2[0]), 
    v1.e[0]*v2.e[1] - v1.e[1]*v2[0]);
}

inline Vec3D& Vec3D::operator+=(const Vec3D &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}
inline Vec3D& Vec3D::operator-=(const Vec3D &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}
inline Vec3D& Vec3D::operator*=(const Vec3D &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}
inline Vec3D& Vec3D::operator/=(const Vec3D &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline Vec3D& Vec3D::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline Vec3D unit_vector(Vec3D v) {
    return v/v.length();
}

#endif
