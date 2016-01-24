#include "Threadpool.h"

using namespace TP;
void __stdcall CleanupGroupCancelCallback(void* ObjectContext, void* CleanupContext)
{
	auto &a = *static_cast<CLEANUP*>(CleanupContext);
	a.c(ObjectContext, a.context);
}

Threadpool::Threadpool()
{
	InitializeThreadpoolEnvironment(&CallBackEnviron);
	pool = CreateThreadpool(nullptr);
	SetThreadpoolCallbackPool(&CallBackEnviron, pool);
	cleanup_group_ = CreateThreadpoolCleanupGroup();

	SetThreadpoolCallbackCleanupGroup(&CallBackEnviron, cleanup_group_, cleanup_group_cancel_callback_);
}

Threadpool::~Threadpool()
{
	DestroyThreadpoolEnvironment(&CallBackEnviron);
	CloseThreadpool(pool);

	CloseThreadpoolCleanupGroup(cleanup_group_);
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

void Threadpool::setCallback(const WORK& w)
{
	caller.w = w;
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
	switch (priority)
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

bool Threadpool::setThreadMinimun(unsigned long cthrdMic) const
{
	return TRUE == SetThreadpoolThreadMinimum(pool, cthrdMic);
}

void Threadpool::setCleanupContext(void* CleanupContext)
{
	cleanup_.context = CleanupContext;
}

void Threadpool::setCleanupCallback(CleanupCallback cleanup_callback)
{
	cleanup_.c = cleanup_callback;
}

void Threadpool::cleanup(bool fCancelPendingCallbacks)
{
	CloseThreadpoolCleanupGroupMembers(cleanup_group_, fCancelPendingCallbacks, &cleanup_);
}
