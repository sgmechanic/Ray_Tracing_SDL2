#include "Camera.h"
Camera::Camera()
{
	CameraPosition = LinAlgVector(std::vector<double>{0.0, -10.0, 0.0});
	CameraLookAt = LinAlgVector(std::vector<double>{0.0, 0.0, 0.0});
	CameraUp = LinAlgVector(std::vector<double> {0.0, 0.0, 1.0});
	CameraLength = 1.0;
	CameraHoriSize = 1.0;
	CameraAspectRatio = 1.0;
}

void Camera::SetPosition(const LinAlgVector& NewPosition)
{
	CameraPosition = NewPosition;
}

void Camera::SetLookAt(const LinAlgVector& NewLookAt)
{
	CameraLookAt = NewLookAt;
}

void Camera::SetUp(const LinAlgVector& UpVector)
{
	CameraUp = UpVector;
}

void Camera::SetLength(const double NewLength)
{
	CameraLength = NewLength;
}

void Camera::SetHoriSize(double NewHoriSize)
{
	CameraHoriSize = NewHoriSize;
}

void Camera::SetAspect(double NewAspect)
{
	CameraAspectRatio = NewAspect;
}

LinAlgVector Camera::GetPosition()
{
	return CameraPosition;
}

LinAlgVector Camera::GetUp()
{
	return CameraUp;
}

double Camera::GetLength()
{
	return CameraLength;
}

double Camera::GetHoriSize()
{
	return CameraHoriSize;
}

double Camera::GetAspect()
{
	return CameraAspectRatio;
}

LinAlgVector Camera::GetU()
{
	return ProjectionScreenU;
}

LinAlgVector Camera::GetV()
{
	return ProjectionScreenV;
}

LinAlgVector Camera::GetScreenCentre()
{
	return ProjectionScreenCentre;
}

void Camera::UpdateCameraGeometry()
{
	AllignmentVector = CameraLookAt - CameraPosition;
	AllignmentVector.Normalize();

	ProjectionScreenU = LinAlgVector::cross(AllignmentVector,CameraUp);
	ProjectionScreenU.Normalize();

	ProjectionScreenV = LinAlgVector::cross(ProjectionScreenU, AllignmentVector);
	ProjectionScreenV.Normalize();

	ProjectionScreenCentre = CameraPosition + (AllignmentVector*CameraLength);

	ProjectionScreenU = ProjectionScreenU * CameraHoriSize;
	ProjectionScreenV = ProjectionScreenV * (CameraHoriSize / CameraAspectRatio);
}

bool Camera::GenerateRay(float proScreenX, float proScreenY, Ray& CameraRay) //Stopped here
{
	LinAlgVector ScreenWorldPart1 = ProjectionScreenCentre + (ProjectionScreenU * proScreenX);
	LinAlgVector ScreenWorldCoordinate = ScreenWorldPart1 + (ProjectionScreenV * proScreenY);

	CameraRay.point1 = CameraPosition;
	CameraRay.point2 = ScreenWorldCoordinate;
	CameraRay.ab = ScreenWorldCoordinate - CameraPosition;

	return true;
}