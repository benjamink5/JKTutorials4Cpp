#pragma once

#include "IDisplay.h"
#include "ITexture.h"

class OpenGLFBOTextureDisplay : public IDisplay
{
private:
	float m_pLightAmbient[4];
	float m_pLightDiffuse[4];
	float m_pLightPosition[4];

	float	xrot;				// X Rotation
	float	yrot;				// Y Rotation
	float xspeed;				// X Rotation Speed
	float yspeed;				// Y Rotation Speed
	float	z;			// Depth Into The Screen

	ITexture* m_pTexture;

public:
	OpenGLFBOTextureDisplay(void);
	~OpenGLFBOTextureDisplay(void);

	bool	Init(HWND hWnd);
	void	Resize(int width, int height);
	void	Render();
};

