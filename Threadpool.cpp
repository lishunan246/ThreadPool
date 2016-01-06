#include "Threadpool.h"

Threadpool::Threadpool()
{
	InitializeThreadpoolEnvironment(&CallBackEnviron);
	pool = CreateThreadpool(NULL);
	SetThreadpoolCallbackPool(&CallBackEnviron, pool);
}

Threadpool::~Threadpool()
{
	DestroyThreadpoolEnvironment(&CallBackEnviron);
	CloseThreadpool(pool);
}

void Threadpool::setContext(void* context)
{
	caller.context = context;
}

void Threadpool::call(void* pcaller)
{
	auto& a = *static_cast<CALLER*>(pcaller);
	a.w(a.context);
}

void Threadpool::setWork(const Threadpool_Work& work)
{
	caller.w = work.w;
}

void Threadpool::setCallbackLibrary(void* mod)
{
	SetThreadpoolCallbackLibrary(&CallBackEnviron, mod);
}

void Threadpool::setCallbackRunsLong()
{
	SetThreadpoolCallbackRunsLong(&CallBackEnviron);
}

void Threadpool::setCallbackPriority(Priority priority)
{
	switch(priority)
	{
	case High: 
		SetThreadpoolCallbackPriority(&CallBackEnviron, TP_CALLBACK_PRIORITY_HIGH);
		break;
	case Low: 
		SetThreadpoolCallbackPriority(&CallBackEnviron, TP_CALLBACK_PRIORITY_LOW);
		break;
	case Normal: 
		SetThreadpoolCallbackPriority(&CallBackEnviron, TP_CALLBACK_PRIORITY_NORMAL);
		break;
	}
}

void Threadpool::setThreadMaximum(unsigned long cthrdMost) const
{
	SetThreadpoolThreadMaximum(pool, cthrdMost);
}

void Threadpool::setThreadMinimun(unsigned long cthrdMic) const
{
	SetThreadpoolThreadMinimum(pool,cthrdMic);
}
