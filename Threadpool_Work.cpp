#include "Threadpool_Work.h"



Threadpool_Work::Threadpool_Work()
{
}

Threadpool_Work::Threadpool_Work(WORK f)
{
	w = f;
}

Threadpool_Work::~Threadpool_Work()
{
}

const WORK& Threadpool_Work::getInstance() const
{
	return w;
}
