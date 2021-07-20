#include "StdAfx.h"
#include "OpenGLShaderLightingDisplay.h"

#include "OpenGLContext.h"
#include "OpenGLSimpleTexture.h"
#include "OpenGLShader.h"

#include <gl\GLU.h>
#include <GL\glext.h>
#include <GL\glut.h>
#include <math.h>

#define glGenBuffers			pglGenBuffers
#define glBindBuffer			pglBindBuffer
#define glBufferData			pglBufferData

OpenGLShaderLightingDisplay::OpenGLShaderLightingDisplay(void)
{
	m_pContext = new OpenGLContext();
	m_pShader = new OpenGLShader();
}

OpenGLShaderLightingDisplay::~OpenGLShaderLightingDisplay(void)
{
	if (m_pContext)
	{
		delete (OpenGLContext*)m_pContext;
		m_pContext = NULL;
	}
}

bool OpenGLShaderLightingDisplay::Init(HWND hWnd)
{
	m_pContext->Init(hWnd);

	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return false;
	}

	glGenBuffers = ( PFNGLGENBUFFERSPROC )wglGetProcAddress( LPCSTR("glGenBuffers" ));
	if ( glGenBuffers == NULL )
	{
		return false;
	}

	glBindBuffer = ( PFNGLBINDBUFFERPROC )wglGetProcAddress( LPCSTR("glBindBuffer" ));
	if ( glBindBuffer == NULL )
	{
		return false;
	}

	glBufferData = ( PFNGLBUFFERDATAPROC )wglGetProcAddress( LPCSTR("glBufferData" ));
	if ( glBufferData == NULL )
	{
		return false;
	}

	// Set the states
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Load the shaders
	if (!m_pShader->Init())
	{
		return false;
	}

	if (!m_pShader->Load("..\\Data\\lightingVS.glsl", "..\\Data\\lightingFS.glsl"))
	{
		return false;
	}

	// set up red/green/blue lights
	m_pLightColor[0] = 1.0f; m_pLightColor[1] = 0.0f; m_pLightColor[2] = 0.0f;
	m_pLightColor[3] = 0.0f; m_pLightColor[4] = 1.0f; m_pLightColor[5] = 0.0f;
	m_pLightColor[6] = 0.0f; m_pLightColor[7] = 0.0f; m_pLightColor[8] = 1.0f;

	// create cylinder
	createCylinder(36);

	// do the first cycle to initialize positions
	m_fLightRotation = 0.0f;

	// setup camera
	m_cameraPosition[0] = 0.0f;
	m_cameraPosition[1] = 0.0f;
	m_cameraPosition[2] = 4.0f;

	return TRUE;
}

void OpenGLShaderLightingDisplay::Resize(int width, int height)
{
	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 200.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();	
}

void OpenGLShaderLightingDisplay::Render()
{
	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return;
	}

	m_pShader->Activate();
	m_pShader->SetUniform3fv("cameraPosition", 1, m_cameraPosition);
	m_pShader->SetUniform3fv("lightPosition", NUM_LIGHTS, m_pLightPosition);
	m_pShader->SetUniform3fv("lightColor", NUM_LIGHTS, m_pLightColor);

	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	glTranslatef(-m_cameraPosition[0], -m_cameraPosition[1], -m_cameraPosition[2]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_cylinderNumVertices);

	// render each light
	for (int i = 0; i < NUM_LIGHTS; ++i) 
	{
		// render sphere with the light's color/position
		glPushMatrix();
		glTranslatef(m_pLightPosition[i * 3 + 0], m_pLightPosition[i * 3 + 1], m_pLightPosition[i * 3 + 2]);
		glColor3fv(m_pLightColor + (i * 3));
		glutSolidSphere(0.04, 36, 36);
		glPopMatrix();
	}

	m_pShader->Deactivate();

	SwapBuffers(((OpenGLContext*)m_pContext)->GetDeviceContext());

	updateLightPosition();
}

void OpenGLShaderLightingDisplay::updateLightPosition()
{
	static unsigned int prevTicks = 0;
	unsigned int ticks;
	float secondsElapsed;
	int i;

	// calculate the number of seconds that have
	// passed since the last call to this function
	if(prevTicks == 0)
		prevTicks = GetTickCount();
	ticks = GetTickCount();
	secondsElapsed = (float)(ticks - prevTicks) / 1000.0f;
	prevTicks = ticks;

	// update the light positions 
	m_fLightRotation += (M_PI / 4.0f) * secondsElapsed;
	for(i = 0; i < NUM_LIGHTS; ++i) {
		const float radius = 1.75f;
		float r = (((M_PI * 2.0f) / (float)NUM_LIGHTS) * (float)i) + m_fLightRotation;

		m_pLightPosition[i * 3 + 0] = cosf(r) * radius;
		m_pLightPosition[i * 3 + 1] = cosf(r) * sinf(r);
		m_pLightPosition[i * 3 + 2] = sinf(r) * radius;
	}

}


void OpenGLShaderLightingDisplay::createCylinder(unsigned int divisions)
{
	const int floatsPerVertex = 6;
	unsigned int i, size;
	float *v;

	m_cylinderNumVertices = (divisions + 1) * 2;
	size = floatsPerVertex * m_cylinderNumVertices;

	// generate vertex data
	v = (float *)malloc(sizeof(float) * size);
	for(i = 0; i <= divisions; ++i) {
		float r = ((M_PI * 2.0f) / (float)divisions) * (float)i;
		unsigned int index1 = i * 2 * floatsPerVertex;
		unsigned int index2 = index1 + floatsPerVertex;

		// vertex positions
		v[index1 + 0] = cosf(r);
		v[index1 + 1] = 1.0f;
		v[index1 + 2] = -sinf(r);
		v[index2 + 0] = cosf(r);
		v[index2 + 1] = -1.0f;
		v[index2 + 2] = -sinf(r);

		// normals
		v[index1 + 3] = cosf(r);
		v[index1 + 4] = 0.0f;
		v[index1 + 5] = -sinf(r);
		v[index2 + 3] = v[index1 + 3];
		v[index2 + 4] = v[index1 + 4];
		v[index2 + 5] = v[index1 + 5];
	}

	// create vertex buffer
	glGenBuffers(1, &m_cylinderBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_cylinderBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, v, GL_STATIC_DRAW);
	free(v);

	// enable arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// set pointers
	glVertexPointer(3, GL_FLOAT, sizeof(float) * floatsPerVertex, 0);
	glNormalPointer(GL_FLOAT, sizeof(float) * floatsPerVertex, (const GLvoid *)(sizeof(float) * 3));
}