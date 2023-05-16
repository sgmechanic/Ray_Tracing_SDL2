#include "LightBase.h"

LightBase::LightBase()
{

}

LightBase::~LightBase()
{

}

bool LightBase::ComputeIllumination(const LinAlgVector& IntPoint, const LinAlgVector& LocalNormal, const std::vector<std::shared_ptr<Figure>>& Figures,
	const std::shared_ptr<Figure>& CurrentFigure, LinAlgVector& color, double& intensity)
{
	return false;
}