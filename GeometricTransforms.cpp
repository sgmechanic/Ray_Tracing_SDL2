#include "GeometricTransforms.h"
GTform::GTform()
{
	FwdTfm.SetToIdentity();
	BckTfm.SetToIdentity();
}
//
GTform::~GTform()
{

}
////
GTform::GTform(const LinAlgMatrix& fwd, const LinAlgMatrix& bck)
{
	if (fwd.GetM() != 4 || fwd.GetN() != 4 || bck.GetM() != 4 || bck.GetN() != 4)
		throw std::invalid_argument("Can't construct GTform, wrong dimensions");
	FwdTfm = fwd;
	BckTfm = bck;
}
GTform::GTform(const LinAlgVector& Translation, const LinAlgVector& Rotation, const LinAlgVector& Scale)
{
	SetTransform(Translation, Rotation, Scale);
	ExtractLinearTransform();
}
//
void GTform::SetTransform(const LinAlgVector& Translation, const LinAlgVector& Rotation, const LinAlgVector& Scale)
{
	LinAlgMatrix TranslationMatrix(4,4);
	LinAlgMatrix RotationMatrixX(4, 4);
	LinAlgMatrix RotationMatrixY(4, 4);
	LinAlgMatrix RotationMatrixZ(4, 4);
	LinAlgMatrix ScaleMatrix(4, 4);

	TranslationMatrix.SetToIdentity();
	RotationMatrixX.SetToIdentity();
	RotationMatrixY.SetToIdentity();
	RotationMatrixY.SetToIdentity();
	RotationMatrixZ.SetToIdentity();
	ScaleMatrix.SetToIdentity();

	TranslationMatrix.Elem(0, 3) = Translation.GetElement(0);
	TranslationMatrix.Elem(1, 3) = Translation.GetElement(1);
	TranslationMatrix.Elem(2, 3) = Translation.GetElement(2);


	RotationMatrixZ.Elem(0, 0) = cos(Rotation.GetElement(2));
	RotationMatrixZ.Elem(0, 1) = -sin(Rotation.GetElement(2));
	RotationMatrixZ.Elem(1, 0) = sin(Rotation.GetElement(2));
	RotationMatrixZ.Elem(1, 1) = cos(Rotation.GetElement(2));

	RotationMatrixY.Elem(0, 0) = cos(Rotation.GetElement(1));
	RotationMatrixY.Elem(0, 2) = -sin(Rotation.GetElement(1));
	RotationMatrixY.Elem(2, 0) = sin(Rotation.GetElement(1));
	RotationMatrixY.Elem(2, 2) = cos(Rotation.GetElement(1));


	RotationMatrixX.Elem(1, 1) = cos(Rotation.GetElement(0));
	RotationMatrixX.Elem(1, 2) = -sin(Rotation.GetElement(0));
	RotationMatrixX.Elem(2, 1) = sin(Rotation.GetElement(0));
	RotationMatrixX.Elem(2, 2) = cos(Rotation.GetElement(0));


	ScaleMatrix.Elem(0, 0) = Scale.GetElement(0);
	ScaleMatrix.Elem(1, 1) = Scale.GetElement(1);
	ScaleMatrix.Elem(2, 2) = Scale.GetElement(2);


	FwdTfm = TranslationMatrix*ScaleMatrix *RotationMatrixX * RotationMatrixY * RotationMatrixZ;

	BckTfm = FwdTfm;
	BckTfm.SimpleInverse();

	//LinTfm = 

	ExtractLinearTransform();
	//LinTfm.PrintMatrix();
}

LinAlgMatrix GTform::GetForward(){
	return FwdTfm;
}

LinAlgMatrix GTform::GetBackward()
{
	return BckTfm;
}

Ray GTform::Apply(const Ray& InputRay, bool DirFlag) 
{
	Ray OutputRay;
	if (DirFlag)
	{
		OutputRay.point1 = this->Apply(InputRay.point1, FWDTFORM);
		OutputRay.point2 = this->Apply(InputRay.point2, FWDTFORM);
		OutputRay.ab = OutputRay.point2 - OutputRay.point1;

	}
	else
	{
		OutputRay.point1 = this->Apply(InputRay.point1, BCKTFORM);
		OutputRay.point2 = this->Apply(InputRay.point2, BCKTFORM);
		OutputRay.ab = OutputRay.point2 - OutputRay.point1;
	}

	return OutputRay;
}

LinAlgVector GTform::Apply(const LinAlgVector& InputVector, bool DirFlag)
{
	std::vector<double> TempData{ InputVector.GetElement(0), InputVector.GetElement(1), InputVector.GetElement(2), 1.0 };
	LinAlgVector TempVector(TempData);
	LinAlgVector ResultVector;
	if (DirFlag)
	{
		ResultVector = FwdTfm*TempVector;
	}
	else
	{
		ResultVector = BckTfm * TempVector;
	}
	LinAlgVector OutputVector(std::vector<double>{ResultVector.GetElement(0), ResultVector.GetElement(1), ResultVector.GetElement(2)});
	return OutputVector;
}

GTform operator*(const GTform& lhs, const GTform& rhs)
{
	LinAlgMatrix FwdResult = lhs.FwdTfm * rhs.FwdTfm;
	LinAlgMatrix BckResult = FwdResult;
	BckResult.SimpleInverse();
	GTform FinalResult(FwdResult, BckResult);
	return FinalResult;
}

GTform GTform::operator=(const GTform& rhs)
{
	if (this != &rhs)
	{
		FwdTfm = rhs.FwdTfm;
		BckTfm = rhs.BckTfm;
		LinTfm = rhs.LinTfm;
	}
	return *this;
}

void GTform::PrintTransform(bool DirFlag)
{
	if (DirFlag)
		FwdTfm.PrintMatrix();
	else
		BckTfm.PrintMatrix();
}

void GTform::Print(const LinAlgMatrix& matrix)
{
	int nRows = matrix.GetM();
	int nCols = matrix.GetN();
	for (int row = 0; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
			std::cout << matrix.GetElem(row, col);
		std::cout << "\n";
	}
}

void GTform::PrintVector(const LinAlgVector& InputVector)
{
	int nRows = InputVector.GetDims();
	for (int row = 0; row < nRows; row++)
		std::cout << InputVector.GetElement(row) << "\n";
}


LinAlgVector GTform::ApplyNorm(const LinAlgVector& inputVector)
{

	// Apply the transform and return the result.
	//ExtractLinearTransform();
	//LinTfm.PrintMatrix();
	//LinTfm.PrintMatrix();
	LinAlgVector result = LinTfm * inputVector;
	return result;
}

void GTform::ExtractLinearTransform()
{
	// Copy the linear portion of the transform.
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			LinTfm.Elem(i, j) =  FwdTfm.Elem(i, j);
		}
	}

	// Invert and transpose.
	LinTfm.SimpleInverse();
	LinTfm = LinTfm.Transpose();
}