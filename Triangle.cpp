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

//BCS
bool Triangle::TestIntersections(const Ray& CastRay, LinAlgVector& intPoint,
	LinAlgVector& localNormal, LinAlgVector& localColor)
{
	//Fill Matrix with vertices coords
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

	LinAlgMatrix FirstStep = (A.Transpose() * A);
	FirstStep.SimpleInverse();
	LinAlgMatrix AFinal = FirstStep * (A.Transpose());


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

	//Check for parallel
	if (!CloseEnough(kz -sqrt(6.0)*kx - sqrt(2.0)*ky, 0.0))
	{
		//Calculate t for this intersection
		double t = (-az + sqrt(6.0) * ax + sqrt(2.0) * ay - sqrt(6.0)) / (kz - sqrt(6.0) * kx - sqrt(2.0) * ky);

		// Ignore intersection if it's behind the camera
		if (t > 0.0)
		{
			// Compute the values for u and v.
			double u = ax + (kx * t);
			double v = ay + (ky * t);
			double w = az + (kz * t);
			//Don't used right now but may be helpful in the future

			//Use previously calculated matrix to find barycentric coords
			LinAlgVector Barycentric = AFinal * LinAlgVector{ std::vector<double>{u,v,w,1.0} };

			double a = Barycentric.GetElement(0);
			double b = Barycentric.GetElement(1);
			double c = Barycentric.GetElement(2);
			
			//Check if point is inside the triangle, using the properties of barycentric coords
			if (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1)
			{
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