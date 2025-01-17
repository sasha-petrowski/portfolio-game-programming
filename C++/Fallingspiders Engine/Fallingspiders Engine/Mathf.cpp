#include "Mathf.h"

/*
//function to calculate cross product of two vectors
void cross_product(int vector_a[], int vector_b[], int temp[]) {
	temp[0] = vector_a[1] * vector_b[2] - vector_a[2] * vector_b[1];
	temp[1] = -(vector_a[0] * vector_b[2] - vector_a[2] * vector_b[0]);
	temp[2] = vector_a[0] * vector_b[1] - vector_a[1] * vector_b[0];
}
*/

namespace SpidersEngine
{
	float Mathf::dot(Vector2 a, Vector2 b)
	{
		return a.x * b.x + a.y * b.y;
	}
}

