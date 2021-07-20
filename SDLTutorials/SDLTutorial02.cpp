#include "SDLTutorial02.h"
#include "MyUtils.h"

#include <iostream>

#include "SDL.h"

namespace JK_SDLTutorials
{
	SDLTutorial02::SDLTutorial02() :
		window(nullptr),
		renderer(nullptr),
		background(nullptr),
		image(nullptr)
	{
	}

	SDLTutorial02::~SDLTutorial02()
	{
	}

	bool SDLTutorial02::Initialize()
	{
		bool bRetVal = false;

		try
		{
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			{
				throw "SDL_Init";
			}

			window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == nullptr)
			{
				throw "CreateWindow";
			}

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr)
			{
				throw "CreateRenderer";
			}

			background = loadTexture("background.bmp", renderer);
			image = loadTexture("image.bmp", renderer);
			if (background == nullptr || image == nullptr)
			{
				throw "loadTexture";
			}

			bRetVal = true;
		}
		catch (const char* errMessage)
		{
			std::cout << errMessage << " error: " << SDL_GetError() << std::endl;
			bRetVal = false;
		}

		return false;
	}

	void SDLTutorial02::Destroy()
	{
		cleanUp(renderer, window, background, image);

		SDL_Quit();
	}

	void SDLTutorial02::Execute()
	{
		try
		{
			SDL_Event e;
			bool quit = false;

			while (!quit)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT) 
					{
						quit = true;
					}
					if (e.type == SDL_KEYDOWN) 
					{
						quit = true;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) 
					{
						quit = true;
					}
				}

				// Render tthe scene
				renderScreen();

				//Take a quick break after all that hard work
				//SDL_Delay(1000);
			}
		}
		catch (const char* errMessage)
		{
			std::cout << errMessage << " error: " << SDL_GetError() << std::endl;
		}
	}

	void SDLTutorial02::renderScreen()
	{
		SDL_RenderClear(renderer);

		// Determin how may tiles we'll need to fill the screen
		int xTiles = SCREEN_WIDTH / TILE_SIZE;
		int yTiles = SCREEN_HEIGHT / TILE_SIZE;

		// Draw the background tiles by calculating their positions
		for (int i = 0; i < xTiles * yTiles; ++i)
		{
			int x = i % xTiles;
			int y = i / xTiles;

			renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}

		// Draw the foreground iamge
		int iW, iH;
		SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
		int x = SCREEN_WIDTH / 2 - iW / 2;
		int y = SCREEN_HEIGHT / 2 - iH / 2;
		renderTexture(image, renderer, x, y);

		//Update the screen
		SDL_RenderPresent(renderer);
	}

	void SDLTutorial02::logSDLError(std::ostream & os, const std::string & msg)
	{
		//os << msg << " error: " << SDL_GetError() << std::endl;
	}
	
	SDL_Texture * SDLTutorial02::loadTexture(const std::string & file, SDL_Renderer * ren)
	{
		//Initialize to nullptr to avoid dangling pointer issues
		SDL_Texture *texture = nullptr;
		//Load the image
		SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
		//If the loading went ok, convert to texture and return the texture
		if (loadedImage != nullptr) {
			texture = SDL_CreateTextureFromSurface(ren, loadedImage);
			SDL_FreeSurface(loadedImage);
			//Make sure converting went ok too
			if (texture == nullptr) {
				logSDLError(std::cout, "CreateTextureFromSurface");
			}
		}
		else {
			logSDLError(std::cout, "LoadBMP");
		}
		return texture;
	}
	
	void SDLTutorial02::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
	{
		//Setup the destination rectangle to be at the position we want
		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		dst.w = w;
		dst.h = h;
		SDL_RenderCopy(ren, tex, NULL, &dst);
	}

	void SDLTutorial02::renderTexture(SDL_Texture * tex, SDL_Renderer * ren, int x, int y)
	{
		//Setup the destination rectangle to be at the position we want
		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		//Query the texture to get its width and height to use
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		SDL_RenderCopy(ren, tex, NULL, &dst);
	}

	/*
	 * Recurse through the list of arguments to clean up, cleaning up
	 * the first one in the list each iteration.
	 */
	template<typename T, typename... Args>
	void SDLTutorial02::cleanUp(T *t, Args&&... args) {
		//Cleanup the first item in the list
		cleanUp(t);
		//Recurse to clean up the remaining arguments
		cleanUp(std::forward<Args>(args)...);
	}
}