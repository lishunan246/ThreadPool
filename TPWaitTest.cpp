#include <iostream>
#include "ThreadpoolWait.h"

using namespace TP;

void print(void* context)
{
	printf_s("Hello%s\n", static_cast<char*>(context));
}

int main()
{
	ThreadpoolWaitObject wo;
	ThreadpoolWait tp;
	tp.setCallbackPriority(Threadpool::Priority::High);
	tp.setCallback(print);

	char c[] = " world2";
	tp.setContext(&c);
	tp.create();
	tp.set(wo);
	wo.set();
	
	Sleep(100);
	
	wo.reset();
	tp.waitForCallbacks();
	tp.close();
}
