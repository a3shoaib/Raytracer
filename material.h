#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "sphere.h"

struct hit_record;

class material {
public: 
    // Scatter tells rays how to react to different material types
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

// Create classes for different types of materials
class lambertian : public material {
public:
    lambertian(const vec3& a) : albedo(a){}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
    vec3 albedo; 
};

// Reflecting material
class metal : public material {
public:
    // f keeps track of fuzziness (to fuzz some of the reflections)
    // Fuzzes by shifting rays slightly off their true path
    metal(const vec3& a, float f) : albedo(a) {if (f < 1) fuzz = f; else fuzz = 1;}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    vec3 albedo; 
    int fuzz;
};

#endif
