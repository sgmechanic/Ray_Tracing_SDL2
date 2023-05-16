#ifndef RAY_H
#define RAY_H
#include "LinAlgVector.h"

class Ray
{
public:
	Ray();
	Ray(const LinAlgVector& point1, const LinAlgVector& point2);
	LinAlgVector GetPoint1() const;
	LinAlgVector GetPoint2() const;
	
	//LinAlgVector point1 = LinAlgVector(3);
	LinAlgVector point1{ 3 };
	LinAlgVector point2{ 3 };
	LinAlgVector ab{ 3 };
};
#endif