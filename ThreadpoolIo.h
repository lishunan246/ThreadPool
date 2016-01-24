#pragma once
#include "Threadpool.h"

void CALLBACK callback(PTP_CALLBACK_INSTANCE instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);

namespace TP
{
	class ThreadpoolIo :
		public Threadpool
	{
	public:
		ThreadpoolIo(HANDLE fl);
		~ThreadpoolIo();
		bool create() override;
		void close() const override;
		void waitForCallbacks(bool fCancelPendingCallbacks = false) const override;
		void start() const;
		void cancel() const;
	private:
		HANDLE handle_ = nullptr;
		PTP_WIN32_IO_CALLBACK callback_ = callback;
		PTP_IO io_ = nullptr;
	};
}


