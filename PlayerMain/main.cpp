#include <stdio.h>

#include "YaoPlayer/YaoDecode.h"
#include "YaoThread/YaoThread.h"
#include "YaoAV/YaoAV.h"

class MyThread : public YaoThread
{
private:
	int a;
public:
	MyThread(int _a)
	{
		a = _a;
	}
	virtual void run() 
	{
		printf("in yaoThread %d \n", a);
	}
};

int main_thread()
{
	int a = 10;
	MyThread * t = new MyThread(a);
	t->start();
	std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}

int main()
{
	YaoAVReader reader;
	int ret = reader.Open("C://video/the5MP4.mp4");
	if (ret) {
		printf("open file fail \n");
		return -1;
	}
	while (1)
	{
		YaoAVPacket packet;
		ret = reader.Read(&packet);
		

		if (ret) {
			break;
		}
		printf("read packet success\n");
	}
	reader.Close();
}