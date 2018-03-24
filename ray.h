//
//  ray.h
//  RayTracingInOneWeek
//
//  Created by 锄禾日当午 on 2018/3/22.
//  Copyright © 2018年 锄禾日当午. All rights reserved.
//

#ifndef ray_h
#define ray_h
#include "vec3.h"

class ray
{
public:
    vec3 A,B;
    
    ray() {}
    ray(const vec3& a,const vec3& b){A = a; B = b;}
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(float t)const{ return A + t*B; }
    
};

#endif /* ray_h */
