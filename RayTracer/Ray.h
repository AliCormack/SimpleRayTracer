#pragma once

#include "stdafx.h"
#include "vec3.h"

class Ray
{
public:
	Ray() {}
	Ray(const vec3& a, const vec3& b) { A = a; B = b; }
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 p(float t) const { return A + t * B; }

	vec3 A;
	vec3 B;
};