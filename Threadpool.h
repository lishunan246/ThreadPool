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
	virtual ~Threadpool();
	void submit(const Threadpool_Work &tp_work);
	virtual void waitForCallbacks() const;
	virtual void close() const;
	void setContext(void* context);
protected:
	CALLER caller;
private:
	PTP_WORK tp_work=nullptr;
};

