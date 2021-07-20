#pragma once

#include "IContext.h"

class OpenGLContext : public IContext
{
public:
	OpenGLContext(void);
	~OpenGLContext(void);

	void Init(HWND hwnd);

	void Purge();

	HGLRC GetRenderContext() { return m_hRC; }
	HDC   GetDeviceContext() { return m_hDC; }

private:
	void reset();

	HWND m_hWnd;
	HDC m_hDC;
	HGLRC m_hRC;
};

