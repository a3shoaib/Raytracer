#include "ray.h"

Ray::Ray(const Vec3D& a, const Vec3D& b) {A=a; B=b;}
Vec3D Ray::origin() const {return A;}
Vec3D Ray::direction() const {return B;}
Vec3D Ray::point_at_parameter(float t) const {return A + t*B;}
