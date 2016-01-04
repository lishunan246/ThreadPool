#pragma once
#include "Threadpool.h"

void CALLBACK wait_callback(PTP_CALLBACK_INSTANCE instance, void * parameter, PTP_WAIT wait,TP_WAIT_RESULT result);

class ThreadpoolWait :
	public Threadpool
{
public:
	ThreadpoolWait();
	~ThreadpoolWait();
	void close() const override;
	bool create();
	void set(Threadpool_Work work, HANDLE handle, int timeout=0);
	void waitForCallbacks() const override;
private:
	PTP_WAIT tp_wait_=nullptr;
	PTP_WAIT_CALLBACK timer_callback_=wait_callback;
};

