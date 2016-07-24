#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>
class vector
{
public:
	double x;
	double y;
	double z;
	
	vector operator- (vector v2){
		vector result;
		result.x = x - v2.x;
		result.y = y - v2.y;
		result.z = z - v2.z;

		return result;
	}

	vector operator+ (vector v2){
		vector result;
		result.x = x + v2.x;
		result.y = y + v2.y;
		result.z = z + v2.z;

		return result;

	}

	double dot (vector v2){
		double result;
		result = x * v2.x + y * v2.y + z * v2.z;

		return result;
	}

	vector operator* (vector v2){
		vector result;
		result.x = y*v2.z - v2.y*z;
		result.y = z*v2.x - x*v2.z;
		result.z = x*v2.y - y*v2.x;

		return result;
	}

	vector operator* (double k){
		vector result;
		result.x = k * x;
		result.y = k * y;
		result.z = k * z;

		return result;
	}

	vector nomalize(){
		vector nomalized;
		double length = pow( (pow(x, 2) + pow(y, 2) + pow(z,2)), 0.5);

		if (length != 0){
			nomalized.x = x / length;
			nomalized.y = y / length;
			nomalized.z = z / length;
		}
		else{
			nomalized.x = x;
			nomalized.y = y;
			nomalized.z = z;
		}

		return nomalized;
	}
};
#endif