#pragma once

#include "ITexture.h"

class OpenGLSimpleTexture : public ITexture
{
public:
	OpenGLSimpleTexture(void);
	~OpenGLSimpleTexture(void);

	bool Load(const char* szImagePath);

	void Unload();
	
	bool Map();
	void Unmap();
	
	unsigned int GetTextureID();

	//unsigned int GetImageWidth() { return m_nImageWidth; }
	//unsigned int GetImageHeight() { return m_nImageHeight; }
	//unsigned int GetImageSize() { return m_nImageSize; }
	//unsigned char* GetImageData() { return m_pImageData; }

private:
	bool loadBmpFile(const char* szImagePath);

	unsigned char*	m_pImageData;		// Actual RGB data
	unsigned int	m_nImageWidth;
	unsigned int	m_nImageHeight;
	unsigned int	m_nImageSize;
};

