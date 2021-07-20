#pragma once

#include "ITexture.h"
#include <GL\gl.h>
#include <GL\glext.h>

class OpenGLFBOTexture : public ITexture
{
public:
	OpenGLFBOTexture(void);
	~OpenGLFBOTexture(void);

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

	unsigned int	m_nFboId;
	unsigned int	m_nRboId;


	PFNGLGENBUFFERSARBPROC pglGenBuffersARB;                     // VBO Name Generation Procedure
	PFNGLBINDBUFFERARBPROC pglBindBufferARB;                     // VBO Bind Procedure
	PFNGLBUFFERDATAARBPROC pglBufferDataARB;                     // VBO Data Loading Procedure
	PFNGLBUFFERSUBDATAARBPROC pglBufferSubDataARB;               // VBO Sub Data Loading Procedure
	PFNGLDELETEBUFFERSARBPROC pglDeleteBuffersARB;               // VBO Deletion Procedure
	PFNGLGETBUFFERPARAMETERIVARBPROC pglGetBufferParameterivARB; // return various parameters of VBO
	PFNGLMAPBUFFERARBPROC pglMapBufferARB;                       // map VBO procedure
	PFNGLUNMAPBUFFERARBPROC pglUnmapBufferARB;                   // unmap VBO procedure

	// Framebuffer object
	PFNGLGENFRAMEBUFFERSPROC                     pglGenFramebuffers;                      // FBO name generation procedure
	PFNGLDELETEFRAMEBUFFERSPROC                  pglDeleteFramebuffers;                   // FBO deletion procedure
	PFNGLBINDFRAMEBUFFERPROC                     pglBindFramebuffer;                      // FBO bind procedure
	PFNGLCHECKFRAMEBUFFERSTATUSPROC              pglCheckFramebufferStatus;               // FBO completeness test procedure
	PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC pglGetFramebufferAttachmentParameteriv;  // return various FBO parameters
	PFNGLGENERATEMIPMAPPROC                      pglGenerateMipmap;                       // FBO automatic mipmap generation procedure
	PFNGLFRAMEBUFFERTEXTURE2DPROC                pglFramebufferTexture2D;                 // FBO texdture attachement procedure
	PFNGLFRAMEBUFFERRENDERBUFFERPROC             pglFramebufferRenderbuffer;              // FBO renderbuffer attachement procedure
	// Renderbuffer object
	PFNGLGENRENDERBUFFERSPROC                    pglGenRenderbuffers;                     // renderbuffer generation procedure
	PFNGLDELETERENDERBUFFERSPROC                 pglDeleteRenderbuffers;                  // renderbuffer deletion procedure
	PFNGLBINDRENDERBUFFERPROC                    pglBindRenderbuffer;                     // renderbuffer bind procedure
	PFNGLRENDERBUFFERSTORAGEPROC                 pglRenderbufferStorage;                  // renderbuffer memory allocation procedure
	PFNGLGETRENDERBUFFERPARAMETERIVPROC          pglGetRenderbufferParameteriv;           // return various renderbuffer parameters
	PFNGLISRENDERBUFFERPROC                      pglIsRenderbuffer;                       // determine renderbuffer object type

};

