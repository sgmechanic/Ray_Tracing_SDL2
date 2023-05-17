#include "LinAlgMatrix.h"
#include "Calc.h"
void LinAlgMatrix::SetData(std::vector<std::vector<double>> Input) //Function to configure Data
{
	if (Input.size() == 0)
		throw std::invalid_argument("It's not a matrix. Wrong Input");
	for (auto CurrentRow: Input)
		if (CurrentRow.size() == 0)
			throw std::invalid_argument("It's not a matrix. Wrong Input");
	Data.clear();
	Data = Input;
}
void LinAlgMatrix::CreateMatrix(const int m, const int n) //Creation of empty m*n matrix
{
	if ( m < 1)
		throw std::invalid_argument("It's not a matrix. Wrong Input");
	if (n < 1)
		throw std::invalid_argument("It's not a matrix. Wrong Input");
	M = m;
	N = n;
	Data.resize(M);
	for (int i = 0; i < M; i++)
		Data.at(i) = std::vector<double>(N, 0);
}

LinAlgMatrix::LinAlgMatrix(const int m, const int n) //Empty m*n matrix
{
	CreateMatrix(m, n);
}

LinAlgMatrix::LinAlgMatrix(const LinAlgMatrix& copy)
{
	M = copy.M;
	N = copy.N;
	Data = copy.Data;
}

LinAlgMatrix& LinAlgMatrix::operator=(const LinAlgMatrix& eq)
{
	M = eq.M;
	N = eq.N;
	Data = eq.Data;
	return *this;
}

void LinAlgMatrix::PrintMatrix()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			std::cout << Data.at(i).at(j) << " ";
		std::cout << '\n';
	}
	std::cout << '\n';
		
}

LinAlgMatrix LinAlgMatrix::Transpose() const
{
	LinAlgMatrix Copy{N,M};
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			Copy.Data.at(i).at(j) = Data.at(j).at(i);
	}
	return Copy;
}

LinAlgMatrix::LinAlgMatrix() // Creates Unitary 4*4 matrix
{
	CreateMatrix(4, 4);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j)
				Data.at(i).at(j) = 1;
}
LinAlgMatrix::LinAlgMatrix(std::vector<std::vector<double>> InputData) // Creates matrix from given data
{
	M = (int)InputData.size();
	N = (int)InputData.at(0).size();
	SetData(InputData);
}
LinAlgMatrix::~LinAlgMatrix() {};

int LinAlgMatrix::GetM() const
{
	return M;
}

int LinAlgMatrix::GetN() const
{
	return N;
}


double& LinAlgMatrix::Elem(size_t i, size_t j) {
	return Data.at(i).at(j);
}

double LinAlgMatrix::GetElem(int i, int j) const {
	return Data.at(i).at(j);
}


bool LinAlgMatrix::Join(const LinAlgMatrix& matrix2)
{
	int numRows1 = M;
	int numRows2 = matrix2.M;
	int numCols1 = N;
	int numCols2 = matrix2.N;

	// If the matrices have different numbers of rows, then this operation makes no sense.
	if (numRows1 != numRows2)
		throw std::invalid_argument("Attempt to join matrices with different numbers of rows is invalid.");


	std::vector<double> MatrixData(numCols1 * numRows1, 0);
	int k = 0;
	for (int i = 0; i < numRows1; i++)
	{
		for (int j = 0; j < numCols1; j++)
		{
			MatrixData.at(k) = Data.at(i).at(j);
			k++;
		}
	}
	std::vector<double> Matrix2Data(numRows2 * numCols2, 0);
	int k2 = 0;
	for (int i = 0; i < numRows2; i++)
	{
		for (int j = 0; j < numCols2; j++)
		{
			Matrix2Data.at(k2) = matrix2.Data.at(i).at(j);
			k2++;
		}
	}
	std::vector<double> newMatrixData(numRows1 * (numCols1 + numCols2), 0);
	int linearIndex, resultLinearIndex;
	for (int i = 0; i < numRows1; ++i)
	{
		for (int j = 0; j < (numCols1 + numCols2); ++j)
		{
			resultLinearIndex = (i * (numCols1 + numCols2)) + j;

			if (j < numCols1)
			{
				linearIndex = (i * numCols1) + j;
				newMatrixData[resultLinearIndex] = MatrixData[linearIndex];
			}
			else
			{
				linearIndex = (i * numCols2) + (j - numCols1);
				newMatrixData[resultLinearIndex] = Matrix2Data[linearIndex];
			}
		}
	}

	N = numCols1 + numCols2;
	for (int i = 0; i < M; i++)
		Data.at(i).resize(N);
	int k3 = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Data.at(i).at(j) = newMatrixData.at(k3);
			k3++;
		}
	}
	return true;
}


bool LinAlgMatrix::Separate(LinAlgMatrix& Matrix1, LinAlgMatrix& Matrix2, int ColNum)
{
	int NumRows = M;
	int NumCols1 = ColNum;
	int NumCols2 = N - ColNum;
	Matrix1.CleanAndResize(NumRows, NumCols1);
	Matrix1.CleanAndResize(NumRows, NumCols2);
	for (int row = 0; row < M; row++)
		for (int col = 0; col < N; col++)
		{
			if (col < ColNum)
				Matrix1.Elem(row, col) = this->Elem(row, col);
			else
				Matrix2.Elem(row, col-ColNum) = this->Elem(row, col);
		}
	return true;
}

bool LinAlgMatrix::IsIdentityMatrix()
{
	if (M != N)
	{
		std::cout << "Not a square matrix!";
		return false;
	}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if ((Data.at(i).at(j) !=0 && i!=j) || (Data.at(i).at(j)!=1 && i == j))
				return false;
	return true;
}

bool LinAlgMatrix::operator!=(const LinAlgMatrix& eq)
{
	if ((M != eq.M) || (N!=eq.N))
	{
		return false;
	}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (Data.at(i).at(j) != eq.Data.at(i).at(j))
				return false;
	return true;
}

void LinAlgMatrix::SetToIdentity()
{
	if (M != N)
	{
		throw std::invalid_argument("Not a square matrix!");
	}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (i == j)
				Data.at(i).at(j) = 1;
			else
				Data.at(i).at(j) = 0;
}

void LinAlgMatrix::CleanMatrix()
{
	for (int i = 0; i < Data.size(); i++)
		Data.at(i).resize(0);
	Data.resize(0);
	M = 0;
	N = 0;
}

void LinAlgMatrix::CleanAndResize(int m, int n)
{
	this->CleanMatrix();
	CreateMatrix(m, n);
}

void LinAlgMatrix::MultAdd(int i, int j, double MultFactor)
{
	for (int k = 0; k < N; k++)
		Data.at(i).at(k) += Data.at(j).at(k) * MultFactor;
}


LinAlgMatrix LinAlgMatrix::operator*(const LinAlgMatrix& prod) const
{
	if (N != prod.M)
		throw std::invalid_argument("The Matrixproduct is not defined for this input");
	LinAlgMatrix ResultMatrix(std::vector<std::vector<double>>(M, std::vector<double>(prod.N, 0)));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < prod.N; j++) {
			ResultMatrix.Data.at(i).at(j) = 0;

			for (int k = 0; k < prod.M; k++) {
				ResultMatrix.Data.at(i).at(j) += Data.at(i).at(k) * prod.Data.at(k).at(j);
			}
		}
	}
	return ResultMatrix;
}

LinAlgVector LinAlgMatrix::operator*(const LinAlgVector& prod) const
{
	if (N != prod.GetDims())
		throw std::invalid_argument("The Matrix and Vector product is not defined for this input");
	//std::vector<double> ResVect(GetM(), 0);
	LinAlgVector result{ GetM() };
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
				result[i] += prod.GetElement(j) * Data.at(i).at(j);
			}
		}
	return result;
	//return LinAlgVector(ResVect);
}

LinAlgMatrix LinAlgMatrix::operator+(const LinAlgMatrix& sum) const
{
	if (M != sum.N || N!= sum.N) 
		throw std::invalid_argument("Matrix dimensions do not match.");

	LinAlgMatrix ResultData(M,N);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
				ResultData.Data.at(i).at(j) = Data.at(i).at(j) + sum.Data.at(i).at(j);
	return ResultData;
}


LinAlgMatrix LinAlgMatrix::operator-(const LinAlgMatrix& dif) const
{
	if (M != dif.N || N != dif.N)
		throw std::invalid_argument("Matrix dimensions do not match.");

	LinAlgMatrix ResultData(M, N);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			ResultData.Data.at(i).at(j) = Data.at(i).at(j) - dif.Data.at(i).at(j);
	return ResultData;
}

LinAlgMatrix LinAlgMatrix::MatrixProduct(const LinAlgMatrix& a, const LinAlgMatrix& b)
{
	if (a.N != b.M)
		throw std::invalid_argument("The Matrixproduct is not defined for this input");
	LinAlgMatrix ResultMatrix(std::vector<std::vector<double>>(a.M, std::vector<double>(b.N, 0)));
	for (int i = 0; i < a.M; i++) {
		for (int j = 0; j < b.N; j++) {
			ResultMatrix.Data.at(i).at(j) = 0;

			for (int k = 0; k < b.M; k++) {
				ResultMatrix.Data.at(i).at(j) += a.Data.at(i).at(k) * b.Data.at(k).at(j);
			}
		}
	}
	return ResultMatrix;
}


//Couple of functions that we may need in the future for solving linear systems
int LinAlgMatrix::FindRowWithMaxElem(int ColNumber, int StartingRow) const
{
	double MaxElem = Data.at(StartingRow).at(ColNumber);
	int IndexOfRaw = StartingRow;
	for (int i = StartingRow + 1; i < M; i++)
	{
		double cur = Data.at(i).at(ColNumber);
		if (cur > MaxElem)
		{
			MaxElem = Data.at(i).at(ColNumber);
			IndexOfRaw = i;
		}
	}
	return IndexOfRaw;
}

void LinAlgMatrix::SwapRow(int first, int second) 
{
	std::vector<double> tmp = Data.at(first);
	Data.at(first) = Data.at(second);
	Data.at(second) = tmp;
}

void LinAlgMatrix::MultRow(int NumRow, double Factor)
{
	for (int j = 0; j < N; j++)
		Data.at(NumRow).at(j) *= Factor;
}

//I didn't expect that, but this simple implementation is stable and shows best performance
bool LinAlgMatrix::SimpleInverse()
{
	if (M == N && M == 3)
	{
		LinAlgMatrix Copy = *this;
		double determinant = +Elem(0, 0) * (Elem(1, 1) * Elem(2, 2) - Elem(2, 1) * Elem(1, 2))
			- Elem(0, 1) * (Elem(1, 0) * Elem(2, 2) - Elem(1, 2) * Elem(2, 0))
			+ Elem(0, 2) * (Elem(1, 0) * Elem(2, 1) - Elem(1, 1) * Elem(2, 0));
		if (CloseEnough(determinant, 0.0))
			throw std::invalid_argument("Matrix is non-singular!");
		double invdet = 1 / determinant;
		Elem(0, 0) = (Copy.Elem(1, 1) * Copy.Elem(2, 2) - Copy.Elem(2, 1) * Copy.Elem(1, 2)) * invdet;
		Elem(1, 0) = -(Copy.Elem(0, 1) * Copy.Elem(2, 2) - Copy.Elem(0, 2) * Copy.Elem(2, 1)) * invdet;
		Elem(2, 0) = (Copy.Elem(0, 1) * Copy.Elem(1, 2) - Copy.Elem(0, 2) * Copy.Elem(1, 1)) * invdet;
		Elem(0, 1) = -(Copy.Elem(1, 0) * Copy.Elem(2, 2) - Copy.Elem(1, 2) * Copy.Elem(2, 0)) * invdet;
		Elem(1, 1) = (Copy.Elem(0, 0) * Copy.Elem(2, 2) - Copy.Elem(0, 2) * Copy.Elem(2, 0)) * invdet;
		Elem(2, 1) = -(Copy.Elem(0, 0) * Copy.Elem(1, 2) - Copy.Elem(1, 0) * Copy.Elem(0, 2)) * invdet;
		Elem(0, 2) = (Copy.Elem(1, 0) * Copy.Elem(2, 1) - Copy.Elem(2, 0) * Copy.Elem(1, 1)) * invdet;
		Elem(1, 2) = -(Copy.Elem(0, 0) * Copy.Elem(2, 1) - Copy.Elem(2, 0) * Copy.Elem(0, 1)) * invdet;
		Elem(2, 2) = (Copy.Elem(0, 0) * Copy.Elem(1, 1) - Copy.Elem(1, 0) * Copy.Elem(0, 1)) * invdet;

		return true;
	}
	else
	{
			LinAlgMatrix Copy = *this;
			double A2323 = Copy.Elem(2, 2) * Copy.Elem(3, 3) - Copy.Elem(2, 3) * Copy.Elem(3, 2);
			double A1323 = Copy.Elem(2, 1) * Copy.Elem(3, 3) - Copy.Elem(2, 3) * Copy.Elem(3, 1);
			double A1223 = Copy.Elem(2, 1) * Copy.Elem(3, 2) - Copy.Elem(2, 2) * Copy.Elem(3, 1);
			double A0323 = Copy.Elem(2, 0) * Copy.Elem(3, 3) - Copy.Elem(2, 3) * Copy.Elem(3, 0);
			double A0223 = Copy.Elem(2, 0) * Copy.Elem(3, 2) - Copy.Elem(2, 2) * Copy.Elem(3, 0);
			double A0123 = Copy.Elem(2, 0) * Copy.Elem(3, 1) - Copy.Elem(2, 1) * Copy.Elem(3, 0);
			double A2313 = Copy.Elem(1, 2) * Copy.Elem(3, 3) - Copy.Elem(1, 3) * Copy.Elem(3, 2);
			double A1313 = Copy.Elem(1, 1) * Copy.Elem(3, 3) - Copy.Elem(1, 3) * Copy.Elem(3, 1);
			double A1213 = Copy.Elem(1, 1) * Copy.Elem(3, 2) - Copy.Elem(1, 2) * Copy.Elem(3, 1);
			double A2312 = Copy.Elem(1, 2) * Copy.Elem(2, 3) - Copy.Elem(1, 3) * Copy.Elem(2, 2);
			double A1312 = Copy.Elem(1, 1) * Copy.Elem(2, 3) - Copy.Elem(1, 3) * Copy.Elem(2, 1);
			double A1212 = Copy.Elem(1, 1) * Copy.Elem(2, 2) - Copy.Elem(1, 2) * Copy.Elem(2, 1);
			double A0313 = Copy.Elem(1, 0) * Copy.Elem(3, 3) - Copy.Elem(1, 3) * Copy.Elem(3, 0);
			double A0213 = Copy.Elem(1, 0) * Copy.Elem(3, 2) - Copy.Elem(1, 2) * Copy.Elem(3, 0);
			double A0312 = Copy.Elem(1, 0) * Copy.Elem(2, 3) - Copy.Elem(1, 3) * Copy.Elem(2, 0);
			double A0212 = Copy.Elem(1, 0) * Copy.Elem(2, 2) - Copy.Elem(1, 2) * Copy.Elem(2, 0);
			double A0113 = Copy.Elem(1, 0) * Copy.Elem(3, 1) - Copy.Elem(1, 1) * Copy.Elem(3, 0);
			double A0112 = Copy.Elem(1, 0) * Copy.Elem(2, 1) - Copy.Elem(1, 1) * Copy.Elem(2, 0);

			double determinant = Copy.Elem(0, 0) * (Copy.Elem(1, 1) * A2323 - Copy.Elem(1, 2) * A1323 + Copy.Elem(1, 3) * A1223)
				- Copy.Elem(0, 1) * (Copy.Elem(1, 0) * A2323 - Copy.Elem(1, 2) * A0323 + Copy.Elem(1, 3) * A0223)
				+ Copy.Elem(0, 2) * (Copy.Elem(1, 0) * A1323 - Copy.Elem(1, 1) * A0323 + Copy.Elem(1, 3) * A0123)
				- Copy.Elem(0, 3) * (Copy.Elem(1, 0) * A1223 - Copy.Elem(1, 1) * A0223 + Copy.Elem(1, 2) * A0123);
			if (CloseEnough(determinant, 0.0))
				throw std::invalid_argument("Matrix is non-singular!");

			determinant = 1 / determinant;

			Elem(0, 0) = determinant * (Copy.Elem(1, 1) * A2323 - Copy.Elem(1, 2) * A1323 + Copy.Elem(1, 3) * A1223);
			Elem(0, 1) = determinant * -(Copy.Elem(0, 1) * A2323 - Copy.Elem(0, 2) * A1323 + Copy.Elem(0, 3) * A1223);
			Elem(0, 2) = determinant * (Copy.Elem(0, 1) * A2313 - Copy.Elem(0, 2) * A1313 + Copy.Elem(0, 3) * A1213);
			Elem(0, 3) = determinant * -(Copy.Elem(0, 1) * A2312 - Copy.Elem(0, 2) * A1312 + Copy.Elem(0, 3) * A1212);
			Elem(1, 0) = determinant * -(Copy.Elem(1, 0) * A2323 - Copy.Elem(1, 2) * A0323 + Copy.Elem(1, 3) * A0223);
			Elem(1, 1) = determinant * (Copy.Elem(0, 0) * A2323 - Copy.Elem(0, 2) * A0323 + Copy.Elem(0, 3) * A0223);
			Elem(1, 2) = determinant * -(Copy.Elem(0, 0) * A2313 - Copy.Elem(0, 2) * A0313 + Copy.Elem(0, 3) * A0213);
			Elem(1, 3) = determinant * (Copy.Elem(0, 0) * A2312 - Copy.Elem(0, 2) * A0312 + Copy.Elem(0, 3) * A0212);
			Elem(2, 0) = determinant * (Copy.Elem(1, 0) * A1323 - Copy.Elem(1, 1) * A0323 + Copy.Elem(1, 3) * A0123);
			Elem(2, 1) = determinant * -(Copy.Elem(0, 0) * A1323 - Copy.Elem(0, 1) * A0323 + Copy.Elem(0, 3) * A0123);
			Elem(2, 2) = determinant * (Copy.Elem(0, 0) * A1313 - Copy.Elem(0, 1) * A0313 + Copy.Elem(0, 3) * A0113);
			Elem(2, 3) = determinant * -(Copy.Elem(0, 0) * A1312 - Copy.Elem(0, 1) * A0312 + Copy.Elem(0, 3) * A0112);
			Elem(3, 0) = determinant * -(Copy.Elem(1, 0) * A1223 - Copy.Elem(1, 1) * A0223 + Copy.Elem(1, 2) * A0123);
			Elem(3, 1) = determinant * (Copy.Elem(0, 0) * A1223 - Copy.Elem(0, 1) * A0223 + Copy.Elem(0, 2) * A0123);
			Elem(3, 2) = determinant * -(Copy.Elem(0, 0) * A1213 - Copy.Elem(0, 1) * A0213 + Copy.Elem(0, 2) * A0113);
			Elem(3, 3) = determinant * (Copy.Elem(0, 0) * A1212 - Copy.Elem(0, 1) * A0212 + Copy.Elem(0, 2) * A0112);
			return true;
		}
}