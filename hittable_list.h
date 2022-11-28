#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "hittable.h"

// Keeps track to list objects
class HittableList: public Hittable{
public: 
    HittableList(){};
    HittableList(Hittable **l, int n) {list = l; list_size = n;}
    virtual bool hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const;

    Hittable **list; int list_size;
};



#endif
