#pragma once
#include "Threadpool.h"

void NTAPI workCallback(PTP_CALLBACK_INSTANCE, void* context, PTP_WORK w);

class ThreadpoolWork :
	public Threadpool
{
public:
	ThreadpoolWork();
	~ThreadpoolWork();
	bool create() override;
	void waitForCallbacks(bool fCancelPendingCallbacks=false) const override;
	void submit() const;
	static bool trySubmit(PTP_SIMPLE_CALLBACK pfns, void * pv);
	void close() const override;
private:
	PTP_WORK_CALLBACK callback_=workCallback;
	PTP_WORK work_ = nullptr;
};

