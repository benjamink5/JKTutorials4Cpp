#include "StdAfx.h"
#include "OpenGLFBOTexture.h"

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

#define glGenFramebuffers                        pglGenFramebuffers
#define glDeleteFramebuffers                     pglDeleteFramebuffers
#define glBindFramebuffer                        pglBindFramebuffer
#define glCheckFramebufferStatus                 pglCheckFramebufferStatus
#define glGetFramebufferAttachmentParameteriv    pglGetFramebufferAttachmentParameteriv
#define glGenerateMipmap                         pglGenerateMipmap
#define glFramebufferTexture2D                   pglFramebufferTexture2D
#define glFramebufferRenderbuffer                pglFramebufferRenderbuffer

#define glGenRenderbuffers                       pglGenRenderbuffers
#define glDeleteRenderbuffers                    pglDeleteRenderbuffers
#define glBindRenderbuffer                       pglBindRenderbuffer
#define glRenderbufferStorage                    pglRenderbufferStorage
#define glGetRenderbufferParameteriv             pglGetRenderbufferParameteriv
#define glIsRenderbuffer                         pglIsRenderbuffer

OpenGLFBOTexture::OpenGLFBOTexture(void)
{
	m_pImageData = NULL;

	m_nImageWidth = 0;
	m_nImageHeight = 0;
	m_nImageSize = 0;
	m_nTextureID = -1;

	m_nPboMode = 0;
}


OpenGLFBOTexture::~OpenGLFBOTexture(void)
{
	if (m_pImageData != NULL)
	{
		delete m_pImageData;
		m_pImageData = NULL;
	}
}

bool OpenGLFBOTexture::loadBmpFile(const char* szImagePath)
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

bool OpenGLFBOTexture::Load(const char* szImagePath)
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nImageWidth, m_nImageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0); // Is it correct to pass NULL for the last argument?
	status = glGetError();
	if (status != 0) return false;

	glBindTexture(GL_TEXTURE_2D, 0);

	// get pointers to GL functions
	glGenFramebuffers                     = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
	glDeleteFramebuffers                  = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
	glBindFramebuffer                     = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
	glCheckFramebufferStatus              = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
	glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
	glGenerateMipmap                      = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	glFramebufferTexture2D                = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
	glFramebufferRenderbuffer             = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
	glGenRenderbuffers                    = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
	glDeleteRenderbuffers                 = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
	glBindRenderbuffer                    = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
	glRenderbufferStorage                 = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
	glGetRenderbufferParameteriv          = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");
	glIsRenderbuffer                      = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbuffer");

	// check once again FBO extension
	if(glGenFramebuffers && glDeleteFramebuffers && glBindFramebuffer && glCheckFramebufferStatus &&
		glGetFramebufferAttachmentParameteriv && glGenerateMipmap && glFramebufferTexture2D && glFramebufferRenderbuffer &&
		glGenRenderbuffers && glDeleteRenderbuffers && glBindRenderbuffer && glRenderbufferStorage &&
		glGetRenderbufferParameteriv && glIsRenderbuffer)
	{
	}
	else
	{
		return false;
	}

	// create a framebuffer object, you need to delete them when program exits.
	glGenFramebuffers(1, &m_nFboId);
	status = glGetError();
	glBindFramebuffer(GL_FRAMEBUFFER, m_nFboId);
	status = glGetError();
	// create a renderbuffer object to store depth info
	// NOTE: A depth renderable image should be attached the FBO for depth test.
	// If we don't attach a depth renderable image to the FBO, then
	// the rendering output will be corrupted because of missing depth test.
	// If you also need stencil test for your rendering, then you must
	// attach additional image to the stencil attachement point, too.
	glGenRenderbuffers(1, &m_nRboId);
	status = glGetError();
	glBindRenderbuffer(GL_RENDERBUFFER, m_nRboId);
	status = glGetError();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_nImageWidth, m_nImageHeight);
	status = glGetError();
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	status = glGetError();

	// attach a texture to FBO color attachement point
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_nTextureID, 0);
	status = glGetError();

	// attach a renderbuffer to depth attachment point
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_nRboId);
	status = glGetError();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	status = glGetError();
 

	return true;
}

void OpenGLFBOTexture::Unload()
{
	glDeleteRenderbuffers(1, &m_nRboId);
	glDeleteFramebuffers(1, &m_nFboId);
}

bool OpenGLFBOTexture::Map()
{
	static int index = 0;
	int nextIndex = 0;                  // pbo index used for next frame
	GLenum status = 0;

	// set the rendering destination to FBO
	glBindFramebuffer(GL_FRAMEBUFFER, m_nFboId);
	status = glGetError();

	// trigger mipmaps generation explicitly
	// NOTE: If GL_GENERATE_MIPMAP is set to GL_TRUE, then glCopyTexSubImage2D()
	// triggers mipmap generation automatically. However, the texture attached
	// onto a FBO should generate mipmaps manually via glGenerateMipmap().
	glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	status = glGetError();

	glGenerateMipmap(GL_TEXTURE_2D);
	status = glGetError();

	//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)m_pImageData);
	//status = glGetError();
	
	//glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, m_nImageWidth, m_nImageHeight, 0);
	//status = glGetError();
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_nImageWidth, m_nImageHeight, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)m_pImageData);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void OpenGLFBOTexture::Unmap()
{
	GLenum status = 0;

	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int OpenGLFBOTexture::GetTextureID()
{ 
	return m_nTextureID; 
}
