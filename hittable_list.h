#ifndef HITTABLELISTH
#define HITTABLELISTH

// Keeps track of something to list off these objects
#include "hittable.h" 

class hittable_list: public hittable{
public: 
    hittable_list(){};
    hittable_list(hittable **l, int n) {list = l; list_size = n;}
    virtual bool hit (const ray& r, float t_min, float t_max, hit_record& rec) const;

    hittable **list; int list_size;
};

bool hittable_list::hit (const ray& r, float t_min, float t_max, hit_record& rec) const {
    // Keeping track of any of the hittables in the list that have been hit
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    // Looping through list and keeping track of what has been hit
    for(int i = 0; i < list_size; i++) {
        if(list[i]->hit(r,t_min,closest_so_far,temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif
