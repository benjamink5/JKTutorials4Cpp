#pragma once

#include "IDisplay.h"

#include <gl/GL.h>

class ITexture;

class OpenGLSimpleTextureDisplay : public IDisplay
{
private:
	GLfloat m_pLightAmbient[4];
	GLfloat m_pLightDiffuse[4];
	GLfloat m_pLightPosition[4];

	GLfloat	xrot;				// X Rotation
	GLfloat	yrot;				// Y Rotation
	GLfloat xspeed;				// X Rotation Speed
	GLfloat yspeed;				// Y Rotation Speed
	GLfloat	z;			// Depth Into The Screen

	ITexture* m_pTexture;

public:
	OpenGLSimpleTextureDisplay(void);
	~OpenGLSimpleTextureDisplay(void);

	bool	Init(HWND hWnd);
	void	Resize(int width, int height);
	void	Render();

};

