//class Figure;
//class LinAlgMatrix;
#ifndef GTFORM_H
#define GTFORM_H
#include "LinAlgMatrix.h"
#include "Ray.h"
#include "LinAlgVector.h"
//#include "Figure.h"

constexpr bool FWDTFORM = true;
constexpr bool BCKTFORM = false;

class GTform
{
public:
	GTform();
	GTform(const LinAlgVector& Translation, const LinAlgVector& Rotation, const LinAlgVector& Scale);
	~GTform();

	GTform(const LinAlgMatrix& fwd, const LinAlgMatrix& bck);

	void SetTransform(const LinAlgVector& Translation, const LinAlgVector& Rotation, const LinAlgVector& Scale);

	LinAlgMatrix GetForward();
	LinAlgMatrix GetBackward();

	Ray Apply(const Ray& InputRay, bool DirFlag);
	LinAlgVector Apply(const LinAlgVector& InputVector, bool DirFlag);
	LinAlgVector ApplyNorm(const LinAlgVector& inputVector);

	friend GTform operator* (const GTform& lhs, const GTform& rhs);

	GTform operator= (const GTform& rhs);

	void PrintTransform(bool DirFlag);

	void Print(const LinAlgMatrix& matrix);

	void ExtractLinearTransform();

	static void PrintVector(const LinAlgVector& vector);
//
private:
	LinAlgMatrix FwdTfm{ 4,4 };
	LinAlgMatrix BckTfm{ 4,4 };
	LinAlgMatrix LinTfm{ 3,3 };
};

#endif