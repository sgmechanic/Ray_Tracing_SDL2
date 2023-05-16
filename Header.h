#ifndef APP_H
#define APP_H
#include "SDL.h"
#include "Img.h"
#include "scene.h"
#include "Camera.h"
#include "LinAlgVector.h"
#include "LinAlgMatrix.h"
class App
{
public:
	App();
	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnExit();
private:
	Scene scene;
	Img Image;
	bool IsRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	void PrintVector(LinAlgVector& InputVector);
};
#endif