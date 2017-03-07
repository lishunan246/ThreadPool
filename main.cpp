#include "ThreadpoolIo.h"
#include "ThreadpoolWait.h"
#include "ThreadpoolTimer.h"
#include "ThreadpoolWork.h"
#include <iostream>

using namespace TP;

void print(void* context)
{
	printf_s("Hello%s\n", static_cast<char*>(context));
}



int main()
{
	OVERLAPPED overlapped;
	HANDLE handle = CreateFile("COM1", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
	int a[100]={};
	//ReadFile(handle, a, 1, NULL, &overlapped);

	ThreadpoolIo threadpool(handle);
	auto i= threadpool.create();
	if (!i)
		return 1;
	threadpool.setCallback(print);
	threadpool.setContext(nullptr);
	threadpool.start();
	Sleep(1000);
	auto r= ReadFile(handle, a, 1, NULL, &overlapped);
	if (!r)
	{
		std::cout<< GetLastError()<<std::endl;
		return 2;
	}
	ReadFile(handle, a, 1, NULL, &overlapped);
	threadpool.close();
	system("pause");
	return 0;
}
