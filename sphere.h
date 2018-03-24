#ifndef SPHERE
#define SPHERE

#include "hitable.h"

class sphere :public hitable {
public:

	vec3 center;
	float radius;

	sphere() {}
	sphere(vec3 cen, float r) :center(cen), radius(r) {};
	virtual bool hit(const ray& r,float tmin, float tmax, hit_record& rec)const;
	
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4 * a*c;
	//dot((A+t*B-C),(A+t*B-C)) = R*R  ->
	//t*tdot(B,B) + 2*t*dot(A-C,A-C) + dot(C,C) - R*R = 0
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / (2.0*a);
		if (temp<t_max && temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / (2.0*a);
		if(temp<t_max && temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}

#endif // SPHERE
