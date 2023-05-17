#ifndef MATERIALBASE_H
#define MATERIALBASE_H
#include <memory>
#include "Figure.h"
#include "LightBase.h"
#include "LinAlgVector.h"
#include "Ray.h"

	class MaterialBase
	{
	public:
		MaterialBase();
		virtual ~MaterialBase();

		// Return the color of the material
		virtual LinAlgVector ComputeColor(const std::vector<std::shared_ptr<Figure>>& objectList,
			const std::vector<std::shared_ptr<LightBase>>& lightList,
		const std::shared_ptr<Figure>& currentObject,
			const LinAlgVector& intPoint, const LinAlgVector& localNormal,
			const Ray& cameraRay);

		// Compute diffuse color.
		static LinAlgVector ComputeDiffuseColor(const std::vector<std::shared_ptr<Figure>>& objectList,
			const std::vector<std::shared_ptr<LightBase>>& lightList,
			const std::shared_ptr<Figure>& currentObject,
			const LinAlgVector& intPoint, const LinAlgVector& localNormal,
			const LinAlgVector& baseColor);

	bool CastRay(const Ray& castRay, const std::vector<std::shared_ptr<Figure>>& objectList,
		const std::shared_ptr<Figure>& thisObject,
			std::shared_ptr<Figure>& closestObject,
			LinAlgVector& closestIntPoint, LinAlgVector& closestLocalNormal,
			LinAlgVector& closestLocalColor);

	public:
		 //Don't use it at the moment
		 static int m_maxReflectionRays;
		 static int m_reflectionRayCount;

};
#endif