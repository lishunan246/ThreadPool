#include "ThreadpoolWait.h"
using namespace TP;

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
	tp_wait_ = CreateThreadpoolWait(wait_callback, static_cast<void *>(&caller), environ_);
	return tp_wait_ != nullptr;
}

void ThreadpoolWait::set(ThreadpoolWaitObject WaitObject, int timeout) const
{
	SetThreadpoolWait(tp_wait_, HANDLE(WaitObject.get()), nullptr);
}

void ThreadpoolWait::waitForCallbacks(bool fCancelPendingCallbacks) const
{
	WaitForThreadpoolWaitCallbacks(tp_wait_, fCancelPendingCallbacks);
}
