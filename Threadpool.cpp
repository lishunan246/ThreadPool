#include "Threadpool.h"


void NTAPI WorkCallback(PTP_CALLBACK_INSTANCE , void* context, PTP_WORK w)
{
	 Threadpool::call(context);
}


Threadpool::Threadpool()
{
}

Threadpool::~Threadpool()
{
}

void Threadpool::waitForCallbacks(bool fCancelPendingCallbacks) const
{
	WaitForThreadpoolWorkCallbacks(tp_work, fCancelPendingCallbacks);
}

void Threadpool::close() const
{
	CloseThreadpoolWork(tp_work);
}

void Threadpool::setContext(void* context)
{
	caller.context = context;
}

void Threadpool::call(void* pcaller)
{
	auto &a = *static_cast< CALLER* >(pcaller);
	a.w(a.context);
}

void Threadpool::setWork(const Threadpool_Work &work)
{
	caller.w = work.w;
}

void Threadpool::submit() const
{
	SubmitThreadpoolWork(tp_work);
}

bool Threadpool::create()
{
	tp_work = CreateThreadpoolWork(WorkCallback, static_cast<void *>(&caller), nullptr);
	return tp_work != nullptr;
}
