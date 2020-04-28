#include <stdio.h>
#include <thread>

class YaoThread {
public:
	virtual void run() = 0;
	int start();
};