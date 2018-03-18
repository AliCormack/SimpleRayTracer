#include "stdafx.h"
#include "Sphere.h"

bool Sphere::hit(const Ray& r, float tmin, float tmax, hit_record& rec) const
{
	// quadratic equation
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float disc = b * b - a*c;

	if (disc > 0)
	{
		float temp = (-b - sqrt(b*b - a * c)) / a;
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.p(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.p(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}