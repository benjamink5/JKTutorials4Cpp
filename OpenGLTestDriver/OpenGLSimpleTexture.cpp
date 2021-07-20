#include "StdAfx.h"
#include "OpenGLSimpleTexture.h"

#include <stdio.h>

#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glext.h>

OpenGLSimpleTexture::OpenGLSimpleTexture(void)
{
	m_pImageData = NULL;

	m_nImageWidth = 0;
	m_nImageHeight = 0;
	m_nImageSize = 0;
	m_nTextureID = -1;
}


OpenGLSimpleTexture::~OpenGLSimpleTexture(void)
{
	if (m_pImageData != NULL)
	{
		delete m_pImageData;
		m_pImageData = NULL;
	}
}

bool OpenGLSimpleTexture::loadBmpFile(const char* szImagePath)
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
		m_nImageSize = m_nImageWidth * m_nImageHeight * 3; // 3 : one byte for each Red, Green and Blue component
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

bool OpenGLSimpleTexture::Load(const char* szImagePath)
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_nImageWidth, m_nImageHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, m_pImageData);
	status = glGetError();
	if (status != 0) return false;

	if (m_pImageData)
	{
		delete m_pImageData;
		m_pImageData = NULL;
	}

	return true;
}

void OpenGLSimpleTexture::Unload()
{

}

bool OpenGLSimpleTexture::Map()
{
	glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	GLenum err = glGetError();

	return true;
}

void OpenGLSimpleTexture::Unmap()
{
}

unsigned int OpenGLSimpleTexture::GetTextureID()
{ 
	return m_nTextureID; 
}

