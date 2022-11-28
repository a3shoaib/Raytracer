#ifndef SPHEREH
#define SPHEREH
#include "hittable.h"

class Material;

class Sphere: public Hittable {
public: 
    Sphere();
    Sphere(Vec3D cen, float r, Material *m) : center(cen), radius(r), material_ptr(m) {};
    
    virtual bool hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const;
    
    // In order to figure out where the circle is and how big it is
    Vec3D center; float radius; Material *material_ptr;
};



#endif
