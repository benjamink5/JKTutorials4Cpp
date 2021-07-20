#pragma once

#include "IDisplay.h"

#include <GL\GL.h>

class ITexture;
class IShader;

class OpenGLFBOShaderTextureDisplay : public IDisplay
{
private:
	GLfloat m_pLightAmbient[4];
	GLfloat m_pLightDiffuse[4];
	GLfloat m_pLightPosition[4];

	GLfloat	z;					// Depth Into The Screen

	ITexture* m_pTexture;
	IShader* m_pShader;

public:
	OpenGLFBOShaderTextureDisplay(void);
	~OpenGLFBOShaderTextureDisplay(void);

	bool	Init(HWND hWnd);
	void	Resize(int width, int height);
	void	Render();
};

