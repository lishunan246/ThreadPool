#include "ThreadpoolTimer.h"

using namespace TP;

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

void ThreadpoolTimer::set(unsigned long long hundredNS, unsigned long msPeriod, unsigned long msWindowLength) const
{
	FILETIME FileTime;
	ULARGE_INTEGER integer;
	integer.QuadPart = 0-hundredNS;
	FileTime.dwHighDateTime = integer.HighPart;
	FileTime.dwLowDateTime = integer.LowPart;
	SetThreadpoolTimer(timer_, &FileTime, msPeriod, msWindowLength);
}

void ThreadpoolTimer::close() const
{
	CloseThreadpoolTimer(timer_);
}
