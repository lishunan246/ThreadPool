#include "ThreadpoolWork.h"
using namespace TP;

void __stdcall workCallback(PTP_CALLBACK_INSTANCE, void* context, PTP_WORK w)
{
	Threadpool::call(context);
}

void CALLBACK SimpleCallback(PTP_CALLBACK_INSTANCE,PVOID Context)
{
	auto& a = *static_cast<CALLER*>(Context);
	a.w(a.context);
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

bool ThreadpoolWork::trySubmit(CALLER* work, void* pv)
{
	
	return TRUE== TrySubmitThreadpoolCallback(SimpleCallback, work,nullptr);
}

void ThreadpoolWork::close() const
{
	CloseThreadpoolWork(work_);
}
