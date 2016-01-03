#include "Threadpool_Work.h"



ThreadPool_Work::ThreadPool_Work()
{
}

ThreadPool_Work::ThreadPool_Work(WORK f)
{
	w = f;
}

ThreadPool_Work::~ThreadPool_Work()
{
}
