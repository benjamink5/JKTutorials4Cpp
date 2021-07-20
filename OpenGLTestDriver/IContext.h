#pragma once

class IContext
{
protected:

public:
	virtual void Init(HWND hwnd) = 0;

	virtual void Purge() = 0;
};