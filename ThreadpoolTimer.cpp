#include "ThreadpoolTimer.h"


void __stdcall callback(PTP_CALLBACK_INSTANCE instance, void* parameter, PTP_TIMER)
{
	Threadpool::call(parameter);
}

ThreadpoolTimer::ThreadpoolTimer()
{
}


ThreadpoolTimer::~ThreadpoolTimer()
{
}

bool ThreadpoolTimer::create()
{
	timer_ = CreateThreadpoolTimer(timer_callback_, &caller, environ_);
	return timer_ != nullptr;
}

bool ThreadpoolTimer::isSet() const
{
	return IsThreadpoolTimerSet(timer_)==TRUE;
}

void ThreadpoolTimer::waitForCallbacks(bool fCancelPendingCallbacks) const
{
	WaitForThreadpoolTimerCallbacks(timer_, fCancelPendingCallbacks);
}

void ThreadpoolTimer::set(PFILETIME pftDueTime, unsigned long msPeriod, unsigned long msWindowLength) const
{
	SetThreadpoolTimer(timer_, pftDueTime, msPeriod, msWindowLength);
}

void ThreadpoolTimer::close() const
{
	CloseThreadpoolTimer(timer_);
}
