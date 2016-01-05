#pragma once
#include "Threadpool.h"

void CALLBACK callback(PTP_CALLBACK_INSTANCE instance, void *parameter, PTP_TIMER);

class ThreadpoolTimer :
	public Threadpool
{
public:
	ThreadpoolTimer();
	~ThreadpoolTimer();
	bool create() override;
	bool isSet() const;
	void waitForCallbacks(bool fCancelPendingCallbacks=false) const override;
	void set(PFILETIME pftDueTime,unsigned long msPeriod, unsigned long msWindowLength) const;
	void close() const override;
private:
	PTP_TIMER_CALLBACK timer_callback_ = callback;
	PTP_TIMER timer_ = nullptr;
};

