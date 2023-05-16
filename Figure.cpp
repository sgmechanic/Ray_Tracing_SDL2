#include "Figure.h"
#include <math.h>

#define EPSILON 1e-21f;

Figure::Figure()
{

}
Figure::~Figure()
{

}
bool Figure::TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor)
{
	return false;
}
bool Figure::CloseEnough(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}

void Figure::SetTransformMatrix(const GTform& Transform)
{
	TransformMatrix = Transform;
}

bool Figure::AssignMaterial(const std::shared_ptr<MaterialBase>& ObjectMaterial)
{
	Material = ObjectMaterial;
	HasMaterial = true;
	return HasMaterial;
}

//bool Figure::AssignMaterial(const std::shared_ptr<MaterialBase>& FigureMaterial)
//{
//	Material = FigureMaterial;
//	FigureHasMaterial = true;
//	return FigureHasMaterial;
//}