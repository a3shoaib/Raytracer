#ifndef HITTABLEH
#define HITTABLEH

#include "ray.h"

class material;

// Keeping track if sphere has been hit or not
struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;

};

class hittable {
public: 
    virtual bool hit (const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
