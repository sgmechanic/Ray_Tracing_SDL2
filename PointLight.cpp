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
	LinAlgVector& color, double& intensity) 
{
	// Construct a vector pointing from the intersection point to the light.
	LinAlgVector lightDir = (LightLocaction - intPoint).Normalized();
	double lightDist = (LightLocaction - intPoint).norm();

	// Starting point
	LinAlgVector startPoint = intPoint;

	// Construct a ray from the Intpoint to the light
	Ray lightRay(startPoint, startPoint + lightDir);

	//Skip currentObject
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
			//This if may be needed, should be tested
		}

		/* This object is
			blocking light from this light source. */
		if (validInt)
			break;
	}
	if (!validInt)
	{
		//angle between the local normal and the light ray
		//we assume that localNormal is a unit vector
		double angle = acos(LinAlgVector::dot(localNormal, lightDir));

		// If the normal is pointing away from the light, then we have no illumination
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




