// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "vec3.h"

using namespace std;

static int screenWidth = 400;
static int screenHeight = 300;

int main()
{
	ofstream out("out.ppm");
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());

	cout << "P3\n" << screenWidth << " " << screenHeight << "\n255\n";

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

