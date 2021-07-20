#include "StdAfx.h"
#include "OpenGLPBOTexture.h"

#include <stdio.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glext.h>

#define glGenBuffersARB           pglGenBuffersARB
#define glBindBufferARB           pglBindBufferARB
#define glBufferDataARB           pglBufferDataARB
#define glBufferSubDataARB        pglBufferSubDataARB
#define glDeleteBuffersARB        pglDeleteBuffersARB
#define glGetBufferParameterivARB pglGetBufferParameterivARB
#define glMapBufferARB            pglMapBufferARB
#define glUnmapBufferARB          pglUnmapBufferARB

OpenGLPBOTexture::OpenGLPBOTexture(void)
{
	m_pImageData = NULL;

	m_nImageWidth = 0;
	m_nImageHeight = 0;
	m_nImageSize = 0;
	m_nTextureID = -1;

	m_nPboMode = 2;
}


OpenGLPBOTexture::~OpenGLPBOTexture(void)
{
	if (m_pImageData != NULL)
	{
		delete m_pImageData;
		m_pImageData = NULL;
	}
}

bool OpenGLPBOTexture::loadBmpFile(const char* szImagePath)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins

	// Open the file
	FILE * file = fopen(szImagePath,"rb");
	if (!file)                              
	{
		printf("Image could not be opened\n"); 
		return 0;
	}

	if ( fread(header, 1, 54, file)!=54 ) // If not 54 bytes read : problem
	{ 
		printf("Not a correct BMP file\n");
		return false;
	}

	if ( header[0]!='B' || header[1]!='M' )
	{
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos			= *(int*)&(header[0x0A]);
	m_nImageSize	= *(int*)&(header[0x22]);
	m_nImageWidth	= *(int*)&(header[0x12]);
	m_nImageHeight	= *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (m_nImageSize == 0)
		m_nImageSize = m_nImageWidth * m_nImageHeight * 4; // 4 : one byte for each Red, Green, Blue, and Alpha component
	if (dataPos == 0)
		dataPos = 54; // The BMP header is done that way

	// Create a buffer
	if (m_pImageData) delete m_pImageData;
	m_pImageData = new unsigned char[m_nImageSize];

	// Read the actual data from the file into the buffer
	fread(m_pImageData, 1, m_nImageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	return true;
}

bool OpenGLPBOTexture::Load(const char* szImagePath)
{
	GLenum status = 0;

	if (!loadBmpFile(szImagePath))
		return false;

	// Create one OpenGL texture
	glGenTextures(1, &m_nTextureID);
	status = glGetError();
	if (status != 0) return false;

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	status = glGetError();
	if (status != 0) return false;
 
	// Give the image to OpenGL 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nImageWidth, m_nImageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0); // Is it correct to pass NULL for the last argument?
	status = glGetError();
	if (status != 0) return false;

	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_nPboMode > 0)
	{
		// get pointers to GL functions
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
		glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)wglGetProcAddress("glBufferSubDataARB");
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
		glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)wglGetProcAddress("glGetBufferParameterivARB");
		glMapBufferARB = (PFNGLMAPBUFFERARBPROC)wglGetProcAddress("glMapBufferARB");
		glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)wglGetProcAddress("glUnmapBufferARB");

		// check once again PBO extension
		if (glGenBuffersARB && glBindBufferARB && glBufferDataARB && glBufferSubDataARB &&
			glMapBufferARB && glUnmapBufferARB && glDeleteBuffersARB && glGetBufferParameterivARB) 
		{
		}
		else
		{
			return false;
		}

		glGenBuffersARB(1, m_pPboIds);
		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_pPboIds[0]);
		glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_nImageSize, 0, GL_STREAM_DRAW_ARB);
		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_pPboIds[1]);
		glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_nImageSize, 0, GL_STREAM_DRAW_ARB);
		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	}

	return true;
}

void OpenGLPBOTexture::Unload()
{

}

bool OpenGLPBOTexture::Map()
{
	static int index = 0;
	int nextIndex = 0;                  // pbo index used for next frame
	GLenum status = 0;

	glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	status = glGetError();

	if (m_nPboMode > 0 && m_nPboMode < 3)
	{
		// "index" is used to copy pixels from a PBO to a texture object
        // "nextIndex" is used to update pixels in a PBO
 		if (m_nPboMode == 1)
		{
			// In single PBO mode, the index and nextIndex are set to 0
			index = nextIndex = 0;
 		}
		else if (m_nPboMode == 2)
		{
			// In dual PBO mode, increment current index first then get the next index
			index = (index + 1) % 2;
			nextIndex = (index + 1) % 2;
		}

		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_pPboIds[index]);
		status = glGetError();

		// copy pixels from PBO to texture object
		// Use offset instead of ponter.
	
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_nImageWidth, m_nImageHeight, GL_BGRA, GL_UNSIGNED_BYTE, 0);
		status = glGetError();

		glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_nImageSize, 0, GL_STREAM_DRAW_ARB);
		status = glGetError();

		// bind PBO to update pixel values
		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_pPboIds[nextIndex]);

		// map the buffer object into client's memory
		// Note that glMapBufferARB() causes sync issue.
		// If GPU is working with this buffer, glMapBufferARB() will wait(stall)
		// for GPU to finish its job. To avoid waiting (stall), you can call
		// first glBufferDataARB() with NULL pointer before glMapBufferARB().
		// If you do that, the previous data in PBO will be discarded and
		// glMapBufferARB() returns a new allocated pointer immediately
		// even if GPU is still working with the previous data.
		GLubyte* pMapPtr = (GLubyte*)glMapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY_ARB);
		if (pMapPtr)
		{
			// update data directly on the mapped buffer
			memcpy(pMapPtr, m_pImageData, m_nImageSize);
			glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB); // release pointer to mapping buffer
		}

		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	}
	else
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_nImageWidth, m_nImageHeight, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)m_pImageData);
	}

	return true;
}

void OpenGLPBOTexture::Unmap()
{
}


unsigned int OpenGLPBOTexture::GetTextureID()
{ 
	return m_nTextureID; 
}
