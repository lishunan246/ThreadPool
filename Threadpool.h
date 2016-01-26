#pragma once


#include <Windows.h>
#include <functional>

using CleanupCallback = std::function<void(void*, void*)>;
using WORK = std::function<void(void*)>;

struct CALLER
{
	WORK w = nullptr;
	void* context = nullptr;
};

struct CLEANUP
{
	CleanupCallback c = [](void*, void*)
	{
		return;
	};
	void* context = nullptr;
};

void CALLBACK CleanupGroupCancelCallback(void* ObjectContext, void* CleanupContext);

namespace TP
{
	class Threadpool
	{
	public:
		enum Priority
		{
			High,
			Low,
			Normal
		};

		Threadpool();
		virtual ~Threadpool();
		virtual bool create() = 0;
		virtual void waitForCallbacks(bool fCancelPendingCallbacks = false) const = 0;
		virtual void close() const = 0;
		void setContext(void* context);
		static void call(void* pcaller);
		void setCallback(const WORK& w);
		void setCallbackLibrary(void* mod);
		void setCallbackRunsLong();
		void setCallbackPriority(Priority priority);
		void setThreadMaximum(unsigned long cthrdMost) const;
		bool setThreadMinimun(unsigned long cthrdMic) const;
		void setCleanupContext(void* CleanupContext);
		void setCleanupCallback(CleanupCallback cleanup_callback);
		void cleanup(bool fCancelPendingCallbacks = false);
	protected:
		CALLER caller;
		TP_CALLBACK_ENVIRON CallBackEnviron;
		PTP_CALLBACK_ENVIRON environ_ = &CallBackEnviron;
		PTP_POOL pool;
		PTP_CLEANUP_GROUP cleanup_group_;
		PTP_CLEANUP_GROUP_CANCEL_CALLBACK cleanup_group_cancel_callback_ = CleanupGroupCancelCallback;
		CLEANUP cleanup_;
	};
}


