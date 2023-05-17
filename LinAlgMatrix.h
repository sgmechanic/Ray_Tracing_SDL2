#ifndef LINALGMATRIX_H
#define LINALGMATRIX_H
#include <stdexcept>
#include <vector>
#include <iostream>
#include <math.h>
#include "LinAlgVector.h"

class LinAlgMatrix {
private:
	std::vector<std::vector<double>> Data;
	int M;//Rows
	int N;//Columns
public:
	void SetData(std::vector<std::vector<double>> Input);
	void CreateMatrix(const int m, const int n);
	LinAlgMatrix();
	LinAlgMatrix(const LinAlgMatrix& copy);
	LinAlgMatrix(const int m, const int n);
	LinAlgMatrix(std::vector<std::vector<double>> InputData);
	~LinAlgMatrix();

	LinAlgMatrix& operator=(const LinAlgMatrix& eq);
	bool operator!=(const LinAlgMatrix& eq);

	int GetM() const;
	int GetN() const;

	//double Determinant();

	bool Join(const LinAlgMatrix& matrix2);
	void PrintMatrix();
	bool SimpleInverse();


	LinAlgMatrix Transpose() const;

	LinAlgMatrix operator+ (const LinAlgMatrix& sum) const;
	LinAlgMatrix operator- (const LinAlgMatrix& dif) const;
	LinAlgMatrix operator* (const LinAlgMatrix& prod) const;
	LinAlgVector operator*(const LinAlgVector& prod) const;
	double& Elem(size_t i,size_t j);

	double GetElem(int i, int j) const;

	static LinAlgMatrix MatrixProduct(const LinAlgMatrix& a, const LinAlgMatrix& b);

	int FindRowWithMaxElem(int ColNumber, int StartingRow) const;


	void CleanMatrix();
	void CleanAndResize(int m, int n);
	void SwapRow(int first, int second);
	void MultRow(int NumRow, double Factor);
	void MultAdd(int i, int j, double MultFactor);
	bool Separate(LinAlgMatrix& Matrix1, LinAlgMatrix& Matrix2, int ColNum);
	bool IsIdentityMatrix();
	void SetToIdentity();
};

#endif