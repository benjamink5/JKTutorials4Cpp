#pragma once
#include "IDisplay.h"

#include <gl/GL.h>
#include <gl/GLU.h>
#include "OpenGLText.h"
#include "IShader.h"

class OpenGLTextDisplay : public IDisplay
{
private:
	OpenGLText *m_pText;
	IShader* m_pShader;

	float	m_fWidth; 
	float	m_fHeight;

public:
	OpenGLTextDisplay(void);
	~OpenGLTextDisplay(void);

	bool	Init(HWND hWnd);
	void	Resize(int width, int height);
	void	Render();

};

