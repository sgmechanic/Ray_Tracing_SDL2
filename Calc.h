#pragma once
#include <cmath>
#define EPSILON 1e-21f;
bool CloseEnough(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}