#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Figure.h"
#include <cmath>
#include "GeometricTransforms.h"

class Triangle : public Figure
{
public:
	Triangle();

	virtual ~Triangle() override;

	virtual bool TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor) override;
private:

};
#endif
