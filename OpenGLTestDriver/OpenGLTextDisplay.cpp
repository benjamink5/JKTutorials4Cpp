#include "StdAfx.h"
#include "OpenGLContext.h"
#include "OpenGLTextDisplay.h"
#include "OpenGLShader.h"

OpenGLTextDisplay::OpenGLTextDisplay(void)
{
	m_pContext = new OpenGLContext();

	m_pText = new OpenGLText();

	m_pShader = new OpenGLShader();
}

OpenGLTextDisplay::~OpenGLTextDisplay(void)
{
	if (m_pText)
	{
		//m_pText->clean();

		delete m_pText;
		m_pText = NULL;
	}

	if (m_pShader)
	{
		delete m_pShader;
		m_pShader = NULL;
	}

	if (m_pContext)
	{
		delete m_pContext;
		m_pContext = NULL;
	}
}

bool OpenGLTextDisplay::Init(HWND hWnd)
{
	m_pContext->Init(hWnd);

	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return FALSE;
	}

	// Load the shaders
	if (!m_pShader->Init())
	{
		return false;
	}

	if (!m_pShader->Load("..\\Data\\textVS.glsl", "..\\Data\\textFS.glsl"))
	{
		return false;
	}

	m_pText->init("../Data/ArchivoBlack-Regular.otf", 128);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);



	return TRUE;
}

void OpenGLTextDisplay::Resize(int width, int height)
{
	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return;
	}

	m_fWidth = width;
	m_fHeight = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
	//gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();	
}

void OpenGLTextDisplay::Render()
{
	if (!((OpenGLContext*)m_pContext)->GetRenderContext())
	{
		return;
	}

	//m_pShader->Activate();
	//float color[4] = {1.0f, 1.0f, 0.0f, 1.0f};
	//m_pShader->SetUniform4fv("color", 4, color);
	//m_pShader->SetUniform1i("tex", 0);
 
	/* clear color and depth buffers */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	{
		glTranslatef(0, 0, -2.0f);
		glRotatef(30.0F, 1.0F, 0.0F, 0.0F);
		glRotatef(30.0F, 0.0F, 1.0F, 0.0F);

		glBegin(GL_QUADS);
		glNormal3f( 0.0F, 0.0F, 1.0F);
		glVertex3f( 0.5F, 0.5F, 0.5F); glVertex3f(-0.5F, 0.5F, 0.5F);
		glVertex3f(-0.5F,-0.5F, 0.5F); glVertex3f( 0.5F,-0.5F, 0.5F);

		glNormal3f( 0.0F, 0.0F,-1.0F);
		glVertex3f(-0.5F,-0.5F,-0.5F); glVertex3f(-0.5F, 0.5F,-0.5F);
		glVertex3f( 0.5F, 0.5F,-0.5F); glVertex3f( 0.5F,-0.5F,-0.5F);

		glNormal3f( 0.0F, 1.0F, 0.0F);
		glVertex3f( 0.5F, 0.5F, 0.5F); glVertex3f( 0.5F, 0.5F,-0.5F);
		glVertex3f(-0.5F, 0.5F,-0.5F); glVertex3f(-0.5F, 0.5F, 0.5F);

		glNormal3f( 0.0F,-1.0F, 0.0F);
		glVertex3f(-0.5F,-0.5F,-0.5F); glVertex3f( 0.5F,-0.5F,-0.5F);
		glVertex3f( 0.5F,-0.5F, 0.5F); glVertex3f(-0.5F,-0.5F, 0.5F);

		glNormal3f( 1.0F, 0.0F, 0.0F);
		glVertex3f( 0.5F, 0.5F, 0.5F); glVertex3f( 0.5F,-0.5F, 0.5F);
		glVertex3f( 0.5F,-0.5F,-0.5F); glVertex3f( 0.5F, 0.5F,-0.5F);

		glNormal3f(-1.0F, 0.0F, 0.0F);
		glVertex3f(-0.5F,-0.5F,-0.5F); glVertex3f(-0.5F,-0.5F, 0.5F);
		glVertex3f(-0.5F, 0.5F, 0.5F); glVertex3f(-0.5F, 0.5F,-0.5F);
		glEnd();
	}
	glPopMatrix();

 	// Draw a text
	glColor3ub(0xff, 0, 0);
	m_pText->write(100, 100, "123ABCabc");
	//m_pText->write("ABC", 100, 100, ALIGN_RIGHT); 

	//m_pShader->Deactivate();

	SwapBuffers(((OpenGLContext*)m_pContext)->GetDeviceContext());
}