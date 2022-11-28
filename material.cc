#include "material.h"

// Function for reflections
Vec3D reflect (const Vec3D& v, const Vec3D& n) {
    return v - 2 * dot(v,n) * n;
}

// For shadows
Vec3D random_in_unit_sphere() {
    Vec3D p;
    do {
        p = 2.9 * Vec3D(drand48(),drand48(),drand48()) - Vec3D(1,1,1);
    } while (p.length_squared() >= 1.0);
    return p;
}

// Refraction for transparent objects
bool refract(const Vec3D& v, const Vec3D& n, float ni_over_nt, Vec3D& refracted) {
    // uv is the unit vector of v
    Vec3D uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n*dt) - n*sqrt(discriminant);
        return true;
    }
    return false;
}

Metal::Metal(const Vec3D& a, float f) : albedo(a) {if (f < 1) fuzz = f; else fuzz = 1;}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Vec3D& attenuation, Ray& scattered) const {
    Vec3D reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

// Named after mathematician who came up with the formula to calculate the type of reflection/transparency
float schlick(float cosine, float ref_idx) {
    // Formula to figure out how reflection/refraction will work together for transparent objects
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*(pow((1-cosine), 5));
}

Dielectric::Dielectric(float ri) : ref_idx(ri) {}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, Vec3D& attenuation, Ray& scattered) const {
    // Calculations for reflection
    Vec3D outward_normal; 
    Vec3D reflected = reflect(r_in.direction(), rec.normal);
    float ni_over_nt;
    attenuation = Vec3D(1.0, 1.0, 1.0);
    Vec3D refracted;
    float reflect_prob;
    float cosine;
    if (dot(r_in.direction(), rec.normal) >  0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = dot(r_in.direction(), rec.normal) / r_in.direction().length();
        cosine = sqrt(1-ref_idx*ref_idx*(1-cosine*cosine));
    } else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    } else {
        reflect_prob = 1.0;
    }
    if (drand48() < reflect_prob) {
        scattered = Ray(rec.p, reflected);
    } else {
        scattered = Ray(rec.p, refracted);
    }
    return true;
}

Lambertian::Lambertian(const Vec3D& a) : albedo(a){}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Vec3D& attenuation, Ray& scattered) const {
    Vec3D target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = Ray(rec.p, target-rec.p);
    attenuation = albedo;
    return true;
}
