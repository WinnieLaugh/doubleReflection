#define h 0.001

#include <stdio.h>
#include <iostream>
#include "vector.h"
#include "doureflection.h"

vector X(int i);
vector T(int i);

int main(int argc, char ** argv)
{
	vector ri, ti, si;
	vector Xi, Xi1, v1, riL, tiL, ti1, v2, ri1, si1, ui1;
	double c1, c2;

	FILE *fout;
	fopen_s(&fout,"D:\\workspace\\C++\\OpenGL\\opengltest\\doreflection\\doubleReflection.obj", "w");

	fprintf(fout, "g default \n");


	Xi = X(0);
	ti = T(0);
	ti = ti.nomalize();
	ri.x = 1.0;
	ri.y = 0.0;
	ri.z = 0.0;
	si = ti * ri;
	si = si.nomalize();

	for (int i = 0; i < 2000; i++){

		fprintf(fout, "v %f %f %f \n", Xi.x, Xi.y, Xi.z);
		fprintf(fout, "v %f %f %f \n",ri.nomalize().x, ri.nomalize().y, ri.nomalize().z);
		fprintf(fout, "v %f %f %f \n", Xi.x + ri.nomalize().x, Xi.y + ri.nomalize().y, Xi.z + ri.nomalize().z);

		Xi1 = X(i + 1);
		ti1 = T(i + 1);

		v1 = Xi1 - Xi;
		c1 = v1.dot(v1);
		//printf("%f", c1);
		//int test;
		//std::cin >> test;

		riL = ri - v1 * (2 / c1) * (v1.dot(ri));
		tiL = ti - v1 * (2 / c1) * (v1.dot(ri));
		v2 = ti1 - tiL;
		c2 = v2.dot(v2);
		ri1 = riL - v2 * (2 / c2) * (v2.dot(riL));
		si1 = ti1 * ri1;

		ti = ti1;
		Xi = Xi1;
		ri = ri1;
		si = si1;
	}

	fprintf(fout, "l ");

	for (int i = 0; i < 2000; i++){
		fprintf(fout, "%d//%d ", i*3+1, i*3+2);
	}

	fprintf(fout, "\n");

	for (int i = 0; i < 2000; i++){
		fprintf(fout, "l %d %d \n", i*3+1, i*3+3);
	}

	return(0);
}

vector X(int i){
	vector X;
	X.x = 10 * (0.6 + 0.3 * cos(7 * i*h)) * cos(2 * i*h);
	X.y = 10 * (0.6 + 0.3*cos(7 * i*h))*sin(2 * i*h);
	X.z = 10 * 0.3*sin(7 * i*h);

	return X;
}

vector T(int i){
	vector t;
	t.x = -0.6 * cos(7 * i*h) * sin(2 * i*h) - 2.1 * sin(7 * i*h) * cos(2 * i*h) - 1.2;
	t.y = 1.2 + 0.6 * cos(7 * i*h) * cos(2 * i*h) - 2.1*sin(7 * i*h)*sin(2 * i*h);
	t.z = -2.1 * cos(7 * i*h);

	return t;
}