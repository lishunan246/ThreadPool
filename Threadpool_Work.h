#pragma once
#include <functional>

using WORK = std::function<void(void*)>;

class ThreadPool_Work
{
	friend class Threadpool;

public:
	ThreadPool_Work();
	ThreadPool_Work(WORK f);
	~ThreadPool_Work();
private:
	WORK w;
	
};

