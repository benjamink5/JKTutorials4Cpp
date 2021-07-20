#pragma once
#include "TestDriverInterface.h"

namespace JK_SDLTutorials
{
	class BaseTestDriver : public TestDriverInterface
	{
	public:
		BaseTestDriver();
		virtual ~BaseTestDriver();

		virtual void Execute();
		virtual bool Initialize();
		virtual void Destroy();
	};
}

