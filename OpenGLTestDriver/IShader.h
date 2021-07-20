#pragma once

class IShader
{
protected:

public:
	virtual bool Init() = 0;
	virtual bool Load(const char *szVertexShaderFile, const char *szFragmentShaderFile) = 0;
	virtual bool Activate() = 0;
	virtual void Deactivate() = 0;

	virtual bool SetUniform1i(char* szVarName, int nVal) = 0;
	virtual bool SetUniform3fv(char* szVarName, int nCount, float *pValue) = 0;
	virtual bool SetUniform4fv(char* szVarName, int nCount, float *pValue) = 0;

};