#include "StdAfx.h"
#include "OpenGLFBOShaderTextureDisplay.h"

#include "OpenGLContext.h"
#include "OpenGLFBOTexture.h"
#include "OpenGLShader.h"

#include <gl\GLU.h>

OpenGLFBOShaderTextureDisplay::OpenGLFBOShaderTextureDisplay(void)
{
	m_pContext = new OpenGLContext();
	m_pTexture = new OpenGLFBOTexture();
	m_pShader = new OpenGLShader();

	m_pLightAmbient[0] = 0.5f; m_pLightAmbient[1] = 0.5f;
	m_pLightAmbient[2] = 0.5f; m_pLightAmbient[3] = 1.0f;
	
	m_pLightDiffuse[0] = 1.0f; m_pLightDiffuse[1] = 1.0f;
	m_pLightDiffuse[2] = 1.0f; m_pLightDiffuse[3] = 1.0f;

	m_pLightPosition[0] = 0.0f; m_pLightPosition[1] = 0.0f;
	m_pLightPosition[2] = 2.0f; m_pLightPosition[3] = 1.0f;

	z = -5.0f;
}


OpenGLFBOShaderTextureDisplay::~OpenGLFBOShaderTextureDisplay(void)
{
	if (m_pTexture)
	{
		m_pTexture->Unload();
		delete (OpenGLFBOTexture*)m_pTexture;
		m_pTexture = NULL;
	}

	if (m_pContext)
	{
		delete (OpenGLContext*)m_pContext;
		m_pContext = NULL;
	}
}

bool OpenGLFBOShaderTextureDisplay::Init(HWND hWnd)
{
	m_pContext->Init(hWnd);

	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return false;
	}

	// Load the texture images
	if (!m_pTexture->Load("..\\Data\\textureInput.bmp"))
	{
		return false;
	}

	// Set the states
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_AMBIENT, m_pLightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_pLightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, m_pLightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One

	glEnable(GL_LIGHTING);

	// Load the shaders
	if (!m_pShader->Init())
	{
		return false;
	}

	if (!m_pShader->Load("..\\Data\\simpleVS.glsl", "..\\Data\\simpleFS.glsl"))
	{
		return false;
	}

	return TRUE;
}

void OpenGLFBOShaderTextureDisplay::Resize(int width, int height)
{
	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();	
}

void OpenGLFBOShaderTextureDisplay::Render()
{
	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return;
	}

	m_pShader->Activate();
	m_pShader->SetUniform1i("myTexture", 0);

	/* clear color and depth buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glTranslatef(0.0f, 0.0f, z);

	m_pTexture->Map();

	glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

	glEnd();

	SwapBuffers(((OpenGLContext*)m_pContext)->GetDeviceContext());

	m_pShader->Deactivate();
}
