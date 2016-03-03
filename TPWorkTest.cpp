#include "ThreadpoolWork.h"

using namespace TP;

CALLER w;
void print(void* context)
{
	printf_s("Hello%s\n", static_cast<char*>(context));
}

int main()
{
	ThreadpoolWork tp;
	tp.setThreadMaximum(1);
	tp.create();
	tp.setCallback(print);
	tp.submit();
	tp.submit();

	char c[] = " world";
	tp.setContext(&c);
	tp.waitForCallbacks();

	
	w.w = print;
	w.context = c;
	TP::ThreadpoolWork::trySubmit(&w,"12");

	tp.close();



	return 0;
}
