#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "sphere.h"

struct HitRecord;

class Material {
public: 
    // Scatter tells rays how to react to different material types
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3D& attenuation, Ray& scattered) const = 0;
};

// Create classes for different types of materials
class Lambertian : public Material {
public:
    Lambertian(const Vec3D& a);
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3D& attenuation, Ray& scattered) const;
    Vec3D albedo; 
};

// Reflecting material
class Metal : public Material {
public:
    // f keeps track of fuzziness (to fuzz some of the reflections)
    // Fuzzes by shifting rays slightly off their true path
    Metal(const Vec3D& a, float f);
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3D& attenuation, Ray& scattered) const;

    Vec3D albedo; 
    int fuzz;
};

// Transparent material
class Dielectric : public Material {
public:
    // f keeps track of fuzziness (to fuzz some of the reflections)
    // Fuzzes by shifting rays slightly off their true path
    Dielectric(float ri);
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3D& attenuation, Ray& scattered) const;
    // Refracted index
    float ref_idx;
};

#endif
