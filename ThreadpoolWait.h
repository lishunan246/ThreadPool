#pragma once
#include "Threadpool.h"

void CALLBACK wait_callback(PTP_CALLBACK_INSTANCE instance, void* parameter, PTP_WAIT wait, TP_WAIT_RESULT result);

namespace TP
{
	class ThreadpoolWait :
		public Threadpool
	{
	public:
		ThreadpoolWait();
		~ThreadpoolWait();
		void close() const override;
		bool create() override;
		void set(HANDLE handle, int timeout = 0) const;
		void waitForCallbacks(bool fCancelPendingCallbacks = false) const override;
	private:
		PTP_WAIT tp_wait_ = nullptr;
		PTP_WAIT_CALLBACK timer_callback_ = wait_callback;
	};
}
