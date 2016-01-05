#include "ThreadpoolIo.h"


void __stdcall callback(PTP_CALLBACK_INSTANCE instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
{
	//todo
}

ThreadpoolIo::ThreadpoolIo(HANDLE fl)
{
	handle_ = fl;
}


ThreadpoolIo::~ThreadpoolIo()
{
}

bool ThreadpoolIo::create()
{
	io_ = CreateThreadpoolIo(handle_, callback_, &caller, environ_);
	return io_ != nullptr;
}

void ThreadpoolIo::close() const
{
	CloseThreadpoolIo(io_);
}

void ThreadpoolIo::start() const
{
	StartThreadpoolIo(io_);
}

void ThreadpoolIo::waitForCallbacks(bool fCancelPendingCallbacks) const
{
	WaitForThreadpoolIoCallbacks(io_, fCancelPendingCallbacks);
}

void ThreadpoolIo::cancel() const
{
	CancelThreadpoolIo(io_);
}
