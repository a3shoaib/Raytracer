#include <iostream>

#include "sdl2temp.h"
    
int main () {
    int width = 800;
    int height = 400;
    // Head of the file that we are printing out to 
    std::cout <<"P3\n" << width << " " << height << "\n255\n";
    sdltemplate::sdl("Ray Tracer", width, height);

    // Looping through the image/pixels and looking where to draw
    for (int y = height-1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            float r = float (x) / float (width);
            float g = float (y) / float (height);
            float b = 0.2;
            int ir = int (255.88*r);
            int ig = int (255.99*g);
            int ib = int (255.99*b);
            std::cout << ir << " " << ig << " " << ib << "\n";
            sdltemplate::setDrawColor
        }
    }
    while (sdltemplate::running){
        sdltemplate::loop();
    }
}