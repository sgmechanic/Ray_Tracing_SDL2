#include "Img.h"
Img::Img() {
	xSize = 0;
	ySize = 0;
	ImgTexture = nullptr;
}

Img::~Img()
{
	if (ImgTexture != nullptr)
		SDL_DestroyTexture(ImgTexture);
}

void Img::Init(const int x, const int y, SDL_Renderer* pRenderer)
{
	RedChannel.resize(x, std::vector<double>(y, 0.0));
	GreenChannel.resize(x, std::vector<double>(y, 0.0));
	BlueChannel.resize(x, std::vector<double>(y, 0.0));

	xSize = x;
	ySize = y;

	ImgRenderer = pRenderer;
	InitTexture();

}

void Img::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
	RedChannel.at(x).at(y) = red;
	GreenChannel.at(x).at(y) = green;
	BlueChannel.at(x).at(y) = blue;
}

void Img::Display()
{
	ComputeMaxValues();
	Uint32* tmpPixels = new Uint32[xSize * ySize];

	memset(tmpPixels, 0, xSize * ySize * sizeof(Uint32));

	for (int x = 0; x < xSize; ++x)
	{
		for (int y = 0; y < ySize; ++y)
		{
			tmpPixels[(y * xSize) + x] = ConvertColor(RedChannel.at(x).at(y), GreenChannel.at(x).at(y), BlueChannel.at(x).at(y));
		}
	}
	SDL_UpdateTexture(ImgTexture, nullptr, tmpPixels, xSize * sizeof(Uint32));

	delete[] tmpPixels;

	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = xSize;
	srcRect.h = ySize;
	bounds = srcRect;
	SDL_RenderCopy(ImgRenderer, ImgTexture, &srcRect, &bounds);
}

void Img::InitTexture()
{
	Uint32 rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else 
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	if (ImgTexture != nullptr)
		SDL_DestroyTexture(ImgTexture);

	SDL_Surface* tmpSurface = SDL_CreateRGBSurface(0, xSize, ySize, 32, rmask, gmask, bmask, amask);
	ImgTexture = SDL_CreateTextureFromSurface(ImgRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

}

Uint32 Img::ConvertColor(const double red, const double green, const double blue)
{


	unsigned char r = static_cast<unsigned char>((red/MaxOverall) * 255.0);
	unsigned char g = static_cast<unsigned char>((green/ MaxOverall) * 255.0);
	unsigned char b = static_cast<unsigned char>((blue/ MaxOverall) * 255.0);

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
	#else
		Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
	#endif

	return pixelColor;
}

int Img::GetXSize() { return xSize; }

int Img::GetYSize() { return ySize; }

void Img::ComputeMaxValues()
{
	MaxRed = 0.0;
	MaxGreen = 0.0;
	MaxBlue = 0.0;
	MaxOverall = 0.0;
	for (int x = 0; x < xSize; ++x)
	{
		for (int y = 0; y < ySize; ++y)
		{
			double redValue = RedChannel.at(x).at(y);
			double greenValue = GreenChannel.at(x).at(y);
			double blueValue = BlueChannel.at(x).at(y);

			if (redValue > MaxRed)
				MaxRed = redValue;
			if (greenValue > MaxGreen)
				MaxGreen = greenValue;
			if (blueValue > MaxBlue)
				MaxBlue = blueValue;
			if (MaxRed > MaxOverall)
				MaxOverall = MaxRed;
			if (MaxGreen > MaxOverall)
				MaxOverall = MaxGreen;
			if (MaxBlue > MaxOverall)
				MaxOverall = MaxBlue;

		}
	}
}