#include "MaterialBase.h"
MaterialBase::MaterialBase()
{

}


MaterialBase::~MaterialBase()
{

}

// Function to compute the color of the material.
LinAlgVector MaterialBase::ComputeColor(const std::vector<std::shared_ptr<Figure>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList,
	const std::shared_ptr<Figure>& currentObject,
	const LinAlgVector& intPoint, const LinAlgVector& localNormal,
	const Ray& cameraRay)
{
// Define an initial material color.
	LinAlgVector matColor{ 3 };
	return matColor;
}

// Function to compute the diffuse color(Simple model)
LinAlgVector MaterialBase::ComputeDiffuseColor(const std::vector<std::shared_ptr<Figure>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList,
	const std::shared_ptr<Figure>& currentObject,
	const LinAlgVector& intPoint, const LinAlgVector& localNormal,
	const LinAlgVector& baseColor)
{
	LinAlgVector diffuseColor{ 3 };
	double intensity;
	LinAlgVector color{ 3 };
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	bool validIllum = false;
	bool illumFound = false;
	for (auto currentLight : lightList)
	{
		validIllum = currentLight->ComputeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity);
		if (validIllum)
		{
			illumFound = true;
			red += color.GetElement(0) * intensity;
			green += color.GetElement(1) * intensity;
			blue += color.GetElement(2) * intensity;
		}
	}

	if (illumFound)
	{
		diffuseColor[0] = red * baseColor.GetElement(0);
		diffuseColor[1] = green * baseColor.GetElement(1);
		diffuseColor[2] = blue * baseColor.GetElement(2);
	}

	// Return the material color.
	return diffuseColor;
}

