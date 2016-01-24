#include "ThreadpoolWork.h"
using namespace TP;

void __stdcall workCallback(PTP_CALLBACK_INSTANCE, void* context, PTP_WORK w)
{
	Threadpool::call(context);
}

ThreadpoolWork::ThreadpoolWork()
{
}


ThreadpoolWork::~ThreadpoolWork()
{
}

bool ThreadpoolWork::create()
{
	work_=CreateThreadpoolWork(callback_, &caller, environ_);
	return work_ != nullptr;
}

void ThreadpoolWork::waitForCallbacks(bool fCancelPendingCallbacks) const
{
	WaitForThreadpoolWorkCallbacks(work_, fCancelPendingCallbacks);
}

void ThreadpoolWork::submit() const
{
	SubmitThreadpoolWork(work_);
}

bool ThreadpoolWork::trySubmit(PTP_SIMPLE_CALLBACK pfns, void* pv)
{
	return TRUE== TrySubmitThreadpoolCallback(pfns, pv,nullptr);
}

void ThreadpoolWork::close() const
{
	CloseThreadpoolWork(work_);
}
