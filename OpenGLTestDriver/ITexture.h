#pragma once

class ITexture
{
protected:
	unsigned int	m_nTextureID;

public:
	virtual unsigned int GetTextureID() = 0;

	virtual bool Map() = 0;
	virtual void Unmap() = 0;
	virtual bool Load(const char* szImagePath) = 0;
	virtual void Unload() = 0;

};