// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"

using namespace std;

float GetRand01()
{
	return rand() / (float)RAND_MAX;
}

vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0 * vec3(GetRand01(), GetRand01(), GetRand01()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);

	return p;
}

vec3 color(const Ray& r, Hitable *world)
{
	hit_record rec;

	if (world->hit(r, 0.001, 10000000000000000000, rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color(Ray(rec.p, target - rec.p), world);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0); // Scale to 0 < t < 1
		return (1.0 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1.0); // blue0
	}	
}

int main()
{
	ofstream out("out.ppm");
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());

	cout << "P3\n" << Camera::screenWidth << " " << Camera::screenHeight << "\n255\n";

	Hitable *list[2];
	list[0] = new Sphere(vec3(0, 0, -1), 0.8);
	list[1] = new Sphere(vec3(0, -100.5, -1), 100);

	HitableList *world = new HitableList(list, 2);
	int ns = 30; // TODO move number samples
	Camera cam;

	for (int j = Camera::screenHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < Camera::screenWidth; i++)
		{
			vec3 col(0, 0, 0);		

			for (int s = 0; s < ns; s++)
			{
				float u = float(i + GetRand01()) / float(Camera::screenWidth);
				float v = float(j + GetRand01()) / float(Camera::screenHeight);
				Ray r = cam.GetRay(u, v);
				//vec3 p = r.p(2.0); // TODO whats this doing?
				col += color(r, world);
			}

			col /= float(ns);

			// Gamma correction (gamma 2 approx)
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}