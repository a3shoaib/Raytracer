#include "hittable_list.h"

bool HittableList::hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    // Keeping track of any of the hittables in the list that have been hit
    HitRecord temp_rec;
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
