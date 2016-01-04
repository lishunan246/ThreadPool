#include "ThreadpoolWait.h"


void __stdcall wait_callback(PTP_CALLBACK_INSTANCE instance, void * parameter, PTP_WAIT wait, TP_WAIT_RESULT result)
{
	auto &a = *static_cast< CALLER* >(parameter);
	a.w(a.context);
}

ThreadpoolWait::ThreadpoolWait()
{
}


ThreadpoolWait::~ThreadpoolWait()
{
}

void ThreadpoolWait::close() const
{
	CloseThreadpoolWait(tp_wait_);
}

bool ThreadpoolWait::create()
{
	tp_wait_ = CreateThreadpoolWait(wait_callback, static_cast<void *>(&caller), nullptr);
	return tp_wait_ != nullptr;
}

void ThreadpoolWait::set(Threadpool_Work work, HANDLE handle, int timeout)
{
	caller.w = work.getInstance();
	SetThreadpoolWait(tp_wait_, handle, nullptr);
}

void ThreadpoolWait::waitForCallbacks() const
{
	WaitForThreadpoolWaitCallbacks(tp_wait_, false);
}
