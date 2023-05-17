#include "Header.h"
#include <vector>
App::App()
{
	IsRunning = true;
	pWindow = nullptr;
	pRenderer = nullptr;
}

bool App::OnInit()
{
	if (SDL_INIT_EVERYTHING < 0)
		return false;
	pWindow = SDL_CreateWindow("RayTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, SDL_WINDOW_SHOWN);
	if (pWindow != nullptr)
	{
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

		Image.Init(300, 300, pRenderer);

		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer);

		scene.Render(Image);
		Image.Display();

		SDL_RenderPresent(pRenderer);

	}
	else
		return false;
	return true;
}

int App::OnExecute()
{
	SDL_Event event;

	if (OnInit() == false)
		return -1;
	while (IsRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}
		OnLoop();
		OnRender();
	}
	return 0;
}

void App::OnEvent(SDL_Event* event) 
{
	if (event->type == SDL_QUIT)
	{
		IsRunning = false;
	}
}

void App::OnLoop()
{

}

void App::OnRender()
{

}

void App::OnExit()
{
	//Deleting SDL2 stuff
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;
	SDL_Quit();
}





void App::PrintVector(LinAlgVector& InputVector)
{
	int nRows = InputVector.GetDims();
	for (int row = 0; row < nRows; ++row)
		std::cout << InputVector[row] << std::endl;
}

