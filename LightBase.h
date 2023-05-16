#pragma once
#ifndef LIGHTBASE_H
#define LIGHTBASE_H
#include "LinAlgVector.h"
#include "Ray.h"
#include "Figure.h"

class LightBase
{
public:
	LightBase();
	virtual ~LightBase();

	virtual bool ComputeIllumination(const LinAlgVector& IntPoint, const LinAlgVector& LocalNormal, const std::vector<std::shared_ptr<Figure>>& Figures,
		const std::shared_ptr<Figure>& CurrentFigure, LinAlgVector& color, double& intensity);
	LinAlgVector LightColor{ 3 };
	LinAlgVector LightLocaction{ 3 };
	double LightIntensity;
};
#endif