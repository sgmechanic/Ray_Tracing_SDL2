#ifndef BOX_H
#define BOX_H
#include "Figure.h"
#include <array>
class Box : public Figure
{
public:
	Box();
	virtual ~Box() override;

	virtual bool TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor) override;

private:
	std::array<double, 6> t;
	std::array<double, 6> u;
	std::array<double, 6> v;
};



#endif
