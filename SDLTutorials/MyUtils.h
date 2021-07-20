#pragma once

#include <SDL.h>

namespace JK_SDLTutorials
{
	class MyUtils
	{
	public:
		template<typename T, typename... Args>
		static void SDL_CleanUp(T *t, Args&&... args);

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
		static inline void SDL_CleanUp<SDL_Window>(SDL_Window *win) {
			if (!win) {
				return;
			}
			SDL_DestroyWindow(win);
		}
		template<>
		static inline void SDL_CleanUp<SDL_Renderer>(SDL_Renderer *ren) {
			if (!ren) {
				return;
			}
			SDL_DestroyRenderer(ren);
		}
		template<>
		static inline void SDL_CleanUp<SDL_Texture>(SDL_Texture *tex) {
			if (!tex) {
				return;
			}
			SDL_DestroyTexture(tex);
		}
		template<>
		static inline void SDL_CleanUp<SDL_Surface>(SDL_Surface *surf) {
			if (!surf) {
				return;
			}
			SDL_FreeSurface(surf);
		}
	};
}

