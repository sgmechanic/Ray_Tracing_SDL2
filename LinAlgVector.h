#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include <vector>
#include <iostream>
#include <math.h>
class LinAlgVector{
private:
	std::vector<double> Data;
	int Dims;
public:
	LinAlgVector();
	LinAlgVector(int NumDims);
	LinAlgVector(std::vector<double> InputData);
	LinAlgVector(const LinAlgVector& Copy);
	~LinAlgVector();

	int GetDims() const;
	double GetElement(int index) const;

	double norm() const ;

	LinAlgVector Normalized();
	void Normalize();
	void PrintVector() const;

	LinAlgVector operator+ (const LinAlgVector& sum) const;
	LinAlgVector operator- (const LinAlgVector& dif) const;
	LinAlgVector operator* (double coef) const;
	LinAlgVector operator= (const LinAlgVector& eq);
	double& operator[](size_t index);

	static LinAlgVector cross(const LinAlgVector& a, const LinAlgVector& b);
	static double dot(const LinAlgVector& a, const LinAlgVector& b);
};
#endif