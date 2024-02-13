#define EXILE_PRIVATE
#include <exile/core/thread/thread.hpp>


exile::Thread::Thread()
{

}

inline u64 exile::Thread::GetThreadId()
{
	return rawThread.threadId;
}

void exile::Thread::Destroy()
{
	exThreadDestroy(&rawThread);
}

u64 exile::Thread::GetCurrentThreadId()
{
	return exThreadGetCurrentId();
}

u8 exile::Thread::IsActive()
{
	return exThreadActive(&rawThread);
}

u8 exile::Thread::Join()
{
	return exThreadJoin(&rawThread);
}

void exile::Thread::Cancel()
{
	exThreadCancel(&rawThread);
}