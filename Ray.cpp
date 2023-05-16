#include "Ray.h"
Ray::Ray()
{
	point1 = LinAlgVector{ std::vector<double>{0.0,0.0,0.0} };
	point2 = LinAlgVector{ std::vector<double>{0.0,0.0,0.0} };
	ab = point2 - point1;
}
Ray::Ray(const LinAlgVector& p1, const LinAlgVector& p2)
{
	point1 = p1;
	point2 = p2;
	ab = p2 - p1;
}

LinAlgVector Ray::GetPoint1() const
{
	return point1;
}

LinAlgVector Ray::GetPoint2() const
{
	return point2;
}