// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "vec3.h"
#include "Ray.h"

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

bool hit_sphere(const vec3& center, float radius, const Ray& r)
{
	// quadratic equation
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float disc = b * b - 4 * a*c;
	return disc > 0;
}

vec3 color(const Ray& r)
{
	if (hit_sphere(vec3(0, 0, -1), 0.5, r))
		return vec3(1, 0, 0);
	
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0); // Scale to 0 < t < 1
	return (1.0 - t) * vec3(1,1,1) + t * vec3(0.5, 0.7, 1.0); // blue0
}

void PrintSphereCenter()
{
	for (int j = screenHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < screenWidth; i++)
		{
			float u = float(i) / float(screenWidth);
			float v = float(j) / float(screenHeight);

			Ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 col = color(r);

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}

void PrintScreenspaceColor()
{
	for (int j = screenHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < screenWidth; i++)
		{
			vec3 col(float(i) / float(screenWidth), float(j) / float(screenHeight), 0.2);

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}

int main()
{
	ofstream out("out.ppm");
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());

	cout << "P3\n" << screenWidth << " " << screenHeight << "\n255\n";

	//PrintScreenspaceColor();

	PrintSphereCenter();
}