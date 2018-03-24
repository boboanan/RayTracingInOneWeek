//
//  main.cpp
//  RayTracingInOneWeek
//
//  Created by 锄禾日当午 on 2018/3/22.
//  Copyright © 2018年 锄禾日当午. All rights reserved.
//

#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "stdlib.h"

float rand_fun() {
	return rand() % 10000 / 10000.0;
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0*vec3(rand_fun(), rand_fun(), rand_fun())-vec3(1,1,1);
	} while (dot(p, p) >= 1.0);
	return p;
}

vec3 color(const ray& r,hitable *world) {
	hit_record rec;
	if (world->hit(r,0.0,FLT_MAX,rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color( ray(rec.p, target-rec.p), world);//diffuse Materials
		//spheres only absorb half the energy on each bounce
		//return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);//trick 0.0<t<1.0
	    									//blended_value = (1-t)start_value + t*end_value
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}



int main(int argc, const char * argv[]) {
    int nx = 200;
    int ny = 100;
	int ns = 100;
    std::cout << "p3\n" <<nx<<" "<<ny<<"\n255\n";
    
	hitable *list[2];
	list[0] = new sphere(vec3(0,0,-1),0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
    
    FILE *fp = fopen ("image.ppm","w");
    fprintf (fp, "P3\n%d %d\n255\n", nx, ny);

    for(int j = ny-1;j >= 0; j--){
        for(int i = 0; i < nx; i++){

			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				
				float u = float(i + rand_fun()) / float(nx);//antialiasing 
														   // a blend of some foreground and some background   0 <= ran < 1
				float v = float(j + rand_fun()) / float(ny);//rand() % 10000 / 10000.0; == drand48()
				ray r = cam.get_ray(u, v);
				col += color(r, world);
			}
          
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
		/*	The reason for this is that almost all image viewers assume that the
				image is “gamma corrected”, meaning the 0 to 1 values have some transform before being
				stored as a byte.There are many good reasons for that, but for our purposes we just need
				to be aware of it.To a first approximation, we can use “gamma 2” which means raising the
				color to the power 1 / gamma, or in our simple case ½*/
            int endColor[3];
            endColor[0] = int(255.99*col[0]);
            endColor[1] = int(255.99*col[1]);
            endColor[2] = int(255.99*col[2]);
            fprintf(fp, "%d %d %d ", endColor[0], endColor[1], endColor[2]);
        }
    }
    
    fclose (fp);
    return 0;
}
