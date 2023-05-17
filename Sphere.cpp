#include "Sphere.h"
#include <cmath>

Sphere::~Sphere()
{

}

bool Sphere::TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor)
{

	//Copy the ray and apply the backwards transform
	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);
	//Compute the values of a,b and c. a is always one due to our choice of sphere and local coords
	LinAlgVector vhat = BckRay.ab;
	vhat.Normalize();
	double b = LinAlgVector::dot(BckRay.point1, vhat) * 2.0;
	double c = LinAlgVector::dot(BckRay.point1, BckRay.point1) - 1.0;

	double D = (b * b) - 4.0 * c;
	LinAlgVector poi;
	if (D > 0.0)
	{
		double numSQRT = sqrtf(D);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;

		if ((t1 < 0.0) || (t2 < 0.0))
		{
			return false;
		}
		else
		{
			//Determine which root is needed
			if (t1 < t2)
				poi = BckRay.point1 + (vhat * t1);
			else
				poi = BckRay.point1 + (vhat * t2);

			//Transform the intersection point back into world coordinates
			IntPoint = TransformMatrix.Apply(poi, FWDTFORM);

			LinAlgVector ObjOrigin(std::vector<double>{0.0, 0.0, 0.0});
			LinAlgVector NewObjOrigin = TransformMatrix.Apply(ObjOrigin, FWDTFORM);

			LocalNormal = IntPoint - NewObjOrigin;
			LocalNormal.Normalize();

			LocalColor = BaseColor;
		}
		return true;
	}
	else
		return false;
}