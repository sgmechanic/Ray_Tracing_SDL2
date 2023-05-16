#include "scene.h"
#include "SimpleMaterial.h"
#include "Factory.h"
#include "FactoryPyramid.h"
#include "FactoryBox.h"
#include "FactorySphere.h"
#include <omp.h>
//#include <fstream>
//#include <map>



//JUST ONE SPHERE
Scene::Scene()
{
	auto testMaterial3 = std::make_shared<SimpleMaterial>(SimpleMaterial());
	testMaterial3->BaseColor = LinAlgVector{ std::vector<double>{0.7, 0.6, 0.6} };
	testMaterial3->reflectivity = 0.25;
	testMaterial3->shininess = 10.0;

SceneCamera.SetPosition(LinAlgVector{ std::vector<double> {0.0, -10.0, -1.0} });
SceneCamera.SetLookAt(LinAlgVector{ std::vector<double> {0.0, 0.0, 0.0} });
SceneCamera.SetUp(LinAlgVector{ std::vector<double> {0.0, 0.0, 1.0} });
SceneCamera.SetHoriSize(0.25);
SceneCamera.SetAspect(16.0 / 9.0);
SceneCamera.UpdateCameraGeometry();

Figures.push_back(std::make_shared<Sphere>(Sphere()));


Figures.at(0)->AssignMaterial(testMaterial3);
//Figures.at(0)->BaseColor = LinAlgVector{ std::vector<double>{0.3, 0.6, 0.9} };


GTform testMatrix1(LinAlgVector{ std::vector<double>{-1.0, 0.0, 0.0} }, LinAlgVector{ std::vector<double>{1.2, 0.8, 0.8} }, LinAlgVector{ std::vector<double>{0.5, 0.5, 0.5} });
Figures.at(0)->SetTransformMatrix(testMatrix1);

Lights.push_back(std::make_shared<PointLight>(PointLight()));
Lights.at(0)->LightLocaction = LinAlgVector{ std::vector<double> {5.0, -10.0, -5.0} };
Lights.at(0)->LightColor = LinAlgVector{ std::vector<double> {1.0,1.0, 1.0} };
}



//JUST ONE PYRAMID
//Scene::Scene()
//{
//	auto testMaterial3 = std::make_shared<SimpleMaterial>(SimpleMaterial());
//	testMaterial3->BaseColor = LinAlgVector{ std::vector<double>{0.8, 0.4, 0.0} };
//	testMaterial3->reflectivity = 0.25;
//	testMaterial3->shininess = 10.0;
//
//	SceneCamera.SetPosition(LinAlgVector{ std::vector<double> {0.0, -10.0, -1.0} });
//	SceneCamera.SetLookAt(LinAlgVector{ std::vector<double> {0.0, 0.0, 0.0} });
//	SceneCamera.SetUp(LinAlgVector{ std::vector<double> {0.0, 0.0, 1.0} });
//	SceneCamera.SetHoriSize(0.25);
//	SceneCamera.SetAspect(16.0 / 9.0);
//	SceneCamera.UpdateCameraGeometry();
//
//	Figures.push_back(std::make_shared<Pyramid>(Pyramid()));
//
//	Figures.at(0)->AssignMaterial(testMaterial3);
//
//	GTform testMatrix1(LinAlgVector{ std::vector<double>{-1.0, 0.0, 0.0} }, LinAlgVector{ std::vector<double>{0.4, 0.3, 0.0} }, LinAlgVector{ std::vector<double>{1.0, 1.0, 1.0} });
//	Figures.at(0)->SetTransformMatrix(testMatrix1);
//
//	Lights.push_back(std::make_shared<PointLight>(PointLight()));
//	Lights.at(0)->LightLocaction = LinAlgVector{ std::vector<double> {5.0, -10.0, -5.0} };
//	Lights.at(0)->LightColor = LinAlgVector{ std::vector<double> {1.0,1.0, 1.0} };
//}



//JUST ONE BOX
//Scene::Scene()
//{
//	/*auto testMaterial3 = std::make_shared<SimpleMaterial>(SimpleMaterial());
//	testMaterial3->BaseColor = LinAlgVector{ std::vector<double>{0.8, 0.4, 0.9} };
//	testMaterial3->reflectivity = 0.25;
//	testMaterial3->shininess = 10.0;*/
//
//	SceneCamera.SetPosition(LinAlgVector{ std::vector<double> {0.0, -10.0, -1.0} });
//	SceneCamera.SetLookAt(LinAlgVector{ std::vector<double> {0.0, 0.0, 0.0} });
//	SceneCamera.SetUp(LinAlgVector{ std::vector<double> {0.0, 0.0, 1.0} });
//	SceneCamera.SetHoriSize(0.25);
//	SceneCamera.SetAspect(16.0 / 9.0);
//	SceneCamera.UpdateCameraGeometry();
//
//	Figures.push_back(std::make_shared<Box>(Box()));
//	Figures.at(0)->BaseColor = LinAlgVector{ std::vector<double>{0.5, 0.5, 0.0} };
//	//Figures.at(0)->AssignMaterial(testMaterial3);
//
//	GTform testMatrix1(LinAlgVector{ std::vector<double>{-1.0, 0.0, 0.0} }, LinAlgVector{ std::vector<double>{0.4, 0.3, 0.0} }, LinAlgVector{ std::vector<double>{1.0, 1.0, 1.0} });
//	Figures.at(0)->SetTransformMatrix(testMatrix1);
//
//	Lights.push_back(std::make_shared<PointLight>(PointLight()));
//	Lights.at(0)->LightLocaction = LinAlgVector{ std::vector<double> {5.0, -10.0, -5.0} };
//	Lights.at(0)->LightColor = LinAlgVector{ std::vector<double> {1.0,1.0, 1.0} };
//}



//ALL 3 FIGURES!!!!!!!!!!!!!!!!!!!!!!!!!!!!! +MATERIALS
//Scene::Scene() {
//		// Create some materials.
//	auto testMaterial = std::make_shared<SimpleMaterial>(SimpleMaterial());
//	auto testMaterial2 = std::make_shared<SimpleMaterial>(SimpleMaterial());
//	auto testMaterial3 = std::make_shared<SimpleMaterial>(SimpleMaterial());
//	auto floorMaterial = std::make_shared<SimpleMaterial>(SimpleMaterial());
//
//	 //Setup the materials.
//	testMaterial->BaseColor = LinAlgVector{ std::vector<double>{0.5, 0.5, 0.8} };
//	testMaterial->reflectivity = 0.1;
//	testMaterial->shininess = 10.0;
//
//	testMaterial2-> BaseColor = LinAlgVector{ std::vector<double>{1.0, 0.5, 0.9} };
//	testMaterial2-> reflectivity = 0.75;
//	testMaterial2-> shininess = 10.0;
//
//	testMaterial3->BaseColor = LinAlgVector{ std::vector<double>{1.0, 0.8, 0.0} };
//	testMaterial3->reflectivity = 0.25;
//	testMaterial3->shininess = 10.0;
//
//	floorMaterial->BaseColor = LinAlgVector{ std::vector<double>{1.0, 1.0, 1.0} };
//	floorMaterial->reflectivity = 0.5;
//	floorMaterial->shininess = 0.0;
//SceneCamera.SetPosition(LinAlgVector{std::vector<double> {0.0, -10.0, -1.0}});
//SceneCamera.SetLookAt(LinAlgVector{std::vector<double> {0.0, 0.0, 0.0}});
//SceneCamera.SetUp(LinAlgVector{std::vector<double> {0.0, 0.0, 1.0}});
//SceneCamera.SetHoriSize(0.25);
//SceneCamera.SetAspect(16.0 / 9.0);
//SceneCamera.UpdateCameraGeometry();
//
//// Construct a test sphere.
//Figures.push_back(std::make_shared<Pyramid>(Pyramid()));  //emplace_back
//Figures.push_back(std::make_shared<Sphere>(Sphere()));
////Figures.push_back(std::make_shared<Sphere>(Sphere()));
//Figures.push_back(std::make_shared<Box>(Box()));
//
//
//Figures.push_back(std::make_shared<Plane>(Plane()));
//Figures.at(3)->BaseColor = LinAlgVector{ std::vector<double> {0.5, 0.5, 0.5} };
//
//// Define a transform for the plane.
//GTform planeMatrix;
//planeMatrix.SetTransform(LinAlgVector{std::vector<double>{0.0, 0.0, 1.0}},
//	LinAlgVector{std::vector<double>{0.0, 0.0, 0.0}},
//	LinAlgVector{std::vector<double>{4.0, 4.0, 1.0}});
//Figures.at(3)->SetTransformMatrix(planeMatrix);
//
//
//
//// Modify the spheres.
//GTform testMatrix1(LinAlgVector{ std::vector<double>{-2.0, 0.0, 0.5} },
//	LinAlgVector{ std::vector<double>{ 0.4, 0.1, 0.0} },
//	LinAlgVector{ std::vector<double>{1.2, 1.2, 1.2} }), 
//	//testMatrix2(LinAlgVector{ std::vector<double>{0.0, 0.0, 0.0} },
//		//LinAlgVector{ std::vector<double>{0.0, 0.0, 0.0} },
//		//LinAlgVector{ std::vector<double>{0.75, 0.5, 0.5} }), 
//	testMatrix3(LinAlgVector{ std::vector<double>{1.5, 0.0, 0.0} },
//			LinAlgVector{ std::vector<double>{0.0, 0.0, 0.0} },
//			LinAlgVector{ std::vector<double>{0.75, 0.75, 0.75} }), 
//	testMatrix4(LinAlgVector{ std::vector<double>{0.0, 0.0, 0.0} },
//				LinAlgVector{ std::vector<double>{0.2, 0.4, 0.3} },
//				LinAlgVector{ std::vector<double>{0.5, 0.5, 0.5} });
////testMatrix1.SetTransform(LinAlgVector{std::vector<double>{-1.5, 0.0, 0.0}},
////	LinAlgVector{std::vector<double>{0.0, 0.0, 0.0}},
////	LinAlgVector{std::vector<double>{0.5, 0.5, 0.75}});
////
////testMatrix2.SetTransform(LinAlgVector{std::vector<double>{0.0, 0.0, 0.0}},
////	LinAlgVector{std::vector<double>{0.0, 0.0, 0.0}},
////	LinAlgVector{std::vector<double>{0.75, 0.5, 0.5}});
////
////testMatrix3.SetTransform(LinAlgVector{std::vector<double>{1.5, 0.0, 0.0}},
////	LinAlgVector{std::vector<double>{0.0, 0.0, 0.0}},
////	LinAlgVector{std::vector<double>{0.75, 0.75, 0.75}});
////testMatrix4.SetTransform(LinAlgVector{ std::vector<double>{0.0, 0.0, 0.0} },
////	LinAlgVector{ std::vector<double>{0.0, 0.0, 0.0} },
////	LinAlgVector{ std::vector<double>{1.0, 1.0, 1.0} });
//
//Figures.at(0)->SetTransformMatrix(testMatrix1);
////Figures.at(1)->SetTransformMatrix(testMatrix2);
//Figures.at(1)->SetTransformMatrix(testMatrix3);
//Figures.at(2)->SetTransformMatrix(testMatrix4);
//Figures.at(0)->BaseColor = LinAlgVector{ std::vector<double>{0.25, 0.5, 0.8} };
//Figures.at(1)->BaseColor = LinAlgVector{ std::vector<double>{1.0, 0.5, 0.0} };
//Figures.at(2)->BaseColor = LinAlgVector{std::vector<double>{1.0, 0.8, 0.0}};
//Figures.at(0)->AssignMaterial(testMaterial3);
//Figures.at(1)->AssignMaterial(testMaterial2);
//Figures.at(2)->AssignMaterial(testMaterial);
//Figures.at(3)->AssignMaterial(floorMaterial);
////Figures.at(3)->BaseColor = LinAlgVector{ std::vector<double>{0.0, 1.0, 0.0} };
//
//// Construct a test light.
//Lights.push_back(std::make_shared<PointLight>(PointLight()));
//Lights.at(0)->LightLocaction= LinAlgVector{ std::vector<double> {5.0, -10.0, -5.0} };
//Lights.at(0)->LightColor = LinAlgVector{ std::vector<double> {1.0,1.0, 1.0} };
//Lights.push_back(std::make_shared<PointLight>(PointLight()));
//Lights.at(1)->LightLocaction = LinAlgVector{ std::vector<double> {-5.0, -10.0, -5.0} };
//Lights.at(1)->LightColor = LinAlgVector{ std::vector<double> {1.0,0.0, 0.0} };
//Lights.push_back(std::make_shared<PointLight>(PointLight()));
//Lights.at(2)->LightLocaction = LinAlgVector{ std::vector<double> {0.0, -10.0, -5.0} };
//Lights.at(2)->LightColor = LinAlgVector{ std::vector<double> {0.0,1.0, 0.0} };
//}




//bool Scene::Render(Img& OutputImage)
//{
//	for (int i = 0; i < 100; i++)
//		for (int j = 0; j < 100; j++)
//		{
//			OutputImage.SetPixel(i, j, 0.0, 0.0, 1.0);
//		}
//	return true;
//
//}






bool Scene::Render(Img& OutputImage)
{
	// Get the dimensions of the output image.
	int xSize = OutputImage.GetXSize();
	int ySize = OutputImage.GetYSize();

	// Loop over each pixel in our image.
	Ray cameraRay;
	LinAlgVector intPoint(3);
	LinAlgVector localNormal(3);
	LinAlgVector localColor(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;

	for (int x = 0; x < xSize; ++x)
	{
		for (int y = 0; y < ySize; ++y)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;

			// Generate the ray for this pixel.
			SceneCamera.GenerateRay(normX, normY, cameraRay);

			// Test for intersections with all objects in the scene.
			std::shared_ptr<Figure> closestObject;
			LinAlgVector closestIntPoint{3};
			LinAlgVector closestLocalNormal{3};
			LinAlgVector closestLocalColor{3};
			bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
			/* Compute the illumination for the closest object, assuming that there
				was a valid intersection. */
			if (intersectionFound)
			{
				if (closestObject->HasMaterial)
				{
					LinAlgVector color = closestObject->Material->ComputeColor(Figures, Lights, closestObject, closestIntPoint, closestLocalNormal, cameraRay);
					OutputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					LinAlgVector matColor = MaterialBase::ComputeDiffuseColor(Figures, Lights, closestObject, closestIntPoint, closestLocalNormal, closestObject->BaseColor);
					//if (matColor.GetElement(0) > matColor.GetElement(1) && matColor.GetElement(0) > matColor.GetElement(2))
					//{
					//matColor.PrintVector();
					//}
					OutputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
		
				}
			}
		}
	}

	return true;
}



bool Scene::CastRay(Ray& CastRay, std::shared_ptr<Figure>& ClosestFigure, LinAlgVector& ClosestIntPoint,
	LinAlgVector& ClosestLocalNormal, LinAlgVector& ClosestLocalColor)
{
	LinAlgVector intPoint{ 3 };
	LinAlgVector localNormal{ 3 };
	LinAlgVector localColor{ 3 };
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : Figures)
	{
		bool validInt = currentObject->TestIntersections(CastRay, intPoint, localNormal, localColor);

		// If we have a valid intersection.
		if (validInt)
		{
			// Set the flag to indicate that we found an intersection.
			intersectionFound = true;

			// Compute the distance between the camera and the point of intersection.
			double dist = (intPoint - CastRay.point1).norm();

			/* If this object is closer to the camera than any one that we have
				seen before, then store a reference to it. */
			if (dist < minDist)
			{
				minDist = dist;
				ClosestFigure = currentObject;
				ClosestIntPoint = intPoint;
				ClosestLocalNormal = localNormal;
				ClosestLocalColor = localColor;
			}
		}
	}
	return intersectionFound;
}



























































// DO NOT MESS UP THESE TWO

//bool Scene::Render(Img& OutputImage)
//{
//	// Get the dimensions of the output image.
//	int xSize = OutputImage.GetXSize();
//	int ySize = OutputImage.GetYSize();
//
//	// Loop over each pixel in our image.
//	Ray cameraRay;
//	LinAlgVector intPoint(3);
//	LinAlgVector localNormal(3);
//	LinAlgVector localColor(3);
//	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
//	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
//	double minDist = 1e6;
//	double maxDist = 0.0;
//	//#pragma omp parallel for private(x,y)
//	//omp_set_num_threads(4);
//	//omp_set_dynamic(0);
//	//#pragma omp parallel for 
//	for (int x = 0; x < xSize; ++x)
//	{
//		for (int y = 0; y < ySize; ++y)
//		{
//			// Normalize the x and y coordinates.
//			double normX = (static_cast<double>(x) * xFact) - 1.0;
//			double normY = (static_cast<double>(y) * yFact) - 1.0;
//
//			// Generate the ray for this pixel.
//			SceneCamera.GenerateRay(normX, normY, cameraRay);
//
//			// Test for intersections with all objects in the scene.
//			std::shared_ptr<Figure> closestObject;
//			LinAlgVector closestIntPoint{ 3 };
//			LinAlgVector closestLocalNormal{ 3 };
//			LinAlgVector closestLocalColor{ 3 };
//			bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
//			/* Compute the illumination for the closest object, assuming that there
//				was a valid intersection. */
//			if (intersectionFound)
//			{
//				if (closestObject->HasMaterial)
//				{
//					LinAlgVector color = closestObject->Material->ComputeColor(Figures, Lights, closestObject, closestIntPoint, closestLocalNormal, cameraRay);
//					OutputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
//				}
//				else
//				{
//					LinAlgVector matColor = MaterialBase::ComputeDiffuseColor(Figures, Lights, closestObject, closestIntPoint, closestLocalNormal, closestObject->BaseColor);
//					OutputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
//
//				}
//			}
//		}
//	}
//
//	return true;
//}
//
//
//
//bool Scene::CastRay(Ray& CastRay, std::shared_ptr<Figure>& ClosestFigure, LinAlgVector& ClosestIntPoint,
//	LinAlgVector& ClosestLocalNormal, LinAlgVector& ClosestLocalColor)
//{
//	LinAlgVector intPoint{ 3 };
//	LinAlgVector localNormal{ 3 };
//	LinAlgVector localColor{ 3 };
//	double minDist = 1e6;
//	bool intersectionFound = false;
//	for (auto currentObject : Figures)
//	{
//		bool validInt = currentObject->TestIntersections(CastRay, intPoint, localNormal, localColor);
//
//		// If we have a valid intersection.
//		if (validInt)
//		{
//			// Set the flag to indicate that we found an intersection.
//			intersectionFound = true;
//
//			// Compute the distance between the camera and the point of intersection.
//			double dist = (intPoint - CastRay.point1).norm();
//
//			/* If this object is closer to the camera than any one that we have
//				seen before, then store a reference to it. */
//			if (dist < minDist)
//			{
//				minDist = dist;
//				ClosestFigure = currentObject;
//				ClosestIntPoint = intPoint;
//				ClosestLocalNormal = localNormal;
//				ClosestLocalColor = localColor;
//			}
//		}
//	}
//	return intersectionFound;
//}
