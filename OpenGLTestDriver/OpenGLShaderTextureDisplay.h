#pragma once

#include "IDisplay.h"

#include <GL\GL.h>

class ITexture;
class IShader;

class OpenGLShaderTextureDisplay : public IDisplay
{
private:
	GLfloat m_pLightAmbient[4];
	GLfloat m_pLightDiffuse[4];
	GLfloat m_pLightPosition[4];

	GLfloat	xrot;				// X Rotation
	GLfloat	yrot;				// Y Rotation
	GLfloat xspeed;				// X Rotation Speed
	GLfloat yspeed;				// Y Rotation Speed
	GLfloat	z;					// Depth Into The Screen

	ITexture* m_pTexture;
	IShader* m_pShader;

public:
	OpenGLShaderTextureDisplay(void);
	~OpenGLShaderTextureDisplay(void);

	bool	Init(HWND hWnd);
	void	Resize(int width, int height);
	void	Render();
};

