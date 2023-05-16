#ifndef SPHERE_H
#define SPHERE_H
#include "Figure.h"
//#include "GeometricTransforms.h"
class Sphere : public Figure
{
private:

public:
	Sphere() : Figure() {} // Unit Sphere at the Origin
	virtual ~Sphere() override;
	virtual bool TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor) override;
};
#endif