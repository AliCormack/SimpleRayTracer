// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "Sphere.h"
#include "HitableList.h"

using namespace std;

static int screenWidth = 600;
static int screenHeight = 400;

static int scale = 100;

static int worldSpaceWidth = screenWidth / scale;
static int worldSpaceHeight = screenHeight / scale;

static vec3 lower_left_corner(-worldSpaceWidth/2, -worldSpaceHeight/2, -1);
static vec3 horizontal(worldSpaceWidth, 0, 0);
static vec3 vertical(0, worldSpaceHeight, 0);
static vec3 origin(0, 0, 0);

static vec3 sphereCenter(1, 0, -1);

vec3 color(const Ray& r, Hitable *world)
{
	hit_record rec;

	if (world->hit(r, 0.0, 999999999, rec))
	{
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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

	cout << "P3\n" << screenWidth << " " << screenHeight << "\n255\n";

	Hitable *list[2];
	list[0] = new Sphere(vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(vec3(0, -100.5, -1), 100);

	HitableList *world = new HitableList(list, 2);

	for (int j = screenHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < screenWidth; i++)
		{
			float u = float(i) / float(screenWidth);
			float v = float(j) / float(screenHeight);

			Ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 p = r.p(2.0);
			vec3 col = color(r, world);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}