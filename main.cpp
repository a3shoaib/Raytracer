#include <iostream>

#include "sdl2template.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include <thread>
#include <vector>
#include <mutex>

std::mutex rendering_mutex;

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

// Creating the scene
hittable *random_scene() {
    int n = 500;
    hittable **list = new hittable *[n+1];
    // World on which all spheres are sitting on
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    // 2D for loop to create a grid of spheres
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            // Setting random materials to other spheres
            float choose_mat = drand48();
            vec3 center (a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if (choose_mat < 0.8) {
                list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
            } else if (choose_mat < 0.95) {
                list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())), 0.5 * drand48()));
            } else {
                // Otherwise make it dielect
                list[i++] = new sphere (center, 0.2, new dielectric (1.5));
            }
        }
    }
    // Defining a few specific spheres
    list[i++] = new sphere(vec3(0, 1, 0), 1, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1, new metal(vec3(0.7, 0.6, 0.5), 0));
    return new hittable_list(list, i);
}
    
int main () {
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 400;
    constexpr int NS = 100;

    // Head of the file that we are printing out to 
    sdltemplate::sdl("Ray Tracer", WIDTH, HEIGHT);
    sdltemplate::loop();
    
    // Creating the scene in main
    hittable *world = random_scene(); 
    const vec3 lookfrom(13, 2, 3);
    const vec3 lookat(0, 0, 0);
    constexpr float dist_to_focus = 10.0;
    constexpr float aperture = 0.1;

    // Defining camera and zooming in, and adding defocus blur/depth in field
    camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(WIDTH) / float(HEIGHT), aperture, dist_to_focus);
    // Looping through the image/pixels and looking where to draw

    auto render_row = [&](int y) {
        for (int x = 0; x < WIDTH; x++) {
            // Define initial colour
            vec3 col(0,0,0);
            for (int s = 0; s < NS; s++) {
                // u and v are horzontal and vertical distances on the point drawn on the panel
                float u = float(x+drand48()) / float (WIDTH);
                float v = float(y+drand48()) / float (HEIGHT);

                ray r = cam.get_ray(u,v); 
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);

            }
            col /= float(NS);

            // To make it less dark
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));

            int ir = int (255.88*col[0]);
            int ig = int (255.99*col[1]);
            int ib = int (255.99*col[2]);
            {
                std::lock_guard<std::mutex> guard(rendering_mutex);
                sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
                sdltemplate::drawPoint(x,HEIGHT-y);
            }
        }
    };

    std::vector<std::thread> threads;
    for (int row = HEIGHT-1; row >= 0; row--) {
        threads.emplace_back(render_row, row);
    }
    for(std::thread& thread: threads) {
        thread.join();
        {
            std::lock_guard<std::mutex> guard(rendering_mutex);
            sdltemplate::loop();
        }
    }
    while (sdltemplate::running){
        sdltemplate::loop();
    }
}
