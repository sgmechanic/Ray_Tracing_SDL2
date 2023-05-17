#include "Plane.h"
#include <cmath>


Plane::Plane()
{

}

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

	//Check for parallel
	if (!CloseEnough(k.GetElement(2), 0.0))
	{
		double t = BckRay.point1.GetElement(2) / -k.GetElement(2);

		//Check if it's behind the camera
		if (t > 0.0)
		{
			// Compute the values for u and v.
			double u = BckRay.point1.GetElement(0) + (k.GetElement(0) * t);
			double v = BckRay.point1.GetElement(1) + (k.GetElement(1) * t);

			//We model our plane as a box
			if ((abs(u) < 1.0) && (abs(v) < 1.0))
			{
				// Compute the point of intersection.
				LinAlgVector poi = BckRay.point1 + k * t;

				// Transform the intersection point back into world coordinates
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


