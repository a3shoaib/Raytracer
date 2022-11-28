#include "camera.h"

// Implements depth in field/defocus blur
Vec3D random_in_unit_disk() {
    Vec3D p;
    do{
        p = 2.0 * Vec3D(drand48(), drand48(), 0.0) - Vec3D(1, 1, 0);
    } while (dot(p,p) >= 1.0);
    return p;
}

Camera::Camera(const Vec3D& lookfrom, const Vec3D& lookat, Vec3D vup, float vfov, float aspect, float aperture, float focus_dist){
    lens_radius = aperture / 2;
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta/2);

    // Aspect is aspect ratio, up is to let camera know which direction is up
    float half_width = aspect * half_height;
    origin = lookfrom; 
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup,w));
    v = cross(w, u);
    // 1.0 since that will always be the distance between the scene and the camera (-1 on z axis)
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    horizontal = 2 * half_width * u * focus_dist;
    vertical = 2 * half_height * v * focus_dist;
}

Ray Camera::get_ray(float s, float t) {
    Vec3D rd = lens_radius * random_in_unit_disk();
    Vec3D offset = u * rd.x() + v*rd.y();
    return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
}
