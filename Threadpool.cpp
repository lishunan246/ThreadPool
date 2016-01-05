#include "Threadpool.h"

Threadpool::Threadpool()
{
}

Threadpool::~Threadpool()
{
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
