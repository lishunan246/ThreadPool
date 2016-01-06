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
	tp.setThreadMaximum(2);
	tp.create();
	tp.setCallback(print);
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
	tp.setCallback(print);

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
	timer.setCallback(print);
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
