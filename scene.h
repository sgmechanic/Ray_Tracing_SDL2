#ifndef SCENE_H
#define SCENE_H
#include "SDL.h"
#include <memory>
#include <vector>
#include "Img.h"
#include "Camera.h"
#include "Sphere.h"
#include "LightBase.h"
#include "PointLight.h"
#include "Plane.h"]
#include "Box.h"
#include "Triangle.h"
#include "Pyramid.h"
#include "MaterialBase.h"


//#include "Figure.h"
class Scene {
private:
	Camera SceneCamera;
	std::vector<std::shared_ptr<Figure>> Figures;
	std::vector<Figure*> FiguresInput;
	std::vector<std::shared_ptr<LightBase>> Lights;
	//Sphere TestSphere;
public:
	Scene();
	bool Render(Img& OutputImage);
	bool CastRay(Ray& CastRay, std::shared_ptr<Figure>& ClosestFigure, LinAlgVector& ClosestIntPoint,
		LinAlgVector& ClosestLocalNormal, LinAlgVector& ClosestLocalColor);
};
#endif