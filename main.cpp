#include "Threadpool.h"

void print(void * context)
{
	printf_s("Hello%s\n",static_cast<char*>(context));
}

int main()
{
	Threadpool tp;
	ThreadPool_Work tp_work(print);
	
	tp.submit(tp_work);

	char c[] = " world";
	tp.setContext(&c);
	tp.waitForCallback();
	tp.close();
	return 0;
}