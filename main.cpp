#include <iostream>

#include "sdl2template.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

// Determines colour based on direction of the ray
// If ray does not pass through circle then continue drawing the background, if hit sphere, add shading
 vec3 color (const ray& r, hittable *world, int depth) {
    hit_record rec;
    if (world->hit(r,0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            // Draw world (circles/spheres), ray will bounce around until it reaches a dead end
            return attenuation * color(scattered, world, depth + 1);
        } else{ 
            return vec3(0,0,0);
        }

    } else {
        // Sky background
        vec3 unit_dir  = unit_vector(r.direction());
        float t =  0.5*(unit_dir.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5,0.7,1.0);
    }
}
    
int main () {
    //sphere = vec3(0,0,-1);
    //sphere_radius = 0.5;
    int width = 800;
    int height = 400;
    int ns = 100;
    // Head of the file that we are printing out to 
    std::cout <<"P3\n" << width << " " << height << "\n255\n";
    sdltemplate::sdl("Ray Tracer", width, height);
    sdltemplate::loop();    

    // Creating world (4 spheres)
    hittable *list[4];
    // First two circles will have a matte finish
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    // Second two circles will have a metal finish and the reflections will fuzz
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.2));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.7));
    hittable *world = new hittable_list (list,4);

    // Defining camera
    camera cam;

    // Looping through the image/pixels and looking where to draw
    for (int y = height-1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            // Define initial colour
            vec3 col(0,0,0);
            for (int s = 0; s < ns; s++) {
                // u and v are horzontal and vertical distances on the point drawn on the panel
                float u = float(x+drand48()) / float (width);
                float v = float(y+drand48()) / float (height);

                ray r = cam.get_ray(u,v); 
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);

            }
            col /= float(ns);

            // To make it less dark
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));

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
