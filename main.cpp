#include "Threadpool.h"
#include "ThreadpoolWait.h"
#include "ThreadpoolTimer.h"
#include "ThreadpoolWork.h"

using namespace TP;

void print(void* context)
{
	printf_s("Hello%s\n", static_cast<char*>(context));
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
	TestThreadpoolTimer();

	return 0;
}
