#ifndef HITTABLEH
#define HITTABLEH

#include "ray.h"

class Material;

// HitRecord keeps track if sphere has been hit
struct HitRecord {
    float t;
    Vec3D p;
    Vec3D normal;
    Material *material_ptr;
};

class Hittable {
public: 
    virtual bool hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

#endif
