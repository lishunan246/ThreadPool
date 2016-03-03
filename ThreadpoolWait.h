#pragma once
#include "Threadpool.h"
#include "ThreadpoolWaitObject.h"

#ifdef WIN32
void CALLBACK wait_callback(PTP_CALLBACK_INSTANCE instance, void* parameter, PTP_WAIT wait, TP_WAIT_RESULT result);

#else
#endif
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
		void set(const ThreadpoolWaitObject& WaitObject, int timeout = 0) const;
		void waitForCallbacks(bool fCancelPendingCallbacks = false) const override;
	private:
#ifdef WIN32
		PTP_WAIT tp_wait_ = nullptr;
		PTP_WAIT_CALLBACK timer_callback_ = wait_callback;
#endif
	};
}
