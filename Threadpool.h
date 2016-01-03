#pragma once
#include "Threadpool_Work.h"
#include <windows.h>

struct CALLER
{
	WORK w=nullptr;
	void * context=nullptr;
};

class Threadpool
{

public:
	Threadpool();
	~Threadpool();
	void submit(const ThreadPool_Work &tp_work);
	void waitForCallback() const;
	void close() const;
	void setContext(void* context);
private:
	PTP_WORK tp_work=nullptr;
	CALLER caller;
};

