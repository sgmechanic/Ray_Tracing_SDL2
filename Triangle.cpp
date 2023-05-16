#include "Triangle.h"
#include <cmath>

// The default constructor.
Triangle::Triangle()
{

}

// The destructor.
Triangle::~Triangle()
{

}
//
//// The function to test for intersections.
//bool Triangle::TestIntersections(const Ray& CastRay, LinAlgVector& intPoint,
//	LinAlgVector& localNormal, LinAlgVector& localColor)
//{
//	LinAlgVector product = LinAlgVector::cross(LinAlgVector{ std::vector<double>{1.0,0.0,0.0} }, LinAlgVector{ std::vector<double>{1.0 / 2.0,sqrt(3) / 2.0,0} });
//	double area = product.norm()/2.0;
//
//	// Copy the ray and apply the backwards transform.
//	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);
//
//	// Copy the m_lab vector from bckRay and normalize it.
//	LinAlgVector k = BckRay.ab;
//	k.Normalize();
//
//	/* Check if there is an intersection, ie. if the castRay is not parallel
//		to the plane. */
//	if (!CloseEnough(k.GetElement(2), 0.0))
//	{
//		// There is an intersection.
//		double t = BckRay.point1.GetElement(2) / -k.GetElement(2);
//
//		/* If t is negative, then the intersection point must be behind
//			the camera and we can ignore it. */
//		if (t > 0.0)
//		{
//			// Compute the values for u and v.
//			//double u = BckRay.point1.GetElement(0) + (k.GetElement(0) * t);
//			double v = 2.0/sqrt(3.0)*BckRay.point1.GetElement(1) + 2.0/sqrt(3.0)*(k.GetElement(1) * t);
//			double u = BckRay.point1.GetElement(0) + (k.GetElement(0) * t) - 0.5 * v;
//
//			//double a = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {1,0.0,0.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }).norm()) / (2.0 * area);
//			//double b = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} }).norm()) / (2.0 * area); //DOESNT WORK!
//			//double b = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} }).norm();
//			//double c = 1 - a - b;
//			double a = (sqrt(3.0) * v - 3.0 * u - 3.0 / 2.0) / -3.0;
//			double b = (3.0 * u + sqrt(3.0) * v - 3.0 / 2.0) / -3.0; //WORKS FINE
//			double c = (2.0 * sqrt(3.0) * v) / 3.0;
//
//			/* If the magnitude of both u and v is less than or equal to one
//				then we must be in the plane. */
//			if (u >= 0 && v >= 0 && (u + v <= 1))
//			{
//				// Compute the point of intersection.
//				LinAlgVector poi = BckRay.point1 + k * t; //////?????
//
//				// Transform the intersection point back into world coordinates.
//				intPoint = TransformMatrix.Apply(poi, FWDTFORM);
//
//				// Compute the local normal.
//				LinAlgVector localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
//				LinAlgVector normalVector{ std::vector<double> {0.0, 0.0, -1.0} };
//				LinAlgVector globalOrigin = TransformMatrix.Apply(localOrigin, FWDTFORM);
//				localNormal = TransformMatrix.Apply(normalVector, FWDTFORM) - globalOrigin;
//				localNormal.Normalize();
//
//				// Return the base color.
//				localColor = BaseColor;
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
//
//	return false;
//}
//
//

////WORKS JUST FINE (ABC)
//bool Triangle::TestIntersections(const Ray& CastRay, LinAlgVector& intPoint,
//	LinAlgVector& localNormal, LinAlgVector& localColor)
//{
//	LinAlgMatrix A{ 4,3 };
//	A.Elem(0, 0) = 0;
//	A.Elem(1, 0) = 0;
//	A.Elem(2, 0) = 0;
//	A.Elem(3, 0) = 1;
//	A.Elem(0, 1) = 1;
//	A.Elem(1, 1) = 0;
//	A.Elem(2, 1) = 0;
//	A.Elem(3, 1) = 1;
//	A.Elem(0, 2) = 1.0/2.0;
//	A.Elem(1, 2) = sqrt(3.0)/2.0;
//	A.Elem(2, 2) = 0;
//	A.Elem(3, 2) = 1;
//	//A.PrintMatrix();
//	LinAlgMatrix FirstStep = (A.Transpose() * A);
//	FirstStep.SimpleInverse();
//	//FirstStep.PrintMatrix();
//	LinAlgMatrix AFinal = FirstStep*(A.Transpose());
//	//AFinal.PrintMatrix();
//	// Copy the ray and apply the backwards transform.
//	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);
//
//	double ax = BckRay.point1.GetElement(0);
//	double ay = BckRay.point1.GetElement(1);
//	double az = BckRay.point1.GetElement(2);
//
//	LinAlgVector k = BckRay.ab;
//	k.Normalize();
//	double kx = k.GetElement(0);
//	double ky = k.GetElement(1);
//	double kz = k.GetElement(2);
//
//	/* Check if there is an intersection, ie. if the castRay is not parallel
//		to the plane. */
//	if (!CloseEnough(kz, 0.0))
//	{
//		// There is an intersection.
//		double t = -az/kz;
//
//		/* If t is negative, then the intersection point must be behind
//			the camera and we can ignore it. */
//		if (t > 0.0)
//		{
//			// Compute the values for u and v.
//			double u = ax + (kx* t);
//			double v = ay + (ky * t);
//			double w = az + (kz * t);
//			LinAlgVector Barycentric = AFinal * LinAlgVector{ std::vector<double>{u,v,w,1.0} };
//			//Barycentric.PrintVector();
//			double a = Barycentric.GetElement(0);
//			double b = Barycentric.GetElement(1);
//			double c = Barycentric.GetElement(2);
//			//double a = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {1,0.0,0.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }).norm()) / (2.0 * area);
//			//double b = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} }).norm()) / (2.0 * area);
//			//double b = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} }).norm();
//			//double c = 1 - a - b;
//			/*double a = (sqrt(3.0) * v - 3.0 * u - 3.0 / 2.0) / -3.0;
//			double b = (3.0 * u + sqrt(3.0) * v - 3.0 / 2.0) / -3.0;
//			double c = (2.0 * sqrt(3.0) * v) / 3.0;*/
//
//			/* If the magnitude of both u and v is less than or equal to one
//				then we must be in the plane. */
//			if (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1)
//			{
//				//std::cout << "check";
//				// Compute the point of intersection.
//				LinAlgVector poi = BckRay.point1 + k * t; //////?????
//
//				// Transform the intersection point back into world coordinates.
//				intPoint = TransformMatrix.Apply(poi, FWDTFORM);
//
//				// Compute the local normal.
//				LinAlgVector localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
//				LinAlgVector normalVector{ std::vector<double> {0, 0, -1.0}};
//				LinAlgVector globalOrigin = TransformMatrix.Apply(localOrigin, FWDTFORM);
//				localNormal = TransformMatrix.Apply(normalVector, FWDTFORM) - globalOrigin;
//				localNormal.Normalize();
//
//				// Return the base color.
//				localColor = BaseColor;
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
//
//	return false;
//}


//WORKS FINE(ABS)
//bool Triangle::TestIntersections(const Ray& CastRay, LinAlgVector& intPoint,
//	LinAlgVector& localNormal, LinAlgVector& localColor)
//{
//	LinAlgMatrix A{ 4,3 };
//	A.Elem(0, 0) = 0;
//	A.Elem(1, 0) = 0;
//	A.Elem(2, 0) = 0;
//	A.Elem(3, 0) = 1;
//	A.Elem(0, 1) = 1;
//	A.Elem(1, 1) = 0;
//	A.Elem(2, 1) = 0;
//	A.Elem(3, 1) = 1;
//	A.Elem(0, 2) = 1.0 / 2.0;
//	A.Elem(1, 2) = sqrt(3.0) / 6.0;
//	A.Elem(2, 2) = -sqrt(6.0)/3.0;
//	A.Elem(3, 2) = 1;
//	//A.PrintMatrix();
//	LinAlgMatrix FirstStep = (A.Transpose() * A);
//	FirstStep.SimpleInverse();
//	//FirstStep.PrintMatrix();
//	LinAlgMatrix AFinal = FirstStep * (A.Transpose());
//	//AFinal.PrintMatrix();
//	// Copy the ray and apply the backwards transform.
//	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);
//
//	double ax = BckRay.point1.GetElement(0);
//	double ay = BckRay.point1.GetElement(1);
//	double az = BckRay.point1.GetElement(2);
//
//	LinAlgVector k = BckRay.ab;
//	k.Normalize();
//	double kx = k.GetElement(0);
//	double ky = k.GetElement(1);
//	double kz = k.GetElement(2);
//
//	/* Check if there is an intersection, ie. if the castRay is not parallel
//		to the plane. */
//	if (!CloseEnough(2*sqrt(2)*ky + kz, 0.0))
//	{
//		// There is an intersection.
//		double t = (- az - 2 * sqrt(2) * ay) / (2*sqrt(2)*ky + kz);
//
//		/* If t is negative, then the intersection point must be behind
//			the camera and we can ignore it. */
//		if (t > 0.0)
//		{
//			// Compute the values for u and v.
//			double u = ax + (kx * t);
//			double v = ay + (ky * t);
//			double w = az + (kz * t);
//			LinAlgVector Barycentric = AFinal * LinAlgVector{ std::vector<double>{u,v,w,1.0} };
//			//Barycentric.PrintVector();
//			double a = Barycentric.GetElement(0);
//			double b = Barycentric.GetElement(1);
//			double c = Barycentric.GetElement(2);
//			//double a = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {1,0.0,0.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }).norm()) / (2.0 * area);
//			//double b = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} }).norm()) / (2.0 * area);
//			//double b = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} }).norm();
//			//double c = 1 - a - b;
//			/*double a = (sqrt(3.0) * v - 3.0 * u - 3.0 / 2.0) / -3.0;
//			double b = (3.0 * u + sqrt(3.0) * v - 3.0 / 2.0) / -3.0;
//			double c = (2.0 * sqrt(3.0) * v) / 3.0;*/
//
//			/* If the magnitude of both u and v is less than or equal to one
//				then we must be in the plane. */
//			if (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1)
//			{
//				//std::cout << "check";
//				// Compute the point of intersection.
//				LinAlgVector poi = BckRay.point1 + k * t; //////?????
//
//				// Transform the intersection point back into world coordinates.
//				intPoint = TransformMatrix.Apply(poi, FWDTFORM);
//
//				// Compute the local normal.
//				LinAlgVector localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
//				LinAlgVector normalVector{ std::vector<double> {0, -2*sqrt(2)/3.0, -1.0/3.0}};
//				LinAlgVector globalOrigin = TransformMatrix.Apply(localOrigin, FWDTFORM);
//				localNormal = TransformMatrix.Apply(normalVector, FWDTFORM) - globalOrigin;
//				localNormal.Normalize();
//
//				// Return the base color.
//				localColor = BaseColor;
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
//
//	return false;
//}

//SOOOO SEEMS FINE(ACS)
//bool Triangle::TestIntersections(const Ray& CastRay, LinAlgVector& intPoint,
//	LinAlgVector& localNormal, LinAlgVector& localColor)
//{
//	LinAlgMatrix A{ 4,3 };
//	A.Elem(0, 0) = 0;
//	A.Elem(1, 0) = 0;
//	A.Elem(2, 0) = 0;
//	A.Elem(3, 0) = 1;
//	A.Elem(0, 1) = 1.0/2.0;
//	A.Elem(1, 1) =	sqrt(3.0)/2.0;
//	A.Elem(2, 1) = 0;
//	A.Elem(3, 1) = 1;
//	A.Elem(0, 2) = 1.0 / 2.0;
//	A.Elem(1, 2) = sqrt(3.0) / 6.0;
//	A.Elem(2, 2) = -sqrt(6.0) / 3.0;
//	A.Elem(3, 2) = 1;
//	//A.PrintMatrix();
//	LinAlgMatrix FirstStep = (A.Transpose() * A);
//	FirstStep.SimpleInverse();
//	//FirstStep.PrintMatrix();
//	LinAlgMatrix AFinal = FirstStep * (A.Transpose());
//	//AFinal.PrintMatrix();
//	// Copy the ray and apply the backwards transform.
//	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);
//
//	double ax = BckRay.point1.GetElement(0);
//	double ay = BckRay.point1.GetElement(1);
//	double az = BckRay.point1.GetElement(2);
//
//	LinAlgVector k = BckRay.ab;
//	k.Normalize();
//	double kx = k.GetElement(0);
//	double ky = k.GetElement(1);
//	double kz = k.GetElement(2);
//
//	/* Check if there is an intersection, ie. if the castRay is not parallel
//		to the plane. */
//	if (!CloseEnough(sqrt(6.0)*kx - sqrt(2.0)*ky + kz, 0.0))
//	{
//		// There is an intersection.
//		double t = (-sqrt(6.0) * ax + sqrt(2.0) * ay - az) / (sqrt(6.0) * kx - sqrt(2.0) * ky + kz);
//
//		/* If t is negative, then the intersection point must be behind
//			the camera and we can ignore it. */
//		if (t > 0.0)
//		{
//			// Compute the values for u and v.
//			double u = ax + (kx * t);
//			double v = ay + (ky * t);
//			double w = az + (kz * t);
//			LinAlgVector Barycentric = AFinal * LinAlgVector{ std::vector<double>{u,v,w,1.0} };
//			//Barycentric.PrintVector();
//			double a = Barycentric.GetElement(0);
//			double b = Barycentric.GetElement(1);
//			double c = Barycentric.GetElement(2);
//			//double a = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {1,0.0,0.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }).norm()) / (2.0 * area);
//			//double b = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} }).norm()) / (2.0 * area);
//			//double b = (LinAlgVector::cross(LinAlgVector{ std::vector<double>{u,v,0.0} } - LinAlgVector{ std::vector < double> {0.5,sqrt(3.0) / 6.0,sqrt(6.0) / 3.0} }, LinAlgVector{ std::vector<double>{u,v,0.0} }).norm();
//			//double c = 1 - a - b;
//			/*double a = (sqrt(3.0) * v - 3.0 * u - 3.0 / 2.0) / -3.0;
//			double b = (3.0 * u + sqrt(3.0) * v - 3.0 / 2.0) / -3.0;
//			double c = (2.0 * sqrt(3.0) * v) / 3.0;*/
//
//			/* If the magnitude of both u and v is less than or equal to one
//				then we must be in the plane. */
//			if (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1)
//			{
//				//std::cout << "check";
//				// Compute the point of intersection.
//				LinAlgVector poi = BckRay.point1 + k * t; //////?????
//
//				// Transform the intersection point back into world coordinates.
//				intPoint = TransformMatrix.Apply(poi, FWDTFORM);
//
//				// Compute the local normal.
//				LinAlgVector localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
//				LinAlgVector normalVector{ std::vector<double> {sqrt(2.0/3.0), -sqrt(2) / 3.0, 1.0 / 3.0}};
//				LinAlgVector globalOrigin = TransformMatrix.Apply(localOrigin, FWDTFORM);
//				localNormal = TransformMatrix.Apply(normalVector, FWDTFORM) - globalOrigin;
//				localNormal.Normalize();
//
//				// Return the base color.
//				localColor = BaseColor;
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
//
//	return false;
//}


//BCS
bool Triangle::TestIntersections(const Ray& CastRay, LinAlgVector& intPoint,
	LinAlgVector& localNormal, LinAlgVector& localColor)
{
	LinAlgMatrix A{ 4,3 };
	A.Elem(0, 0) = 1;
	A.Elem(1, 0) = 0;
	A.Elem(2, 0) = 0;
	A.Elem(3, 0) = 1;
	A.Elem(0, 1) = 1.0 / 2.0;
	A.Elem(1, 1) = sqrt(3.0) / 2.0;
	A.Elem(2, 1) = 0;
	A.Elem(3, 1) = 1;
	A.Elem(0, 2) = 1.0 / 2.0;
	A.Elem(1, 2) = sqrt(3.0) / 6.0;
	A.Elem(2, 2) = -sqrt(6.0) / 3.0;
	A.Elem(3, 2) = 1;
	//A.PrintMatrix();
	LinAlgMatrix FirstStep = (A.Transpose() * A);
	FirstStep.SimpleInverse();
	//FirstStep.PrintMatrix();
	LinAlgMatrix AFinal = FirstStep * (A.Transpose());
	//AFinal.PrintMatrix();
	// Copy the ray and apply the backwards transform.
	Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);

	double ax = BckRay.point1.GetElement(0);
	double ay = BckRay.point1.GetElement(1);
	double az = BckRay.point1.GetElement(2);

	LinAlgVector k = BckRay.ab;
	k.Normalize();
	double kx = k.GetElement(0);
	double ky = k.GetElement(1);
	double kz = k.GetElement(2);

	/* Check if there is an intersection, ie. if the castRay is not parallel
		to the plane. */
	if (!CloseEnough(kz -sqrt(6.0)*kx - sqrt(2.0)*ky, 0.0))
	{
		// There is an intersection.
		double t = (-az + sqrt(6.0) * ax + sqrt(2.0) * ay - sqrt(6.0)) / (kz - sqrt(6.0) * kx - sqrt(2.0) * ky);

		/* If t is negative, then the intersection point must be behind
			the camera and we can ignore it. */
		if (t > 0.0)
		{
			// Compute the values for u and v.
			double u = ax + (kx * t);
			double v = ay + (ky * t);
			double w = az + (kz * t);
			LinAlgVector Barycentric = AFinal * LinAlgVector{ std::vector<double>{u,v,w,1.0} };
			//Barycentric.PrintVector();
			double a = Barycentric.GetElement(0);
			double b = Barycentric.GetElement(1);
			double c = Barycentric.GetElement(2);
			/* If the magnitude of both u and v is less than or equal to one
				then we must be in the plane. */
			if (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1)
			{
				//std::cout << "check";
				// Compute the point of intersection.
				LinAlgVector poi = BckRay.point1 + k * t; //////?????

				// Transform the intersection point back into world coordinates.
				intPoint = TransformMatrix.Apply(poi, FWDTFORM);

				// Compute the local normal.
				LinAlgVector localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
				LinAlgVector normalVector{ std::vector<double> {sqrt(2.0 / 3.0), sqrt(2) / 3.0, -1.0 / 3.0} };
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