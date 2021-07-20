#pragma once

#include "IDisplay.h"

#include <GL\GL.h>
#include <GL\glext.h>

class ITexture;
class IShader;

#define NUM_LIGHTS 3
#define M_PI       3.14159265358979323846

class OpenGLShaderLightingDisplay :	public IDisplay
{
private:
	GLuint m_cylinderBufferId;
	unsigned int m_cylinderNumVertices;

	float m_cameraPosition[3];

	float m_pLightPosition[NUM_LIGHTS * 3];
	float m_pLightColor[NUM_LIGHTS * 3];
	float m_fLightRotation;

	IShader* m_pShader;

	void createCylinder(unsigned int divisions);
	void updateLightPosition();

public:
	OpenGLShaderLightingDisplay(void);
	~OpenGLShaderLightingDisplay(void);

	bool	Init(HWND hWnd);
	void	Resize(int width, int height);
	void	Render();

	PFNGLGENBUFFERSPROC pglGenBuffers;
	PFNGLBINDBUFFERPROC pglBindBuffer;
	PFNGLBUFFERDATAPROC pglBufferData;

};

