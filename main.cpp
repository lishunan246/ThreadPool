#include "Threadpool.h"
#include "ThreadpoolWait.h"
#include "ThreadpoolTimer.h"
#include "ThreadpoolWork.h"
void print(void * context)
{
	printf_s("Hello%s\n",static_cast<char*>(context));
}

void TestThreadpool()
{
	ThreadpoolWork tp;
	Threadpool_Work tp_work(print);
	tp.setThreadMaximum(2);
	tp.create();
	tp.setWork(tp_work);
	tp.submit();

	char c[] = " world";
	tp.setContext(&c);
	tp.waitForCallbacks();
	tp.close();
}

void TestThreadpoolWait()
{
	HANDLE handle;
	handle = CreateEvent(nullptr, false, false, nullptr);
	
	ThreadpoolWait tp;
	tp.setCallbackPriority(Threadpool::High);
	Threadpool_Work tp_work(print);
	tp.setWork(tp_work);

	char c[] = " world2";
	tp.setContext(&c);
	tp.create();
	tp.set(handle);
	SetEvent(handle);


	Sleep(100);
	ResetEvent(handle);

	tp.waitForCallbacks();
	tp.close();
}

void TestThreadpoolTimer()
{
	ThreadpoolTimer timer;
	Threadpool_Work tp_work(print);
	timer.setWork(tp_work);
	timer.create();
	char c[] = " Timer";
	timer.setContext(&c);


	FILETIME FileTime;
	ULARGE_INTEGER integer;
	integer.QuadPart = (unsigned)-50000000;
	FileTime.dwHighDateTime = integer.HighPart;
	FileTime.dwLowDateTime = integer.LowPart;
	timer.set(&FileTime, 100, 0);
	Sleep(10000);
	timer.close();
}

int main()
{
	TestThreadpool();
	TestThreadpoolWait();

	TestThreadpoolTimer();

	return 0;
}
