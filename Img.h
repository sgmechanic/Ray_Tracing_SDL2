#pragma once
#ifndef IMG_H
#define IMG_H
#include <string>
#include <vector>
#include "SDL.h"
class Img {
public:
private:
	std::vector < std::vector < double>> RedChannel;
	std::vector < std::vector < double>> GreenChannel;
	std::vector < std::vector < double>> BlueChannel;
	int xSize;
	int ySize;

	double MaxRed, MaxGreen, MaxBlue, MaxOverall;

	SDL_Renderer* ImgRenderer;
	SDL_Texture* ImgTexture;
	Uint32 ConvertColor(const double red, const double green, const double blue);
	void InitTexture();
	void ComputeMaxValues();
public:
	Img();

	~Img();

	void Init(const int x, const int y, SDL_Renderer* pRenderer);

	void SetPixel(const int x, const int y, const double red, const double gree, const double blue);

	void save_texture(SDL_Renderer* ren, SDL_Texture* tex, const char* filename);

	void Display();

	int GetXSize();

	int GetYSize();
};
#endif