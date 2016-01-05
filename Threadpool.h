#pragma once
#include "Threadpool_Work.h"
#include <windows.h>

struct CALLER
{
	WORK w = nullptr;
	void* context = nullptr;
};

class Threadpool
{
public:
	Threadpool();
	virtual ~Threadpool();
	virtual bool create() =0;
	virtual void waitForCallbacks(bool fCancelPendingCallbacks = false) const = 0;
	virtual void close() const = 0;
	void setContext(void* context);
	static void call(void* pcaller);
	virtual void setWork(const Threadpool_Work& work);
protected:
	CALLER caller;
};

