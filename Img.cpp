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
	save_texture(ImgRenderer, ImgTexture, "Result.bmp");
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
	//SDL_SaveBMP(tmpSurface, "Result.bmp");
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

void Img::save_texture(SDL_Renderer* ren, SDL_Texture* tex, const char* filename)
{
	SDL_Texture* ren_tex;
	SDL_Surface* surf;
	int st;
	int w;
	int h;
	int format;
	void* pixels;

	pixels = NULL;
	surf = NULL;
	ren_tex = NULL;
	format = SDL_PIXELFORMAT_RGBA32;

	/* Get information about texture we want to save */
	st = SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	if (st != 0) {
		SDL_Log("Failed querying texture: %s\n", SDL_GetError());
		goto cleanup;
	}

	ren_tex = SDL_CreateTexture(ren, format, SDL_TEXTUREACCESS_TARGET, w, h);
	if (!ren_tex) {
		SDL_Log("Failed creating render texture: %s\n", SDL_GetError());
		goto cleanup;
	}

	/*
	 * Initialize our canvas, then copy texture to a target whose pixel data we
	 * can access
	 */
	st = SDL_SetRenderTarget(ren, ren_tex);
	if (st != 0) {
		SDL_Log("Failed setting render target: %s\n", SDL_GetError());
		goto cleanup;
	}

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(ren);

	st = SDL_RenderCopy(ren, tex, NULL, NULL);
	if (st != 0) {
		SDL_Log("Failed copying texture data: %s\n", SDL_GetError());
		goto cleanup;
	}

	/* Create buffer to hold texture data and load it */
	pixels = malloc(w * h * SDL_BYTESPERPIXEL(format));
	if (!pixels) {
		SDL_Log("Failed allocating memory\n");
		goto cleanup;
	}

	st = SDL_RenderReadPixels(ren, NULL, format, pixels, w * SDL_BYTESPERPIXEL(format));
	if (st != 0) {
		SDL_Log("Failed reading pixel data: %s\n", SDL_GetError());
		goto cleanup;
	}

	/* Copy pixel data over to surface */
	surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, SDL_BITSPERPIXEL(format), w * SDL_BYTESPERPIXEL(format), format);
	if (!surf) {
		SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
		goto cleanup;
	}

	/* Save result to an image */
	st = SDL_SaveBMP(surf, filename);
	if (st != 0) {
		SDL_Log("Failed saving image: %s\n", SDL_GetError());
		goto cleanup;
	}

	SDL_Log("Saved texture as BMP to \"%s\"\n", filename);

cleanup:
	SDL_FreeSurface(surf);
	free(pixels);
	SDL_DestroyTexture(ren_tex);
}