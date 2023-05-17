#include "SimpleMaterial.h"

SimpleMaterial::SimpleMaterial()
{

}
SimpleMaterial::~SimpleMaterial()
{

}
LinAlgVector SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<Figure>>& Figures, const std::vector<std::shared_ptr<LightBase>>& Lights,
	const std::shared_ptr<Figure>& currentObject, const LinAlgVector& intPoint, const LinAlgVector& localNormal, const Ray& cameraRay)
{
	LinAlgVector matColor{ 3 };
	LinAlgVector refColor{ 3 };
	LinAlgVector difColor{ 3 };
	LinAlgVector spccolor{ 3 };

	difColor = ComputeDiffuseColor(Figures, Lights, currentObject, intPoint, localNormal, BaseColor);

	if (shininess > 0.0)
	{
		spccolor = ComputeSpecular(Figures, Lights, intPoint, localNormal, cameraRay);
	}
	matColor = difColor + spccolor;
	return matColor;
}

//Implementation of model
LinAlgVector SimpleMaterial::ComputeSpecular(const std::vector<std::shared_ptr<Figure>>& Figures, const std::vector<std::shared_ptr<LightBase>>& Lights,
	const LinAlgVector& intPoint, const LinAlgVector& localNormal, const Ray& cameraRay)
{
	LinAlgVector spcColor{ 3 };
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;

	for (auto currentLight : Lights)
	{
		double intensity = 0.0;
		LinAlgVector lightDir = (currentLight->LightLocaction - intPoint).Normalized();

		LinAlgVector startPoint = intPoint + (lightDir * 0.001);

		Ray lightRay(startPoint, startPoint + lightDir);

		LinAlgVector poi{ 3 };
		LinAlgVector poiNormal{ 3 };
		LinAlgVector potColor{ 3 };
		bool validInt = false;
		for (auto sceneObject : Figures)
		{
			validInt = sceneObject->TestIntersections(lightRay, poi, poiNormal, potColor);
			if (validInt)
				break;
		}
		if (!validInt)
		{
			LinAlgVector d = lightRay.ab;
			LinAlgVector r = d - (localNormal * (2 * LinAlgVector::dot(d, localNormal)));
			r.Normalize();

			LinAlgVector v = cameraRay.ab;
			v.Normalize();
			double dotProduct = LinAlgVector::dot(r, v);
			if (dotProduct > 0.0)
			{
				intensity = reflectivity * std::pow(dotProduct, shininess);
			}
		}
		red += currentLight->LightColor.GetElement(0) * intensity;
		green += currentLight->LightColor.GetElement(1) * intensity;
		blue += currentLight->LightColor.GetElement(2) * intensity;
	}
	spcColor[0] = red;
	spcColor[1] = green;
	spcColor[2] = blue;
	
	return spcColor;
}