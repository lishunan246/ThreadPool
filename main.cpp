#include "Threadpool.h"
#include "ThreadpoolWait.h"

void print(void * context)
{
	printf_s("Hello%s\n",static_cast<char*>(context));
}

void TestThreadpool()
{
	Threadpool tp;
	Threadpool_Work tp_work(print);
	
	tp.submit(tp_work);

	char c[] = " world";
	tp.setContext(&c);
	tp.waitForCallbacks();
	tp.close();
}

void TestThreadpoolWait()
{
	HANDLE handle = NULL;
	handle = CreateEvent(NULL, false, false, NULL);
	
	ThreadpoolWait tp;
	Threadpool_Work tp_work(print);

	char c[] = " world2";
	tp.setContext(&c);
	tp.create();
	tp.set(tp_work,handle);
	SetEvent(handle);


	Sleep(100);
	ResetEvent(handle);

	tp.waitForCallbacks();
	tp.close();
}

int main()
{
	TestThreadpool();
	TestThreadpoolWait();

	return 0;
}
