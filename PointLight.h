#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "LightBase.h"
class PointLight : public LightBase
{
public:
	PointLight();

	virtual ~PointLight() override;

	virtual bool ComputeIllumination(const LinAlgVector& IntPoint, const LinAlgVector& LocalNormal, const std::vector<std::shared_ptr<Figure>>& Figures,
		const std::shared_ptr<Figure>& CurrentFigure, LinAlgVector& color, double& intensity) override;


};
#endif