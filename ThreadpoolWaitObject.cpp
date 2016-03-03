#include "ThreadpoolWaitObject.h"

TP::ThreadpoolWaitObject::ThreadpoolWaitObject()
{
}

TP::ThreadpoolWaitObject::~ThreadpoolWaitObject()
{
}

void* TP::ThreadpoolWaitObject::get() const
{
	return handle;
}

void TP::ThreadpoolWaitObject::set() const
{
	SetEvent(handle);
}

void TP::ThreadpoolWaitObject::reset() const
{
	ResetEvent(handle);
}

