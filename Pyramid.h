#ifndef PYRAMID_H
#define PYRAMID_H
#include "Figure.h"
#include <array>
class Pyramid : public Figure
{
public:
	Pyramid();
	virtual ~Pyramid() override;

	virtual bool TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor) override;

private:
	std::array<double, 4> t;
	std::array<double, 4> u;
	std::array<double, 4> v;
	std::array<double, 4> w;
	std::array<double, 4> a;
	std::array<double, 4> b;
	std::array<double, 4> c;
};

#endif
