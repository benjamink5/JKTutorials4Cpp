#include "StdAfx.h"
#include "OpenGLShader.h"

#include <stdio.h>
#include <GL/GL.h>
#include <GL/glext.h>

#define glCreateShader			pglCreateShader
#define glAttachShader			pglAttachShader
#define glCreateProgram			pglCreateProgram
#define glCompileShader			pglCompileShader
#define glGetUniformLocation	pglGetUniformLocation
#define glUseProgram			pglUseProgram
#define glLinkProgram			pglLinkProgram
#define glGetProgramiv			pglGetProgramiv
#define glDeleteProgram			pglDeleteProgram
#define glUniformMatrix4fv		pglUniformMatrix4fv
#define glShaderSource			pglShaderSource
#define glGetShaderiv			pglGetShaderiv
#define glGetShaderInfoLog		pglGetShaderInfoLog
#define glGetUniformBlockIndex	pglGetUniformBlockIndex
#define glUniform1i				pglUniform1i
#define glUniform3fv			pglUniform3fv
#define glUniform4fv			pglUniform4fv

OpenGLShader::OpenGLShader(void)
{
	m_nProgram = 0;
}

OpenGLShader::~OpenGLShader(void)
{
	if (m_nProgram != 0)
	{
		glDeleteProgram(m_nProgram);
	}
}

bool OpenGLShader::compile(GLuint shader)
{
	GLenum status = 0;

	// Compile the shader sources into the object
	glCompileShader(shader);
	status = glGetError();
	if (status != 0)
	{
		return false;
	}

	// Verify that the shader sucessfully compiled
	GLint success;
	GLint gl_int_response;
	GLchar * gl_message;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &gl_int_response);
	gl_message = new GLchar[gl_int_response + 1];
	glGetShaderInfoLog(shader, gl_int_response, NULL, gl_message);
	if (!success)
	{		
		return false;
	}

	return true;
}

bool OpenGLShader::Init()
{
	GLenum status = 0;

	glCreateShader = ( PFNGLCREATESHADERPROC )wglGetProcAddress( LPCSTR("glCreateShader" ));
	if ( glCreateShader == NULL )
	{
		return false;
	}
		
	glAttachShader = ( PFNGLATTACHSHADERPROC )wglGetProcAddress( LPCSTR("glAttachShader" ));
	if ( glAttachShader == NULL )
	{
		return false;
	}

	glCreateProgram = ( PFNGLCREATEPROGRAMPROC )wglGetProcAddress( LPCSTR("glCreateProgram" ));
	if ( glCreateProgram == NULL )
	{
		return false;
	}
		
	glCompileShader = ( PFNGLCOMPILESHADERPROC )wglGetProcAddress( LPCSTR("glCompileShader" ));
	if ( glCompileShader == NULL )
	{
		return false;
	}

	glGetUniformLocation = ( PFNGLGETUNIFORMLOCATIONPROC )wglGetProcAddress( LPCSTR("glGetUniformLocation" ));
	if ( glGetUniformLocation == NULL )
	{
		return false;
	}

	glUseProgram = ( PFNGLUSEPROGRAMPROC )wglGetProcAddress( LPCSTR("glUseProgram" ));
	if ( glUseProgram == NULL )
	{
		return false;
	}
		
	glUniformMatrix4fv = ( PFNGLUNIFORMMATRIX4FVPROC )wglGetProcAddress( LPCSTR("glUniformMatrix4fv" ));
	if ( glUniformMatrix4fv == NULL )
	{
		return false;
	}

	glShaderSource = ( PFNGLSHADERSOURCEPROC )wglGetProcAddress( LPCSTR("glShaderSource" ));
	if ( glShaderSource == NULL )
	{
		return false;
	}

	glLinkProgram = ( PFNGLLINKPROGRAMPROC )wglGetProcAddress( LPCSTR("glLinkProgram" ));
	if ( glLinkProgram == NULL )
	{
		return false;
	}

	glGetShaderiv = ( PFNGLGETSHADERIVPROC )wglGetProcAddress( LPCSTR("glGetShaderiv" ));
	if ( glGetShaderiv == NULL )
	{
		return false;
	}

	glGetShaderInfoLog = ( PFNGLGETSHADERINFOLOGPROC )wglGetProcAddress( LPCSTR("glGetShaderInfoLog" ));
	if ( glGetShaderInfoLog == NULL )
	{
		return false;
	}

	glGetProgramiv = ( PFNGLGETPROGRAMIVPROC )wglGetProcAddress( LPCSTR("glGetProgramiv" ));
	if ( glGetProgramiv == NULL )
	{
		return false;
	}

	glDeleteProgram = ( PFNGLDELETEPROGRAMPROC )wglGetProcAddress( LPCSTR("glDeleteProgram" ));
	if ( glDeleteProgram == NULL )
	{
		return false;
	}

	glGetUniformBlockIndex = ( PFNGLGETUNIFORMBLOCKINDEXPROC )wglGetProcAddress( LPCSTR("glGetUniformBlockIndex" ));
	if ( glGetUniformBlockIndex == NULL )
	{
		return false;
	}

	glUniform1i = ( PFNGLUNIFORM1IPROC )wglGetProcAddress( LPCSTR("glUniform1i" ));
	if ( glUniform1i == NULL )
	{
		return false;
	}

	glUniform3fv = ( PFNGLUNIFORM3FVPROC )wglGetProcAddress( LPCSTR("glUniform3fv" ));
	if ( glUniform3fv == NULL )
	{
		return false;
	}

	glUniform4fv = ( PFNGLUNIFORM4FVPROC )wglGetProcAddress( LPCSTR("glUniform4fv" ));
	if ( glUniform4fv == NULL )
	{
		return false;
	}

	// Create a shader program
	m_nProgram = glCreateProgram();
	status = glGetError();
	if (status != 0)
	{
		return false;
	}

	return true;
}

bool OpenGLShader::Load(const char *szVertexShaderFile, const char *szFragmentShaderFile)
{
	if (!loadFromFile(szVertexShaderFile, GL_VERTEX_SHADER))
	{
		return false;
	}

	if (!loadFromFile(szFragmentShaderFile, GL_FRAGMENT_SHADER))
	{
		return false;
	}

	if (!link())
	{
		return false;
	}

	return true;
}

bool OpenGLShader::loadFromFile(const char *szFilePath, GLenum type)
{
	// Load the pre-compiled vertex shader
	FILE * shader = fopen( szFilePath, "r" );
	if ( shader == NULL )
	{
		printf("Could not load '%s': make sure this file is located in the same folder as the executable", szFilePath );
		return false;
	}

	fseek( shader, 0, SEEK_END );
	int dataSize = ftell( shader );
	fseek( shader, 0, SEEK_SET );

	char * buffer = new char[ dataSize + 1 ];
	size_t bytesRead = fread( buffer, 1, (size_t)dataSize, shader );
	buffer[bytesRead] = '\0';

	if (!loadFromMemory( buffer, dataSize, type ))
	{
		return false;
	}
		
	fclose( shader );
	free( buffer );

	return true;
}

bool OpenGLShader::loadFromMemory(const void * in_binaryData, size_t in_dataSize, GLenum type)
{
	// Create a shader object
	GLuint nShader = glCreateShader(type);
	GLenum status =  glGetError();
	if (status != 0)
		return false;

	// Assign the shader source which was read from the shader file
	glShaderSource(nShader, 1, (const GLchar**)&in_binaryData, NULL);
	status =  glGetError();
	if (status != 0)
		return false;

	// Compile shader
	if (!compile(nShader))
	{
		return false;
	}
		
	// Attach our shader object to the shader program
	glAttachShader(m_nProgram, nShader);
	status =  glGetError();
	if (status != 0)
	{
		return false;
	}

	return true;
}

bool OpenGLShader::link()
{
	GLenum status = 0;

	// Link the shader program
	glLinkProgram(m_nProgram);
	status = glGetError();
	if (status != 0)
	{
		return false;
	}

	// Verify that the shader link phase completed successfully
	GLint success;
	glGetProgramiv(m_nProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glDeleteProgram(m_nProgram);
		return false;
	}

	return true;
}

bool OpenGLShader::Activate()
{
	GLenum status = 0;

	// Use the shader for vertex of frament processing
	glUseProgram(m_nProgram);
	status = glGetError();
	if (status != 0)
	{
		return false;
	}
	return true;
}

void OpenGLShader::Deactivate()
{
	glUseProgram(0);
}

bool OpenGLShader::SetUniform1i(char* szVarName, int nVal)
{
	GLint loc;

	loc = getUniformLocation(szVarName);
	if (loc==-1) 
		return false;

	glUniform1i(loc, nVal);

	return true;
}

bool OpenGLShader::SetUniform3fv(char* szVarName, int nCount, float *pValue)
{
	GLint loc;

	loc = getUniformLocation(szVarName);
	if (loc==-1) 
		return false;

	glUniform3fv(loc, nCount, pValue);

	return true;
}

bool OpenGLShader::SetUniform4fv(char* szVarName, int nCount, float *pValue)
{
	GLint loc;

	loc = getUniformLocation(szVarName);
	if (loc==-1) 
		return false;

	glUniform4fv(loc, nCount, pValue);

	return true;
}

int OpenGLShader::getUniformLocation(const char* name)
{
	GLint loc;

	loc = glGetUniformLocation(m_nProgram, name);
	if (loc == -1) 
	{
        printf("Error: can't find uniform variable \"%s\"\n", name);
	}

 	return loc;
}