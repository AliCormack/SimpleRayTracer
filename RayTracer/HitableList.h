#pragma once

#include "stdafx.h"
#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList() {}
	HitableList(Hitable **l, int n) { list = l; list_size = n; }
	virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
	Hitable **list;
	int list_size;
};