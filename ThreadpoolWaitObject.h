#pragma once
#ifdef WIN32
#include <windows.h>
#endif

namespace TP
{
	class ThreadpoolWaitObject
	{
	public:
		ThreadpoolWaitObject();
		~ThreadpoolWaitObject();
		void *get() const;
		void set() const;
		void reset() const;
	private:
#ifdef WIN32
		HANDLE handle = CreateEvent(nullptr, false, false, nullptr);
#endif
	};
}

