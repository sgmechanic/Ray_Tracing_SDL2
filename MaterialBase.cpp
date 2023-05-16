

#include "MaterialBase.h"
#include <omp.h>
// Constructor / destructor.
MaterialBase::MaterialBase()
{
//m_maxReflectionRays = 3;
	//m_reflectionRayCount = 0;
}
//
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
//	// Define an initial material color.
	LinAlgVector matColor{ 3 };
//
	return matColor;
}
//
// Function to compute the diffuse color.
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


//
//// Function to compute the color due to reflection.
//LinAlgVector MaterialBase::ComputeReflectionColor(const std::vector<std::shared_ptr<Figure>>& objectList,
//	const std::vector<std::shared_ptr<LightBase>>& lightList,
//	const std::shared_ptr<Figure>& currentObject,
//	const LinAlgVector& intPoint, const LinAlgVector& localNormal,
//	const Ray& incidentRay)
//{
//	LinAlgVector reflectionColor{ 3 };
//
//	// Compute the reflection vector.
//	LinAlgVector d = incidentRay.ab;
//	LinAlgVector reflectionVector = d - (localNormal*2 * LinAlgVector::dot(d, localNormal));
//
//	// Construct the reflection ray.
//	Ray reflectionRay(intPoint, intPoint + reflectionVector);
//
//	/* Cast this ray into the scene and find the closest object that it intersects with. */
//	std::shared_ptr<Figure> closestObject;
//	LinAlgVector closestIntPoint{ 3 };
//	LinAlgVector closestLocalNormal{ 3 };
//	LinAlgVector closestLocalColor{ 3 };
//	bool intersectionFound = CastRay(reflectionRay, objectList, currentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
//
//	/* Compute illumination for closest object assuming that there was a
//		valid intersection. */
//	LinAlgVector matColor{ 3 };
//	if ((intersectionFound) && (m_reflectionRayCount < m_maxReflectionRays))
//	{
//		// Increment the reflectionRayCount.
//		m_reflectionRayCount++;
//
//		// Check if a material has been assigned.
//		if (closestObject->FigureHasMaterial)
//		{
//			// Use the material to compute the color.
//			matColor = closestObject->Material->ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, reflectionRay);
//		}
//		else
//		{
//			matColor = MaterialBase::ComputeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->BaseColor);
//		}
//	}
//	else
//	{
//		// Leave matColor as it is.
//	}
//
//	reflectionColor = matColor;
//	return reflectionColor;
//}
//
//// Function to cast a ray into the scene.
//bool MaterialBase::CastRay(const Ray& castRay, const std::vector<std::shared_ptr<Figure>>& objectList,
//	const std::shared_ptr<Figure>& thisObject,
//	std::shared_ptr<Figure>& closestObject,
//	LinAlgVector& closestIntPoint, LinAlgVector& closestLocalNormal,
//	LinAlgVector& closestLocalColor)
//{
//	// Test for intersections with all of the objects in the scene.
//	LinAlgVector intPoint{ 3 };
//	LinAlgVector localNormal{ 3 };
//	LinAlgVector localColor{ 3 };
//
//	double minDist = 1e6;
//	bool intersectionFound = false;
//	for (auto currentObject : objectList)
//	{
//		if (currentObject != thisObject)
//		{
//			bool validInt = currentObject->TestIntersections(castRay, intPoint, localNormal, localColor);
//
//			// If we have a valid intersection.
//			if (validInt)
//			{
//				// Set the flag to show that we found an intersection.
//				intersectionFound = true;
//
//				// Compute the distance between the source and the intersection point.
//				double dist = (intPoint - castRay.point1).norm();
//
//				// Store a reference to this object if it is the closest.
//				if (dist < minDist)
//				{
//					minDist = dist;
//					closestObject = currentObject;
//					closestIntPoint = intPoint;
//					closestLocalNormal = localNormal;
//					closestLocalColor = localColor;
//				}
//			}
//		}
//	}
//
//	return intersectionFound;
//}
//
//
//
//
//
//
