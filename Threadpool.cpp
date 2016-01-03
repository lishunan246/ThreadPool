#include "Threadpool.h"


void NTAPI WorkCallback(PTP_CALLBACK_INSTANCE , void* context, PTP_WORK w)
{
	 auto a=*static_cast< CALLER* >(context);
	 a.w(a.context);
}


Threadpool::Threadpool()
{
}

Threadpool::~Threadpool()
{
}

void Threadpool::waitForCallback() const
{
	WaitForThreadpoolWorkCallbacks(tp_work, FALSE);
}

void Threadpool::close() const
{
	CloseThreadpoolWork(tp_work);
}

void Threadpool::setContext(void* context)
{
	caller.context = context;
}

void Threadpool::submit(const ThreadPool_Work &t)
{
	caller.w = t.w;
	tp_work = CreateThreadpoolWork(WorkCallback, static_cast<void *>(&caller), nullptr);

	SubmitThreadpoolWork(tp_work);
}
