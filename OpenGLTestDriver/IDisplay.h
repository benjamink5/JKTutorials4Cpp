#pragma once

class IContext;

class IDisplay
{
protected:
	IContext* m_pContext;

public:
	virtual bool	Init(HWND hWnd) = 0;
	virtual void	Resize(int width, int height) = 0;
	virtual void	Render() = 0;

};