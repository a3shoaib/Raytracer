#ifndef RAYH
#define RAYH

#include "vec3.h"

// Vector is a point in space. The ray will be a linear line with an origin and direction that will be kept track of

// To find a point on the line, we will use p(t) = A + t*B, where t is the given spot we want to look for,
// A is the origin, and B is the direction
class Ray {
public:
    Ray(){}
    Ray(const Vec3D& a, const Vec3D& b);
    Vec3D origin() const;
    Vec3D direction() const;
    Vec3D point_at_parameter(float t) const;

    Vec3D A, B;
};

#endif
