#pragma once

#include <GL/GL.h>
#include <GL/glext.h>

#include "IShader.h"

class OpenGLShader : public IShader
{
public:
	OpenGLShader(void);
	~OpenGLShader(void);

	bool	Init();
	bool	Load(const char *szVertexShaderFile, const char *szFragmentShaderFile);
	bool	Activate();
	void	Deactivate();

	bool	SetUniform1i(char* szVarName, int nVal);
	bool	SetUniform3fv(char* szVarName, int nCount, float *pValue);
	bool	SetUniform4fv(char* szVarName, int nCount, float *pValue);

	GLuint  getProgramId() { return m_nProgram; }

private:
	GLuint	m_nProgram;

	bool	compile(GLuint shader);
	bool	link();
	bool	loadFromFile(const char *szFilePath, GLenum type);
	bool	loadFromMemory(const void * in_binaryData, size_t in_dataSize, unsigned int type);

	int		getUniformLocation(const char* name);

	PFNGLCREATESHADERPROC			pglCreateShader;
	PFNGLATTACHSHADERPROC			pglAttachShader;
	PFNGLCREATEPROGRAMPROC			pglCreateProgram;
	PFNGLCOMPILESHADERPROC			pglCompileShader;
	PFNGLGETUNIFORMLOCATIONPROC		pglGetUniformLocation;
	PFNGLUSEPROGRAMPROC				pglUseProgram;
	PFNGLLINKPROGRAMPROC			pglLinkProgram;
	PFNGLGETPROGRAMIVPROC			pglGetProgramiv;
	PFNGLDELETEPROGRAMPROC			pglDeleteProgram;
	PFNGLUNIFORMMATRIX4FVPROC		pglUniformMatrix4fv;
	PFNGLSHADERSOURCEPROC			pglShaderSource;
	PFNGLGETSHADERIVPROC			pglGetShaderiv;
	PFNGLGETSHADERINFOLOGPROC		pglGetShaderInfoLog;
	PFNGLGETUNIFORMBLOCKINDEXPROC	pglGetUniformBlockIndex;
	PFNGLUNIFORM1IPROC				pglUniform1i;
	PFNGLUNIFORM3FVPROC				pglUniform3fv;
	PFNGLUNIFORM4FVPROC				pglUniform4fv;
};

