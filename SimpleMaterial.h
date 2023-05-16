#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H
#include "MaterialBase.h"
class SimpleMaterial : public MaterialBase
{
public:
	SimpleMaterial();
	virtual ~SimpleMaterial() override;

	virtual LinAlgVector ComputeColor(const std::vector<std::shared_ptr<Figure>>& Figures, const std::vector<std::shared_ptr<LightBase>>& Lights,
		const std::shared_ptr<Figure>& currentObject, const LinAlgVector& intPoint, const LinAlgVector& localNormal, const Ray& cameraRay) override;
	LinAlgVector ComputeSpecular(const std::vector<std::shared_ptr<Figure>>& Figures, const std::vector<std::shared_ptr<LightBase>>& Lights,
		const LinAlgVector& intPoint, const LinAlgVector& localNormal, const Ray& cameraRay);


		LinAlgVector BaseColor {std::vector<double> {1.0, 1.0, 1.0}};
		double reflectivity = 0.0;
		double shininess = 0.0;
};





#endif

