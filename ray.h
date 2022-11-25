#include "vec3.h"


// Vector is a point in space. The ray will be a linear line with an origin and direction that will be kept track of

// To find a point on the line, we will use p(t) = A + t*B, where t is the given spot we want to look for,
// A is the origin, and B is the direction
class ray {
public:
    ray(){}
    ray(const vec3& a, const vec3& b) {A=a; B=b;}
    vec3 origin() const {return A;}
    vec3 direction() const {return B;}
    vec3 point_at_parameter(float t) const {return A + t*B;}

    vec3 A, B;
};