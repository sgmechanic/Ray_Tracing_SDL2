#include "LinAlgVector.h"
LinAlgVector::LinAlgVector()
{
	Dims = 0;
	Data = std::vector<double>();
}
LinAlgVector::LinAlgVector(int NumDims)
{
	Dims = NumDims;
	Data = std::vector<double>(Dims,0.0);
}
LinAlgVector::LinAlgVector(std::vector<double> InputData)
{
	Dims = InputData.size();
	Data = InputData;
}
LinAlgVector::LinAlgVector(const LinAlgVector& Copy)
{
	Dims = Copy.Dims;
	Data.resize(Copy.Data.size()); // Is it really necessary?????? Should dig about operator = for std::vector
	Data = Copy.Data;
}
LinAlgVector::~LinAlgVector() {};

int LinAlgVector::GetDims() const
{
	return Dims;
}

double& LinAlgVector::operator[](size_t index) {
	return Data[index];
}


double LinAlgVector::norm() const
{
	double sum = 0.0;
	for (int i = 0; i < Dims; ++i)
		sum += (Data.at(i) * Data.at(i));
	return sqrt(sum);
}

LinAlgVector LinAlgVector::Normalized()
{
	double VecNorm = this->norm();
	LinAlgVector result(Data);
	return result * (1.0 / VecNorm);
}

void LinAlgVector::Normalize()
{
	double VecNorm = this->norm();
	if (VecNorm == 0)
	{
		for (int i = 0; i < Dims; ++i)
		{
			Data.at(i) = 0;
		}
	}
	else
	{
		for (int i = 0; i < Dims; ++i)
		{
			double tmp = Data.at(i) * (1.0 / VecNorm);
			Data.at(i) = tmp;
		}
	}
}

LinAlgVector LinAlgVector::operator*(double coef) const
{
	LinAlgVector result{ Dims };
	for (int i = 0; i < Dims; ++i)
		result[i] = (Data.at(i) * coef);
	return result;
}

LinAlgVector LinAlgVector::operator+ (const LinAlgVector& sum) const
{
	if (Dims != sum.Dims)
		throw std::invalid_argument("Vector dimensions do not match.");

	std::vector<double> ResultData;
	for (int i = 0; i < Dims; ++i)
		ResultData.emplace_back(Data.at(i) + sum.Data.at(i));

	LinAlgVector result(ResultData);
	return result;
	/*LinAlgVector result{ Dims };
	for (int i = 0; i < Dims; ++i)
		result[i] = (Data.at(i) * sum.Data.at(i));
	return result;*/
}

LinAlgVector LinAlgVector::operator= (const LinAlgVector& eq)
{
	Dims = eq.Dims;
	Data.resize(eq.Data.size());
	Data = eq.Data;
	return *this;
}


void LinAlgVector::PrintVector() const
{
	for (int i = 0; i < Dims; i++)
		std::cout << Data[i]<<" ";
	std::cout << "\n";
}

LinAlgVector LinAlgVector::operator-(const LinAlgVector& dif) const
{
	if (Dims != dif.Dims)
		throw std::invalid_argument("Vector dimensions do not match.");

	std::vector<double> ResultData;
	for (int i = 0; i < Dims; ++i)
		ResultData.emplace_back(Data.at(i) - dif.Data.at(i));

	LinAlgVector result(ResultData);
	return result;
}

LinAlgVector LinAlgVector::cross(const LinAlgVector& a, const LinAlgVector& b) 
{
	if (a.Dims != b.Dims)
		throw std::invalid_argument("The cross-product is not defined for this input");

	if (a.Dims != 3)
		throw std::invalid_argument("The cross-product is not defined for this input");

	// Compute the cross product.
	/*std::vector<double> ResultData;
	ResultData.emplace_back((a.Data.at(1) * b.Data.at(2)) - (a.Data.at(2) * b.Data.at(1)));
	ResultData.emplace_back(-((a.Data.at(0) * b.Data.at(2)) - (a.Data.at(2) * b.Data.at(0))));
	ResultData.emplace_back((a.Data.at(0) * b.Data.at(1)) - (a.Data.at(1) * b.Data.at(0)));

	LinAlgVector result(ResultData);*/
	LinAlgVector result{ a.Dims };
	result[0] = (a.Data.at(1) * b.Data.at(2)) - (a.Data.at(2) * b.Data.at(1));
	result[1] = (a.Data.at(0) * b.Data.at(2)) - (a.Data.at(2) * b.Data.at(0));
	result[2] = (a.Data.at(0) * b.Data.at(1)) - (a.Data.at(1) * b.Data.at(0));
	return result;
}
double LinAlgVector::dot(const LinAlgVector& a, const LinAlgVector& b)
{
	if (a.Dims != b.Dims)
		throw std::invalid_argument("The dot product is not defined for this input");

	if (a.Dims != 3)
		throw std::invalid_argument("The dot product is not defined for this input");
	double result = 0.0;
	for (int i = 0; i < a.Dims; i++)
	{
		result += a.Data.at(i) * b.Data.at(i);
	}

	return result;
}

double LinAlgVector::GetElement(int index) const
{
	return Data.at(index);
}

//LinAlgVector LinAlgVector::operator*(const LinAlgMatrix& prod) const
//{
//	if (Dims != prod.GetN())
//		throw std::invalid_argument("The Matrix and Vector product is not defined for this input");
//	std::vector<double> ResVect(prod.GetN(), 0);
//	for (int i = 0; i < prod.GetM(); i++) {
//		for (int j = 0; j < prod.GetN(); j++) {
//			ResVect[i] += Data.at(j) * prod.GetElem(i,j);
//		}
//	}
//	return LinAlgVector(ResVect);
//}