#ifndef LINALGMATRIX_H
#define LINALGMATRIX_H
#include <stdexcept>
//#include "Header.h"
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
	//double GetElement(int index) const;
	//void SetElement(int index, double value); insteal let's use operator[] with double&

	double Determinant(); //Not needed?

	//LinAlgMatrix Inversed();
	bool Join(const LinAlgMatrix& matrix2);
	bool Inverse(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SOMETHING IS WRONG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
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
	//static double dot(const LinAlgVector& a, const LinAlgVector& b);

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