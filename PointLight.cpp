#include "PointLight.h"
PointLight::PointLight()
{
	LightColor = LinAlgVector(std::vector<double>{1.0, 1.0, 1.0});
	LightIntensity = 1.0;
}

PointLight::~PointLight()
{

}


bool PointLight::ComputeIllumination(const LinAlgVector& intPoint, const LinAlgVector& localNormal,
	const std::vector<std::shared_ptr<Figure>>& objectList,
	const std::shared_ptr<Figure>& currentObject,
	LinAlgVector& color, double& intensity) //CHANGE HERE KILLS PERFORMANCE :(((
{
	// Construct a vector pointing from the intersection point to the light.
	LinAlgVector lightDir = (LightLocaction - intPoint).Normalized();
	double lightDist = (LightLocaction - intPoint).norm();

	// Compute a starting point.
	LinAlgVector startPoint = intPoint;

	// Construct a ray from the point of intersection to the light.
	Ray lightRay(startPoint, startPoint + lightDir);

	/* Check for intersections with all of the objects
		in the scene, except for the current one. */
	LinAlgVector poi{ 3 };
	LinAlgVector poiNormal{ 3 };
	LinAlgVector poiColor{ 3 };
	bool validInt = false;
	for (auto sceneObject : objectList)
	{
		if (sceneObject != currentObject)
		{
			validInt = sceneObject->TestIntersections(lightRay, poi, poiNormal, poiColor);
		/*	if (validInt)
			{
				double dist = (poi - startPoint).norm(); //KILLING PERFORMANCE HARD
				if (dist > lightDist)
					validInt = false;
			}*/
		}

		/* If we have an intersection, then there is no point checking further
			so we can break out of the loop. In other words, this object is
			blocking light from this light source. */
		if (validInt)
			break;
	}

	/* Only continue to compute illumination if the light ray didn't
		intersect with any objects in the scene. Ie. no objects are
		casting a shadow from this light source. */
	if (!validInt)
	{
		// Compute the angle between the local normal and the light ray.
		// Note that we assume that localNormal is a unit vector.
		double angle = acos(LinAlgVector::dot(localNormal, lightDir));

		// If the normal is pointing away from the light, then we have no illumination.
		if (angle > 1.5708)
		{
			// No illumination.
			color = LightColor;
			intensity = 0.0;
			return false;
		}
		else
		{
			// We do have illumination.
			color = LightColor;
			intensity = LightIntensity * (1.0 - (angle / 1.5708));
			return true;
		}
	}
	else
	{
		// Shadow, so no illumination.
		color = LightColor;
		intensity = 0.0;
		return false;
	}
}





//bool PointLight::ComputeIllumination(const LinAlgVector& IntPoint, const LinAlgVector& LocalNormal, const std::vector<std::shared_ptr<Figure>>& Figures,
//	const std::shared_ptr<Figure>& CurrentFigure, LinAlgVector& color, double& intensity)
//{
//	//std::cout << "before:" << "\n";
//	//(LightLocaction - IntPoint).PrintVector();
//	LinAlgVector LightDir = (LightLocaction - IntPoint).Normalized();
//	//std::cout << "after:" << "\n";
//	//LightDir.PrintVector();
//
//	LinAlgVector StartPoint = IntPoint; //We will see why it's useful later
//
//	//We assume that LocalNorm is a unit vector. It simplifies denominator
//	double angle = acos(LinAlgVector::dot(LocalNormal, LightDir));
//	if (angle < 1.5708)
//		//std::cout << "check:" << angle << "\n";
//
//	if (angle > 1.5708)
//	{
//		color = LightColor;
//		intensity = 0.0;
//		return false;
//	}
//	else
//	{
//		color = LightColor;
//		intensity = LightIntensity * (1.0 - (angle / 1.5708));
//		return true;
//	}
//}