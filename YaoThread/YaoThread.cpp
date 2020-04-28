#include "YaoThread.h"

int YaoThread::start()
{
	std::thread t(&YaoThread::run, this);
	t.detach();
	return 0;
}
