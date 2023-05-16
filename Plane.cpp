//#include <cmath>
//#include "Plane.h"
//
//Plane::Plane()
//{
//
//}
//
//Plane::~Plane()
//{
//
//}
//
//bool Plane::TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor)
//{
//	//Copy the ray and apply the backwords transform
//	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);
//	LinAlgVector k = BckRay.ab;
//	k.Normalize();
//
//	//Check if there is an intersection
//	if (!CloseEnough(k.GetElement(2), 0.0))
//	{
//		//There is an intersection
//		double t = BckRay.point1.GetElement(2) / -k.GetElement(2);
//
//		// if t is negative it must be behind the camera and we can ignore it
//		if (t > 0.0)
//		{
//			// Compute the values for u and v (razlozhenie po bazisu!)
//			double u = BckRay.point1.GetElement(0) + (k.GetElement(0) * t);
//			double v = BckRay.point1.GetElement(1) + (k.GetElement(1) * t);
//
//			//If the magnitude of both u and v is less than or equal to one than we must be in the plane
//			if ((abs(u) < 1.0) && (abs(v) < 1.0))
//			{
//				LinAlgVector poi = BckRay.point1 + k * t;
//
//				IntPoint = TransformMatrix.Apply(poi, FWDTFORM);
//
//				LinAlgVector LocalOrigin(std::vector<double>{0.0, 0.0, 0.0});
//				LinAlgVector NormalVector(std::vector<double>{0.0, 0.0, -1.0});
//				LinAlgVector GlobalOrigin = TransformMatrix.Apply(LocalOrigin, FWDTFORM);
//				LocalNormal = TransformMatrix.Apply(NormalVector, FWDTFORM) - GlobalOrigin;
//				LocalNormal.Normalize();
//				LocalColor = BaseColor;
//
//				return true;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	return false;
//}




#include "Plane.h"
#include <cmath>

// The default constructor.
Plane::Plane()
{

}

// The destructor.
Plane::~Plane()
{

}

// The function to test for intersections.
bool Plane::TestIntersections(const Ray& CastRay, LinAlgVector& intPoint,
	LinAlgVector& localNormal, LinAlgVector& localColor)
{
	// Copy the ray and apply the backwards transform.
	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);

	// Copy the m_lab vector from bckRay and normalize it.
	LinAlgVector k = BckRay.ab;
	k.Normalize();

	/* Check if there is an intersection, ie. if the castRay is not parallel
		to the plane. */
	if (!CloseEnough(k.GetElement(2), 0.0))
	{
		// There is an intersection.
		double t = BckRay.point1.GetElement(2) / -k.GetElement(2);

		/* If t is negative, then the intersection point must be behind
			the camera and we can ignore it. */
		if (t > 0.0)
		{
			// Compute the values for u and v.
			double u = BckRay.point1.GetElement(0) + (k.GetElement(0) * t);
			double v = BckRay.point1.GetElement(1) + (k.GetElement(1) * t);

			/* If the magnitude of both u and v is less than or equal to one
				then we must be in the plane. */
			if ((abs(u) < 1.0) && (abs(v) < 1.0))
			{
				// Compute the point of intersection.
				LinAlgVector poi = BckRay.point1 + k * t; //////?????

				// Transform the intersection point back into world coordinates.
				intPoint = TransformMatrix.Apply(poi, FWDTFORM);

				// Compute the local normal.
				LinAlgVector localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
				LinAlgVector normalVector{ std::vector<double> {0.0, 0.0, -1.0} };
				LinAlgVector globalOrigin = TransformMatrix.Apply(localOrigin, FWDTFORM);
				localNormal = TransformMatrix.Apply(normalVector, FWDTFORM) - globalOrigin;
				localNormal.Normalize();

				// Return the base color.
				localColor = BaseColor;

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return false;
}


