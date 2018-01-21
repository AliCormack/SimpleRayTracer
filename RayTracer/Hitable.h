#pragma once

#include "stdafx.h"
#include "ray.h"

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
};

class Hitable
{
public:
	virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const = 0;
};