#include "MyUtils.h"

namespace JK_SDLTutorials
{

	/*
	 * Recurse through the list of arguments to clean up, cleaning up
	 * the first one in the list each iteration.
	 */
	template<typename T, typename... Args>
	void MyUtils::SDL_CleanUp(T *t, Args&&... args) {
		//Cleanup the first item in the list
		SDL_CleanUp(t);
		//Recurse to clean up the remaining arguments
		SDL_CleanUp(std::forward<Args>(args)...);
	}


}