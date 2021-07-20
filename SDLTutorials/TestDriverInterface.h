#pragma once

namespace JK_SDLTutorials
{
	class TestDriverInterface
	{
	public:
		virtual ~TestDriverInterface() {}

		virtual bool Initialize() = 0;
		virtual void Destroy() = 0;
		virtual void Execute() = 0;
	};
}