#pragma once

#include <iostream>

#include "BaseTestDriver.h"

#include "SDL_render.h"

namespace JK_SDLTutorials
{
	
	class SDLTutorial02 : public BaseTestDriver
	{
	public:
		SDLTutorial02();
		~SDLTutorial02();

		void Execute();
		bool Initialize();
		void Destroy();

	private:
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

		//We'll just be using square tiles for now
		const int TILE_SIZE = 40;

		SDL_Window *window;
		SDL_Renderer *renderer;

		SDL_Texture *background;
		SDL_Texture *image;

		/**
		* Render the screen
		*/
		void renderScreen();

		/**
		* Log an SDL error with some error message to the output stream of our choice
		* @param os The output stream to write the message to
		* @param msg The error message to write, format will be msg error: SDL_GetError()
		*/
		void logSDLError(std::ostream &os, const std::string &msg);

		/**
		* Loads a BMP image into a texture on the rendering device
		* @param file The BMP image file to load
		* @param ren The renderer to load the texture onto
		* @return the loaded texture, or nullptr if something went wrong.
		*/
		SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

		/**
		* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
		* width and height
		* @param tex The source texture we want to draw
		* @param ren The renderer we want to draw to
		* @param x The x coordinate to draw to
		* @param y The y coordinate to draw to
		* @param w The width of the texture to draw
		* @param h The height of the texture to draw
		*/
		void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

		/**
		* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
		* the texture's width and height
		* @param tex The source texture we want to draw
		* @param ren The renderer we want to draw to
		* @param x The x coordinate to draw to
		* @param y The y coordinate to draw to
		*/
		void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

//		void cleanup();

		template<typename T, typename... Args>
		static void cleanUp(T *t, Args&&... args);

		/*
		 * These specializations serve to free the passed argument and also provide the
		 * base cases for the recursive call above, eg. when args is only a single item
		 * one of the specializations below will be called by
		 * cleanup(std::forward<Args>(args)...), ending the recursion
		 * We also make it safe to pass nullptrs to handle situations where we
		 * don't want to bother finding out which values failed to load (and thus are null)
		 * but rather just want to clean everything up and let cleanup sort it out
		 */
		template<>
		static inline void cleanUp<SDL_Window>(SDL_Window *win) {
			if (!win) {
				return;
			}
			SDL_DestroyWindow(win);
		}
		template<>
		static inline void cleanUp<SDL_Renderer>(SDL_Renderer *ren) {
			if (!ren) {
				return;
			}
			SDL_DestroyRenderer(ren);
		}
		template<>
		static inline void cleanUp<SDL_Texture>(SDL_Texture *tex) {
			if (!tex) {
				return;
			}
			SDL_DestroyTexture(tex);
		}
		template<>
		static inline void cleanUp<SDL_Surface>(SDL_Surface *surf) {
			if (!surf) {
				return;
			}
			SDL_FreeSurface(surf);
		}
	};
}

