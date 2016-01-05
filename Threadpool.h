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
	void submit() const;
	virtual bool create();
	virtual void waitForCallbacks(bool fCancelPendingCallbacks=false) const;
	virtual void close() const;
	void setContext(void* context);
	static void call(void * pcaller);
	virtual void setWork(const Threadpool_Work &work);
protected:
	CALLER caller;
	
private:
	PTP_WORK tp_work=nullptr;
};

