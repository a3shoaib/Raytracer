#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

// Doing anti-aliasing through a camera class on the rigid spheres to make edges smooth
class Camera {
public: 
    Camera(const Vec3D& lookfrom, const Vec3D& lookat, Vec3D vup, float vfov, float aspect, float aperture, float focus_dist);

    Ray get_ray(float s, float t);

    Vec3D lower_left_corner, horizontal, vertical, origin;
    float lens_radius;
    Vec3D u, v, w;
};

#endif
