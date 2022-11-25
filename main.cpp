#include <iostream>

#include "sdl2template.h"
#include "ray.h"

// Check if ray hits the sphere inside point drawn in panel
bool hit_sphere(const vec3 center, float radius, const ray& r) {
    vec3 oc = r.origin()-center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
} 

vec3 sphere;
float sphere_radius;
// Determines colour based on direction of the ray
// If ray does not pass through circle then continue drawing the background, if hit sphere, return red
 vec3 color (const ray& r) {
    if (hit_sphere(sphere, sphere_radius, r)) {return vec3(1,0,0);}
    vec3 unit_dir  = unit_vector(r.direction());
    float t =  0.5*(unit_dir.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5,0.7,1.0);
}
    
int main () {
    sphere = vec3(0,0,-1);
    sphere_radius = 0.5;
    int width = 800;
    int height = 400;
    // Head of the file that we are printing out to 
    std::cout <<"P3\n" << width << " " << height << "\n255\n";
    sdltemplate::sdl("Ray Tracer", width, height);
    sdltemplate::loop();

    // Defining coordinates of the panel on which the ray will be displayed on
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin (0.0, 0.0, 0.0);

    // Looping through the image/pixels and looking where to draw
    for (int y = height-1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            // u and v are horzontal and vertical distances on the point drawn on the panel
            float u = float(x) / float (width);
            float v = float(y) / float (height);

            // Creating a ray
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            
            // Using vector class to draw
            vec3 col = color(r);

            int ir = int (255.88*col[0]);
            int ig = int (255.99*col[1]);
            int ib = int (255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
            sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
            sdltemplate::drawPoint(x,height-y);
        }
    }
    while (sdltemplate::running){
        sdltemplate::loop();
    }
}