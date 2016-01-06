#pragma once
#include "Threadpool_Work.h"
#include <Windows.h>


struct CALLER
{
	WORK w = nullptr;
	void* context = nullptr;
};

class Threadpool
{
public:
	enum Priority {High,Low,Normal};
	Threadpool();
	virtual ~Threadpool();
	virtual bool create() = 0;
	virtual void waitForCallbacks(bool fCancelPendingCallbacks = false) const = 0;
	virtual void close() const = 0;
	void setContext(void* context);
	static void call(void* pcaller);
	void setWork(const Threadpool_Work& work);
	void setCallbackLibrary(void *mod);
	void setCallbackRunsLong();
	void setCallbackPriority(Priority priority);
protected:
	CALLER caller;
	TP_CALLBACK_ENVIRON CallBackEnviron;
	PTP_CALLBACK_ENVIRON environ_=&CallBackEnviron;
};

