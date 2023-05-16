#ifndef CAMERA_H
#define CAMERA_H
#include "LinAlgVector.h"
#include "Ray.h"
class Camera {
private:
	LinAlgVector CameraPosition{ 3 };
	LinAlgVector CameraLookAt{ 3 };
	LinAlgVector CameraUp{ 3 };

	double CameraLength;
	double CameraHoriSize;
	double CameraAspectRatio;

	LinAlgVector AllignmentVector{ 3 };
	LinAlgVector ProjectionScreenU{ 3 };
	LinAlgVector ProjectionScreenV{ 3 };
	LinAlgVector ProjectionScreenCentre{ 3 };


public:
	Camera();

	void SetPosition(const LinAlgVector& NewPosition);
	void SetLookAt(const LinAlgVector& NewLookAt);
	void SetUp(const LinAlgVector& UpVector);
	void SetLength(double NewLength);
	void SetHoriSize(double NewHoriSize);
	void SetAspect(double NewAspect);

	LinAlgVector GetPosition();
	LinAlgVector GetLookAt();
	LinAlgVector GetUp();
	LinAlgVector GetU();
	LinAlgVector GetV();
	LinAlgVector GetScreenCentre();
	double GetLength();
	double GetHoriSize();
	double GetAspect();

	bool GenerateRay(float proScreenX, float proScreenY, Ray& CameraRay);

	void UpdateCameraGeometry();
};
#endif