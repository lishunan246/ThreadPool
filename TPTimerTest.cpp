#include "ThreadpoolTimer.h"

using namespace TP;

void print(void* context)
{
	printf_s("Hello%s\n", static_cast<char*>(context));
}

int main()
{
	ThreadpoolTimer timer;
	timer.setCallback(print);
	timer.create();
	char c[] = " Timer";
	timer.setContext(&c);


	//wait for 2s, then repeat every 1s
	timer.set(20000000,1000, 0);

	Sleep(10000);
	timer.close();
}
