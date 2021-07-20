#pragma once

#include "IDisplay.h"

class OpenGLSimpleDisplay : public IDisplay
{
private:

public:
	OpenGLSimpleDisplay(void);
	~OpenGLSimpleDisplay(void);

	bool	Init(HWND hWnd);
	void	Resize(int width, int height);
	void	Render();
};

