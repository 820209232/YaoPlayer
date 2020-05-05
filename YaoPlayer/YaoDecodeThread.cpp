#include "YaoPlayer.h"

YaoDecodeThread::YaoDecodeThread()
{
	decode = new Decoder();
}

YaoDecodeThread::~YaoDecodeThread()
{
	if (decode != nullptr) {
		decode->close();
		delete decode;
		decode = nullptr;
	}
}

void YaoDecodeThread::run()
{
	int frameCount = 0;
	while (!stopFlag) {
		YaoAVPacket* packet = nullptr;
		int ret = packetQueue.pop(&packet);
		if (ret) {
			continue;
		}
		//½âÂë
		decode->sendPacket(packet);
		while (1) {
			YaoAVFrame frame;
			ret = decode->receiveFrame(&frame);
			if (ret) {
				break;
			}
			printf("decode success\n");
			frameCount++;
			printf("frameCount:%d\n", frameCount);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	
	}
}

int YaoDecodeThread::init(YaoAVStream* stream)
{
	return decode->init(stream);
}

int YaoDecodeThread::pushPacket(YaoAVPacket* packet)
{
	return packetQueue.push(packet);
}

int YaoDecodeThread::packetQueueSize()
{
	return packetQueue.queueSize();
}