#ifndef FIGURE_H
#define FIGURE_H
#include "LinAlgVector.h"
#include "Ray.h"
#include "GeometricTransforms.h"
#include <memory>

class MaterialBase;

class Figure
{
public:
	Figure();
	virtual ~Figure();
	virtual bool TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor);
	bool CloseEnough(const double f1, const double f2);
	LinAlgVector BaseColor{ 3 };
	GTform TransformMatrix;
	std::shared_ptr<MaterialBase> Material;
	bool HasMaterial = false;
	bool AssignMaterial(const std::shared_ptr<MaterialBase>& ObjectMaterial);
	void SetTransformMatrix(const GTform& Transform);
};
#endif