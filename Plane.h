#ifndef PLANE_H
#define PLANE_H

#include "Figure.h"
#include "GeometricTransforms.h"

class Plane : public Figure
{
public:
	Plane();

	virtual ~Plane() override;

	virtual bool TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor) override;
private:

};

#endif
