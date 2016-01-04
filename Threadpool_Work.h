#pragma once
#include <functional>

using WORK = std::function<void(void*)>;

class Threadpool_Work
{
	friend class Threadpool;

public:
	Threadpool_Work();
	explicit Threadpool_Work(WORK f);
	~Threadpool_Work();
	const WORK& getInstance() const;
private:
	WORK w;
	
};

