#include "Sphere.h"
#include <cmath>


//Sphere::Sphere()
//{
//
//}

Sphere::~Sphere()
{

}

//bool Sphere::TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor)
//{
//	//Compute the values of a,b and c.
//	LinAlgVector vhat = CastRay.ab;
//	vhat.Normalize();
//	//a will always be 1;
//	double b = LinAlgVector::dot(CastRay.point1, vhat)*2.0;
//	//Calculate C
//	double c = LinAlgVector::dot(CastRay.point1, CastRay.point1) - 1.0;
//
//	double D = (b * b) - 4.0 * c;
//
//	if (D > 0.0)
//	{
//		double numSQRT = sqrtf(D);
//		double t1 = (-b + numSQRT) / 2.0;
//		double t2 = (-b - numSQRT) / 2.0;
//		
//		if ((t1 < 0.0) || (t2 < 0.0))
//		{
//			return false;
//		}
//		else
//		{
//			//Determine which point of intersection was closest to the camera.
//			if (t1 < t2)
//				IntPoint = CastRay.point1 + (vhat * t1);
//			else
//				IntPoint = CastRay.point1 + (vhat * t2);
//			LocalNormal = IntPoint;
//			LocalNormal.Normalize();
//		}
//		return true;
//	}
//	else
//		return false;
//
//}

bool Sphere::TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor)
{
	//CastRay.point1.PrintVector();
	//CastRay.point2.PrintVector();
	//std::cout << "cast ab"<<"\n";
	//Copy the ray and apply the backwards transform
	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);
	//BckRay.point1.PrintVector();
	//BckRay.point2.PrintVector();
	//std::cout << "back ab"<<"\n";
	//Compute the values of a,b and c.
	LinAlgVector vhat = BckRay.ab;
	//vhat.PrintVector();
	//std::cout << " back ab";
	vhat.Normalize();
	//vhat.PrintVector();
	//std::cout << "back ab normalized";
	//a will always be 1;
	double b = LinAlgVector::dot(BckRay.point1, vhat) * 2.0;
	//Calculate C
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
			//Determine which point of intersection was closest to the camera.
			if (t1 < t2)
				poi = BckRay.point1 + (vhat * t1);
			else
				poi = BckRay.point1 + (vhat * t2);
			//poi.PrintVector();
			//Transform the intersection point back into world coordinates
			IntPoint = TransformMatrix.Apply(poi, FWDTFORM);
			//IntPoint.PrintVector();

			LinAlgVector ObjOrigin(std::vector<double>{0.0, 0.0, 0.0});
			//ObjOrigin.PrintVector();
			//std::cout << "old origin" << "\n";
			LinAlgVector NewObjOrigin = TransformMatrix.Apply(ObjOrigin, FWDTFORM);
			//NewObjOrigin.PrintVector();
			//std::cout << "new origin" << "\n";

			LocalNormal = IntPoint - NewObjOrigin;
			//LocalNormal.PrintVector();
			LocalNormal.Normalize();
			//LocalNormal.PrintVector();

			LocalColor = BaseColor;
		}
		return true;
	}
	else
		return false;
}