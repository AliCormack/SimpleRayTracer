#pragma once

#include "Ray.h"

class Camera
{
public:

	static const int screenWidth = 600;
	static const int screenHeight = 300;

	int scale = 100;

	int worldSpaceWidth = screenWidth / scale;
	int worldSpaceHeight = screenHeight / scale;

	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;

	Camera()
	{
		lower_left_corner = vec3(-worldSpaceWidth, -worldSpaceHeight, -1);
		horizontal = vec3(worldSpaceWidth * 2, 0, 0);
		vertical = vec3(0, worldSpaceHeight * 2, 0);
		origin = vec3(0, 0, 0);
	}

	Ray GetRay(float u, float v)
	{
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
};