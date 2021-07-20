// Reference: https://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world

#include "SDLTutorial01.h"

#include <iostream>

#include "SDL.h"

namespace JK_SDLTutorials
{
	void SDLTutorial01::Execute()
	{
		SDL_Window *win = NULL;
		SDL_Renderer *ren = NULL;
		SDL_Surface *bmp = NULL;
		SDL_Texture *tex = NULL;

		try
		{
			if (SDL_Init(SDL_INIT_VIDEO) != 0) {
				throw "SDL_Init Error: ";
			}
			// Create a window to display our render in
			win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
			if (win == nullptr) {
				throw "SDL_CreateWindow Error: ";
			}

			// Create a renderer to draw to the window
			ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (ren == nullptr) {
				throw "SDL_CreateRenderer Error: ";
			}

			// Load a bitmap image into memory
			std::string imagePath = "hello.bmp";
			bmp = SDL_LoadBMP(imagePath.c_str());
			if (bmp == nullptr) {
				throw "SDL_LoadBMP Error: ";
			}

			// Upload the image to the renderer
			tex = SDL_CreateTextureFromSurface(ren, bmp);
			SDL_FreeSurface(bmp);
			if (tex == nullptr) {
				throw "SDL_CreateTextureFromSurface Error: "; 
			}

			//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
			for (int i = 0; i < 3; ++i) {
				//First clear the renderer
				SDL_RenderClear(ren);
				//Draw the texture
				SDL_RenderCopy(ren, tex, NULL, NULL);
				//Update the screen
				SDL_RenderPresent(ren);
				//Take a quick break after all that hard work
				SDL_Delay(1000);
			}
		}
		catch (const char* errMessage)
		{
			std::cout << errMessage << SDL_GetError() << std::endl;
		}

		if (tex)
			SDL_DestroyTexture(tex);
		if (ren)
			SDL_DestroyRenderer(ren);
		if (win)
			SDL_DestroyWindow(win);

		SDL_Quit();
	}
}