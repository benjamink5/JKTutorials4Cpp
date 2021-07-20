#pragma once

#include "ITexture.h"
#include <GL\gl.h>
#include <GL\glext.h>

class OpenGLPBOTexture :
	public ITexture
{
public:
	OpenGLPBOTexture(void);
	~OpenGLPBOTexture(void);

	bool Load(const char* szImagePath);

	void Unload();
	
	unsigned int GetTextureID();

	bool Map();
	void Unmap();

private:
	bool loadBmpFile(const char* szImagePath);

	unsigned char*	m_pImageData;		// Actual RGB data
	unsigned int	m_nImageWidth;
	unsigned int	m_nImageHeight;
	unsigned int	m_nImageSize;

	unsigned int	m_pPboIds[2];                   // IDs of PBO
	unsigned int	m_nPboMode;


	PFNGLGENBUFFERSARBPROC pglGenBuffersARB;                     // VBO Name Generation Procedure
	PFNGLBINDBUFFERARBPROC pglBindBufferARB;                     // VBO Bind Procedure
	PFNGLBUFFERDATAARBPROC pglBufferDataARB;                     // VBO Data Loading Procedure
	PFNGLBUFFERSUBDATAARBPROC pglBufferSubDataARB;               // VBO Sub Data Loading Procedure
	PFNGLDELETEBUFFERSARBPROC pglDeleteBuffersARB;               // VBO Deletion Procedure
	PFNGLGETBUFFERPARAMETERIVARBPROC pglGetBufferParameterivARB; // return various parameters of VBO
	PFNGLMAPBUFFERARBPROC pglMapBufferARB;                       // map VBO procedure
	PFNGLUNMAPBUFFERARBPROC pglUnmapBufferARB;                   // unmap VBO procedure
};

